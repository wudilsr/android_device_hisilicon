/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.hisilicon.android;

import android.util.Log;
import android.os.ServiceManager;
import android.graphics.Rect;
import com.hisilicon.android.DispFmt;

/**
* HiDisplayManager interface<br>
* CN: HiDisplayManager接口
*/
public class HiDisplayManager  {

    /*
     * Format and its value
     * It must be defined same as hi_unf_display.h
     * /
    public final static int ENC_FMT_1080P_60 = 0;         /*1080p60hz*/
    public final static int ENC_FMT_1080P_50 = 1;         /*1080p50hz*/
    public final static int ENC_FMT_1080P_30 = 2;         /*1080p30hz*/
    public final static int ENC_FMT_1080P_25 = 3;         /*1080p25hz*/
    public final static int ENC_FMT_1080P_24 = 4;         /*1080p24hz*/
    public final static int ENC_FMT_1080i_60 = 5;         /*1080i60hz*/
    public final static int ENC_FMT_1080i_50 = 6;         /*1080i60hz*/
    public final static int ENC_FMT_720P_60 = 7;          /*720p60hz*/
    public final static int ENC_FMT_720P_50 = 8;          /*720p50hz*/
    public final static int ENC_FMT_576P_50 = 9;          /*576p50hz*/
    public final static int ENC_FMT_480P_60 = 10;         /*480p60hz*/
    public final static int ENC_FMT_PAL = 11;             /*BDGHIPAL*/
    public final static int ENC_FMT_PAL_N = 12;           /*(N)PAL*/
    public final static int ENC_FMT_PAL_Nc = 13;          /*(Nc)PAL*/
    public final static int ENC_FMT_NTSC = 14;            /*(M)NTSC*/
    public final static int ENC_FMT_NTSC_J = 15;          /*NTSC-J*/
    public final static int ENC_FMT_NTSC_PAL_M = 16;      /*(M)PAL*/
    public final static int ENC_FMT_SECAM_SIN = 17;
    public final static int ENC_FMT_SECAM_COS = 18;

    public final static int ENC_FMT_1080P_24_FRAME_PACKING = 19;
    public final static int ENC_FMT_720P_60_FRAME_PACKING = 20;
    public final static int ENC_FMT_720P_50_FRAME_PACKING = 21;

    public final static int ENC_FMT_861D_640X480_60 = 22;
    public final static int ENC_FMT_VESA_800X600_60 = 23;
    public final static int ENC_FMT_VESA_1024X768_60 =  24;
    public final static int ENC_FMT_VESA_1280X720_60 = 25;
    public final static int ENC_FMT_VESA_1280X800_60 = 26;
    public final static int ENC_FMT_VESA_1280X1024_60 = 27;
    public final static int ENC_FMT_VESA_1360X768_60 = 28;
    public final static int ENC_FMT_VESA_1366X768_60 = 29;
    public final static int ENC_FMT_VESA_1400X1050_60 =   30;
    public final static int ENC_FMT_VESA_1440X900_60 =    31;
    public final static int ENC_FMT_VESA_1440X900_60_RB = 32;
    public final static int ENC_FMT_VESA_1600X900_60_RB =  33;
    public final static int ENC_FMT_VESA_1600X1200_60 =   34;
    public final static int ENC_FMT_VESA_1680X1050_60 =   35;
    public final static int ENC_FMT_VESA_1680X1050_60_RB =  36;
    public final static int ENC_FMT_VESA_1920X1080_60 =   37;
    public final static int ENC_FMT_VESA_1920X1200_60 =   38;
    public final static int ENC_FMT_VESA_1920X1440_60 =   39;
    public final static int ENC_FMT_VESA_2048X1152_60 =   40;
    public final static int ENC_FMT_VESA_2560X1440_60_RB =   41;
    public final static int ENC_FMT_VESA_2560X1600_60_RB =   42;

    public final static int ENC_FMT_3840X2160_24             = 0x100;
    public final static int ENC_FMT_3840X2160_25             = 0x101;
    public final static int ENC_FMT_3840X2160_30             = 0x102;
    public final static int ENC_FMT_3840X2160_50             = 0x103;
    public final static int ENC_FMT_3840X2160_60             = 0x104;

    public final static int ENC_FMT_4096X2160_24             = 0x105;
    public final static int ENC_FMT_4096X2160_25             = 0x106;
    public final static int ENC_FMT_4096X2160_30             = 0x107;
    public final static int ENC_FMT_4096X2160_50             = 0x108;
    public final static int ENC_FMT_4096X2160_60             = 0x109;

    public final static int ENC_FMT_3840X2160_23_976         = 0x10a;
    public final static int ENC_FMT_3840X2160_29_97          = 0x10b;
    public final static int ENC_FMT_720P_59_94               = 0x10c;
    public final static int ENC_FMT_1080P_59_94              = 0x10d;
    public final static int ENC_FMT_1080P_29_97              = 0x10e;
    public final static int ENC_FMT_1080P_23_976             = 0x10f;
    public final static int ENC_FMT_1080i_59_94              = 0x110;

    public final static int HI_DISP_MODE_NORMAL = 0;
    public final static int HI_DISP_MODE_FRAME_PACKING = 1;
    public final static int HI_DISP_MODE_SIDE_BY_SIDE = 2;
    public final static int HI_DISP_MODE_TOP_BOTTOM = 3;

    private IHiDisplayManager m_Display;
    private static String TAG = "DisplayManagerClient";

    public HiDisplayManager()
    {
        m_Display = IHiDisplayManager.Stub.asInterface(ServiceManager.getService("HiDisplay"));
    }

    /**
     * set image brightness.
     * <br>
     * CN:设置图像亮度
     * @param brightness<br>
     *       CN:亮度
     * @return int
     */
    public int setBrightness(int brightness)
    {
        try
        {
            return m_Display.setBrightness(brightness);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get image brightness.
     * <br>
     * CN:获取图像亮度
     * @return brightness<br>
     *       CN:亮度
     */
    public int getBrightness()
    {
        try
        {
            return m_Display.getBrightness();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * set image saturation.
     * <br>
     * CN:设置图像饱和度
     * @param saturation<br>
     *       CN:饱和度
     * @return int
     */
    public int setSaturation(int saturation)
    {
        try
        {
            return m_Display.setSaturation(saturation);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get image saturation.
     * <br>
     * CN:获取图像饱和度
     * @return saturation<br>
     *       CN:饱和度
     */
    public int getSaturation()
    {
        try
        {
            return m_Display.getSaturation();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * set image contrast.
     * <br>
     * CN:设置图像对比度
     * @param contrast<br>
     *       CN:对比度
     * @return int
     */
    public int setContrast(int contrast)
    {
        try
        {
            return m_Display.setContrast(contrast);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get image contrast.
     * <br>
     * CN:获取图像对比度
     * @return contrast<br>
     *       CN:对比度
     */
    public int getContrast()
    {
        try
        {
            return m_Display.getContrast();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * set image hue.
     * <br>
     * CN:设置图像色度
     * @param hue<br>
     *       CN:色度
     * @return int
     */
    public int setHue(int hue)
    {
        try
        {
            return m_Display.setHue(hue);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get image hue.
     * <br>
     * CN:获取图像色度
     * @return hue<br>
     *       CN:色度
     */
    public int getHue()
    {
        try
        {
            return m_Display.getHue();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * set display format.
     * <br>
     * CN:设置显示制式
     * @param fmt format<br>
     *       CN:fmt 制式
     * @return int
     */
    public int setFmt(int fmt)
    {
        try
        {
            return m_Display.setFmt(fmt);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get display format.
     * <br>
     * CN:获取显示制式
     * @return fmt format<br>
     *       CN:fmt 制式
     */
    public int getFmt()
    {
        try
        {
            return (int)m_Display.getFmt();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * set screen display area size.
     * <br>
     * CN:设置屏幕显示区域大小
     * @param x:screen display area coordinate origin x <br>
     *       CN:屏幕显示区域x坐标
     * @param y:screen display area coordinate origin y <br>
     *       CN:屏幕显示区域y坐标
     * @param x:screen display area width <br>
     *       CN:屏幕显示区域宽度
     * @param x:screen display area height <br>
     *       CN:屏幕显示区域高度
     * @return int
     */
    public int setOutRange(int x,int y,int w ,int h)
    {
        try
        {
            return m_Display.setOutRange(x,y,w,h);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get screen display area size.
     * <br>
     * CN:获取屏幕显示区域大小
     * @return rect
     *     CN:返回矩形
     */
    public Rect getOutRange()
    {
        try
        {
            return m_Display.getOutRange();
        }
        catch(Exception ex)
        {
            return null;
        }
    }
    /**
     * set Macro Vision.
     * <br>
     * CN:设置Macro版本
     * @param mode<br>
     *       CN:模式
     * @return int
     */
    public int setMacroVision(int enMode)
    {
        try
        {
            return m_Display.setMacroVision(enMode);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get Macro Vision.
     * <br>
     * CN:获取Macro版本
     * @return mode<br>
     *       CN:模式
     */
    public int getMacroVision()
    {
        try
        {
            return m_Display.getMacroVision();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * set HDCP.
     * <br>
     * CN:设置HDCP
     * @param mode<br>
     *       CN:模式
     * @return int
     */
    public int setHdcp(boolean mode)
    {
        try
        {
            return m_Display.setHdcp(mode);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get HDCP.
     * <br>
     * CN:获取HDCP
     * @return mode<br>
     *       CN:模式
     */
    public int getHdcp()
    {
        try
        {
            return m_Display.getHdcp();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * set stereo out mode.
     * <br>
     * CN:设置立体声输出模式
     * @param mode<br>
     *       CN:模式
     * @return int
     */
    public int SetStereoOutMode(int mode, int videofps)
    {
        try
        {
            if(mode < HI_DISP_MODE_NORMAL || mode > HI_DISP_MODE_TOP_BOTTOM)
            {
                Log.e(TAG, "stereo mode must be in 0,1,2,3,please check it .");
                return -1;
            }
            return m_Display.setStereoOutMode(mode, videofps);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get stereo out mode.
     * <br>
     * CN:获取立体声输出模式
     * @return mode<br>
     *       CN:模式
     */
    public int GetStereoOutMode()
    {
        try
        {
            return m_Display.getStereoOutMode();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * set right eye priority.
     * <br>
     * CN:设置右眼优先
     * @param Outpriority<br>
     *       CN:优先级
     * @return int
     */
    public int SetRightEyeFirst(int Outpriority)
    {
        try
        {
            return m_Display.setRightEyeFirst(Outpriority);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
     /**
     * set right eye priority.
     * <br>
     * CN:设置右眼优先级别
     * @param Outpriority<br>
     *       CN:优先级
     * @return int
     */
    public int GetRightEyeFirst()
    {
        try
        {
            return m_Display.getRightEyeFirst();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public DispFmt GetDisplayCapability()
    {
        try
        {
            return m_Display.getDisplayCapability();
        }
        catch(Exception ex)
        {
            return null;
        }
    }
    /**
     * set video aspect ratio.
     * <br>
     * CN:设置视频宽高比
     * @param ratio 0:auto,1:4:3,2:16:9<br>
     *      CN:比例 0:自动,1:4:3,2:16:9
     * @return int
     */
    public int setAspectRatio(int ratio)
    {
        try
        {
            return m_Display.setAspectRatio(ratio);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get video aspect ratio.
     * <br>
     * CN:获取视频宽高比
     * @return ratio 0:auto,1:4:3,2:16:9<br>
     *      CN:比例 0:自动,1:4:3,2:16:9
     */
    public int getAspectRatio()
    {
        try
        {
            return m_Display.getAspectRatio();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * set maintain aspect ratio mode.
     * <br>
     * CN:设置视频宽高比转换方式
     * @param cvrs 0:extrude,1:add black<br>
     *     CN:模式 0:拉伸,1:加黑边
     * @return int
     */
    public int setAspectCvrs(int cvrs)
    {
        try
        {
            return m_Display.setAspectCvrs(cvrs);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get maintain aspect ratio mode.
     * <br>
     * CN:获取视频宽高比转换方式
     * @return cvrs 0:extrude,1:add black<br>
     *      CN:模式 0:拉伸,1:加黑边
     */
    public int getAspectCvrs()
    {
        try
        {
            return m_Display.getAspectCvrs();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * enable format to optimal format
     * <br>
     * @param able 0:disable,1:enable
     * @return int
     */
    public int setOptimalFormatEnable(int able)
    {
        try
        {
            return m_Display.setOptimalFormatEnable(able);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get optimal format enable or not
     * <br>
     * @return able 0:disable,1:enable
     */
    public int getOptimalFormatEnable()
    {
        try
        {
            return m_Display.getOptimalFormatEnable();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * get display device type
     * <br>
     * CN:
     * @return type,1 is tv,0 is pc<br>
     */
    public int getDisplayDeviceType()
    {
        try
        {
            return m_Display.getDisplayDeviceType();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    /**
     * save parameter.
     * <br>
     * CN:保存参数
     * @return int
     */
    public int SaveParam()
    {
        try
        {
            return m_Display.saveParam();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int attachIntf()
    {
        try
        {
            return m_Display.attachIntf();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int detachIntf()
    {
        try
        {
            return m_Display.detachIntf();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int setVirtScreen(int outFmt)
    {
        try
        {
            return m_Display.setVirtScreen(outFmt);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int getVirtScreen()
    {
        try
        {
            return m_Display.getVirtScreen();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    /**
     * reset brightness/chroma/contrast/saturation to 50.
     * <br>
     * CN:
     * @return 0<br>
     */
    public int reset()
    {
        try
        {
            return m_Display.reset();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    /**
      * set hdmi suspend time.
      * <br>
      * @param iTime :time
      * @return int
      */
    public int setHDMISuspendTime(int iTime)
    {
        try
        {
            return m_Display.setHDMISuspendTime(iTime);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    /**
    * get hdmi suspend time.
    * <br>
    * @return int
    */
    public int getHDMISuspendTime()
    {
        try
        {
            return m_Display.getHDMISuspendTime();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    /**
    * set hdmi suspend enable.
    * @param iEnable :enable
    * @return int
    */
    public int setHDMISuspendEnable(int iEnable)
    {
        try
        {
            return m_Display.setHDMISuspendEnable(iEnable);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    /**
    * get hdmi suspend enable.
    * @return int
    */
    public int getHDMISuspendEnable()
    {
        try
        {
            return m_Display.getHDMISuspendEnable();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int reload()
    {
        try
        {
            return m_Display.reload();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    /**
      * setOutputEnable: enable output port or not.
      * @param port: 0 -> HDMI, 1 -> CVBS
      * @param enable: 0 -> disabled (close this port), 1 -> enabled (open this port)
      * @return 0 -> success, -1 -> fail
      */
    public int setOutputEnable(int port, int enable)
    {
        try
        {
            return m_Display.setOutputEnable(port, enable);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    /**
      * getOutputEnable: get output port status.
      * @param port: 0 -> HDMI, 1 -> CVBS
      * @return 0 -> disabled, 1 -> enabled
      */
    public int getOutputEnable(int port)
    {
        try
        {
            return m_Display.getOutputEnable(port);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
}
