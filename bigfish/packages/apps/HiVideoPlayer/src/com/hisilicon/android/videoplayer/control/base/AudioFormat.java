package com.hisilicon.android.videoplayer.control.base;

public class AudioFormat
{
    private static final int FORMAT_MP2 = 0;

    private static final int FORMAT_MP3 = 1;

    private static final int FORMAT_AAC = 2;

    private static final int FORMAT_AC3 = 3;

    private static final int FORMAT_DTS = 4;

    private static final int FORMAT_VORBIS = 5;

    private static final int FORMAT_DVAUDIO = 6;

    private static final int FORMAT_WMAV1 = 7;

    private static final int FORMAT_WMAV2 = 8;

    private static final int FORMAT_MACE3 = 9;

    private static final int FORMAT_MACE6 = 10;

    private static final int FORMAT_VMDAUDIO = 11;

    private static final int FORMAT_SONIC = 12;

    private static final int FORMAT_SONIC_LS = 13;

    private static final int FORMAT_FLAC = 14;

    private static final int FORMAT_MP3ADU = 15;

    private static final int FORMAT_MP3ON4 = 16;

    private static final int FORMAT_SHORTEN = 17;

    private static final int FORMAT_ALAC = 18;

    private static final int FORMAT_WESTWOOD_SND1 = 19;

    private static final int FORMAT_GSM = 20;

    private static final int FORMAT_QDM2 = 21;

    private static final int FORMAT_COOK = 22;

    private static final int FORMAT_TRUESPEECH = 23;

    private static final int FORMAT_TTA = 24;

    private static final int FORMAT_SMACKAUDIO = 25;

    private static final int FORMAT_QCELP = 26;

    private static final int FORMAT_WAVPACK = 27;

    private static final int FORMAT_DSICINAUDIO = 28;

    private static final int FORMAT_IMC = 29;

    private static final int FORMAT_MUSEPACK7 = 30;

    private static final int FORMAT_MLP = 31;

    private static final int FORMAT_GSM_MS = 32;

    private static final int FORMAT_ATRAC3 = 33;

    private static final int FORMAT_VOXWARE = 34;

    private static final int FORMAT_APE = 35;

    private static final int FORMAT_NELLYMOSER = 36;

    private static final int FORMAT_MUSEPACK8 = 37;

    private static final int FORMAT_SPEEX = 38;

    private static final int FORMAT_WMAVOICE = 39;

    private static final int FORMAT_WMAPRO = 40;

    private static final int FORMAT_WMALOSSLESS = 41;

    private static final int FORMAT_ATRAC3P = 42;

    private static final int FORMAT_EAC3 = 43;

    private static final int FORMAT_SIPR = 44;

    private static final int FORMAT_MP1 = 45;

    private static final int FORMAT_TWINVQ = 46;

    private static final int FORMAT_TRUEHD = 47;

    private static final int FORMAT_MP4ALS = 48;

    private static final int FORMAT_ATRAC1 = 49;

    private static final int FORMAT_BINKAUDIO_RDFT = 50;

    private static final int FORMAT_BINKAUDIO_DCT = 51;

    private static final int FORMAT_DRA = 52;

    /* various PCM "codecs" */
    private static final int FORMAT_PCM = 0x100;

    private static final int FORMAT_PCM_BLURAY = 0x121;

    /* various ADPCM codecs */
    private static final int FORMAT_ADPCM = 0x130;

    /* AMR */
    private static final int FORMAT_AMR_NB = 0x160;

    private static final int FORMAT_AMR_WB = 0x161;

    private static final int FORMAT_AMR_AWB = 0x162;

    /* RealAudio codecs */
    private static final int FORMAT_RA_144 = 0x170;

    private static final int FORMAT_RA_288 = 0x171;

    /* various DPCM codecs */
    private static final int FORMAT_DPCM = 0x180;

    /* various G.7xx codecs */
    private static final int FORMAT_G711 = 0x190;

    private static final int FORMAT_G722 = 0x191;

    private static final int FORMAT_G7231 = 0x192;

    private static final int FORMAT_G726 = 0x193;

    private static final int FORMAT_G728 = 0x194;

    private static final int FORMAT_G729AB = 0x195;

    /* support multi codecs */
    private static final int FORMAT_MULTI = 0x1f0;

    private static final int FORMAT_BUTT = 0x1ff;

    public static String getFormat(int pFormatId)
    {
        String _Format = "";

        switch (pFormatId)
        {
            case FORMAT_MP2:
                _Format = "MP2";
                break;
            case FORMAT_MP3:
                _Format = "MP3";
                break;
            case FORMAT_AAC:
                _Format = "AAC";
                break;
            case FORMAT_AC3:
                _Format = "AC3";
                break;
            case FORMAT_DTS:
                _Format = "DTS";
                break;
            case FORMAT_VORBIS:
                _Format = "VORBIS";
                break;
            case FORMAT_DVAUDIO:
                _Format = "DVAUDIO";
                break;
            case FORMAT_WMAV1:
                _Format = "WMAV1";
                break;
            case FORMAT_WMAV2:
                _Format = "WMAV2";
                break;
            case FORMAT_MACE3:
                _Format = "MACE3";
                break;
            case FORMAT_MACE6:
                _Format = "MACE6";
                break;
            case FORMAT_VMDAUDIO:
                _Format = "VMDAUDIO";
                break;
            case FORMAT_SONIC:
                _Format = "SONIC";
                break;
            case FORMAT_SONIC_LS:
                _Format = "SONIC_LS";
                break;
            case FORMAT_FLAC:
                _Format = "FLAC";
                break;
            case FORMAT_MP3ADU:
                _Format = "MP3ADU";
                break;
            case FORMAT_MP3ON4:
                _Format = "MP3ON4";
                break;
            case FORMAT_SHORTEN:
                _Format = "SHORTEN";
                break;
            case FORMAT_ALAC:
                _Format = "ALAC";
                break;
            case FORMAT_WESTWOOD_SND1:
                _Format = "WESTWOOD_SND1";
                break;
            case FORMAT_GSM:
                _Format = "GSM";
                break;
            case FORMAT_QDM2:
                _Format = "QDM2";
                break;
            case FORMAT_COOK:
                _Format = "COOK";
                break;
            case FORMAT_TRUESPEECH:
                _Format = "TRUESPEECH";
                break;
            case FORMAT_TTA:
                _Format = "TTA";
                break;
            case FORMAT_SMACKAUDIO:
                _Format = "SMACKAUDIO";
                break;
            case FORMAT_QCELP:
                _Format = "QCELP";
                break;
            case FORMAT_WAVPACK:
                _Format = "WAVPACK";
                break;
            case FORMAT_DSICINAUDIO:
                _Format = "DSICINAUDIO";
                break;
            case FORMAT_IMC:
                _Format = "IMC";
                break;
            case FORMAT_MUSEPACK7:
                _Format = "MUSEPACK7";
                break;
            case FORMAT_MLP:
                _Format = "MLP";
                break;
            case FORMAT_GSM_MS:
                _Format = "GSM_MS";
                break;
            case FORMAT_ATRAC3:
                _Format = "ATRAC3";
                break;
            case FORMAT_VOXWARE:
                _Format = "VOXWARE";
                break;
            case FORMAT_APE:
                _Format = "APE";
                break;
            case FORMAT_NELLYMOSER:
                _Format = "NELLYMOSER";
                break;
            case FORMAT_MUSEPACK8:
                _Format = "MUSEPACK8";
                break;
            case FORMAT_SPEEX:
                _Format = "SPEEX";
                break;
            case FORMAT_WMAVOICE:
                _Format = "WMAVOICE";
                break;
            case FORMAT_WMAPRO:
                _Format = "WMAPRO";
                break;
            case FORMAT_WMALOSSLESS:
                _Format = "WMALOSSLESS";
                break;
            case FORMAT_ATRAC3P:
                _Format = "ATRAC3P";
                break;
            case FORMAT_EAC3:
                _Format = "EAC3";
                break;
            case FORMAT_SIPR:
                _Format = "SIPR";
                break;
            case FORMAT_MP1:
                _Format = "MP1";
                break;
            case FORMAT_TWINVQ:
                _Format = "TWINVQ";
                break;
            case FORMAT_TRUEHD:
                _Format = "TRUEHD";
                break;
            case FORMAT_MP4ALS:
                _Format = "MP4ALS";
                break;
            case FORMAT_ATRAC1:
                _Format = "ATRAC1";
                break;
            case FORMAT_BINKAUDIO_RDFT:
                _Format = "BINKAUDIO_RDFT";
                break;
            case FORMAT_BINKAUDIO_DCT:
                _Format = "BINKAUDIO_DCT";
                break;
            case FORMAT_DRA:
                _Format = "DRA";
                break;
            case FORMAT_PCM:
                _Format = "PCM";
                break;
            case FORMAT_PCM_BLURAY:
                _Format = "PCM_BLURAY";
                break;
            case FORMAT_ADPCM:
                _Format = "ADPCM";
                break;
            case FORMAT_AMR_NB:
                _Format = "AMR_NB";
                break;
            case FORMAT_AMR_WB:
                _Format = "AMR_WB";
                break;
            case FORMAT_AMR_AWB:
                _Format = "AMR_AWB";
                break;
            case FORMAT_RA_144:
                _Format = "RA_144";
                break;
            case FORMAT_RA_288:
                _Format = "RA_288";
                break;
            case FORMAT_DPCM:
                _Format = "DPCM";
                break;
            case FORMAT_G711:
                _Format = "G711";
                break;
            case FORMAT_G722:
                _Format = "G722";
                break;
            case FORMAT_G7231:
                _Format = "G7231";
                break;
            case FORMAT_G726:
                _Format = "G726";
                break;
            case FORMAT_G728:
                _Format = "G728";
                break;
            case FORMAT_G729AB:
                _Format = "G729AB";
                break;
            case FORMAT_MULTI:
                _Format = "MULTI";
                break;
            case FORMAT_BUTT:
                _Format = "BUTT";
                break;
            default:
                break;
        }

        return _Format;
    }
}
