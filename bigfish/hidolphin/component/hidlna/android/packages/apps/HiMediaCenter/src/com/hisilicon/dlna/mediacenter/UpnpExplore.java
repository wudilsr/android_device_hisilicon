package com.hisilicon.dlna.mediacenter;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import android.util.Log;

import com.hisilicon.dlna.file.AbstractFile;
import com.hisilicon.dlna.file.DLNADevice;
import com.hisilicon.dlna.file.DMSDevice;
import com.hisilicon.dlna.dmp.DMPNative;
import com.hisilicon.dlna.dmp.DMPNative.OnDMSChangeListener;
import com.hisilicon.dlna.file.DMSFile;
import com.hisilicon.dlna.file.TopLevel;
import com.hisilicon.dlna.file.util.DeviceHandler;
import com.hisilicon.dlna.mediacenter.listener.NotifyType;
import com.hisilicon.dlna.mediacenter.listener.UpdateCompleteListener;

public class UpnpExplore implements AbstractExplore,OnDMSChangeListener
{
    private static final String TAG = "UpnpExplore";

    private AbstractFile focusFile;
    private AbstractFile parent;
    private List<AbstractFile> fileList;
    private List<DMSDevice> deviceList;
    private Location location;
    private Object synchronizedObject;
    private UpdateCompleteListener updateCompleteListener;
    private boolean isSearchDMS;
    private boolean isInterrupted;

    public UpnpExplore(UpdateCompleteListener updateCompleteListener)
    {
        this.updateCompleteListener = updateCompleteListener;
        fileList = new ArrayList<AbstractFile>();
        deviceList = new LinkedList<DMSDevice>();
        DMSFile.setMaxNumEachSearch((short) 200);
        synchronizedObject = new Object();
        isSearchDMS = false;
        DMPNative.setOnDMSChangeListener(null);
        isInterrupted = false;
    }

    public void breakBrowse()
    {
        isInterrupted = true;
        isSearchDMS = false;
        DMPNative.setOnDMSChangeListener(null);
    }

    public void updateTopList()
    {
        isInterrupted = false;
        parent = null;
        focusFile = null;
        location = Location.TOPLEVEL;
        List<DMSDevice> searchedDeviceList = DMSDevice.searchDMSDevices();
        if(isInterrupted)
        {
            return;
        }
        isSearchDMS = true;
        DMPNative.setOnDMSChangeListener(this);
        synchronized(synchronizedObject)
        {
            for (Iterator<DMSDevice> it = deviceList.iterator(); it.hasNext();)
            {
                DMSDevice device = (DMSDevice) it.next();
                if (!searchedDeviceList.contains(device))
                {
                    it.remove();
                }
            }
            for (DMSDevice device : searchedDeviceList)
            {
                if (!deviceList.contains(device))
                {
                    deviceList.add(device);
                }
            }
            Log.d(TAG, "deviceList.size():" + deviceList.size());
        }
        if(isInterrupted)
        {
            isSearchDMS = false;
            return;
        }
        updateCompleteListener.updateCompleteNotify(NotifyType.DEVICE);

    }

    public void gotoTop(TopLevel device)
    {
        if (!(device instanceof DMSDevice))
        {
            return;
        }
        isInterrupted = false;
        DMPNative.setOnDMSChangeListener(null);
        isSearchDMS = false;
        Log.d(TAG, "gotoTop start");
        DMSFile[] files = DMSFile.getTopFiles((DMSDevice) device);
        if (files == null)
        {
            Log.d(TAG, "top files is null");
            return;
        }
        if(isInterrupted)
        {
            return;
        }
        Log.d(TAG, "gotoTop OK");
        synchronized(synchronizedObject)
        {
            fileList.clear();
            parent = null;
            location = Location.TOP;
            for (DMSFile file : files)
            {
                fileList.add(file);
            }
            if (fileList.size() > 0)
            {
                focusFile = fileList.get(0);
            }
        }
        if(isInterrupted)
        {
            return;
        }
        updateCompleteListener.updateCompleteNotify(NotifyType.FILE);
        Log.d(TAG, "gotoTop end");
    }

    public synchronized void gotoSubDir()
    {
        if (location == Location.TOP)
        {
            location = Location.SECOND;
        }
        else
        {
            location = Location.FILE;
        }
        isSearchDMS = false;
        DMPNative.setOnDMSChangeListener(null);
        if (focusFile instanceof DMSFile)
        {
            DMSFile[] files = ((DMSFile) focusFile).listFiles();
            if (files == null)
            {
                Log.e(TAG, "subdir is null");
                fileList.clear();
                parent = focusFile;
                focusFile = null;
                if(!isInterrupted)
                {
                    updateCompleteListener.updateCompleteNotify(NotifyType.FILE);
                }
                else
                {
                    Log.d(TAG, "isInterrupted no updateCompleteNotify");
                }
                return;
            }
            fileList.clear();
            for (DMSFile file : files)
            {
                fileList.add(file);
            }
            parent = focusFile;
            if (fileList.size() == 0)
            {
                focusFile = null;
            }
            else
            {
                focusFile = fileList.get(0);
            }
        }
        else
        {
            Log.e(TAG, "focusFile is not a DMSFile");
        }
        if(!isInterrupted)
        {
            updateCompleteListener.updateCompleteNotify(NotifyType.FILE);
        }
        else
        {
            Log.d(TAG, "isInterrupted no updateCompleteNotify");
        }
    }

    public synchronized void gotoParent()
    {
        fileList.clear();
        Log.d(TAG, "parent:" + parent);
        isSearchDMS = false;
        DMPNative.setOnDMSChangeListener(null);
        if (parent == null)
        {
            if (location == Location.TOP)
            {
                // parentΪnull
                Log.d(TAG, "parent is device folder");
                // updateTopList();
                return;
            }
            else if (location == Location.TOPLEVEL)
            {
                Log.d(TAG, "now is device");
                location = Location.ROOT;
                return;
            }
        }
        else
        {
            if (location == Location.SECOND)
            {
                Log.d(TAG, "parent is top");
                    DMSDevice device = ((DMSFile)parent).getDevice();
                    if (null != device)
                    {
                        gotoTop(device);
                    }
                    else
                    {
                        Log.d(TAG,"get parent device is null");
                    }
                parent = null;
                return;
            }
            else
            {
                if (parent.getParentFile() == null)
                {
                    Log.e(TAG, "wrong situation");
                    return;
                }
                if (parent.getParentFile().getParentFile() == null)
                {
                    location = Location.SECOND;
                }
                else
                {
                    location = Location.FILE;
                }
                focusFile = parent;
                parent = parent.getParentFile();
                ((DMSFile) parent).setOffsetOfSearch((short) 0);
                DMSFile[] files = ((DMSFile) parent).listFiles();
                if (files == null)
                {
                    Log.e(TAG, "parent file is null");
                    if(!isInterrupted)
                    {
                        updateCompleteListener.updateCompleteNotify(NotifyType.NULL);
                    }
                    return;
                }
                for (DMSFile file : files)
                {
                    fileList.add(file);
                }
                if(!isInterrupted)
                {
                    updateCompleteListener.updateCompleteNotify(NotifyType.FILE);
                }
            }
        }
    }

    public synchronized void gotoNextPage()
    {
        if (parent instanceof DMSFile)
        {
            DMSFile[] files = ((DMSFile) parent).listFiles();

            if (files == null)
            {
                Log.e(TAG, "next page file is null");
                return;
            }
            // fileList.clear();
            for (DMSFile file : files)
            {
                fileList.add(file);
            }

            updateCompleteListener.updateCompleteNotify(NotifyType.NEXTPAGE);
        }
        else
        {
            Log.e(TAG, "parent is not a DMSFile");
        }
    }

    public synchronized void gotoPageIncludeIndex(int index)
    {
        if (parent instanceof DMSFile)
        {
            while (index > fileList.size())
            {
                DMSFile[] files = ((DMSFile) parent).listFiles();

                if (files == null)
                {
                    Log.e(TAG, "next page file is null");
                    return;
                }
                for (DMSFile file : files)
                {
                    fileList.add(file);
                }
            }
            updateCompleteListener.updateCompleteNotify(NotifyType.NEXTPAGE);
        }
        else
        {
            Log.e(TAG, "parent is not a DMSFile");
        }
    }

    public synchronized Location getLocation()
    {
        return location;
    }

    public synchronized String getPath(AbstractFile file)
    {
        StringBuffer path = new StringBuffer(file.getName());
        while (file.getParentFile() != null)
        {
            file = file.getParentFile();
            path.insert(0, file.getName() + "/");
        }
        if (file instanceof DMSFile)
        {
            String deviceName = ((DMSFile) file).getDevice().getName();
            path.insert(0, deviceName + "/");
        }
        return path.toString();
    }

    public synchronized void setFocusFile(AbstractFile focusFile)
    {
        this.focusFile = focusFile;
    }

    public synchronized AbstractFile getFocusFile()
    {
        return focusFile;
    }

    public synchronized List<DMSDevice> getDeviceList()
    {
        return deviceList;
    }

    public synchronized AbstractFile getParent()
    {
        return parent;
    }

    public synchronized List<AbstractFile> getFileList()
    {
        return fileList;
    }

    @Override
    public void onDMSItemChange(boolean isAdd, String strDevice)
    {
        if ((true == isSearchDMS) && (false == isInterrupted))
        {
            if (isAdd)
            {
                DeviceHandler handler = new DeviceHandler();
                handler.parse("<devs>" + strDevice + "</devs>");
                for (DLNADevice device : handler.getDevices())
                {
                    deviceList.add((DMSDevice)device);
                }
            }
            else
            {
                for (DMSDevice device : deviceList)
                {
                    if (strDevice.equalsIgnoreCase(device.getUUID()))
                    {
                        deviceList.remove(device);
                        device = null;
                        break;
                    }
                }
            }
            updateCompleteListener.updateCompleteNotify(NotifyType.DEVICE);
        }
        return;
    }
}
