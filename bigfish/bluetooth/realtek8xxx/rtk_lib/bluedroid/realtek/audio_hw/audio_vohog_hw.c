/*
 * Copyright (C) 2011 The Android Open Source Project
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

#define LOG_TAG "audio_vohog_default"
//#define LOG_NDEBUG 0

#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>

#include <cutils/log.h>

#include <hardware/hardware.h>
#include <system/audio.h>
#include <hardware/audio.h>

#include <cutils/log.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/poll.h>
#include <sys/errno.h>
#include <cutils/str_parms.h>
#include <cutils/sockets.h>


#include "audio_vohog_hw.h"

#define FNLOG()             ALOGV("%s", __FUNCTION__);
#define DEBUG(fmt, ...)     ALOGD("%s: " fmt,__FUNCTION__, ## __VA_ARGS__)
#define INFO(fmt, ...)      ALOGI("%s: " fmt,__FUNCTION__, ## __VA_ARGS__)
#define ERROR(fmt, ...)     ALOGE("%s: " fmt,__FUNCTION__, ## __VA_ARGS__)

struct vohog_audio_device {
    struct audio_hw_device device;
    pthread_mutex_t         lock;
    //int ctrlfd;
};

struct vohog_stream_out {
    struct audio_stream_out stream;
    struct vohog_audio_device *dev;
    struct timeval base,ts;
    int outfd;
    int samplerate;
};

struct vohog_stream_in {
    struct audio_stream_in stream;
    struct vohog_audio_device *dev;
    struct timeval base,ts;
    int infd;
    int ctrl_fd;
    int samplerate;
};

#define RCVBUFSIZE  (20*VOHOG_IN_BUFSIZE)

static int skt_connect(char *path, int sndbufsize, int rcvbufsize, int sndto, int rcvto)
{
    int ret;
    int skt_fd;
    struct sockaddr_un remote;
    int val;
    struct timeval tv;

    DEBUG("connect to %s (sz %d)", path, sndbufsize);

    skt_fd = socket(AF_LOCAL, SOCK_STREAM, 0);

    if(socket_local_client_connect(skt_fd, path,
            ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM) < 0)
    {
        DEBUG("failed to connect (%s)", strerror(errno));
        close(skt_fd);
        return -1;
    }
    if(sndbufsize > 0)
    {
        val = sndbufsize;
        ret = setsockopt(skt_fd, SOL_SOCKET, SO_SNDBUF, (char*)&val, (int)sizeof(val));
        if (ret < 0)
            DEBUG("setsockopt failed (%s)", strerror(errno));
    }
    if(rcvbufsize > 0)
    {
        val = rcvbufsize;
        ret = setsockopt(skt_fd, SOL_SOCKET, SO_RCVBUF, (char*)&val, (int)sizeof(val));
        if (ret < 0)
            DEBUG("setsockopt failed (%s)", strerror(errno));
    }

    if(sndto > 0)
    {
        tv.tv_sec = sndto/1000000;
        tv.tv_usec = sndto%1000000;
        ret = setsockopt(skt_fd, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, (int)sizeof(tv));
        if (ret < 0)
            DEBUG("setsockopt failed (%s)", strerror(errno));
    }
    if(rcvto > 0)
    {
        tv.tv_sec = rcvto/1000000;
        tv.tv_usec = rcvto%1000000;
        ret = setsockopt(skt_fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, (int)sizeof(tv));
        if (ret < 0)
            DEBUG("setsockopt failed (%s)", strerror(errno));
    }

    DEBUG("connected to %s fd = %d", path, skt_fd);

    return skt_fd;
}


static int skt_disconnect(int fd)
{
    DEBUG("fd %d", fd);

    if (fd > 0)
    {
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
    return 0;
}

static int vohog_command(struct vohog_stream_in *in, char cmd)
{
    DEBUG("VOHOG COMMAND %d", cmd);
    char ack;
    int i = 0;
    uint8_t temp[5];
    temp[0] = 0xAA;
    temp[1] = 0x55;
    temp[2] = 0xCC;
    temp[3] = 0x33;
    temp[4] = cmd;
    /* send command */
    while(i < 5)
    {
        if (send(in->ctrl_fd, temp, 5, MSG_NOSIGNAL) == -1)
        {
            ERROR("cmd failed (%s)", strerror(errno));
            if (i == 4){
            skt_disconnect(in->ctrl_fd);
            in->ctrl_fd = VOHOG_SKT_DISCONNECTED;
            return -1;
            }
            usleep(100000);
            in->ctrl_fd = skt_connect(VOHOG_CTRL_PATH, 0, 0, 0, 0);
            i++;
        }
        else
            break;
    }

    /* wait for ack byte */
    if (recv(in->ctrl_fd, &ack, 1, MSG_NOSIGNAL) < 0)
    {
        ERROR("ack failed (%s)", strerror(errno));
        skt_disconnect(in->ctrl_fd);
        in->ctrl_fd = VOHOG_SKT_DISCONNECTED;
        return -1;
    }

    DEBUG("VOHOG COMMAND:DONE STATUS %d",ack);

    if (ack != VOHOG_CTRL_ACK_SUCCESS)
        return -1;

    return 0;
}

static uint32_t out_get_sample_rate(const struct audio_stream *stream)
{
    return 0;
}


static int out_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
    DEBUG("rate = %d return 0\n",rate);
    return 0;
}

static size_t out_get_buffer_size(const struct audio_stream *stream)
{
//  DEBUG("return %d\n",SCO_OUT_BUFSIZE*2);
    return 0;
}

static audio_channel_mask_t out_get_channels(const struct audio_stream *stream)
{
    audio_channel_mask_t mask = AUDIO_CHANNEL_OUT_MONO;
//  DEBUG("return %08x\n",mask);
    return mask;
}

static audio_format_t out_get_format(const struct audio_stream *stream)
{
//  DEBUG("return AUDIO_FORMAT_PCM_16_BIT\n");
    return AUDIO_FORMAT_PCM_16_BIT;
}

static int out_set_format(struct audio_stream *stream, audio_format_t format)
{
    DEBUG(" return 0\n");
    return 0;
}

static int out_standby(struct audio_stream *stream)
{
    DEBUG("return 0\n");
    return 0;
}

static int out_dump(const struct audio_stream *stream, int fd)
{
    DEBUG("fd=%d return 0\n",fd);
    return 0;
}

static int out_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    if(kvpairs)
        DEBUG("%s return 0\n",kvpairs);
    else
        DEBUG("return 0\n");
    return 0;
}

static char * out_get_parameters(const struct audio_stream *stream, const char *keys)
{
    if(keys)
        DEBUG("%s\n",keys);
    else
        DEBUG("");
    return strdup("");
}

static uint32_t out_get_latency(const struct audio_stream_out *stream)
{
    DEBUG("return 0\n");
    return 0;
}

static int out_set_volume(struct audio_stream_out *stream, float left,
                          float right)
{
    DEBUG("left=%f right=%f return 0\n",left,right);
    return 0;
}

static ssize_t out_write(struct audio_stream_out *stream, const void* buffer,
                         size_t bytes)
{
    DEBUG("return\n");
    return 0;
}

static int out_get_render_position(const struct audio_stream_out *stream,
                                   uint32_t *dsp_frames)
{
    DEBUG("return -EINVAL(%d)\n",-EINVAL);
    return -EINVAL;
}

static int out_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    DEBUG("return 0\n");
    return 0;
}

static int out_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    DEBUG("return 0\n");
    return 0;
}

static int out_get_next_write_timestamp(const struct audio_stream_out *stream,
                                        int64_t *timestamp)
{
//  DEBUG("return -EINVAL(%d)\n",-EINVAL);
    return -EINVAL;
}

/** audio_stream_in implementation **/
static uint32_t in_get_sample_rate(const struct audio_stream *stream)
{
    DEBUG("\n");
    return VOHOG_SAMPLE_RATE_16K;
}

static int in_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
    DEBUG("rate=%d return 0\n",rate);
    return 0;
}

static size_t in_get_buffer_size(const struct audio_stream *stream)
{
    DEBUG("%d\n",VOHOG_IN_BUFSIZE);
    return VOHOG_IN_BUFSIZE;
}

static audio_channel_mask_t in_get_channels(const struct audio_stream *stream)
{
    audio_channel_mask_t mask = AUDIO_CHANNEL_IN_MONO;
//  DEBUG("return %08x\n",mask);
    return mask;
}

static audio_format_t in_get_format(const struct audio_stream *stream)
{
    DEBUG("return AUDIO_FORMAT_PCM_16_BIT\n");
    return AUDIO_FORMAT_PCM_16_BIT;
}

static int in_set_format(struct audio_stream *stream, audio_format_t format)
{
    DEBUG("return 0\n");
    return 0;
}

static int in_standby(struct audio_stream *stream)
{
    struct vohog_stream_in *in = (struct vohog_stream_in *)stream;
    DEBUG("return 0\n");
    memset(&(in->ts), 0,sizeof(in->ts));
    memset(&(in->base), 0,sizeof(in->base));
    return 0;
}

static int in_dump(const struct audio_stream *stream, int fd)
{
    DEBUG("fd=%d return 0\n",fd);
    return 0;
}

static int in_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    DEBUG("in_set_parameters: %s", kvpairs);
    return 0;
}

static char * in_get_parameters(const struct audio_stream *stream,
                                const char *keys)
{
    if(keys)
        DEBUG("%s\n",keys);
    else
        DEBUG("");
    return strdup("");
}

static int in_set_gain(struct audio_stream_in *stream, float gain)
{
    DEBUG("gain=%f return 0\n",gain);
    return 0;
}

static ssize_t in_read(struct audio_stream_in *stream, void* buffer,
                       size_t bytes)
{
    int32_t len=0;
    int32_t ret=0;
    int16_t num = 0;
    struct vohog_stream_in * in = (struct vohog_stream_in *)stream;
#ifdef RTK_PATCH_DEBUG
    static uint32_t progress = 0;
    if((progress % 40) == 0)
        DEBUG("in_read...\n");
    progress++;
#endif

    if(in->infd <= 0){
        DEBUG("cheng_@begin to connect VOHOG_DATA_IN_PATH\n");
        in->infd = skt_connect(VOHOG_DATA_IN_PATH, 0, RCVBUFSIZE, 0, 0);
        }

    if(in->infd > 0)
    {
        int temp = (int)buffer;
        if(temp%4)
        {
            DEBUG("buffer not align %08x\n",buffer);
            bytes -= temp%4;
            temp=(temp+3)&(~0x3);
            buffer = temp;
        }
        for(num=0;num<10;num++)
        {
            len = recv(in->infd, buffer, bytes, (MSG_DONTWAIT|MSG_NOSIGNAL));
            if(len > 0)
            {
                if(len != bytes)
                {
                    memset(&buffer[len], 0, (bytes-len));
                    DEBUG("read failed with len=%d bytes=%d errno=%d\n", len, bytes, errno);
                }
                ret = bytes;
                break;
            } else
            {
                ret =0;
                usleep(10000);
            }
        }
    }else {
       usleep(10000);
    }

    DEBUG("num=%d len=%d ret=%d",num,len,ret);
    return ret;
}

static uint32_t in_get_input_frames_lost(struct audio_stream_in *stream)
{
    DEBUG("");
    return 0;
}

static int in_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    DEBUG("");
    return 0;
}

static int in_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    DEBUG("");
    return 0;
}

static uint32_t adev_get_supported_devices(const struct audio_hw_device *dev)
{
    uint32_t devices = (AUDIO_DEVICE_OUT_ALL_SCO | AUDIO_DEVICE_IN_ALL_SCO);///////////////////modify later
    DEBUG("return %08x\n",devices);
    return devices;
}

static int adev_open_output_stream(struct audio_hw_device *dev,
                                   audio_io_handle_t handle,
                                   audio_devices_t devices,
                                   audio_output_flags_t flags,
                                   struct audio_config *config,
                                   struct audio_stream_out **stream_out)
{
    struct vohog_audio_device *ladev = (struct vohog_audio_device *)dev;
    struct vohog_stream_out *out;
    int ret;

    DEBUG("");
    out = (struct vohog_stream_out *)calloc(1, sizeof(struct vohog_stream_out));
    if (!out)
        return -ENOMEM;

    out->stream.common.get_sample_rate = out_get_sample_rate;
    out->stream.common.set_sample_rate = out_set_sample_rate;
    out->stream.common.get_buffer_size = out_get_buffer_size;
    out->stream.common.get_channels = out_get_channels;
    out->stream.common.get_format = out_get_format;
    out->stream.common.set_format = out_set_format;
    out->stream.common.standby = out_standby;
    out->stream.common.dump = out_dump;
    out->stream.common.set_parameters = out_set_parameters;
    out->stream.common.get_parameters = out_get_parameters;
    out->stream.common.add_audio_effect = out_add_audio_effect;
    out->stream.common.remove_audio_effect = out_remove_audio_effect;
    out->stream.get_latency = out_get_latency;
    out->stream.set_volume = out_set_volume;
    out->stream.write = out_write;
    out->stream.get_render_position = out_get_render_position;
    out->stream.get_next_write_timestamp = out_get_next_write_timestamp;

    out->samplerate = 0;
    memset(&(out->base), 0,sizeof(out->base));

    *stream_out = &out->stream;
    return 0;

err_open:
    free(out);
    *stream_out = NULL;
    return ret;
}

static void adev_close_output_stream(struct audio_hw_device *dev,
                                     struct audio_stream_out *stream)
{
    DEBUG("cheng_@adev_close_output_stream!");
    struct vohog_stream_out *out = (struct vohog_stream_in *) stream;
    if(out->outfd > 0)
    {
        skt_disconnect(out->outfd);
        out->outfd = -1;
    }
    free(stream);
}

static int adev_set_parameters(struct audio_hw_device *dev, const char *kvpairs)
{
    if(kvpairs)
        DEBUG("%s return 0\n",kvpairs);
    else
        DEBUG("return 0\n");
    return -ENOSYS;
}

static char * adev_get_parameters(const struct audio_hw_device *dev,
                                  const char *keys)
{
    if(keys)
        DEBUG("%s return 0\n",keys);
    else
        DEBUG("return 0\n");
    return NULL;
}

static int adev_init_check(const struct audio_hw_device *dev)
{
    DEBUG("");
    return 0;
}

static int adev_set_voice_volume(struct audio_hw_device *dev, float volume)
{
    DEBUG("volume=%f return -ENOSYS\n", volume);
    return -ENOSYS;
}

static int adev_set_master_volume(struct audio_hw_device *dev, float volume)
{
    DEBUG("volume=%f return -ENOSYS\n", volume);
    return -ENOSYS;
}

static int adev_set_mode(struct audio_hw_device *dev, audio_mode_t mode)
{
    DEBUG("mode=%d return 0\n",mode);
    return 0;
}

static int adev_set_mic_mute(struct audio_hw_device *dev, bool state)
{
    DEBUG("state=%d return -ENOSYS\n",state);
    return -ENOSYS;
}

static int adev_get_mic_mute(const struct audio_hw_device *dev, bool *state)
{
    DEBUG("return -ENOSYS\n");
    return -ENOSYS;
}

static size_t adev_get_input_buffer_size(const struct audio_hw_device *dev,
                                         const struct audio_config *config)
{
    DEBUG("return 320\n");
    return 320;
}

static int adev_open_input_stream(struct audio_hw_device *dev,
                                  audio_io_handle_t handle,
                                  audio_devices_t devices,
                                  struct audio_config *config,
                                  struct audio_stream_in **stream_in)
{
    struct vohog_audio_device *ladev = (struct vohog_audio_device *)dev;
    struct vohog_stream_in *in;
    int i;
    int ret;

    DEBUG("cheng_@adev_open_input_stream");
    DEBUG("handle:%d device:%08x sample_rate:%d,channel_mask:%08x,format:%d\n", handle, devices, config->sample_rate, config->channel_mask, config->format);

    in = (struct vohog_stream_in *)calloc(1, sizeof(struct vohog_stream_in));
    if (!in)
        return -ENOMEM;

    in->dev = ladev;
    in->stream.common.get_sample_rate = in_get_sample_rate;
    in->stream.common.set_sample_rate = in_set_sample_rate;
    in->stream.common.get_buffer_size = in_get_buffer_size;
    in->stream.common.get_channels = in_get_channels;
    in->stream.common.get_format = in_get_format;
    in->stream.common.set_format = in_set_format;
    in->stream.common.standby = in_standby;
    in->stream.common.dump = in_dump;
    in->stream.common.set_parameters = in_set_parameters;
    in->stream.common.get_parameters = in_get_parameters;
    in->stream.common.add_audio_effect = in_add_audio_effect;
    in->stream.common.remove_audio_effect = in_remove_audio_effect;
    in->stream.set_gain = in_set_gain;
    in->stream.read = in_read;
    in->stream.get_input_frames_lost = in_get_input_frames_lost;

    in->infd = -1;

    in->samplerate = 0;
    memset(&(in->base), 0,sizeof(in->base));
    memset(&(in->ts), 0,sizeof(in->ts));
    /*cheng_add*/
    if (config)
   {
      config->format = in_get_format((const struct audio_stream *)&in->stream);
      config->sample_rate = in_get_sample_rate((const struct audio_stream *)&in->stream);
      config->channel_mask = in_get_channels((const struct audio_stream *)&in->stream);
   }
    /*cheng_add*/

    *stream_in = &in->stream;

    /* connect control channel if not already connected */
    if ((in->ctrl_fd = skt_connect(VOHOG_CTRL_PATH, 0, 0, 0, 0)) > 0)
    {
        DEBUG("connetct socket success");
        if (vohog_command(in,VOHOG_CTRL_CMD_START)<0){
        skt_disconnect(in->ctrl_fd);
        in->ctrl_fd = VOHOG_SKT_DISCONNECTED;
        }
    }

    if (in->ctrl_fd == VOHOG_SKT_DISCONNECTED)
    {
        ERROR("ctrl socket failed to connect (%s)", strerror(errno));
        ret = -1;
        goto err_open;
    }

    DEBUG("success");
    return 0;

err_open:
    free(in);
    *stream_in = NULL;
    return ret;
}

static void adev_close_input_stream(struct audio_hw_device *dev,
                                   struct audio_stream_in *stream)
{
    DEBUG("cheng_@adev_close_input_stream");
    struct vohog_stream_in *in = (struct vohog_stream_in *) stream;
    vohog_command(in,VOHOG_CTRL_CMD_STOP);
    if(in->infd > 0)
    {
        skt_disconnect(in->infd);
        in->infd = VOHOG_SKT_DISCONNECTED;
    }
    if(in->ctrl_fd > 0)
    {
        skt_disconnect(in->ctrl_fd);
        in->ctrl_fd = VOHOG_SKT_DISCONNECTED;
    }

    free(stream);
    return;
}

static int adev_dump(const audio_hw_device_t *device, int fd)
{
    DEBUG("fd=%d return 0\n",fd);
    return 0;
}

static int adev_close(hw_device_t *device)
{
    DEBUG("");
    free(device);
    return 0;
}

static int adev_open(const hw_module_t* module, const char* name,
                     hw_device_t** device)
{
    struct vohog_audio_device *adev;
    pthread_mutexattr_t lock_attr;
    int ret;

    if (strcmp(name, AUDIO_HARDWARE_INTERFACE) != 0)
        return -EINVAL;

    DEBUG("adev_open name=%s\n",name);
    adev = calloc(1, sizeof(struct vohog_audio_device));
    if (!adev)
        return -ENOMEM;

    adev->device.common.tag = HARDWARE_DEVICE_TAG;
    adev->device.common.version = AUDIO_DEVICE_API_VERSION_2_0;
    adev->device.common.module = (struct hw_module_t *) module;
    adev->device.common.close = adev_close;

    adev->device.get_supported_devices  = adev_get_supported_devices;
    adev->device.init_check = adev_init_check;
    adev->device.set_voice_volume = adev_set_voice_volume;
    adev->device.set_master_volume = adev_set_master_volume;
    adev->device.set_mode = adev_set_mode;
    adev->device.set_mic_mute = adev_set_mic_mute;
    adev->device.get_mic_mute = adev_get_mic_mute;
    adev->device.set_parameters = adev_set_parameters;
    adev->device.get_parameters = adev_get_parameters;
    adev->device.get_input_buffer_size = adev_get_input_buffer_size;
    adev->device.open_output_stream = adev_open_output_stream;
    adev->device.close_output_stream = adev_close_output_stream;
    adev->device.open_input_stream = adev_open_input_stream;
    adev->device.close_input_stream = adev_close_input_stream;
    adev->device.dump = adev_dump;

    //adev->ctrlfd = VOHOG_SKT_DISCONNECTED;

    pthread_mutexattr_init(&lock_attr);
    pthread_mutexattr_settype(&lock_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&adev->lock, &lock_attr);

    *device = &adev->device.common;

    return 0;
}

static struct hw_module_methods_t hal_module_methods = {
    .open = adev_open,
};

struct audio_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = AUDIO_MODULE_API_VERSION_0_1,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = AUDIO_HARDWARE_MODULE_ID,
        .name = "VOHOG audio HW HAL",
        .author = "The Android Open Source Project",
        .methods = &hal_module_methods,
    },
};
