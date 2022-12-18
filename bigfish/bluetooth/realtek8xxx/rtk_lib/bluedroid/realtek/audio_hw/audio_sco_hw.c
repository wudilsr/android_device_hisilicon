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

#define LOG_TAG "audio_sco_hw"
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
#include "audio_sco_hw.h"


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/poll.h>
#include <sys/errno.h>
#include <cutils/str_parms.h>
#include <cutils/sockets.h>

#include "audio_sco_hw.h"

//#define STREAM_DUMP_DEBUG
#ifdef STREAM_DUMP_DEBUG
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define RECORDER_PCM_LOC "/data/misc/audio/record_debug.pcm"
#define PLAYBACK_PCM_LOC "/data/misc/audio/playback_debug.pcm"

static int debug_record_fd  = 0;
static int debug_playback_fd  = 0;

static void debug_pcm_data_open(int *pfd, bool is_playback)
{
    ALOGD("%s: is_playback %d", __FUNCTION__, is_playback);

    *pfd = (is_playback) ? (open(PLAYBACK_PCM_LOC, O_WRONLY | O_CREAT | O_TRUNC,
                S_IRUSR | S_IWUSR | S_IRGRP)) : (open(RECORDER_PCM_LOC, O_WRONLY | O_CREAT | O_TRUNC,
                    S_IRUSR | S_IWUSR | S_IRGRP));

    if (*pfd < 0) {
        ALOGE("%s: Cannot open file[%s], %s", __FUNCTION__, is_playback ? PLAYBACK_PCM_LOC:
                RECORDER_PCM_LOC, strerror(errno));
        return;
    }
}

static void debug_pcm_data_write(int pfd, const void* buffer, size_t bytes)
{
    if (pfd != 0) {
        write(pfd , buffer, bytes);
    }
}

static void debug_pcm_data_close(int *pfd)
{
    ALOGD("%s", __FUNCTION__);
    close(*pfd);
    *pfd = 0;
}
#endif

#define DEBUG(fmt, ...)     ALOGD("%s: " fmt,__FUNCTION__, ## __VA_ARGS__)
#define INFO(fmt, ...)      ALOGI("%s: " fmt,__FUNCTION__, ## __VA_ARGS__)
#define ERROR(fmt, ...)     ALOGE("%s: " fmt,__FUNCTION__, ## __VA_ARGS__)

struct sco_audio_device {
    struct audio_hw_device device;
    struct sco_stream_out *output;
    struct sco_stream_in *input;
    pthread_mutex_t lock;
    int ctrlfd;
};

struct sco_stream_out {
    struct audio_stream_out stream;
    struct sco_audio_device *dev;
    struct timeval base, ts;
    int outfd;
    int samplerate;
};

struct sco_stream_in {
    struct audio_stream_in stream;
    struct sco_audio_device *dev;
    struct timeval base, ts;
    int infd;
    int samplerate;
};
#define SNDBUFSIZE  (5*SCO_OUT_BUFSIZE)
#define RCVBUFSIZE  (5*SCO_IN_BUFSIZE)

static int skt_connect(char *path, int sndbufsize, int rcvbufsize, int sndto, int rcvto)
{
    int ret;
    int skt_fd;
    struct sockaddr_un remote;
    int val;
    struct timeval tv;

    DEBUG("connect to %s (sz %d)", path, sndbufsize);

    skt_fd = socket(AF_LOCAL, SOCK_STREAM, 0);

    if (socket_local_client_connect(skt_fd, path,
            ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM) < 0) {
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

    if (fd != SCO_SKT_DISCONNECTED) {
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }

    return 0;
}

static uint32_t sco_get_sample_rate(struct sco_audio_device * dev)
{
    char response[64];
    int res;
    uint32_t samplerate = SCO_SAMPLE_RATE_8K;

    if(dev) {
        pthread_mutex_lock(&(dev->lock));
        if (dev->ctrlfd <= 0)
            dev->ctrlfd = skt_connect(SCO_CTRL_PATH, 0, 0, 0, 2000000);
        if (dev->ctrlfd > 0) {
            memset(response,0,sizeof(response));
            res = send(dev->ctrlfd, SCO_CTRL_GETSAMPLERATE, strlen(SCO_CTRL_GETSAMPLERATE),0);
            res = recv(dev->ctrlfd, response, sizeof(response),0);
//          skt_disconnect(dev->ctrlfd);
//          dev->ctrlfd = -1;
            if((res > 0)&&(memcmp(response,SCO_CTRL_GETSAMPLERATE"=",strlen(SCO_CTRL_GETSAMPLERATE"=")) == 0)) {
                samplerate = (uint32_t)atoi(&response[strlen(SCO_CTRL_GETSAMPLERATE)+1]);
            }
        }
        pthread_mutex_unlock(&(dev->lock));
    }
    DEBUG("response=%s samplerate=%d", response, samplerate);
    return samplerate;
}

static uint32_t out_get_sample_rate(const struct audio_stream *stream)
{
    struct sco_stream_out *out = (struct sco_stream_out *)stream;

    out->samplerate = sco_get_sample_rate(out->dev);
    if (out->samplerate == 0)
        out->samplerate = 16000;

    DEBUG("samplerate %d", out->samplerate);

    return out->samplerate;
}

static uint32_t out_get_cached_sample_rate(const struct audio_stream *stream)
{
    struct sco_stream_out * out = (struct sco_stream_out *)stream;

    if (out->samplerate > 0)
        return out->samplerate;
    else
        return 8000;
}

static int out_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
    DEBUG("rate = %d return 0",rate);
    return 0;
}

static size_t out_get_buffer_size(const struct audio_stream *stream)
{
//  DEBUG("return %d",SCO_OUT_BUFSIZE*2);
    return SCO_OUT_BUFSIZE*2;
}

static audio_channel_mask_t out_get_channels(const struct audio_stream *stream)
{
    audio_channel_mask_t mask = AUDIO_CHANNEL_OUT_STEREO;
//  DEBUG("return %08x",mask);
    return mask;
}

static audio_format_t out_get_format(const struct audio_stream *stream)
{
//  DEBUG("return AUDIO_FORMAT_PCM_16_BIT");
    return AUDIO_FORMAT_PCM_16_BIT;
}

static int out_set_format(struct audio_stream *stream, audio_format_t format)
{
    DEBUG("format=%08x return 0", format);
    return 0;
}

static int out_standby(struct audio_stream *stream)
{
    DEBUG("return 0");
    struct sco_stream_out * out = (struct sco_stream_out *)stream;
    memset(&(out->base), 0,sizeof(out->base));
    return 0;
}

static int out_dump(const struct audio_stream *stream, int fd)
{
    DEBUG("fd=%d return 0",fd);
    return 0;
}

static int out_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    if(kvpairs)
        DEBUG("%s return 0",kvpairs);
    else
        DEBUG("return 0");
    return 0;
}

static char * out_get_parameters(const struct audio_stream *stream, const char *keys)
{
    if(keys)
        DEBUG("%s",keys);
    else
        DEBUG("");
    return strdup("");
}

static uint32_t out_get_latency(const struct audio_stream_out *stream)
{
    DEBUG("return 0");
    return 0;
}

static int out_set_volume(struct audio_stream_out *stream, float left,
                          float right)
{
    DEBUG("left=%f right=%f return 0",left,right);
    return 0;
}

static ssize_t out_write(struct audio_stream_out *stream, const void* buffer,
                         size_t bytes)
{
    struct sco_stream_out *out = (struct sco_stream_out *)stream;
    struct timeval tv_before, tv_after;
    struct timeval tv_write, tv_wrote;

    ALOGV("in out_write");

    gettimeofday(&tv_before, NULL);

    uint16_t *pcm = (uint16_t *)malloc(bytes);
    if (pcm) {
        memcpy(pcm, buffer, bytes);
        // Convert stereo PCM to mono PCM
        size_t i;
        for (i = 0; i < bytes / 4; i++)
            pcm[i] = pcm[2*i];
    } else {
        DEBUG("allocate mem for pcm convertion failed");
        return (ssize_t)bytes;
    }

#ifdef STREAM_DUMP_DEBUG
    if (debug_playback_fd == 0)
        debug_pcm_data_open(&debug_playback_fd, true);

    if (debug_playback_fd != 0)
        debug_pcm_data_write(debug_playback_fd, buffer, bytes);
#endif

    if (out->outfd <= 0)
        out->outfd = skt_connect(SCO_OUT_PATH, SNDBUFSIZE, RCVBUFSIZE, 0, 0);

    if (out->outfd > 0) {
        ssize_t len = send(out->outfd, pcm, bytes / 2, MSG_DONTWAIT | MSG_NOSIGNAL);
        if ((len > 0) && ((size_t)len < bytes / 2))
            DEBUG("write %d of %d bytes failed, errno %d", len, bytes/ 2, errno);
    }

    //DEBUG("sockfd %d bytes %d len %d", out->outfd, bytes, len);

    // use btyes instead of (bytes/2) to calculate frames from AudioFlinger.
    int frames = bytes / audio_stream_frame_size(&stream->common);
    tv_write.tv_sec = frames / out_get_cached_sample_rate(&stream->common);
    tv_write.tv_usec = (frames * 1000000 / out_get_cached_sample_rate(&stream->common)) % 1000000;

    gettimeofday(&tv_after, NULL);
    timersub(&tv_after, &tv_before, &tv_wrote);
    //DEBUG("tv_write sec %ld, usec %06ld; tv_wrote sec %ld, usec %06ld",
    //        tv_write.tv_sec, tv_write.tv_usec,
    //        tv_wrote.tv_sec, tv_wrote.tv_usec);

    if (timercmp(&tv_write, &tv_wrote, >=)) {
        long usecs = (tv_write.tv_sec - tv_wrote.tv_sec) * 1000000 + (tv_write.tv_usec - tv_wrote.tv_usec);
        usleep(usecs);
    } else
        DEBUG("delayed sec %ld, usec %06ld", tv_wrote.tv_sec - tv_write.tv_sec,
                tv_wrote.tv_usec - tv_write.tv_usec);

    return (ssize_t)bytes;
}

static int out_get_render_position(const struct audio_stream_out *stream,
                                   uint32_t *dsp_frames)
{
    DEBUG("return -EINVAL");
    return -EINVAL;
}

static int out_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    DEBUG("return 0");
    return 0;
}

static int out_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    DEBUG("return 0");
    return 0;
}

static int out_get_next_write_timestamp(const struct audio_stream_out *stream,
                                        int64_t *timestamp)
{
//  DEBUG("return -EINVAL(%d)",-EINVAL);
    return -EINVAL;
}

/** audio_stream_in implementation **/
static uint32_t in_get_sample_rate(const struct audio_stream *stream)
{
    struct sco_stream_in * in = (struct sco_stream_in *)stream;

    in->samplerate = sco_get_sample_rate(in->dev);
    DEBUG("in->samplerate = sco_get_sample_rate() return %d", in->samplerate);

    if(in->samplerate > 0)
        return in->samplerate;
    else
        return 8000;
}

static uint32_t in_get_cached_sample_rate(const struct audio_stream *stream)
{
    struct sco_stream_in * in = (struct sco_stream_in *)stream;

    if (in->samplerate > 0)
        return in->samplerate;
    else
        return 8000;
}

static int in_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
    DEBUG("rate=%d return 0",rate);
    return 0;
}

static size_t in_get_buffer_size(const struct audio_stream *stream)
{
//  DEBUG("return 240");
    return SCO_IN_BUFSIZE;
}

static audio_channel_mask_t in_get_channels(const struct audio_stream *stream)
{
    audio_channel_mask_t mask = AUDIO_CHANNEL_IN_MONO;
//  DEBUG("return %08x",mask);
    return mask;
}

static audio_format_t in_get_format(const struct audio_stream *stream)
{
//  DEBUG("return AUDIO_FORMAT_PCM_16_BIT");
    return AUDIO_FORMAT_PCM_16_BIT;
}

static int in_set_format(struct audio_stream *stream, audio_format_t format)
{
    DEBUG("format=%08x return 0", format);
    return 0;
}

static int in_standby(struct audio_stream *stream)
{
    struct sco_stream_in *in = (struct sco_stream_in *)stream;
    DEBUG("return 0");
    memset(&(in->ts), 0,sizeof(in->ts));
    memset(&(in->base), 0,sizeof(in->base));
    return 0;
}

static int in_dump(const struct audio_stream *stream, int fd)
{
    DEBUG("fd=%d return 0",fd);
    return 0;
}

static int in_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    struct sco_stream_in *in = (struct sco_stream_in *)stream;
    struct sco_audio_device *adev = in->dev;

    struct str_parms *parms;
    char *str;
    char value[128];
    int ret = 0, val = 0;
    bool do_standby = false;

    DEBUG("in_set_parameters: %s", kvpairs);
/*
    parms = str_parms_create_str(kvpairs);

    ret = str_parms_get_str(parms, AUDIO_PARAMETER_STREAM_INPUT_SOURCE, value, sizeof(value));
    if (ret >= 0) {
        val = atoi(value);
        if ((in->source != val) && (val != 0)) {
            do_standby = true;
        }
    }

    ret = str_parms_get_str(parms, AUDIO_PARAMETER_STREAM_ROUTING, value, sizeof(value));
    if (ret >= 0) {
        val = atoi(value);
        if ((in->source != val) && (val != 0)) {
            do_standby = true;
        }
    }

    in->standby = do_standby;

    str_parms_destroy(parms);
*/
    return ret;
}

static char * in_get_parameters(const struct audio_stream *stream,
                                const char *keys)
{
    if(keys)
        DEBUG("%s",keys);
    else
        DEBUG("");
    return strdup("");
}

static int in_set_gain(struct audio_stream_in *stream, float gain)
{
    DEBUG("gain=%f return 0",gain);
    return 0;
}

static ssize_t in_read(struct audio_stream_in *stream, void* buffer,
                       size_t bytes)
{
    struct sco_stream_in *in = (struct sco_stream_in *)stream;
    struct timeval tv_before, tv_after;
    struct timeval tv_read, tv;
    uint32_t Tsleep;
    ssize_t len;

    ALOGV("in in_read");

    gettimeofday(&tv_before, NULL);

    //if ((in->base.tv_sec == 0) && (in->base.tv_usec == 0)) {
    //    gettimeofday(&(in->base), NULL);
    //    memset(&(in->ts), 0, sizeof(in->ts));
    //}

    if (in->infd <= 0)
        in->infd = skt_connect(SCO_IN_PATH, SNDBUFSIZE, RCVBUFSIZE, 0, 0);

    if (in->infd > 0) {
        len = recv(in->infd, buffer, bytes, MSG_DONTWAIT | MSG_NOSIGNAL);
        if ((len > 0) && ((size_t)len < bytes)) {
            memset((int8_t *)buffer + len, 0, bytes - len);
            DEBUG("read %d of %d bytes", len, bytes);
        } else if (len <= 0) {
            memset(buffer, 0, bytes);
            DEBUG("read %d of %d bytes failed, errno %d", len, bytes, errno);
        }
    }

#ifdef STREAM_DUMP_DEBUG
    if (debug_record_fd == 0)
        debug_pcm_data_open(&debug_record_fd, false);

    if(debug_record_fd != 0)
        debug_pcm_data_write(debug_record_fd, buffer, bytes);
#endif

    //DEBUG("sockfd %d bytes %d len %d", in->infd, bytes, len);

    int frames = bytes / audio_stream_frame_size(&stream->common);
    tv.tv_sec = frames / in_get_cached_sample_rate(&stream->common);
    tv.tv_usec = (frames * 1000000 / in_get_cached_sample_rate(&stream->common)) % 1000000;

    gettimeofday(&tv_after, NULL);
    timersub(&tv_after, &tv_before, &tv_read);

    //DEBUG("tv_read sec %ld, usec %06ld; tv_cal sec %ld, usec %06ld",
    //        tv_read.tv_sec, tv_read.tv_usec,
    //        tv.tv_sec, tv.tv_usec);

    if (timercmp(&tv, &tv_read, >=)) {
        long usecs = (tv.tv_sec - tv_read.tv_sec) * 1000000 + (tv.tv_usec - tv_read.tv_usec);
        usleep(usecs);
    } else
        DEBUG("delayed sec %ld, usec %06ld", tv.tv_sec - tv_read.tv_sec,
                tv.tv_usec - tv_read.tv_usec);

    return (ssize_t)bytes;
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
    uint32_t devices = (AUDIO_DEVICE_OUT_ALL_SCO | AUDIO_DEVICE_IN_ALL_SCO);
    DEBUG("return %08x", devices);
    return devices;
}

static int adev_open_output_stream(struct audio_hw_device *dev,
                                   audio_io_handle_t handle,
                                   audio_devices_t devices,
                                   audio_output_flags_t flags,
                                   struct audio_config *config,
                                   struct audio_stream_out **stream_out)
{
    struct sco_audio_device *sco_dev = (struct sco_audio_device *)dev;
    struct sco_stream_out *out;
    int ret;

    DEBUG("");

#ifdef STREAM_DUMP_DEBUG
    ALOGE("%s: Try to open pcm file", __FUNCTION__);
    if (debug_playback_fd == 0)
        debug_pcm_data_open(&debug_playback_fd, true);
#endif

    out = (struct sco_stream_out *)calloc(1, sizeof(struct sco_stream_out));
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

    out->dev = sco_dev;
    out->samplerate = 0;
    memset(&(out->base), 0,sizeof(out->base));

    *stream_out = &out->stream;
    sco_dev->output = out;

    return 0;

err_open:
    free(out);
    *stream_out = NULL;
    return ret;
}

static void adev_close_output_stream(struct audio_hw_device *dev,
                                     struct audio_stream_out *stream)
{
    struct sco_audio_device *sco_dev = (struct sco_audio_device *) dev;
    struct sco_stream_out *out = (struct sco_stream_out *) stream;

    DEBUG("");

#ifdef STREAM_DUMP_DEBUG
    if (debug_playback_fd != 0) {
        debug_pcm_data_close(&debug_playback_fd);
        debug_playback_fd = 0;
    }
#endif

    if (out->outfd > 0) {
        skt_disconnect(out->outfd);
        out->outfd = -1;
    }

    if (sco_dev->output && out == sco_dev->output) {
        free(out);
        sco_dev->output = NULL;
    }
}

static int adev_set_parameters(struct audio_hw_device *dev, const char *kvpairs)
{
    if (kvpairs)
        DEBUG("%s return 0",kvpairs);
    else
        DEBUG("return 0");
    return -ENOSYS;
}

static char * adev_get_parameters(const struct audio_hw_device *dev,
                                  const char *keys)
{
    if (keys)
        DEBUG("%s return 0", keys);
    else
        DEBUG("return 0");
    return NULL;
}

static int adev_init_check(const struct audio_hw_device *dev)
{
    DEBUG("");
    return 0;
}

static int adev_set_voice_volume(struct audio_hw_device *dev, float volume)
{
    DEBUG("volume=%f return -ENOSYS", volume);
    return -ENOSYS;
}

static int adev_set_master_volume(struct audio_hw_device *dev, float volume)
{
    DEBUG("volume=%f return -ENOSYS", volume);
    return -ENOSYS;
}

static int adev_get_master_volume(struct audio_hw_device *dev, float *volume)
{
    DEBUG("return -ENOSYS");
    return -ENOSYS;
}

static int adev_set_master_mute(struct audio_hw_device *dev, bool muted)
{
    DEBUG("return -ENOSYS");
    return -ENOSYS;
}

static int adev_get_master_mute(struct audio_hw_device *dev, bool *muted)
{
    DEBUG("return -ENOSYS");
    return -ENOSYS;
}

static int adev_set_mode(struct audio_hw_device *dev, audio_mode_t mode)
{
    DEBUG("mode=%d return 0",mode);
    return 0;
}

static int adev_set_mic_mute(struct audio_hw_device *dev, bool state)
{
    DEBUG("state=%d return -ENOSYS",state);
    return -ENOSYS;
}

static int adev_get_mic_mute(const struct audio_hw_device *dev, bool *state)
{
    DEBUG("return -ENOSYS");
    return -ENOSYS;
}

static size_t adev_get_input_buffer_size(const struct audio_hw_device *dev,
                                         const struct audio_config *config)
{
    DEBUG("return 320");
    return 320;
}

static int adev_open_input_stream(struct audio_hw_device *dev,
                                  audio_io_handle_t handle,
                                  audio_devices_t devices,
                                  struct audio_config *config,
                                  struct audio_stream_in **stream_in)
{
    struct sco_audio_device *sco_dev = (struct sco_audio_device *)dev;
    struct sco_stream_in *in;
    int ret;

    DEBUG("handle:%d device:%08x sample_rate:%d,channel_mask:%08x,format:%d", handle, devices, config->sample_rate, config->channel_mask, config->format);

#ifdef STREAM_DUMP_DEBUG
    ALOGE("%s: Try to open recorder pcm file", __FUNCTION__);
    if (debug_record_fd == 0)
        debug_pcm_data_open(&debug_record_fd, false);
#endif

    in = (struct sco_stream_in *)calloc(1, sizeof(struct sco_stream_in));
    if (!in)
        return -ENOMEM;

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

    in->dev = sco_dev;
    in->infd = -1;

    in->samplerate = 0;
    memset(&(in->base), 0,sizeof(in->base));
    memset(&(in->ts), 0,sizeof(in->ts));

    *stream_in = &in->stream;
    sco_dev->input = in;

    return 0;

err_open:
    free(in);
    *stream_in = NULL;
    return ret;
}

static void adev_close_input_stream(struct audio_hw_device *dev,
                                   struct audio_stream_in *stream)
{
    struct sco_audio_device *sco_dev = (struct sco_audio_device *)dev;
    struct sco_stream_in *in = (struct sco_stream_in *)stream;

    DEBUG("");

#ifdef STREAM_DUMP_DEBUG
    if (debug_record_fd != 0) {
        debug_pcm_data_close(&debug_record_fd);
        debug_record_fd = 0;
    }
#endif

    if (in->infd > 0) {
        skt_disconnect(in->infd);
        in->infd = -1;
    }

    if (sco_dev->input && in == sco_dev->input) {
        free(in);
        sco_dev->input = NULL;
    }

    return;
}

static int adev_dump(const audio_hw_device_t *device, int fd)
{
    DEBUG("fd=%d return 0",fd);
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
    struct sco_audio_device *adev;
    pthread_mutexattr_t lock_attr;
    int ret;

    INFO("adev_open in Sco_hw module");

    if (strcmp(name, AUDIO_HARDWARE_INTERFACE) != 0) {
        ERROR("interface %s not matching [%s]", name, AUDIO_HARDWARE_INTERFACE);
        return -EINVAL;
    }

    adev = calloc(1, sizeof(struct sco_audio_device));
    if (!adev)
        return -ENOMEM;

    adev->device.common.tag = HARDWARE_DEVICE_TAG;
    adev->device.common.version = AUDIO_DEVICE_API_VERSION_CURRENT;
    adev->device.common.module = (struct hw_module_t *) module;
    adev->device.common.close = adev_close;

    // Audio HAL implementations started with AUDIO_DEVICE_API_VERSION_2_0 do not supprot this interface.
    //adev->device.get_supported_devices  = adev_get_supported_devices;
    adev->device.init_check = adev_init_check;
    adev->device.set_voice_volume = adev_set_voice_volume;
    adev->device.set_master_volume = adev_set_master_volume;
    adev->device.get_master_volume = adev_get_master_volume;
    adev->device.set_master_mute = adev_set_master_mute;
    adev->device.get_master_mute = adev_get_master_mute;
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

    adev->ctrlfd = -1;


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
        .name = "SCO Audio HW HAL",
        .author = "The Android Open Source Project",
        .methods = &hal_module_methods,
    },
};
