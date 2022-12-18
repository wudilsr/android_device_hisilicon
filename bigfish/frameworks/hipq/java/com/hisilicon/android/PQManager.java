
package com.hisilicon.android;

import android.util.Log;
import android.os.ServiceManager;


/**
* PQManager interface<br>
*/
public class PQManager  {
    private static String TAG = "PQManager";

    //image mode
    public final static int HI_PQ_IMAGE_MODE_STANDARD = 0;
    public final static int HI_PQ_IMAGE_MODE_COLORFUL = 1;
    public final static int HI_PQ_IMAGE_MODE_THEATER = 2;
    public final static int HI_PQ_IMAGE_MODE_SPORT = 3;
    public final static int HI_PQ_IMAGE_MODE_CUSTOMIZE = 4;

    //shop mode
    public final static int HI_PQ_SHOP_MODE_ON = 0;
    public final static int HI_PQ_SHOP_MODE_SPLITSCREEN = 1;
    public final static int HI_PQ_SHOP_MODE_OFF = 2;

    //color enhance mode
    public final static int HI_PQ_COLOR_ENHANCE_MODE_AUTO = 0;
    public final static int HI_PQ_COLOR_ENHANCE_MODE_BLUE = 1;
    public final static int HI_PQ_COLOR_ENHANCE_MODE_GREEN = 2;
    public final static int HI_PQ_COLOR_ENHANCE_MODE_CYAN = 3;
    public final static int HI_PQ_COLOR_ENHANCE_MODE_SKIN = 4;
    public final static int HI_PQ_COLOR_ENHANCE_MODE_CUSTOMIZE = 5;

    //six base color type
    public final static int HI_PQ_BASE_COLOR_TYPE_RED = 0;
    public final static int HI_PQ_BASE_COLOR_TYPE_BLUE = 1;
    public final static int HI_PQ_BASE_COLOR_TYPE_GREEN = 2;
    public final static int HI_PQ_BASE_COLOR_TYPE_CYAN = 3;
    public final static int HI_PQ_BASE_COLOR_TYPE_MAGENTA = 4;
    public final static int HI_PQ_BASE_COLOR_TYPE_YELLOW = 5;

    //dynamic contrast mode
    public final static int HI_PQ_DYNAMIC_CONTRAST_MODE_OFF = 0;
    public final static int HI_PQ_DYNAMIC_CONTRAST_MODE_LOW = 1;
    public final static int HI_PQ_DYNAMIC_CONTRAST_MODE_MIDDLE = 2;
    public final static int HI_PQ_DYNAMIC_CONTRAST_MODE_HIGH = 3;

    //save type
    public final static int HI_PQ_SAVE_TYPE_IMAGE = 0;
    public final static int HI_PQ_SAVE_TYPE_COLOR = 1;
    public final static int HI_PQ_SAVE_TYPE_SHARPNESS = 2;
    public final static int HI_PQ_SAVE_TYPE_DYNCCONTRAST = 3;
    public final static int HI_PQ_SAVE_TYPE_SHOPMODE = 4;
    public final static int HI_PQ_SAVE_TYPE_SUPERRESOLUTION = 5;

    private IPQManager m_Pq;

    public PQManager()
    {
        m_Pq = IPQManager.Stub.asInterface(ServiceManager.getService("HiPQ"));
    }

    public int setImageMode(int mode)
    {
        try
        {
            return m_Pq.setImageMode(mode);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int getImageMode()
    {
        try
        {
            return m_Pq.getImageMode();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int setBrightness(int brightness)
    {
        try
        {
            return m_Pq.setBrightness(brightness);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int getBrightness()
    {
        try
        {
            return m_Pq.getBrightness();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int setSaturation(int saturation)
    {
        try
        {
            return m_Pq.setSaturation(saturation);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int getSaturation()
    {
        try
        {
            return m_Pq.getSaturation();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int setContrast(int contrast)
    {
        try
        {
            return m_Pq.setContrast(contrast);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int getContrast()
    {
        try
        {
            return m_Pq.getContrast();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int setHue(int hue)
    {
        try
        {
            return m_Pq.setHue(hue);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int getHue()
    {
        try
        {
            return m_Pq.getHue();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }


    public int setShopMode(int mode)
    {
        try
        {
            return m_Pq.setShopMode(mode);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int getShopMode()
    {
        try
        {
            return m_Pq.getShopMode();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int setColorEnhanceMode(int mode)
    {
        try
        {
            return m_Pq.setColorEnhanceMode(mode);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int getColorEnhanceMode()
    {
        try
        {
            return m_Pq.getColorEnhanceMode();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int setCustomizeColor(int basecolor, int value)
    {
        try
        {
            return m_Pq.setCustomizeColor( basecolor, value);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int getCustomizeColor(int basecolor)
    {
        try
        {
            return m_Pq.getCustomizeColor(basecolor);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int setDynamicContrast(int mode)
    {
        try
        {
            return m_Pq.setDynamicContrast(mode);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int getDynamicContrast()
    {
        try
        {
            return m_Pq.getDynamicContrast();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int setSharpness(int sharp)
    {
        try
        {
            return m_Pq.setSharpness(sharp);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int getSharpness()
    {
        try
        {
            return m_Pq.getSharpness();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int setSuperResolution(int enable)
    {
        try
        {
            return m_Pq.setSuperResolution(enable);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }
    public int getSuperResolution()
    {
        try
        {
            return m_Pq.getSuperResolution();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int saveParam(int savetype)
    {
        try
        {
            return m_Pq.saveParam(savetype);
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

    public int reset()
    {
        try
        {
            return m_Pq.reset();
        }
        catch(Exception ex)
        {
            return -1;
        }
    }

}
