package com.hisilicon.android.videoplayer.activity;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Collections;
import java.util.Comparator;

import com.hisilicon.android.videoplayer.R;
import com.hisilicon.android.videoplayer.bd.BDInfo;
import com.hisilicon.android.videoplayer.bd.DVDInfo;
import com.hisilicon.android.videoplayer.listmanager.FMMediaFileList;
import com.hisilicon.android.videoplayer.util.Common;
import com.hisilicon.android.videoplayer.util.FilterType;
import com.hisilicon.android.sdkinvoke.HiSdkinvoke;

import android.app.Service;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.ComponentName;
import android.database.Cursor;
import android.net.Uri;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;
import android.os.storage.IMountService;
import android.os.ServiceManager;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningTaskInfo;

public class MediaFileListService extends Service
{
    private String TAG = "MediaFileListService";
    private IBinder binder = new MyBinder();

    private VideoModel _currVideoModel = null;
    private static int _currPosition = 0;
    private boolean _haveGetPosition = false;
    private String _currPath = null;
    private static ArrayList <VideoModel> _list = null;
    private GetVideoListThread _getVideoListThread = null;
    private boolean _runFlag = false;

    private Object lock = new Object();
    private BDInfo mBDInfo;
    private DVDInfo mDVDInfo;

    public int getCurrPosition()
    {
        synchronized (lock){
            return this._currPosition;
        }
    }

    public void setCurrPosition(int vpos)
    {
        synchronized (lock){
            this._currPosition = vpos;
        }
    }

    public boolean isHaveGetPosition()
    {
        synchronized (lock){
            return this._haveGetPosition;
        }
    }

    public void setHaveGetPosition(boolean haveGetPosition)
    {
        synchronized (lock){
            this._haveGetPosition = haveGetPosition;
        }
    }

    public String getCurrPath()
    {
        synchronized (lock){
            return this._currPath;
        }
    }

    public void setCurrPath(String currPath)
    {
        synchronized (lock){
            this._currPath = currPath;
        }
    }

    public ArrayList <VideoModel> getList()
    {
        synchronized (lock){
            return this._list;
        }
    }

    public void setList(ArrayList < VideoModel > list)
    {
        synchronized (lock){
            this._list = list;
        }
    }

    public GetVideoListThread getThread()
    {
        synchronized (lock){
            return this._getVideoListThread;
        }
    }

    public void setThread(GetVideoListThread t)
    {
        synchronized (lock){
            this._getVideoListThread = t;
        }
    }

    public void setNewThread(File file)
    {
        synchronized (lock){
            setThread(new GetVideoListThread(file));
        }
    }

    public void setThreadStart()
    {
        synchronized (lock){
            try
            {
                if(this._getVideoListThread != null)
                {
                    this._getVideoListThread.start();
                }
            }
            catch(IllegalThreadStateException ex)
            {
                Log.e(TAG,"setThreadStart error!"+ex);
            }
        }
    }

    public boolean isRunFlag()
    {
        synchronized (lock){
            return this._runFlag;
        }
    }

    public void setStopFlag(boolean runFlag)
    {
        synchronized (lock){
            this._runFlag = runFlag;
        }
    }

    public VideoModel getCurrVideoModel()
    {
        synchronized (lock){
            return this._currVideoModel;
        }
    }

    public void setCurrVideoModel(VideoModel model)
    {
        synchronized (lock){
            this._currVideoModel = model;
        }
    }

    public class MyBinder extends Binder
    {
        public MediaFileListService getService()
        {
            return MediaFileListService.this;
        }
    }

    @Override
    public void onCreate()
    {
        FilterType.filterType(getApplicationContext());
        mBDInfo = new BDInfo();
        File file=new File("/system/lib/libdvdinfo_jni.so");
        if(file.exists())
            mDVDInfo = new DVDInfo();
        else
            mDVDInfo = null;
        super.onCreate();
        String chipVersion = HiSdkinvoke.getChipVersion();
        Log.i(TAG,"chipVersion:"+chipVersion);
        if(chipVersion.equals("Unknown chip ID"))
            stopSelf();
    }

    @Override
    public IBinder onBind(Intent arg0)
    {
        return binder;
    }

    @Override
    public void onStart(Intent intent, int startId)
    {
        super.onStart(intent, startId);

        if(isRunningForeground())
        {
            Log.i("TAG","stopSelf");
            return;
        }

        Intent cmd = new Intent("com.android.music.musicservicecommand");
        cmd.putExtra("command", "stop");
        MediaFileListService.this.sendBroadcast(cmd);

        cmd = new Intent("com.hisilicon.android.music.musicservicecommand");
        cmd.putExtra("command", "stop");
        MediaFileListService.this.sendBroadcast(cmd);

        if (getList() != null)
        {
            getList().clear();
        }
        else
        {
            setList(new ArrayList <VideoModel>());
        }

        setCurrPosition(0);
        setHaveGetPosition(false);

        try
        {

            String curPath = intent.getData().getPath();

            if (curPath.startsWith("/external/"))
            {
                Log.d("starts with external", "");
                ContentResolver resolver = getContentResolver();
                Cursor cursor = null;
                try
                {
                    cursor = resolver.query(Uri.parse("content://media" + curPath),
                                            new String[] {"_id", "_data", "_display_name", "_size", "duration",
                                                          "date_added"},
                                              null, null, null);
                    while (cursor.moveToNext())
                    {
                        String getCurrPath = cursor.getString(1);
                        Log.d("getCurrPath", "getCurrPath==" + getCurrPath);
                        curPath = getCurrPath;
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
                finally {
                    if (cursor != null)
                    {
                        cursor.close();
                        cursor = null;
                    }
                }
            }

            setCurrPath(curPath);

            File f = new File(curPath);
            VideoModel currvideo = new VideoModel();
            currvideo.setTitle(f.getName());
            currvideo.setAddedTime(f.lastModified());
            currvideo.setPath(f.getPath());
            currvideo.setSize(f.length());
            setCurrVideoModel(currvideo);
            Log.i(TAG,"curPath:"+curPath);
            Common.sortCount = intent.getIntExtra("sortCount", -1);
            String currPathParent = getCurrPath().substring(0, getCurrPath().lastIndexOf("/"));
            File file = new File(currPathParent);
            if (file.exists() && file.isDirectory())
            {
                setStopFlag(true);
                waitThreadToIdle(getThread());
                setThread(new GetVideoListThread(file));
                setStopFlag(false);
                //getThread().start();

                Intent i = new Intent();
                if(mBDInfo.isBDFile(intent.getData().toString()))
                {
                    i.setClassName("com.hisilicon.android.videoplayer", "com.hisilicon.android.videoplayer.activity.BDActivityNavigation");
                    i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    i.putExtra("path", intent.getData().toString());
                    i.putExtra("BDISOName", intent.getData().toString());
                    i.putExtra("BDISOPath", intent.getData().toString());
                    MediaFileListService.this.startActivity(i);
                }
                else if(mDVDInfo != null && mDVDInfo.isDVDFile(intent.getData().toString()))
                {
                    i.setClassName("com.hisilicon.android.videoplayer", "com.hisilicon.android.videoplayer.activity.DVDActivityNavigation");
                    i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    i.putExtra("path", intent.getData().toString());
                    i.putExtra("DVDISOName", intent.getData().toString());
                    i.putExtra("DVDISOPath", intent.getData().toString());
                    MediaFileListService.this.startActivity(i);
                }
                else if(intent.getType().equals("video/iso"))
                {
                    try
                    {
                        Log.i(TAG,"check ! udf://"+f.getPath()+"#");
                        if(mBDInfo.isBDFile("udf://"+f.getPath()+"#"))
                        {
                            String mISOPath = f.getAbsolutePath();
                            Log.i(TAG,"bd iso:"+mISOPath);
                            i.setClassName("com.hisilicon.android.videoplayer", "com.hisilicon.android.videoplayer.activity.BDActivityNavigation");
                            i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                            i.putExtra("path", mISOPath);
                            i.putExtra("BDISOName", f.getName());
                            i.putExtra("BDISOPath", mISOPath);
                            MediaFileListService.this.startActivity(i);
                        }
                        else
                        {
                            String mntPath = getMountService().mountISO(tranString(f.getPath()));
                            String mISOName = f.getName();
                            String mISOPath = f.getAbsolutePath();
                            String mISOLoopPath = mntPath;
                            if((mntPath != null || !mntPath.equals("")) && (mDVDInfo != null && mDVDInfo.isDVDFile(mISOLoopPath)))
                            {
                                Log.i(TAG,"mount dvd iso success:"+mISOLoopPath);
                                i.setClassName("com.hisilicon.android.videoplayer", "com.hisilicon.android.videoplayer.activity.DVDActivityNavigation");
                                i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                                i.putExtra("path", mISOLoopPath);
                                i.putExtra("DVDISOName", mISOName);
                                i.putExtra("DVDISOPath", mISOPath);
                                MediaFileListService.this.startActivity(i);
                            }
                        }
                        Log.i(TAG,"mount iso error:"+f.getPath());
                    }
                    catch(Exception e)
                    {
                        Log.e(TAG,"mount iso file error:"+e);
                    }
                }
                else
                {
                    i.setClassName("com.hisilicon.android.videoplayer", "com.hisilicon.android.videoplayer.activity.VideoActivity");
                    i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    i.setDataAndType(intent.getData(), "video/*");
                    i.putExtra("MediaFileList", new FMMediaFileList(getCurrPath(),f.getName()));
                    MediaFileListService.this.startActivity(i);
                }
            }
        } catch (Exception e) {
            Log.e(TAG, "== onstart error :" + e);
            this.stopSelf(startId);
        }
    }

    private class GetVideoListThread extends Thread
    {
        public File file = null;
        public GetVideoListThread(File file)
        {
            this.file = file;
        }
        public void run()
        {
            //because the '_list' and '_currPosition' is the static Variable
            //this must be clear before the Thread start everytime
            if (getList() != null)
            {
                getList().clear();
            }
            else
            {
                setList(new ArrayList <VideoModel>());
            }
            setCurrPosition(0);

            Common.setLoadSuccess(false);
            VideoModel model = null;
            long time = System.currentTimeMillis();
            File[] files = file.listFiles();
            if(files == null)
                return;
            time = System.currentTimeMillis();
            for (int i = 0; i < files.length; i++)
            {
                if (!isRunFlag())
                {
                    if (files[i].isFile())
                    {
                        String filename = files[i].getName();
                        String dex = filename.substring(filename.lastIndexOf(".") + 1, filename.length());
                        SharedPreferences share = getSharedPreferences("VIDEO", Context.MODE_WORLD_READABLE);
                        dex = dex.toUpperCase();
                        String videoSuffix = share.getString(dex, "");
                        if (!videoSuffix.equals(""))
                        {
                            model = new VideoModel();
                            model.setPath(files[i].getPath());
                            model.setTitle(filename);
                            model.setSize(files[i].length());
                            model.setAddedTime(files[i].lastModified());
                            if(dex.equals("ISO"))
                                model.setMimeType("video/iso");
                            else
                                model.setMimeType("video/*");
                            Log.i(TAG, "Find media:" + files[i].getPath());
                            getList().add(model);
                        }
                    }
                    else if (files[i].isDirectory() && mBDInfo.isBDFile(files[i].getPath()))
                    {
                        String filename = files[i].getName();
                        model = new VideoModel();
                        model.setPath(files[i].getPath());
                        model.setMimeType("video/bd");
                        model.setTitle(filename);
                        Log.i(TAG, "Find Bluray:" + files[i].getPath());
                        getList().add(model);
                    }
                }
                else
                {
                    break;
                }
            }
            ArrayList <VideoModel> _tmplist = sortFile(getList());
            _list = _tmplist;

            time = System.currentTimeMillis();
            if (!isRunFlag())
            {
                for (int i = 0; i < getList().size(); i++)
                {
                    if (getCurrPath().equals(getList().get(i).getPath()))
                    {
                        setCurrPosition(i);
                        break;
                    }
                    else
                    {
                        setCurrPosition(0);
                    }
                }
            }

            Common.setLoadSuccess(true);
        }
    }

    @Override
    public boolean onUnbind(Intent intent)
    {
        setStopFlag(true);
        return super.onUnbind(intent);
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
    }

    public VideoModel getVideoInfo(int flag)
    {
        VideoModel model = getCurrVideoModel();

        if (!((getList() == null) || (getList().size() == 0)))
        {
            if (flag == 1)
            {
                if (Common.isLoadSuccess())
                {
                    if (getCurrPosition() >= getList().size() - 1)
                    {
                        setCurrPosition(0);
                    }
                    else
                    {
                        setCurrPosition(getCurrPosition() + 1);
                    }
                }
            }
            else if (flag == 2)
            {
                if (Common.isLoadSuccess())
                {
                    if (getCurrPosition() <= 0)
                    {
                        setCurrPosition(getList().size() - 1);
                    }
                    else
                    {
                        setCurrPosition(getCurrPosition() - 1);
                    }
                }
            }
            else if (flag == 3)
            {
                Random random = new Random();
                setCurrPosition(random.nextInt(getList().size()));
            }
            else if (flag == 4)
            {
                if (Common.isLoadSuccess())
                {
                    if (getCurrPosition() >= getList().size() - 1)
                    {
                        setCurrPosition(0);
                        Common.isLastMediaFile = true;
                    }
                    else
                    {
                        setCurrPosition(getCurrPosition() + 1);
                    }
                }
            }

            if (Common.isLoadSuccess())
            {
                model = getList().get(getCurrPosition());
                setCurrPath(model.getPath());

                if ((model.getMimeType() != null) && model.getMimeType().equals("video/iso"))
                {
                    try
                    {
                        Log.i(TAG,"iso:"+model.getPath());
                        File f = new File(model.getPath());
                        if (mBDInfo.isBDFile("udf://"+model.getPath()+"#"))
                        {
                            Log.i(TAG,"bd iso:"+model.getPath());
                            model.setPath(model.getPath());
                            model.setISOPath(model.getPath());
                            model.setMimeType("video/bd");
                        }
                        else
                        {
                            String mntPath = getMountService().mountISO(tranString(f.getPath()));
                            String mBDISOName   = f.getName();
                            String mBDISOPath   = f.getAbsolutePath();
                            String mISOLoopPath = mntPath;
                            if (((mntPath != null) || !mntPath.equals("")) && (mDVDInfo != null && mDVDInfo.isDVDFile(mISOLoopPath)))
                            {
                                Log.i(TAG,"mount dvd iso success:"+mISOLoopPath);
                                model.setPath(mISOLoopPath);
                                model.setISOPath(mBDISOPath);
                                model.setMimeType("video/dvd");
                            }
                            else
                            {
                                return getVideoInfo(flag);
                            }
                        }
                    } catch (Exception e) {
                        Log.e(TAG, "mountiso file error:" + e);
                        return null;
                    }
                }
            }

            return model;
        }
        else
        {
            return null;
        }
    }

    public static ArrayList <VideoModel> sortFile(ArrayList <VideoModel> videoList) {

		Collections.sort(videoList, new Comparator<VideoModel>()
        {
		    public int compare(VideoModel object1, VideoModel object2)
            {
                return compareByName(object1, object2);
            }
        });

		return videoList;
	}

    private static int compareByName(String object1, String object2) {
		if (object1.startsWith("d") && object2.startsWith("d"))
			return object1.split("\\|")[1].toLowerCase().compareTo(
					object2.split("\\|")[1].toLowerCase());
		if (object1.startsWith("f") && object2.startsWith("f"))
			return object1.split("\\|")[1].toLowerCase().compareTo(
					object2.split("\\|")[1].toLowerCase());
		else
			return 0;
	}

	private static int compareByName(VideoModel object1, VideoModel object2) {
		String objectName1 = object1.getTitle().toLowerCase();
		String objectName2 = object2.getTitle().toLowerCase();
		int result = objectName1.compareTo(objectName2);
		if (result == 0) {
			return 0;
		} else if (result < 0) {
			return -1;
		} else {
			return 1;
		}
	}

    private static boolean threadBusy(Thread thrd)
    {
        if (thrd == null)
        {
            return false;
        }

        if ((thrd.getState() != Thread.State.TERMINATED)
            && (thrd.getState() != Thread.State.NEW))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    private static void waitThreadToIdle(Thread thrd)
    {
        while (threadBusy(thrd))
        {
            try
            {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    protected String tranString(String path)
    {
        String tranPath = "";
        for (int i = 0; i < path.length(); i++) {
            tranPath += "\\" + path.substring(i, i + 1);
        }

        return tranPath;
    }
    private static IMountService getMountService() {
		IBinder service = ServiceManager.getService("mount");
		if (service != null) {
			return IMountService.Stub.asInterface(service);
		} else {
			Log.e("MediaFileListService", "Can't get mount service");
		}
		return null;
    }
    public boolean isRunningForeground(){
        String topActivityClassName=getTopActivityName(this);
        Log.i(TAG,"topActivityClassName:"+topActivityClassName);
        if(topActivityClassName !=null && topActivityClassName.startsWith("com.hisilicon.android.videoplayer.activity"))
        {
            if(topActivityClassName.equals("com.hisilicon.android.videoplayer.activity.TransitActivity"))
                return false;
            else
            {
                Log.i(TAG,"topActivityClassName error!");
                return true;
            }
        }
        else
            return false;
    }
    public  String getTopActivityName(Context context){
        String topActivityClassName=null;
         ActivityManager activityManager =
        (ActivityManager)(context.getSystemService(android.content.Context.ACTIVITY_SERVICE )) ;
         List<RunningTaskInfo> runningTaskInfos = activityManager.getRunningTasks(1) ;
         if(runningTaskInfos != null){
             ComponentName f=runningTaskInfos.get(0).topActivity;
             topActivityClassName=f.getClassName();
         }
         return topActivityClassName;
    }
}
