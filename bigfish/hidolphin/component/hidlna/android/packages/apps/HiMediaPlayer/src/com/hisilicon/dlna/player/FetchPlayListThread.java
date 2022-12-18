package com.hisilicon.dlna.player;

import java.util.List;

import android.content.Context;
import android.util.Log;

import com.hisilicon.dlna.dmp.DMPManager;
import com.hisilicon.dlna.dmp.DMPNative;
import com.hisilicon.dlna.file.DMSDevice;
import com.hisilicon.dlna.file.DMSFile;
import com.hisilicon.dlna.file.FileType;
import com.hisilicon.dlna.util.CommonDef;

/**
 * Get sibling play list from one child file.<br>
 * CN: 从一个子文件获取同一级目录文件播放列表
 *
 * @author c00190074
 *
 */
public class FetchPlayListThread extends Thread
{
    private static final String TAG = "FetchPlayListThread";
    private static final int MAX_DEVICE_SEARCH_TIMES = 5;
    private DMSFile mChildFile;
    private FileType mFilterType;
    private List<String> mPlayList;
    private List<DMSFile> mFileList;
    private EventCallback mEventCallback;
    private boolean mIsInterrupted;
    private final static String DEFAULT_USE_ADAPTER_WIFI_ETHERNET = "wlan";

    /**
     * Event callback of the thread.<br>
     * CN: 获取播放列表线程的回调函数
     */
    public interface EventCallback
    {

        /**
         * Notify caller when DMS device not found.<br>
         * CN: 当对应的DMS设备未找到时通知调用者
         */
        void deviceNotFountNotify();

        /**
         * Notify caller when search one file.<br>
         * CN: 当搜索到一个文件时通知调用者
         *
         * @param file The file has been searched.<br>
         *        CN: 搜索到的文件
         */
        void fileAddedNotify(DMSFile file);

        /**
         * Notify caller when searched item number is less than NUM_OF_FIRST_PAGE.<br>
         * CN: 当搜索到的文件数小于NUM_OF_FIRST_PAGE时每搜索一次通知一次调用者，如果大于NUM_OF_FIRST_PAGE, 则搜索完毕再通知调用者
         *
         * @param index if current file is searched, return the index. otherwise return 0.<br>
         *        CN: 如果当前文件已经被搜索到，则返回当前文件索引，否则返回0
         */
        void currentIndexNotify(int index);

        /**
         * Notify caller when search is finished.<br>
         * CN: 当搜索完毕时通知调用者
         */
        void finishNotify();
    }

    /**
     * register event callback funtion.<br>
     * CN: 注册事件回调函数
     */
    public void registerEventCallback(EventCallback callback)
    {
        mEventCallback = callback;
    }

    /**
     * Interrupt the search thread.<br>
     * CN: 打断搜索线程
     */
    public void interruptThread()
    {
        mIsInterrupted = true;
    }

    /**
     * Constructor.<br>
     *
     * @param childFile the searched files are all childFile's brother.<br>
     *        CN: 所有搜索到的文件都是此文件的同一级目录文件
     * @param filterType which type of file you want to search.<br>
     *        CN: 搜索文件的类型
     * @param playList play list, must be initiallized by caller first.<br>
     *        CN: 播放列表，必须由调用者事先初始化
     * @param fileList dms file list, must be initiallized by caller first.<br>
     *        CN: DMS文件列表，和playList一一对应，必须由调用者事先初始化
     */
    public FetchPlayListThread(Context context, DMSFile childFile, FileType filterType, List<String> playList,
            List<DMSFile> fileList)
    {
        mChildFile = childFile;
        mFilterType = filterType;
        mPlayList = playList;
        mFileList = fileList;
        mIsInterrupted = false;
        DMPManager dmpManager = new DMPManager(DMPNative.getInstance());
        try
        {
            CommonDef.setDefaultAdapterName(DEFAULT_USE_ADAPTER_WIFI_ETHERNET);
            dmpManager.create(context);
        }
        catch (Exception e)
        {
            Log.e(TAG, "mDMPManager.create()", e);
        }
    }

    @Override
    public void run()
    {
        DMSDevice device = findDevice(mChildFile);
        if (device == null)
        {
            if (mEventCallback != null)
            {
                mEventCallback.deviceNotFountNotify();
            }
            return;
        }
        DMSFile parentFile = (DMSFile) mChildFile.getParentFile();
        if(null == parentFile)
        {
            return;
        }
        parentFile.setOffsetOfSearch((short) 0);
        int numOfAllFiles = mChildFile.getSumNumOfSubFiles();
        int index = 0;
        int indexOfPlayList = 0;
        int childIndex = 0;
        boolean findCurrentFlag = false;
        Log.d(TAG, "this directory has " + numOfAllFiles + " files and directorys");
        mPlayList.clear();
        mFileList.clear();
        while (index < numOfAllFiles)
        {
            if (mIsInterrupted)
            {
                Log.d(TAG,"run thread is end,mIsInterrupted="+mIsInterrupted);
                return;
            }
            try
            {
                DMSFile[] dmsFiles = parentFile.listFiles();
                if (dmsFiles != null)
                {
                    for (DMSFile tmpFile : dmsFiles)
                    {
                        index++;
                        if (tmpFile.getFileType() != mFilterType)
                        {
                            Log.e(TAG,"the file type is not the type,type="+tmpFile.getFileType()+",url="+tmpFile.getUrl());
                            continue;
                        }
                        if (mIsInterrupted)
                        {
                            return;
                        }
                        mFileList.add(tmpFile);
                        mPlayList.add(tmpFile.getUrl());
                        mEventCallback.fileAddedNotify(tmpFile);
                        if (tmpFile.getId().equals(mChildFile.getId()))
                        {
                            childIndex = indexOfPlayList;
                            findCurrentFlag = true;
                        }
                        indexOfPlayList++;
                    }
                }
                else
                {
                    Log.e(TAG, "parentFile.listFiles() fail, index: " + index);
                    if (mEventCallback != null)
                    {
                        mEventCallback.deviceNotFountNotify();
                    }
                    break;
                }
                if (findCurrentFlag)
                {
                    //only update the first page
                    mEventCallback.currentIndexNotify(childIndex);
                    findCurrentFlag = false;
                }
                Log.d(TAG, "deviceFount loop index: " + index);
                mEventCallback.finishNotify();
            }
            catch (Exception e)
            {
                Log.e(TAG, "find the file error : e=" + e);
                if (mEventCallback != null)
                {
                    mEventCallback.deviceNotFountNotify();
                }
                break;
            }
        }
    }

    private DMSDevice findDevice(DMSFile dmsFile)
    {
        DMSDevice device = dmsFile.getDevice();
        List<DMSDevice> deviceList = DMSDevice.searchDMSDevices();
        int count = MAX_DEVICE_SEARCH_TIMES;
        boolean isDeviceFound = false;
        while (count > 0 && !mIsInterrupted)
        {
            if (deviceList.contains(device))
            {
                isDeviceFound = true;
                break;
            }
            try
            {
                Thread.sleep(1000);
            }
            catch (InterruptedException e)
            {
                Log.e(TAG, "device search interrupted", e);
                return null;
            }
            deviceList = DMSDevice.searchDMSDevices();
            count--;
        }
        if (isDeviceFound)
        {
            return device;
        }
        return null;
    }

}
