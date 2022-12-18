/* alsa_default.cpp
 **
 ** Copyright 2009 Wind River Systems
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

#define LOG_TAG "ALSAModule"
#define LOG_NDEBUG 0
#include <utils/Log.h>
#include <cutils/properties.h>

#include "AudioHardwareALSA.h"
#include <media/AudioRecord.h>

#undef DISABLE_HARWARE_RESAMPLING

#define ALSA_NAME_MAX 128

#define ALSA_STRCAT(x,y) \
     if (strlen(x) + strlen(y) < ALSA_NAME_MAX) \
        strcat(x, y);
#ifndef ALSA_DEFAULT_SAMPLE_RATE
#define ALSA_DEFAULT_SAMPLE_RATE 48000 // in Hz
#endif
#define DEFAULT_SAMPLE_RATE_IN 8000

using namespace android;
namespace android_audio_legacy
{
static int s_device_open(const hw_module_t*, const char*, hw_device_t**);
static int s_device_close(hw_device_t*);
static status_t s_init(alsa_device_t *, ALSAHandleList &);
static status_t s_open(alsa_handle_t *, uint32_t, int);
static status_t s_close(alsa_handle_t *);
static status_t s_route(alsa_handle_t *, uint32_t, int);

static hw_module_methods_t s_module_methods = {
    open            : s_device_open
};
extern "C" audio_module HAL_MODULE_INFO_SYM = {
    common : {
        tag : HARDWARE_MODULE_TAG,
        module_api_version : AUDIO_MODULE_API_VERSION_0_1,
        hal_api_version : HARDWARE_HAL_API_VERSION,
        id : ALSA_HARDWARE_MODULE_ID,
        name : "ALSA module",
        author : " wind river",
        methods : &s_module_methods,
        dso : NULL,
        reserved : {0},
        },
};

static int s_device_open(const hw_module_t* module, const char* name,
        hw_device_t** device)
{
    ALOGI("S_DEVICE_OPEN");
    alsa_device_t *dev;
    dev = (alsa_device_t *) malloc(sizeof(*dev));
    if (!dev) return -ENOMEM;

    memset(dev, 0, sizeof(*dev));

    /* initialize the procs */
    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (hw_module_t *) module;
    dev->common.close = s_device_close;
    dev->init = s_init;
    dev->open = s_open;
    dev->close = s_close;
    dev->route = s_route;

    *device = &dev->common;
    ALOGI("S_DEVICE_OPEN OVER");
    return 0;
}

static int s_device_close(hw_device_t* device)
{
    free(device);
    return 0;
}

static const int DEFAULT_SAMPLE_RATE = ALSA_DEFAULT_SAMPLE_RATE;

static const char *devicePrefix[SND_PCM_STREAM_LAST + 1] = {
        /* SND_PCM_STREAM_PLAYBACK : */"AndroidPlayback",
        /* SND_PCM_STREAM_CAPTURE  : */"AndroidCapture",
};

static alsa_handle_t _defaultsOut = {
    module      : 0,
    devices     : AudioSystem::DEVICE_OUT_ALL,
    curDev      : 0,
    curMode     : 0,
    handle      : 0,
    format      : SND_PCM_FORMAT_S16_LE, // AudioSystem::PCM_16_BIT
    channels    : 2,
    sampleRate  : DEFAULT_SAMPLE_RATE,
    latency     : 250000, // Desired Delay in usec
    bufferSize  : 2048, // Desired Number of samples
    modPrivate  : 0,
};

static alsa_handle_t _defaultsIn = {
    module      : 0,
    devices     : AudioSystem::DEVICE_IN_ALL,
    curDev      : 0,// 01000000,
    curMode     : 0,
    handle      : 0,
    format      : SND_PCM_FORMAT_S16_LE, // AudioSystem::PCM_16_BIT
    channels    : 1,
    sampleRate  : DEFAULT_SAMPLE_RATE_IN,//AudioRecord::DEFAULT_SAMPLE_RATE,
    latency     : 250000, // Desired Delay in usec
    bufferSize  : 2048, // Desired Number of samples
    modPrivate  : 0,
};

struct device_suffix_t {
    const AudioSystem::audio_devices device;
    const char *suffix;
};

/* The following table(s) need to match in order of the route bits
 */
static const device_suffix_t deviceSuffix[] = {
        {AudioSystem::DEVICE_OUT_EARPIECE,       "_Earpiece"},
        {AudioSystem::DEVICE_OUT_SPEAKER,        "_Speaker"},
        {AudioSystem::DEVICE_OUT_ANLG_DOCK_HEADSET, "_Usb"},
        {AudioSystem::DEVICE_OUT_BLUETOOTH_SCO,  "_Bluetooth"},
        {AudioSystem::DEVICE_OUT_WIRED_HEADSET,  "_Headset"},
        {AudioSystem::DEVICE_OUT_BLUETOOTH_A2DP, "_Bluetooth-A2DP"},
        //add output device
        {AudioSystem::DEVICE_OUT_WIRED_HEADPHONE, "_Headphone"},
        {AudioSystem::DEVICE_IN_WIRED_HEADSET, "_Headset"}, //2,0
        {AudioSystem::DEVICE_IN_USB_MIC, "_UsbMic"}, //3,0
        {AudioSystem::DEVICE_IN_BUILTIN_MIC, "_Ai0"},
};

static const int deviceSuffixLen = (sizeof(deviceSuffix)
        / sizeof(device_suffix_t));

snd_pcm_stream_t direction(alsa_handle_t *handle)
{
    return (handle->devices & AudioSystem::DEVICE_OUT_ALL) ? SND_PCM_STREAM_PLAYBACK
            : SND_PCM_STREAM_CAPTURE;
}


bool isUsbMicCaptureDevice(alsa_handle_t *handle)
{
    return (handle->devices & AudioSystem::DEVICE_IN_USB_MIC) ? true : false;
}

const char *deviceName(alsa_handle_t *handle, uint32_t device, int mode)
{
    static char devString[ALSA_NAME_MAX];
    int hasDevExt = 0;

    strcpy(devString, devicePrefix[direction(handle)]);

    for (int dev = 0; device && dev < deviceSuffixLen; dev++)
        if (device & deviceSuffix[dev].device) {
            ALSA_STRCAT (devString, deviceSuffix[dev].suffix);
            device &= ~deviceSuffix[dev].device;
            hasDevExt = 1;
        }

    if (hasDevExt) switch (mode) {
    case AudioSystem::MODE_NORMAL:
        ALSA_STRCAT (devString, "_normal")
        ;
        break;
    case AudioSystem::MODE_RINGTONE:
        ALSA_STRCAT (devString, "_ringtone")
        ;
        break;
    case AudioSystem::MODE_IN_CALL:
        ALSA_STRCAT (devString, "_incall")
        ;
        break;
    };

    return devString;
}

const char *streamName(alsa_handle_t *handle)
{
    return snd_pcm_stream_name(direction(handle));
}

status_t setHardwareParams(alsa_handle_t *handle)
{
    snd_pcm_hw_params_t *hardwareParams;
    status_t err;

    snd_pcm_uframes_t bufferSize = handle->bufferSize;
    unsigned int requestedRate = handle->sampleRate;
    unsigned int requestedchannels = handle->channels;
    unsigned int latency = handle->latency;

    // snd_pcm_format_description() and snd_pcm_format_name() do not perform
    // proper bounds checking.
    bool validFormat = (static_cast<int> (handle->format)
            > SND_PCM_FORMAT_UNKNOWN) && (static_cast<int> (handle->format)
            <= SND_PCM_FORMAT_LAST);
    const char *formatDesc = validFormat ? snd_pcm_format_description(
            handle->format) : "Invalid Format";
    const char *formatName = validFormat ? snd_pcm_format_name(handle->format)
            : "UNKNOWN";

    if (snd_pcm_hw_params_malloc(&hardwareParams) < 0) {
        ALOGE("Failed to allocate ALSA hardware parameters!");
        return NO_INIT;
    }

    err = snd_pcm_hw_params_any(handle->handle, hardwareParams);
    if (err < 0) {
        ALOGE("Unable to configure hardware: %s", snd_strerror(err));
        goto done;
    }

    // Set the interleaved read and write format.
    err = snd_pcm_hw_params_set_access(handle->handle, hardwareParams,
            SND_PCM_ACCESS_RW_INTERLEAVED);
    if (err < 0) {
        ALOGE("Unable to configure PCM read/write format: %s",
                snd_strerror(err));
        goto done;
    }

    err = snd_pcm_hw_params_set_format(handle->handle, hardwareParams,
            handle->format);
    if (err < 0) {
        ALOGE("Unable to configure PCM format %s (%s): %s",
                formatName, formatDesc, snd_strerror(err));
        goto done;
    }

    ALOGV("Set %s PCM format to %s (%s)", streamName(handle), formatName, formatDesc);
    if(1 == direction(handle) && (true == isUsbMicCaptureDevice(handle))) //just for usbmic capture device
    {                                                                     //resample by audioflinger
        err = snd_pcm_hw_params_set_channels_near(handle->handle, hardwareParams,
                &requestedchannels);
        if (err < 0) {
            ALOGE("Unable to set channel count to %i: %s",
                    handle->channels, snd_strerror(err));
            goto done;
        }

        if(requestedchannels != handle->channels)
        {
            ALOGW("Requested channel (%d) does not match actual channel (%d)",
                    handle->channels, requestedchannels);

            ALOGW("requestedChannel %d, need AF RS...",requestedchannels);
            handle->channels = requestedchannels;
        }
    }
    else
    {
        err = snd_pcm_hw_params_set_channels(handle->handle, hardwareParams,
                handle->channels);
        if (err < 0) {
            ALOGE("Unable to set channel count to %i: %s",
                    handle->channels, snd_strerror(err));
            goto done;
        }
    }

    ALOGV("Using %i %s for %s.", handle->channels,
            handle->channels == 1 ? "channel" : "channels", streamName(handle));

    err = snd_pcm_hw_params_set_rate_near(handle->handle, hardwareParams,
            &requestedRate, 0);

    if (err < 0)
        ALOGE("Unable to set %s sample rate to %u: %s",
                streamName(handle), handle->sampleRate, snd_strerror(err));
    else if (requestedRate != handle->sampleRate){
        // Some devices have a fixed sample rate, and can not be changed.
        // This may cause resampling problems; i.e. PCM playback will be too
        // slow or fast.
        ALOGW("Requested rate (%u HZ) does not match actual rate (%u HZ)",
            handle->sampleRate, requestedRate);
        ALOGI("requestedRate %d",requestedRate);

       if(1 == direction(handle) && (true == isUsbMicCaptureDevice(handle)))  //just for usbmic capture device
       {                                                                      //resample by audioflinger
           ALOGI("requestedRate %d, need AF RS...",requestedRate);
           handle->sampleRate=requestedRate;//MK required
        }

    }
    else
        ALOGV("Set sample rate to %u HZ", requestedRate);

#ifdef DISABLE_HARWARE_RESAMPLING
    // Disable hardware re-sampling.
    err = snd_pcm_hw_params_set_rate_resample(handle->handle,
            hardwareParams,
            static_cast<int>(resample));
    if (err < 0) {
        ALOGE("Unable to %s hardware resampling: %s",
                resample ? "enable" : "disable",
                snd_strerror(err));
        goto done;
    }
#endif

    // Make sure we have at least the size we originally wanted
    err = snd_pcm_hw_params_set_buffer_size_near(handle->handle, hardwareParams,
            &bufferSize);

    if (err < 0) {
        ALOGE("Unable to set buffer size to %d:  %s",
                (int)bufferSize, snd_strerror(err));
        goto done;
    }

    // Setup buffers for latency
    err = snd_pcm_hw_params_set_buffer_time_near(handle->handle,
            hardwareParams, &latency, NULL);
    if (err < 0) {
        /* That didn't work, set the period instead */
        unsigned int periodTime = latency / 4;
        err = snd_pcm_hw_params_set_period_time_near(handle->handle,
                hardwareParams, &periodTime, NULL);
        if (err < 0) {
            ALOGE("Unable to set the period time for latency: %s", snd_strerror(err));
            goto done;
        }
        snd_pcm_uframes_t periodSize;
        err = snd_pcm_hw_params_get_period_size(hardwareParams, &periodSize,
                NULL);
        if (err < 0) {
            ALOGE("Unable to get the period size for latency: %s", snd_strerror(err));
            goto done;
        }
        bufferSize = periodSize * 4;
        if (bufferSize < handle->bufferSize) bufferSize = handle->bufferSize;
        err = snd_pcm_hw_params_set_buffer_size_near(handle->handle,
                hardwareParams, &bufferSize);
        if (err < 0) {
            ALOGE("Unable to set the buffer size for latency: %s", snd_strerror(err));
            goto done;
        }
    } else {
        // OK, we got buffer time near what we expect. See what that did for bufferSize.
        err = snd_pcm_hw_params_get_buffer_size(hardwareParams, &bufferSize);
        if (err < 0) {
            ALOGE("Unable to get the buffer size for latency: %s", snd_strerror(err));
            goto done;
        }
        // Does set_buffer_time_near change the passed value? It should.
        err = snd_pcm_hw_params_get_buffer_time(hardwareParams, &latency, NULL);
        if (err < 0) {
            ALOGE("Unable to get the buffer time for latency: %s", snd_strerror(err));
            goto done;
        }
        unsigned int periodTime = latency / 4;
        err = snd_pcm_hw_params_set_period_time_near(handle->handle,
                hardwareParams, &periodTime, NULL);
        if (err < 0) {
            ALOGE("Unable to set the period time for latency: %s", snd_strerror(err));
            goto done;
        }
    }

    ALOGV("Buffer size: %d", (int)bufferSize);
    ALOGV("Latency: %d", (int)latency);

    handle->bufferSize = bufferSize;
    handle->latency = latency;

    // Commit the hardware parameters back to the device.
    err = snd_pcm_hw_params(handle->handle, hardwareParams);
    if (err < 0) ALOGE("Unable to set hardware parameters: %s", snd_strerror(err));

    done:
    snd_pcm_hw_params_free(hardwareParams);

    return err;
}

status_t setSoftwareParams(alsa_handle_t *handle)
{
    snd_pcm_sw_params_t * softwareParams;
    int err;

    snd_pcm_uframes_t bufferSize = 0;
    snd_pcm_uframes_t periodSize = 0;
    snd_pcm_uframes_t startThreshold, stopThreshold;

    if (snd_pcm_sw_params_malloc(&softwareParams) < 0) {
        ALOGE("Failed to allocate ALSA software parameters!");
        return NO_INIT;
    }

    // Get the current software parameters
    err = snd_pcm_sw_params_current(handle->handle, softwareParams);
    if (err < 0) {
        ALOGE("Unable to get software parameters: %s", snd_strerror(err));
        goto done;
    }

    // Configure ALSA to start the transfer when the buffer is almost full.
    snd_pcm_get_params(handle->handle, &bufferSize, &periodSize);

    if (handle->devices & AudioSystem::DEVICE_OUT_ALL) {
        // For playback, configure ALSA to start the transfer when the
        // buffer is full.
        startThreshold = bufferSize - 1;
        stopThreshold = bufferSize;
    } else {
        // For recording, configure ALSA to start the transfer on the
        // first frame.
        startThreshold = 1;
        stopThreshold = bufferSize;
    }

    err = snd_pcm_sw_params_set_start_threshold(handle->handle, softwareParams,
            startThreshold);
    if (err < 0) {
        ALOGE("Unable to set start threshold to %lu frames: %s",
                startThreshold, snd_strerror(err));
        goto done;
    }

    err = snd_pcm_sw_params_set_stop_threshold(handle->handle, softwareParams,
            stopThreshold);
    if (err < 0) {
        ALOGE("Unable to set stop threshold to %lu frames: %s",
                stopThreshold, snd_strerror(err));
        goto done;
    }

    // Allow the transfer to start when at least periodSize samples can be
    // processed.
    err = snd_pcm_sw_params_set_avail_min(handle->handle, softwareParams,
            periodSize);
    if (err < 0) {
        ALOGE("Unable to configure available minimum to %lu: %s",
                periodSize, snd_strerror(err));
        goto done;
    }

    // Commit the software parameters back to the device.
    err = snd_pcm_sw_params(handle->handle, softwareParams);
    if (err < 0) ALOGE("Unable to configure software parameters: %s",
            snd_strerror(err));

    done:
    snd_pcm_sw_params_free(softwareParams);

    return err;
}

// ----------------------------------------------------------------------------

static status_t s_init(alsa_device_t *module, ALSAHandleList &list)
{
    char value[PROPERTY_VALUE_MAX] = {0};

    list.clear();

    snd_pcm_uframes_t bufferSize = _defaultsOut.bufferSize;

    for (size_t i = 1; (bufferSize & ~i) != 0; i <<= 1)
        bufferSize &= ~i;

    _defaultsOut.module = module;

    if(property_get("app.compatibility.enhancement", value, NULL) && !strcasecmp("true", value))
    {
        if(2048 != bufferSize)
	{
           ALOGV("force defaultsOut.bufferSize %d to 2048", (int)bufferSize);
           bufferSize = 2048;
        }
    }

    _defaultsOut.bufferSize = bufferSize;



    list.push_back(_defaultsOut);

    bufferSize = _defaultsIn.bufferSize;

    for (size_t i = 1; (bufferSize & ~i) != 0; i <<= 1)
        bufferSize &= ~i;

    _defaultsIn.module = module;
    _defaultsIn.bufferSize = bufferSize;

    list.push_back(_defaultsIn);

    return NO_ERROR;
}

void stringUp(char* s8Str, int s32Length)
{
    int i = 0;

    for (i = 0; i < s32Length; i++)
    {
        if (s8Str[i] >= 'a' && s8Str[i] <= 'z')
        {
            s8Str[i] -= 32;
        }
    }

    return;
}

static int getUsbMicId()
{
    FILE* fp = NULL;
    const char* pUsbTag = "USB";
    const char* pCapture = "capture";
    const char* pCameraTag = "CAM";
    const int DEFAULTID = 0;
    const int MAX_LINE_SIZE = 256;
    int usbMicCount = 0;

    char buf[MAX_LINE_SIZE];
    memset(buf, 0, MAX_LINE_SIZE);

    fp = fopen("/proc/asound/pcm", "r");
    if (!fp)
    {
        return DEFAULTID;
    }

    while (fgets(buf, MAX_LINE_SIZE, fp) != NULL)
    {
        if ((strstr(buf, pUsbTag) != NULL) &&
            (strstr(buf, pCapture) != NULL))
        {
            usbMicCount++;
        }
        memset(buf, 0, MAX_LINE_SIZE);
    }
    fclose(fp);

    if (usbMicCount > 0)
    {
        if (1 == usbMicCount)
        {
            return 2;
        }

        fp = fopen("/proc/asound/cards", "r");
        if (!fp)
        {
            return DEFAULTID;
        }

        while (fgets(buf, MAX_LINE_SIZE, fp) != NULL)
        {
            if (strstr(buf, pUsbTag) != NULL)
            {
                stringUp((char* )buf, strlen(buf));
                if (strstr(buf, pCameraTag) == NULL)
                {
                    fclose(fp);
                    return (buf[1] - '0');
                }
            }
            memset(buf, 0, MAX_LINE_SIZE);
        }
        fclose(fp);
    }

    return DEFAULTID;
}


static status_t s_open(alsa_handle_t *handle, uint32_t devices, int mode)
{
    // Close off previously opened device.
    // It would be nice to determine if the underlying device actually
    // changes, but we might be recovering from an error or manipulating
    // mixer settings (see asound.conf).
    //
    uint32_t DstDevices;
    int CardId;
    s_close(handle);

    ALOGD("open called for devices %08x in mode %d...", devices, mode);

    const char *stream = streamName(handle);
    DstDevices = devices;
    if(SND_PCM_STREAM_CAPTURE == direction(handle))
    {
        CardId = getUsbMicId();
        ALOGE("device CardId is %d",CardId);
        if(CardId == 2)
        {
             DstDevices = AudioSystem::DEVICE_IN_WIRED_HEADSET;
        }
        else
        {
            DstDevices = AudioSystem::DEVICE_IN_USB_MIC;
        }
    }
    const char *devName = deviceName(handle, DstDevices, mode);

    int err;
    ALOGE("device name is %s",devName);
    for (;;) {
        // The PCM stream is opened in blocking mode, per ALSA defaults.  The
        // AudioFlinger seems to assume blocking mode too, so asynchronous mode
        // should not be used.
        err = snd_pcm_open(&handle->handle, devName, direction(handle),
                SND_PCM_ASYNC);
        if (err == 0) break;

        // See if there is a less specific name we can try.
        // Note: We are changing the contents of a const char * here.
        char *tail = strrchr(devName, '_');
        if (!tail) break;
        *tail = 0;
    }

    if ((err < 0) && (direction(handle) == 0)) {
        // None of the Android defined audio devices exist. Open a generic one.
        devName = "hw:0,0";
        err = snd_pcm_open(&handle->handle, devName, direction(handle), 0);
    }

    if (err < 0) {
        ALOGE("Failed to Initialize any ALSA device,errno: %s", strerror(err));
        return NO_INIT;
    }
    err = setHardwareParams(handle);
    if (err == NO_ERROR) err = setSoftwareParams(handle);
    ALOGI("Initialized ALSA device %x",devices);
    handle->curDev = devices;
    handle->curMode = mode;
    return err;
}

static status_t s_close(alsa_handle_t *handle)
{
    status_t err = NO_ERROR;
    snd_pcm_t *h = handle->handle;
    handle->handle = 0;
    handle->curDev = 0;
    handle->curMode = 0;
    if (h) {
        snd_pcm_drop(h);
        err = snd_pcm_close(h);
    }

    return err;
}

static status_t s_route(alsa_handle_t *handle, uint32_t devices, int mode)
{
    ALOGD("route called for devices %08x in mode %d...", devices, mode);
    return s_open(handle, devices, mode);
}

}
