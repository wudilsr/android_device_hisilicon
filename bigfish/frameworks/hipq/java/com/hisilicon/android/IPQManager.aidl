
package com.hisilicon.android;

interface IPQManager
{
    int setImageMode(int mode);
    int getImageMode();
    int setBrightness(int brightness);
    int getBrightness();
    int setContrast(int contrast);
    int getContrast();
    int setHue(int hue);
    int getHue();
    int setSaturation(int saturation);
    int getSaturation();
 
    int saveParam(int savetype);
    int reset();

    int setShopMode(int mode);
    int getShopMode();

    int setColorEnhanceMode(int mode);
    int getColorEnhanceMode();
    int setCustomizeColor(int basecolor, int value);
    int getCustomizeColor(int basecolor);

    int setDynamicContrast(int mode);
    int getDynamicContrast();

    int setSharpness(int sharp);
    int getSharpness();

	int setSuperResolution(int enable);
    int getSuperResolution();
}
