package com.hisilicon.android.music;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Collections;
import java.util.Comparator;

import com.hisilicon.android.music.Common;
import com.hisilicon.android.music.FMMediaFileList;
import com.hisilicon.android.music.FilterType;

import android.app.Service;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.net.Uri;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

/**
 * media file manager
 * @author
 */
public class MediaFileListService extends Service {
    private String TAG = "MediaFileListService";
    private IBinder binder = new MyBinder();

    private MusicModel _currMusicModel = null;
    private int _currPosition = 0; // current Music file's position
    private boolean _haveGetPosition = false; // whether have get the position
                                              // that current Music
    private String _currPath = null;
    private ArrayList<MusicModel> _list = null;
    private GetMusicListThread _getMusicListThread = null;
    private boolean _runFlag = false;

    private Object lock = new Object();

    public int getCurrPosition() {
        synchronized (lock) {
            return this._currPosition;
        }
    }

    public void setCurrPosition(int vpos) {
        synchronized (lock) {
            this._currPosition = vpos;
        }
    }

    public boolean isHaveGetPosition() {
        synchronized (lock) {
            return this._haveGetPosition;
        }
    }

    public void setHaveGetPosition(boolean haveGetPosition) {
        synchronized (lock) {
            this._haveGetPosition = haveGetPosition;
        }
    }

    public String getCurrPath() {
        synchronized (lock) {
            return this._currPath;
        }
    }

    public void setCurrPath(String currPath) {
        synchronized (lock) {
            this._currPath = currPath;
        }
    }

    public ArrayList<MusicModel> getList() {
        synchronized (lock) {
            return this._list;
        }
    }

    public void setList(ArrayList<MusicModel> list) {
        synchronized (lock) {
            this._list = list;
        }
    }

    public GetMusicListThread getThread() {
        synchronized (lock) {
            return this._getMusicListThread;
        }
    }

    public void setThread(GetMusicListThread t) {
        synchronized (lock) {
            this._getMusicListThread = t;
        }
    }

    public boolean isRunFlag() {
        synchronized (lock) {
            return this._runFlag;
        }
    }

    public void setStopFlag(boolean runFlag) {
        synchronized (lock) {
            this._runFlag = runFlag;
        }
    }

    public MusicModel getCurrMusicModel() {
        synchronized (lock) {
            return this._currMusicModel;
        }
    }

    public void setCurrMusicModel(MusicModel model) {
        synchronized (lock) {
            this._currMusicModel = model;
        }
    }

    /**
     * @author
     */
    public class MyBinder extends Binder {
        public MediaFileListService getService() {
            return MediaFileListService.this;
        }
    }

    @Override
    public void onCreate() {
        FilterType.filterType(getApplicationContext());
        super.onCreate();
    }

    @Override
    public IBinder onBind(Intent arg0) {
        return binder;
    }

    @Override
    public void onStart(Intent intent, int startId) {
        super.onStart(intent, startId);
        if (getList() != null) {
            getList().clear();
        } else {
            setList(new ArrayList<MusicModel>());
        }
        setCurrPosition(0);
        setHaveGetPosition(false);

        try {

            String curPath = intent.getData().getPath();

            if (curPath.startsWith("/external/")) {
                Log.d("starts with external", "");
                ContentResolver resolver = getContentResolver();
                Cursor cursor = null;
                try {
                    cursor = resolver.query(
                            Uri.parse("content://media" + curPath),
                            new String[] { "_id", "_data", "_display_name",
                                    "_size", "duration", "date_added" }, null,
                            null, null);
                    while (cursor.moveToNext()) {
                        String getCurrPath = cursor.getString(1);
                        Log.d("getCurrPath", "getCurrPath==" + getCurrPath);
                        curPath = getCurrPath;
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                } finally {
                    if (cursor != null) {
                        cursor.close();
                        cursor = null;
                    }
                }
            }

            setCurrPath(curPath);

            File f = new File(curPath);
            MusicModel currMusic = new MusicModel();
            currMusic.setTitle(f.getName());
            currMusic.setAddedTime(f.lastModified());
            currMusic.setPath(f.getPath());
            currMusic.setSize(f.length());
            setCurrMusicModel(currMusic);

            Common.sortCount = intent.getIntExtra("sortCount", -1);
            String currPathParent = getCurrPath().substring(0,
                    getCurrPath().lastIndexOf("/"));

            File file = new File(currPathParent);
            if (file.exists() && file.isDirectory()) {
                setStopFlag(true);
                waitThreadToIdle(getThread());
                setThread(new GetMusicListThread(file));
                setStopFlag(false);
                getThread().start();

                Intent i = new Intent();
                i.setClassName("com.hisilicon.android.music",
                        "com.hisilicon.android.music.MediaPlaybackActivity");
                i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                i.setDataAndType(intent.getData(), "audio/*");
                i.putExtra("MediaFileList", new FMMediaFileList(getCurrPath()));
                MediaFileListService.this.startActivity(i);
            }
        } catch (Exception e) {
            this.stopSelf(startId);
        }
    }

    /**
     * get all Music file from current folder
     * @author
     */
    private class GetMusicListThread extends Thread {
        private File file = null;

        public GetMusicListThread(File file) {
            this.file = file;
        }

        public void run() {
            Common.setLoadSuccess(false);
            MusicModel model = null;
            long time = System.currentTimeMillis();
            File[] files = file.listFiles();
            time = System.currentTimeMillis();
            for (int i = 0; i < files.length; i++) {
                if (!isRunFlag()) {
                    if (files[i].isFile()) {
                        String filename = files[i].getName();
                        String dex = filename.substring(
                                filename.lastIndexOf(".") + 1,
                                filename.length());
                        SharedPreferences share = getSharedPreferences("AUDIO",
                                Context.MODE_WORLD_READABLE);
                        dex = dex.toUpperCase();
                        String musicSuffix = share.getString(dex, "");
                        if (!musicSuffix.equals("")) {
                            model = new MusicModel();
                            model.setPath(files[i].getPath());
                            model.setTitle(filename);
                            model.setSize(files[i].length());
                            model.setAddedTime(files[i].lastModified());
                            getList().add(model);
                        }
                    }
                } else {
                    break;
                }
            }

            ArrayList <MusicModel> _tmplist = sortFile(getList());
            _list = _tmplist;

            time = System.currentTimeMillis();
            if (!isRunFlag()) {
                // setList(Common.sortFile(getList(),Common.sortCount));
                // getList().indexOf();
                for (int i = 0; i < getList().size(); i++) {
                    if (getCurrPath().equals(getList().get(i).getPath())) {
                        setCurrPosition(i);
                        break;
                    } else {
                        setCurrPosition(0);
                    }
                }
            }

            Common.setLoadSuccess(true);
        }
    }

    @Override
    public boolean onUnbind(Intent intent) {
        setStopFlag(true);
        return super.onUnbind(intent);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    public MusicModel getMusicInfo(int flag) {
        MusicModel model = getCurrMusicModel();

        if (!((getList() == null) || (getList().size() == 0))) {
            if (flag == 1) {
                // next Music
                if (Common.isLoadSuccess()) {
                    if (getCurrPosition() >= getList().size() - 1) {
                        setCurrPosition(0);
                    } else {
                        setCurrPosition(getCurrPosition() + 1);
                    }
                }
            } else if (flag == 2) {
                // previous Music
                if (Common.isLoadSuccess()) {
                    if (getCurrPosition() <= 0) {
                        setCurrPosition(getList().size() - 1);
                    } else {
                        setCurrPosition(getCurrPosition() - 1);
                    }
                }
            } else if (flag == 3) {
                // random Music
                Random random = new Random();
                setCurrPosition(random.nextInt(getList().size()));
            } else if (flag == 4) {
                // next Music with no cycle mode
                if (Common.isLoadSuccess()) {
                    if (getCurrPosition() >= getList().size() - 1) {
                        setCurrPosition(getCurrPosition());
                        Common.isLastMediaFile = true;
                    } else {
                        setCurrPosition(getCurrPosition() + 1);
                    }
                }
            }

            if (Common.isLoadSuccess()) {
                model = getList().get(getCurrPosition());
                setCurrPath(model.getPath());
            }

            return model;
        } else {
            return null;
        }
    }

    public static ArrayList <MusicModel> sortFile(ArrayList <MusicModel> musicList) {

		Collections.sort(musicList, new Comparator<MusicModel>()
        {
		    public int compare(MusicModel object1, MusicModel object2)
            {
                return compareByName(object1, object2);
            }
        });

		return musicList;
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

	private static int compareByName(MusicModel object1, MusicModel object2) {
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

    /**
     * check if the thread thrd is busy
     * @param thrd
     * @return
     */
    private static boolean threadBusy(Thread thrd) {
        if (thrd == null) {
            return false;
        }

        if ((thrd.getState() != Thread.State.TERMINATED)
                && (thrd.getState() != Thread.State.NEW)) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * before recreate a new thread, be sure the old thread is idle
     * @param thrd
     */
    private static void waitThreadToIdle(Thread thrd) {
        while (threadBusy(thrd)) {
            try {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
