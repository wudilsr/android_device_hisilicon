package com.hisilicon.android.mediaplayer;

/**
  * Argument Description of Invoke <br>
  */
public class HiMediaPlayerDefine
{
    /**
        Enum of decode mode
        <br>
    */
    public enum ENUM_VIDEO_FRAME_MODE_ARG
    {
        /**
          Decode all<br>
          Value:0<br>
        */
        ENUM_INVOKE_DECODE_NORMAL,
        /**
           Decode IP frame<br>
           Value:1<br>
         */
        ENUM_INVOKE_DECODE_IP,
        /**
           Decode I frame<br>
           Value:2<br>
         */
        ENUM_INVOKE_DECODE_I,
        /**
           Decode all frames except the first B frame sequence behind I frames<br>
           Value:3<br>
         */
        ENUM_INVOKE_DECODE_DROP_INVALID_B,
        /**
           invalid mode<br>
           Value:4<br>
         */
        ENUM_INVOKE_DECODE_BUTT
    };

    /**
        Conversion mode of AspectRatio
        <br>
    */
    public enum ENUM_VIDEO_CVRS_ARG
    {
        /**
           Display full screen<br>
           Value:0<br>
         */
        ENUM_INVOKE_RATIO_IGNORE,
        /**
           Letterbox mode<br>
           Value:1<br>
         */
        ENUM_INVOKE_RATIO_LETTERBOX
    };

    /**
      Defines the mode of audio channels<br>
      <br>
    */
    public enum ENUM_AUDIO_CHANNEL_MODE_ARG
    {
        /**
           Stereo<br>
           Value:0<br>
         */
        ENUM_INVOKE_AUDIO_CHANNEL_STEREO,
        /**
           Data is output after being mixed in the audio-left channel and audio-right channel.<br>
           Value:1<br>
         */
        ENUM_INVOKE_AUDIO_CHANNEL_DOUBLE_MONO,
        /**
           The audio-left channel and audio-right channel output the data of the audio-left channel.<br>
           Value:2<br>
         */
        ENUM_INVOKE_AUDIO_CHANNEL_DOUBLE_LEFT,
        /**
           The audio-left channel and audio-right channel output the data of the audio-right channel.<br>
           Value:3<br>
         */
        ENUM_INVOKE_AUDIO_CHANNEL_DOUBLE_RIGHT,
        /**
           Data is output after being exchanged in the audio-left channel and audio-right channel.<br>
           Value:4<br>
         */
        ENUM_INVOKE_AUDIO_CHANNEL_EXCHANGE,
        /**
           Only the data in the audio-right channel is output.<br>
           Value:5<br>
         */
        ENUM_INVOKE_AUDIO_CHANNEL_ONLY_RIGHT,
        /**
           Only the data in the audio-left channel is output.<br>
           Value:6<br>
         */
        ENUM_INVOKE_AUDIO_CHANNEL_ONLY_LEFT,
        /**
           Mute.<br>
           Value:7<br>
         */
        ENUM_INVOKE_AUDIO_CHANNEL_MUTED,
        /**
           invalid value.<br>
           Value:8<br>
         */
        ENUM_INVOKE_AUDIO_CHANNEL_BUTT
    };

    /**
        Defines the style of subtitle style
        <br>
    */
    public enum ENUM_SUB_FONT_STYLE_ARG
    {
        /**
           Value:0<br>
        */
        ENUM_INVOKE_SUB_FONT_STYLE_NORMAL,
        /**
           Value:1<br>
        */
        ENUM_INVOKE_SUB_FONT_STYLE_SHADOW,
        /**
           Value:2<br>
        */
        ENUM_INVOKE_SUB_FONT_STYLE_HOLLOW,
        /**
           Value:3<br>
        */
        ENUM_INVOKE_SUB_FONT_STYLE_EMBOLDEN,
        /**
           Value:4<br>
        */
        ENUM_INVOKE_SUB_FONT_STYLE_ITALTIC,
        /**
           Value:5<br>
        */
        ENUM_INVOKE_SUB_FONT_STYLE_STROKE,
    }

    /**
        Defines playlist type
        <br>
    */
    public enum ENUM_PLAYLIST_TYPE_ARG
    {
           /**
           Value:0<br>
           */
           ENUM_INVOKE_M3U8,
           /**
           Value:1<br>
           */
           ENUM_INVOKE_M3U9,
           /**
           Value:2<br>
           */
           ENUM_INVOKE_NO_PLAYLIST,
    }

    /**
        Defines the Z order
        <br>
    */
    public enum ENUM_VIDEO_Z_ORDER_ARG
    {
        /**
            Move to the top
            <br>
            Value:0<br>
        */
        ENUM_LAYER_ZORDER_MOVETOP,
        /**
            Move up
            <br>
            Value:1<br>
        */
        ENUM_LAYER_ZORDER_MOVEUP,
        /**
            Move to the bottom
            <br>
            Value:2<br>
        */
        ENUM_LAYER_ZORDER_MOVEBOTTOM,
        /**
            Move down
            <br>
            Value:3<br>
        */
        ENUM_LAYER_ZORDER_MOVEDOWN,
        /**
            Invalid value
            <br>
            Value:4<br>
        */
        ENUM_LAYER_ZORDER_BUTT
    }

    /**
        Defines if cut 3D file subtitle
        <br>
    */
    public enum ENUM_3D_SUBTITLE_CUT_METHOD_ARG
    {
        /**
           Value:0<br>
        */
        ENUM_CUT_3D_FILE_SUBTITLE,
        /**
           Value:1<br>
        */
        ENUM_NOT_CUT_3D_FILE_SUBTITLE
    }
    /**
        Defines DOLBY type
        <br>
    */
    public enum ENUM_DOLBYINFO_ARG
    {
        /**
           Value:0<br>
        */
        ENUM_DOLBY,
        /**
           Value:1<br>
        */
        ENUM_DOLBYPLUS
    }

    /**
        Defines subtitle alignment mode
        <br>
    */
    public enum ENUM_SUB_FONT_ALIGNMENT_ARG
    {
        /**
           Value:0<br>
        */
        ENUM_SUBTITLE_LEFT,
        /**
           Value:1<br>
        */
        ENUM_SUBTITLE_CENTER,
        /**
           Value:2<br>
        */
        ENUM_SUBTITLE_RIGHT
    }

    /**
        Audio mute define
        <br>
    */
    public enum ENUM_AUDIO_MUTE_STATUS_ARG
    {
        /**
           Value:0<br>
        */
        ENUM_AUDIO_NOT_MUTE,
        /**
           Value:1<br>
        */
        ENUM_AUDIO_MUTE
    }

    /**
        Sync mode defines
        <br>
    */
    public enum ENUM_SYNC_MODE_ARG
    {
        /**
            Free playing without synchronization
            <br>
            Value:0<br>
        */
        ENUM_SYNC_REF_NONE,
        /**
            Audio-based synchronization
            <br>
            Value:1<br>
        */
        ENUM_SYNC_REF_AUDIO,
        /**
            Video-based synchronization
            <br>
            Value:2<br>
        */
        ENUM_SYNC_REF_VIDEO,
        /**
            Program clock reference (PCR)-based synchronization
            <br>
            Value:3<br>
        */
        ENUM_SYNC_REF_PCR,
        /**
            Program clock reference (SCR)-based synchronization
            <br>
            Value:4<br>
        */
        ENUM_SYNC_REF_SCR,
        /**
            invalid value
            <br>
            Value:5<br>
        */
        ENUM_SYNC_REF_BUTT
    }

    /**
        Freeze mode define
        <br>
    */
    public enum ENUM_VIDEO_FREEZE_MODE_ARG
    {
        /**
            Display last frame
            <br>
            Value:0<br>
        */
        ENUM_VIDEO_FREEZE_MODE_LAST,
        /**
            Display black frame
            <br>
            Value:1<br>
        */
        ENUM_VIDEO_FREEZE_MODE_BLACK
    }

    /**
       Stereo type define
       <br>
    */
    public enum ENUM_STEREOVIDEO_TYPE_ARG
    {
        /**
           Value:0<br>
        */
        ENUM_STEREOVIDEO_2D,
        /**
           Value:1<br>
        */
        ENUM_STEREOVIDEO_SBS,
        /**
           Value:2<br>
        */
        ENUM_STEREOVIDEO_TAB
    }

    /**
        Video output strategy
        <br>
        Description:ENUM_STEREOVIDEO_STRATEGY_3D_MASK can use with ENUM_STEREOVIDEO_STRATEGY_ADAPT_MASK,
        ENUM_STEREOVIDEO_STRATEGY_2D_MASK and ENUM_STEREOVIDEO_STRATEGY_24FPS_MASK by '|'
    */

    /**
       Video encode format
       <br>
    */
    public class DEFINE_VIDEO_ENCODING_FORMAT
    {
        public final static int ENUM_FORMAT_VIDEO_MPEG2 = 0;
        public final static int ENUM_FORMAT_VIDEO_MPEG4 = 1;
        public final static int ENUM_FORMAT_VIDEO_AVS = 2;
        public final static int ENUM_FORMAT_VIDEO_H263 = 3;
        public final static int ENUM_FORMAT_VIDEO_H264 = 4;
        public final static int ENUM_FORMAT_VIDEO_REAL8 = 5;
        public final static int ENUM_FORMAT_VIDEO_REAL9 = 6;
        public final static int ENUM_FORMAT_VIDEO_VC1 = 7;
        public final static int ENUM_FORMAT_VIDEO_VP6 = 8;
        public final static int ENUM_FORMAT_VIDEO_VP6F = 9;
        public final static int ENUM_FORMAT_VIDEO_VP6A = 10;
        public final static int ENUM_FORMAT_VIDEO_MJPEG = 11;
        public final static int ENUM_FORMAT_VIDEO_SORENSON = 12;
        public final static int ENUM_FORMAT_VIDEO_DIVX3 = 13;
        public final static int ENUM_FORMAT_VIDEO_RAW = 14;
        public final static int ENUM_FORMAT_VIDEO_JPEG = 15;
        public final static int ENUM_FORMAT_VIDEO_VP8 = 16;
        public final static int ENUM_FORMAT_VIDEO_MSMPEG4V1 = 17;
        public final static int ENUM_FORMAT_VIDEO_MSMPEG4V2 = 18;
        public final static int ENUM_FORMAT_VIDEO_MSVIDEO1 = 19;
        public final static int ENUM_FORMAT_VIDEO_WMV1 = 20;
        public final static int ENUM_FORMAT_VIDEO_WMV2 = 21;
        public final static int ENUM_FORMAT_VIDEO_RV10 = 22;
        public final static int ENUM_FORMAT_VIDEO_RV20 = 23;
        public final static int ENUM_FORMAT_VIDEO_SVQ1 = 24;
        public final static int ENUM_FORMAT_VIDEO_SVQ3 = 25;
        public final static int ENUM_FORMAT_VIDEO_H261 = 26;
        public final static int ENUM_FORMAT_VIDEO_VP3 = 27;
        public final static int ENUM_FORMAT_VIDEO_VP5 = 28;
        public final static int ENUM_FORMAT_VIDEO_CINEPAK = 29;
        public final static int ENUM_FORMAT_VIDEO_INDEO2 = 30;
        public final static int ENUM_FORMAT_VIDEO_INDEO3 = 31;
        public final static int ENUM_FORMAT_VIDEO_INDEO4 = 32;
        public final static int ENUM_FORMAT_VIDEO_INDEO5 = 33;
        public final static int ENUM_FORMAT_VIDEO_MJPEGB = 34;
        public final static int ENUM_FORMAT_VIDEO_MVC = 35;
        public final static int ENUM_FORMAT_VIDOE_HEVC = 36;
        public final static int ENUM_FORMAT_VIDEO_DV = 37;
        public final static int ENUM_FORMAT_VIDEO_BUTT = 38;
    }

    /**
       Audio encode format
       <br>
    */
        public class DEFINE_AUDIO_ENCODING_FORMAT
        {
        public final static int DEFINE_FORMAT_AUDIO_MP2 = 0;
        public final static int DEFINE_FORMAT_AUDIO_MP3 = 1;
        public final static int DEFINE_FORMAT_AUDIO_AAC = 2;
        public final static int DEFINE_FORMAT_AUDIO_AC3 = 3;
        public final static int DEFINE_FORMAT_AUDIO_DTS = 4;
        public final static int DEFINE_FORMAT_AUDIO_VORBIS = 5;
        public final static int DEFINE_FORMAT_AUDIO_DVAUDIO = 6;
        public final static int DEFINE_FORMAT_AUDIO_WMAV1 = 7;
        public final static int DEFINE_FORMAT_AUDIO_WMAV2 = 8;
        public final static int DEFINE_FORMAT_AUDIO_MACE3 = 9;
        public final static int DEFINE_FORMAT_AUDIO_MACE6 = 10;
        public final static int DEFINE_FORMAT_AUDIO_VMDAUDIO = 11;
        public final static int DEFINE_FORMAT_AUDIO_SONIC = 12;
        public final static int DEFINE_FORMAT_AUDIO_SONIC_LS = 13;
        public final static int DEFINE_FORMAT_AUDIO_FLAC = 14;
        public final static int DEFINE_FORMAT_AUDIO_MP3ADU = 15;
        public final static int DEFINE_FORMAT_AUDIO_MP3ON4 = 16;
        public final static int DEFINE_FORMAT_AUDIO_SHORTEN = 17;
        public final static int DEFINE_FORMAT_AUDIO_ALAC = 18;
        public final static int DEFINE_FORMAT_AUDIO_WESTWOOD_SND1 = 19;
        public final static int DEFINE_FORMAT_AUDIO_GSM = 20;
        public final static int DEFINE_FORMAT_AUDIO_QDM2 = 21;
        public final static int DEFINE_FORMAT_AUDIO_COOK = 22;
        public final static int DEFINE_FORMAT_AUDIO_TRUESPEECH = 23;
        public final static int DEFINE_FORMAT_AUDIO_TTA = 24;
        public final static int DEFINE_FORMAT_AUDIO_SMACKAUDIO = 25;
        public final static int DEFINE_FORMAT_AUDIO_QCELP = 26;
        public final static int DEFINE_FORMAT_AUDIO_WAVPACK = 27;
        public final static int DEFINE_FORMAT_AUDIO_DSICINAUDIO = 28;
        public final static int DEFINE_FORMAT_AUDIO_IMC = 29;
        public final static int DEFINE_FORMAT_AUDIO_MUSEPACK7 = 30;
        public final static int DEFINE_FORMAT_AUDIO_MLP = 31;
        public final static int DEFINE_FORMAT_AUDIO_GSM_MS = 32;
        public final static int DEFINE_FORMAT_AUDIO_ATRAC3 = 33;
        public final static int DEFINE_FORMAT_AUDIO_VOXWARE = 34;
        public final static int DEFINE_FORMAT_AUDIO_APE = 35;
        public final static int DEFINE_FORMAT_AUDIO_NELLYMOSER = 36;
        public final static int DEFINE_FORMAT_AUDIO_MUSEPACK8 = 37;
        public final static int DEFINE_FORMAT_AUDIO_SPEEX = 38;
        public final static int DEFINE_FORMAT_AUDIO_WMAVOICE = 39;
        public final static int DEFINE_FORMAT_AUDIO_WMAPRO = 40;
        public final static int DEFINE_FORMAT_AUDIO_WMALOSSLESS = 41;
        public final static int DEFINE_FORMAT_AUDIO_ATRAC3P = 42;
        public final static int DEFINE_FORMAT_AUDIO_EAC3 = 43;
        public final static int DEFINE_FORMAT_AUDIO_SIPR = 44;
        public final static int DEFINE_FORMAT_AUDIO_MP1 = 45;
        public final static int DEFINE_FORMAT_AUDIO_TWINVQ = 46;
        public final static int DEFINE_FORMAT_AUDIO_TRUEHD = 47;
        public final static int DEFINE_FORMAT_AUDIO_MP4ALS = 48;
        public final static int DEFINE_FORMAT_AUDIO_ATRAC1 = 49;
        public final static int DEFINE_FORMAT_AUDIO_BINKAUDIO_RDFT = 50;
        public final static int DEFINE_FORMAT_AUDIO_BINKAUDIO_DCT = 51;
        public final static int DEFINE_FORMAT_AUDIO_DRA = 52;

        public final static int DEFINE_FORMAT_AUDIO_PCM = 0x100;
        public final static int DEFINE_FORMAT_AUDIO_PCM_BLURAY = 0x121;
        public final static int DEFINE_FORMAT_AUDIO_ADPCM = 0x130;
        public final static int DEFINE_FORMAT_AUDIO_AMR_NB = 0x160;
        public final static int DEFINE_FORMAT_AUDIO_AMR_WB = 0x161;
        public final static int DEFINE_FORMAT_AUDIO_AMR_AWB = 0x162;
        public final static int DEFINE_FORMAT_AUDIO_RA_144 = 0x170;
        public final static int DEFINE_FORMAT_AUDIO_RA_288 = 0x171;
        public final static int DEFINE_FORMAT_AUDIO_DPCM = 0x180;
        public final static int DEFINE_FORMAT_AUDIO_G711 = 0x190;
        public final static int DEFINE_FORMAT_AUDIO_G722 = 0x191;
        public final static int DEFINE_FORMAT_AUDIO_G7231 = 0x192;
        public final static int DEFINE_FORMAT_AUDIO_G726 = 0x193;
        public final static int DEFINE_FORMAT_AUDIO_G728 = 0x194;
        public final static int DEFINE_FORMAT_AUDIO_G729AB = 0x195;
        public final static int DEFINE_FORMAT_AUDIO_MULTI = 0x1f0;
        public final static int DEFINE_FORMAT_AUDIO_BUTT = 0x1ff;
        }

    /**
       subtitle format
       <br>
    */
        public class DEFINE_SUBT_FORMAT
    {
        /**
        text subtitle
        */
        public final static int DEFINE_FORMAT_SUBT_ASS = 0x0;
        /**
        text subtitle
        */
        public final static int DEFINE_FORMAT_SUBT_LRC = 0x1;
        /**
        text subtitle
        */
        public final static int DEFINE_FORMAT_SUBT_SRT = 0x2;
        /**
        text subtitle
        */
        public final static int DEFINE_FORMAT_SUBT_SMI = 0x3;
        /**
        text subtitle
        */
        public final static int DEFINE_FORMAT_SUBT_SUB = 0x4;
        /**
        text subtitle
        */
        public final static int DEFINE_FORMAT_SUBT_TXT = 0x5;
        /**
        picture subtitle
        */
        public final static int DEFINE_FORMAT_SUBT_HDMV_PGS = 0x6;
        /**
        picture subtitle
        */
        public final static int DEFINE_FORMAT_SUBT_DVB_SUB = 0x7;
        /**
        picture subtitle
        */
        public final static int DEFINE_FORMAT_SUBT_DVD_SUB = 0x8;
        /**
        unsupport sub type
        */
        public final static int DEFINE_FORMAT_SUBT_BUTT = 0x9;
    }

    /**
       subtitle encode format
       <br>
    */
        public class DEFINE_SUBT_ENCODE_FORMAT
    {
        public final static int DEFINE_ENCODE_FORMAT_SUBT_AUTO = 0;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_BIG5 = 1;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_UTF8 = 2;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_1_Western_Europe = 3;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_2_Central_Europe = 4;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_3_Southern_Europe = 5;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_4_Nordic = 6;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_5_Slavic = 7;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_6_Arabic = 8;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_7_Greek = 9;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_8_Hebrew = 10;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_9_Turkish = 11;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_10_Germanic = 12;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_11_Thai = 13;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_13_Baltic = 14;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_14_Celtic = 15;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_15_Western_Europe = 16;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_ISO8859_16_Southeastern_Europe = 17;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_UNICODE_16LE_Universal_Character_Set = 18;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_UNICODE_16BE_Universal_Character_Set = 19;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_GBK_Chinese = 20;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_CP1250_Central_Europe = 21;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_CP1251_Slavic = 22;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_CP1252_German = 23;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_CP1253_Greek = 24;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_CP1254_Turkish = 25;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_CP1255_Hebrew = 26;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_CP1256_Arabic = 27;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_CP1257_Baltic = 28;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_CP1258_Vietnamese = 29;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_CP874_Thai = 30;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_UNICODE_32LE_Universal_Character_Set = 31;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_UNICODE_32BE_Universal_Character_Set = 32;
        public final static int DEFINE_ENCODE_FORMAT_SUBT_CP949_Korean = 33;
    }

    /**
       network event<br>
    */
        public class DEFINE_NETWORK_EVENT
        {
            public final static int DEFINE_NETWORK_ERROR_UNKNOW = 0;
            public final static int DEFINE_NETWORK_ERROR_CONNECT_FAILED = 1;
            public final static int DEFINE_NETWORK_ERROR_TIMEOUT = 2;
            public final static int DEFINE_NETWORK_ERROR_DISCONNECT= 3;
            public final static int DEFINE_NETWORK_ERROR_RESOURCE_NOT_FOUND = 4;
            public final static int DEFINE_NETWORK_NORMAL = 5;

        }

    /**
    adaptive output, if the TV supports 3D, and the file is MVC file, output mode is set to 3D mode <br>
    */
    public final static int DEFINE_STEREOVIDEO_STRATEGY_ADAPT_MASK = 0x0001;
    /**
    output mode is set to 2D output<br>
    */
    public final static int DEFINE_STEREOVIDEO_STRATEGY_2D_MASK = 0x0002;
    /**
    output mode is forced to 3D output mode<br>
    */
    public final static int DEFINE_STEREOVIDEO_STRATEGY_3D_MASK = 0x0004;
    /**
    if it is 24 fps stream and TV support 24 frame mode, then forced TV 24 frame rate output mode<br>
    */
    public final static int DEFINE_STEREOVIDEO_STRATEGY_24FPS_MASK = 0x0008;
}