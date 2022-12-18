/* //device/java/android/android/os/IDisplayManager.aidl
**
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

package com.hisilicon.android;
import android.graphics.Rect;
import com.hisilicon.android.DispFmt;

/** @hide */
interface IHiDisplayManager
{
    int setBrightness(int brightness);
    int getBrightness();
    int setContrast(int contrast);
    int getContrast();
    int setFmt(int fmt);
    int getFmt();
    int setHue(int hue);
    int getHue();
    int setSaturation(int saturation);
    int getSaturation();
    int setOutRange(int x,int y,int a,int b);
    Rect getOutRange();
    int setMacroVision(int enMode);
    int getMacroVision();
    int setHdcp(boolean mode);
    int getHdcp();
    int setStereoOutMode(int mode, int videofps);
    int getStereoOutMode();
    int setRightEyeFirst(int Outpriority);
    int getRightEyeFirst();
    DispFmt getDisplayCapability();
    int setAspectRatio(int ratio);
    int getAspectRatio();
    int setAspectCvrs(int cvrs);
    int getAspectCvrs();
    int setOptimalFormatEnable(int able);
    int getOptimalFormatEnable();
    int getDisplayDeviceType();
    int saveParam();
    int attachIntf();
    int detachIntf();
    int setVirtScreen(int outFmt);
    int getVirtScreen();
    int reset();
    int setHDMISuspendTime(int iTime);
    int getHDMISuspendTime();
    int setHDMISuspendEnable(int iEnable);
    int getHDMISuspendEnable();
    int reload();
    int setOutputEnable(int port, int enable);
    int getOutputEnable(int port);
}
