package com.hisilicon.uvmos.monitor;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Locale;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;

import android.media.MediaPlayer.VideoFrameInfos;

public class MonitorService extends Service {

    private MediaReceiver mReceiver;

    private MediaInfo info;

    private Date startDate;

    private boolean isPrepare;
    private boolean isStart;

    private String StartPlayTime = "";
    private String DisplayFirstFrameTime = "";
    private String StallingHappenTime = "";
    private String StallingRestoreTime = "";
    private String SeekStartTime = "";
    private String SeekEndTime = "";
    private String PlayQuitTime = "";

    private String curInputFile = "";

    private int frameNo;

    private ArrayList<VideoFrameInfos> mVidFrmList;

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        Util.initFile();
        mReceiver = new MediaReceiver();
        registerReceiver(mReceiver, new IntentFilter(Util.M_MEDIA_PLAY_ACTION));
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {
        if (null != mReceiver) {
            unregisterReceiver(mReceiver);
            mReceiver = null;
        }
        super.onDestroy();
    }

    private MediaInfo getMediaInfo(Intent i) {
        MediaInfo info = new MediaInfo();
        info.SessionID = i.getIntExtra(Util.M_SESSION_ID, 0);
        info.PlayerType = i.getStringExtra(Util.M_PLAYER_TYPE);
        info.VideoURL = i.getStringExtra(Util.M_URL);
        info.MediaWidthResolution = i.getLongExtra(Util.M_MEDIA_WIDTH, 0);
        info.MediaHeightResolution = i.getLongExtra(Util.M_MEDIA_HEIGHT, 0);
        info.VideoRate = i.getLongExtra(Util.M_VIDEO_RATE, 0);
        info.FrameRate = i.getIntExtra(Util.M_FRAME_RATE, 0);
        info.EncodeType = i.getStringExtra(Util.M_ENCODE_TYPE);
        if (null == info.PlayerType) {
            info.PlayerType = "";
        }
        if (null == info.VideoURL) {
            info.VideoURL = "";
        }
        if (null == info.EncodeType) {
            info.EncodeType = "";
        }
        if (info.EncodeType.contains("/")) {
            String type = info.EncodeType;
            info.EncodeType = type.split("/")[1].trim();
        }
        return info;
    }

     private String getFrameInfo(VideoFrameInfos info) {
        frameNo++;
		if(1 == info.getVframeTypeValue())
			return "{" + frameNo + "," + "I" + ","
                + info.getVframeSizeValue() + "," + info.getVframeQPValue()
                + "," + info.getVframePtsValue() + "}";
		else if(2 == info.getVframeTypeValue())
		    return "{" + frameNo + "," + "P" + ","
                + info.getVframeSizeValue() + "," + info.getVframeQPValue()
                + "," + info.getVframePtsValue() + "," + info.getVframeMaxMvValue() +","+ info.getVframeMinMvValue()
                + "," + info.getVframeAvgMvValue() + "," + info.getVframeSkipRatioValue() + "}";
		else if(3 == info.getVframeTypeValue())
		    return "{" + frameNo + "," + "B" + ","
                + info.getVframeSizeValue() + "," + info.getVframeQPValue()
                + "," + info.getVframePtsValue() + "}";
		else
			return null;
    }

    private String createInputFile() {
        SimpleDateFormat format = new SimpleDateFormat("yyyyMMddHHmmss",
                Locale.getDefault());
        String fileName = Util.FILE_PATH_INPUT + format.format(new Date())
                + ".log";
        Util.createFile(fileName);
        return fileName;
    }

    private class MediaReceiver extends BroadcastReceiver {

        @Override
        public void onReceive(Context context, Intent intent) {
            StringBuilder sb = new StringBuilder();
            String status = intent.getStringExtra(Util.M_MESSAGE_STATUS);
            if (!isPrepare && Util.M_MESSAGE_PLAY_PREPARE.equals(status)) {

                Util.clearInputFile();
                curInputFile = createInputFile();
                info = getMediaInfo(intent);
                startDate = new Date(intent.getLongExtra(Util.M_START_TIME,
                        System.currentTimeMillis()));
                StartPlayTime = Util.formatTime(startDate);
                sb.append(StartPlayTime).append("\n");
                Util.writeFile(Util.FILE_PATH_ENTER, sb.toString(), true);
                frameNo = -1;
                isPrepare = true;
            } else if (isPrepare && !isStart
                    && Util.M_MESSAGE_PLAY_START.equals(status)) {
                DisplayFirstFrameTime = Util.formatTime(intent,
                        Util.M_PLAY_TIME);

                sb.append("SessionID=").append(info.SessionID).append("\n");
                sb.append("VideoURL=").append(info.VideoURL).append("\n");
                sb.append("PlayerType=").append(info.PlayerType).append("\n");
                sb.append("StartPlayTime=").append(StartPlayTime).append("\n");
                sb.append("VideoRate=").append(info.VideoRate).append("\n");
                sb.append("MediaWidthResolution=")
                        .append(info.MediaWidthResolution).append("\n");
                sb.append("MediaHeightResolution=")
                        .append(info.MediaHeightResolution).append("\n");
                sb.append("EncodeType=").append(info.EncodeType).append("\n");
                sb.append("DisplayFirstFrameTime=")
                        .append(DisplayFirstFrameTime).append("\n");
                sb.append("FrameRate=").append(info.FrameRate).append("\n");
                Util.writeFile(curInputFile, sb.toString(), false);
                isStart = true;
            } else if (isStart && Util.M_BUFFER_START.equals(status)) {
                StallingHappenTime = Util.formatTime(intent,
                        Util.M_BUFFER_START_TIME);

                sb.append("StallingHappenTime=");
                sb.append(StallingHappenTime);
                sb.append("\n");
                Util.writeFile(curInputFile, sb.toString(), true);
            } else if (isStart && Util.M_MESSAGE_VIDEO_INFO.equals(status)) {
                Bundle bundle = intent.getExtras();
                mVidFrmList = (ArrayList<VideoFrameInfos>) (bundle
                        .getSerializable(Util.M_VIDEO_INFO));
                int count = mVidFrmList.size();
                sb.append("FrameInfo=[").append(count);
                for (int i = 0; i < count; i++) {
                    sb.append(",");
                    sb.append(getFrameInfo(mVidFrmList.get(i)));
                }
                sb.append("]");
                sb.append("\n");

                Util.writeFile(curInputFile, sb.toString(), true);
            } else if (isStart && Util.M_BUFFER_END.equals(status)) {
                StallingRestoreTime = Util.formatTime(intent,
                        Util.M_BUFFER_END_TIME);
                sb.append("StallingRestoreTime=");
                sb.append(StallingRestoreTime);
                sb.append("\n");
                Util.writeFile(curInputFile, sb.toString(), true);
            } else if (isStart && Util.M_SEEK_START.equals(status)) {

                SeekStartTime = Util.formatTime(intent, Util.M_SEEK_START_TIME);
                sb.append("SeekStartTime=");
                sb.append(SeekStartTime);
                sb.append("\n");
                Util.writeFile(curInputFile, sb.toString(), true);
            } else if (isStart && Util.M_SEEK_END.equals(status)) {

                SeekEndTime = Util.formatTime(intent, Util.M_SEEK_END_TIME);
                sb.append("SeekEndTime=");
                sb.append(SeekEndTime);
                sb.append("\n");
                Util.writeFile(curInputFile, sb.toString(), true);
            } else if (isStart && Util.M_MESSAGE_PLAY_COMPLETE.equals(status)) {

                PlayQuitTime = Util.formatTime(intent, Util.M_STOP_TIME);
                sb.append("PlayQuitTime=").append(PlayQuitTime).append("\n");
                Util.writeFile(curInputFile, sb.toString(), true);

                Util.writeFile(Util.FILE_PATH_QUIT, PlayQuitTime + "\n", true);
                isPrepare = false;
                isStart = false;
            }
        }
    }

}
