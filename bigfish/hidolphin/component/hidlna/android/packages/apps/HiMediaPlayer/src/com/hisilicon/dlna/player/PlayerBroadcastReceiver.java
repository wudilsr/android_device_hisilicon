package com.hisilicon.dlna.player;

import java.util.List;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningTaskInfo;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.os.SystemClock;
import android.util.Log;
import android.widget.Toast;

import com.hisilicon.dlna.dmr.*;
import com.hisilicon.dlna.dmr.action.SetURLAction;
import com.hisilicon.dlna.dmr.action.PlayAction;
import com.hisilicon.dlna.dmr.action.SeekAction;
import com.hisilicon.dlna.dmr.action.BaseAction;
import com.hisilicon.dlna.dmr.util.DMRFileInfo;
import com.hisilicon.dlna.file.DMSFile;
import com.hisilicon.dlna.file.FileType;
import com.hisilicon.dlna.file.LocalFile;
import com.hisilicon.dlna.util.CommonDef;

public class PlayerBroadcastReceiver extends BroadcastReceiver
{
    private static final String TAG = "PlayerBroadcastReceiver";
    public static final String START_AGAIN_BROADCAST_VIDEO = "com.hisilicon.dlna.player.startagain.video";
    public static final String START_AGAIN_BROADCAST_IMAGE = "com.hisilicon.dlna.player.startagain.image";
    public static final String START_AGAIN_BROADCAST_AUDIO = "com.hisilicon.dlna.player.startagain.audio";

    public static final String START_AGAIN_BROADCAST_MAIN = "com.hisilicon.dlna.player.startagain.main";
    public static final String DLNA_MAIN_ACTIVITY_NAME = "com.hisilicon.dlna.player/com.hisilicon.dlna.player.MainPlayerActivity";

    private int FLAG_START_ACTIVITY = Intent.FLAG_ACTIVITY_NEW_TASK;
    private static final int MAX_CHECK_TOPACTIVITY_COUNT = 4;
    //private static final int MAX_CHECK_TOPACTIVITY_COUNT = 10;

    private String playUrl = null;
    private FileType fileType = null;
    private Context mContext = null;
    private DMRFileInfo dmrFileInfo = null;
    private BaseAction action;
    private static int mWaiteCount = 0;
    private String ContentType;
    private String ContentLength;
    @Override
    public void onReceive(Context context, Intent intent)
    {
        Log.d(TAG, "receive player broadcast");

        mContext = context;
        action = (BaseAction) intent.getSerializableExtra("action");
        ContentType = (String)intent.getSerializableExtra("ContentType");
        ContentLength = (String)intent.getSerializableExtra("ContentLength");
        if (action instanceof SetURLAction)
        {
            Log.d(TAG, "SetURLAction");
            playUrl = ((SetURLAction) action).getUrlwithOutlpcmhead();
            if (playUrl == null)
            {
                if (((SetURLAction) action).getFile() instanceof DMSFile)
                {
                    playUrl = ((DMSFile) ((SetURLAction) action).getFile()).getUrl();
                }
                else if (((SetURLAction) action).getFile() instanceof LocalFile)
                {
                    playUrl = ((LocalFile) ((SetURLAction) action).getFile()).getFile()
                            .getAbsolutePath();
                }
            }
            if (((SetURLAction) action).getFile() == null)
            {
                // 如果SetURLAction.getFile()为null,则说明为传的为URL
                dmrFileInfo = ((SetURLAction) action).getFileInfo();
                if (dmrFileInfo != null)
                {
                    String upnpClass = dmrFileInfo.getUpnpClass();
                    if (upnpClass != null)
                    {
                        if (upnpClass.contains("audio"))
                        {
                            fileType = FileType.AUDIO;
                        }
                        else if (upnpClass.contains("image"))
                        {
                            fileType = FileType.IMAGE;
                        }
                        else if (upnpClass.contains("video"))
                        {
                            fileType = FileType.VIDEO;
                        }
                    }
                }
            }
            else
            {
                // 传过来的为AbstractFile
                fileType = ((SetURLAction) action).getFile().getFileType();
                dmrFileInfo = ((SetURLAction) action).getFileInfo();
            }
        }
        else if (action instanceof PlayAction)
        {
            Log.d(TAG, "PlayAction");
            playUrl = ((PlayAction) action).getUrlwithOutlpcmhead();
            if (playUrl == null)
            {
                if (((PlayAction) action).getFile() instanceof DMSFile)
                {
                    playUrl = ((DMSFile) ((PlayAction) action).getFile()).getUrl();
                }
                else if (((PlayAction) action).getFile() instanceof LocalFile)
                {
                    playUrl = ((LocalFile) ((PlayAction) action).getFile()).getFile()
                            .getAbsolutePath();
                }
            }

            if (((PlayAction) action).getFile() == null)
            {
                // 如果SetURLAction.getFile()为null,则说明为传的为URL
                dmrFileInfo = ((PlayAction) action).getFileInfo();
                if (dmrFileInfo != null)
                {
                    String upnpClass = dmrFileInfo.getUpnpClass();
                    if (upnpClass != null)
                    {
                        if (upnpClass.contains("audio"))
                        {
                            fileType = FileType.AUDIO;
                        }
                        else if (upnpClass.contains("image"))
                        {
                            fileType = FileType.IMAGE;
                        }
                        else if (upnpClass.contains("video"))
                        {
                            fileType = FileType.VIDEO;
                        }
                    }
                }
            }
            else
            {
                // 传过来的为AbstractFile
                fileType = ((PlayAction) action).getFile().getFileType();
                dmrFileInfo = ((PlayAction) action).getFileInfo();
            }
        }
        else if (action instanceof SeekAction)
        {
            Log.d(TAG, "SeekAction");
            playUrl = ((SeekAction) action).getUrlwithOutlpcmhead();
            if (playUrl == null)
            {
                if (((SeekAction) action).getFile() instanceof DMSFile)
                {
                    playUrl = ((DMSFile) ((SeekAction) action).getFile()).getUrl();
                }
                else if (((SeekAction) action).getFile() instanceof LocalFile)
                {
                    playUrl = ((LocalFile) ((SeekAction) action).getFile()).getFile()
                            .getAbsolutePath();
                }
            }

            if (((SeekAction) action).getFile() == null)
            {
                // 如果SetURLAction.getFile()为null,则说明为传的为URL
                dmrFileInfo = ((SeekAction) action).getFileInfo();
                if (dmrFileInfo != null)
                {
                    String upnpClass = dmrFileInfo.getUpnpClass();
                    if (upnpClass != null)
                    {
                        if (upnpClass.contains("audio"))
                        {
                            fileType = FileType.AUDIO;
                        }
                        else if (upnpClass.contains("image"))
                        {
                            fileType = FileType.IMAGE;
                        }
                        else if (upnpClass.contains("video"))
                        {
                            fileType = FileType.VIDEO;
                        }
                    }
                }
            }
            else
            {
                // 传过来的为AbstractFile
                fileType = ((SeekAction) action).getFile().getFileType();
                dmrFileInfo = ((SeekAction) action).getFileInfo();
            }
        }

        if (fileType == null)
        {
            if(playUrl != null)
            {
                if(playUrl.contains("mp3"))
                {
                    Log.v(TAG,"DmrfileType = FileType.AUDIO");
                    fileType = FileType.AUDIO;
                }
                else if(playUrl.contains("mp4"))
                {
                   Log.v(TAG,"DmrfileType = FileType.VIDEO");
                   fileType = FileType.VIDEO;
                }
                else if(playUrl.contains("jpg"))
                {
                   Log.v(TAG,"DmrfileType = FileType.IMAGE");
                   fileType = FileType.IMAGE;
                }
                else
                {
                    Toast.makeText(mContext, R.string.file_type_unsupport, Toast.LENGTH_LONG).show();
                    return;
                }
            }
            else
            {
                Toast.makeText(mContext, R.string.file_type_unsupport, Toast.LENGTH_LONG).show();
                return;
            }
        }
        sendScreenOnBC(); // SMART_SUSPEND_QUIT,for screen on
        String content_length = null;
        if(ContentLength != null)
            content_length = ContentLength.replaceAll(" ","");
        startPlayerActivity(fileType,ContentType,content_length);
        CommonDef.removeStickyBroadcastEx(mContext,intent);
    }

    private void startPlayerActivity(FileType ft,String contentType,String contentLength)
    {

        if (FileType.IMAGE != ft)
        {
            stopHisiMusicPlayer();
        }

        stopBackgroundMusic(mContext);
        Intent intent = new Intent();
        intent.putExtra(Constant.FILE_PLAY_PATH, action);
        intent.putExtra(Constant.FILE_PLAY_TYPE, ft);
        intent.putExtra(Constant.FILE_CONTENT_TYPE, contentType);
        intent.putExtra(Constant.FILE_CONTENT_LENGTH, contentLength);
        Log.d(TAG,
                "ft = " + ft + ",action=" + action.getActionCode() + ",c=" + action.getController());
        mWaiteCount = 0;
        if (isMainActivateOnTop())
        {
            intent.setAction(START_AGAIN_BROADCAST_MAIN);
            Log.d(TAG, " the activity is runing,then send broadcast");
            CommonDef.sendBroadcastEx(mContext,intent);
        }
        else
        {
            intent.setFlags(FLAG_START_ACTIVITY);
            intent.setClass(mContext, MainPlayerActivity.class);
            long curtime = System.currentTimeMillis();
            long waitetime = 1000 -(curtime - MainPlayerActivity.mLastStopTime);
            Log.d(TAG, " MainPlayerActivity.mLastStopTime " + MainPlayerActivity.mLastStopTime+" ms");
            Log.d(TAG, " CurrentTime " + curtime+" ms");

            if((waitetime > 0) && (waitetime < 1000))
            {
                Log.d(TAG, " the activity may in destroy process, waite " + waitetime+" ms");
                SystemClock.sleep( waitetime );
            }
            else
                Log.d(TAG, " do not need to waite activity finish destroy process");
            CommonDef.startActivityEx(mContext,intent);
        }
    }

    private void stopBackgroundMusic(Context context)
    {
        Intent intent = new Intent();
        intent.setAction("com.android.music.musicservicecommand.pause");
        intent.putExtra("command", "pause");
        CommonDef.sendBroadcastEx(mContext,intent);
    }

    private Boolean isMainActivateOnTop()
    {
        ActivityManager am = (ActivityManager) mContext.getSystemService(Context.ACTIVITY_SERVICE);
        List<RunningTaskInfo> lstTaskInfo = am.getRunningTasks(1);
        if ((null == lstTaskInfo) || (lstTaskInfo.size() == 0))
        {
            return false;
        }
        ComponentName cn = lstTaskInfo.get(0).topActivity;
        Log.d(TAG, "mWaiteCount=" + mWaiteCount + ",f=" + MainPlayerActivity.mIsActivityIsRuning );

        String curActivityName = cn.toString();
        Log.d(TAG, "Top Activity name =" + curActivityName  );
        if (curActivityName.contains(DLNA_MAIN_ACTIVITY_NAME))
        {
            // if the activity is finishing
            if (false == MainPlayerActivity.mIsActivityIsRuning)
            {
                if (mWaiteCount > MAX_CHECK_TOPACTIVITY_COUNT)
                {
                    return false;
                }
                //If you wait for the 5 time isn't closed, is forced to kill process
                else if (mWaiteCount > (MAX_CHECK_TOPACTIVITY_COUNT / 2))
                {
                    ActivityManager activityManager = (ActivityManager) mContext
                            .getSystemService(Context.ACTIVITY_SERVICE);
                    Log.d(TAG, "DLNA kill playerself use ActivityManager");
                    activityManager.killBackgroundProcesses("com.hisilicon.dlna.player");
                }
                long curtime = System.currentTimeMillis();
                long waitetime = 1000 -(curtime - MainPlayerActivity.mLastStopTime);
                Log.d(TAG, " MainPlayerActivity.mLastStopTime " + MainPlayerActivity.mLastStopTime+" ms");
                Log.d(TAG, " CurrentTime " + curtime+" ms");
                Log.d(TAG, " waitetime " + waitetime+" ms");

                if((waitetime > 0) && (waitetime < 1000))
                {
                    Log.d(TAG, " the activity may in destroy process, waite " + waitetime +" ms");
                    SystemClock.sleep( waitetime );
                }
                else
                    SystemClock.sleep(20);
                mWaiteCount++;
                return isMainActivateOnTop();
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    private void stopHisiMusicPlayer()
    {
        Intent i = new Intent("com.android.music.musicservicecommand");
        i.putExtra("command", "stop");
        CommonDef.sendBroadcastEx(mContext,i);

        i = new Intent("com.hisilicon.android.music.musicservicecommand");
        i.putExtra("command", "stop");
        CommonDef.sendBroadcastEx(mContext,i);
    }

    private void sendScreenOnBC()
    {
        Intent intent = new Intent();
        intent.setAction("smart_suspend_broadcast_quit");
        try
        {
            Log.d(TAG, "before sendScreenOnBC()");
            CommonDef.sendBroadcastEx(mContext,intent);
        }
        catch (Exception e)
        {
            Log.e(TAG, "callback.sendScreenOnBC()", e);
        }
    }
}
