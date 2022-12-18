package com.hisilicon.android;

import android.os.Parcel;
import android.os.Parcelable;

public class DispFmt
{
    /** Whether 3D is supported or not. */
    public       int is_support_3d                    = 0;
    /** Whether display format 1080p60hz is supported or not. */
    public       int ENC_FMT_1080P_60                 = 0;
    /** Whether display format 1080p50hz is supported or not. */
    public       int ENC_FMT_1080P_50                 = 1;
    /** Whether display format 1080p30hz is supported or not. */
    public       int ENC_FMT_1080P_30                 = 2;
    /** Whether display format 1080p25hz is supported or not. */
    public       int ENC_FMT_1080P_25                 = 3;
    /** Whether display format 1080p24hz is supported or not. */
    public       int ENC_FMT_1080P_24                 = 4;
    /** Whether display format 1080i60hz is supported or not. */
    public       int ENC_FMT_1080i_60                 = 5;
    /** Whether display format 1080i50hz is supported or not. */
    public       int ENC_FMT_1080i_50                 = 6;
    /** Whether display format 720p60hz is supported or not. */
    public       int ENC_FMT_720P_60                  = 7;
    /** Whether display format 720p50hz is supported or not. */
    public       int ENC_FMT_720P_50                  = 8;
    /** Whether display format 576p50hz is supported or not. */
    public       int ENC_FMT_576P_50                  = 9;
    /** Whether display format 480p60hz is supported or not. */
    public       int ENC_FMT_480P_60                  = 10;
    /** Whether display format BDGHIPAL is supported or not. */
    public       int ENC_FMT_PAL                      = 11;
    /** Whether display format (N)PAL is supported or not. */
    public       int ENC_FMT_PAL_N                    = 12;
    /** Whether display format (Nc)PAL is supported or not. */
    public       int ENC_FMT_PAL_Nc                   = 13;
    /** Whether display format (M)NTSC is supported or not. */
    public       int ENC_FMT_NTSC                     = 14;
    /** Whether display format NTSC-J is supported or not. */
    public       int ENC_FMT_NTSC_J                   = 15;
    /** Whether display format (M)PAL is supported or not. */
    public       int ENC_FMT_NTSC_PAL_M               = 16;
    /** Whether display format SECAM_SIN is supported or not. */
    public       int ENC_FMT_SECAM_SIN                = 17;
    /** Whether display format SECAM_COS is supported or not. */
    public       int ENC_FMT_SECAM_COS                = 18;

    /** Whether display format 1080p24hz frame packing is supported or not. */
    public       int ENC_FMT_1080P_24_FRAME_PACKING   = 19;
    /** Whether display format 720p60hz frame packing is supported or not. */
    public       int ENC_FMT_720P_60_FRAME_PACKING    = 20;
    /** Whether display format 720p50hz frame packing is supported or not. */
    public       int ENC_FMT_720P_50_FRAME_PACKING    = 21;

    /** Whether display format 861D 640x480 60hz is supported or not. */
    public       int ENC_FMT_861D_640X480_60          = 22;
    /** Whether display format VESA 800x600 60hz is supported or not. */
    public       int ENC_FMT_VESA_800X600_60          = 23;
    /** Whether display format VESA 1024x768 60hz is supported or not. */
    public       int ENC_FMT_VESA_1024X768_60         = 24;
    /** Whether display format VESA 1280x720 60hz is supported or not. */
    public       int ENC_FMT_VESA_1280X720_60         = 25;
    /** Whether display format VESA 1280x800 60hz is supported or not. */
    public       int ENC_FMT_VESA_1280X800_60         = 26;
    /** Whether display format VESA 1280x1024 60hz is supported or not. */
    public       int ENC_FMT_VESA_1280X1024_60        = 27;
    /** Whether display format VESA 1360x768 60hz is supported or not. */
    public       int ENC_FMT_VESA_1360X768_60         = 28;
    /** Whether display format VESA 1366x768 60hz is supported or not. */
    public       int ENC_FMT_VESA_1366X768_60         = 29;
    /** Whether display format VESA 1400x1050 60hz is supported or not. */
    public       int ENC_FMT_VESA_1400X1050_60        = 30;
    /** Whether display format VESA 1440x900 60hz is supported or not. */
    public       int ENC_FMT_VESA_1440X900_60         = 31;
    /** Whether display format VESA 1440x900 60hz RB is supported or not. */
    public       int ENC_FMT_VESA_1440X900_60_RB      = 32;
    /** Whether display format VESA 1600x900 60hz RB is supported or not. */
    public       int ENC_FMT_VESA_1600X900_60_RB      = 33;
    /** Whether display format VESA 1600x1200 60hz is supported or not. */
    public       int ENC_FMT_VESA_1600X1200_60        = 34;
    /** Whether display format VESA 1680x1050 60hz is supported or not. */
    public       int ENC_FMT_VESA_1680X1050_60        = 35;
    /** Whether display format VESA 1680x1050 60hz RB is supported or not. */
    public       int ENC_FMT_VESA_1680X1050_60_RB     = 36;
    /** Whether display format VESA 1920x1080 60hz is supported or not. */
    public       int ENC_FMT_VESA_1920X1080_60        = 37;
    /** Whether display format VESA 1920x1200 60hz is supported or not. */
    public       int ENC_FMT_VESA_1920X1200_60        = 38;
    /** Whether display format VESA 1920x1440 60hz is supported or not. */
    public       int ENC_FMT_VESA_1920X1440_60        = 39;
    /** Whether display format VESA 2048x1152 60hz is supported or not. */
    public       int ENC_FMT_VESA_2048X1152_60        = 40;
    /** Whether display format VESA 2560x1440 60hz RB is supported or not. */
    public       int ENC_FMT_VESA_2560X1440_60_RB     = 41;
    /** Whether display format VESA 2560x1600 60hz RB is supported or not. */
    public       int ENC_FMT_VESA_2560X1600_60_RB     = 42;

    /** Whether display format 3840x2160p 24hz is supported or not. */
    public       int ENC_FMT_3840X2160_24             = 0x100;
    /** Whether display format 3840x2160p 25hz is supported or not. */
    public       int ENC_FMT_3840X2160_25             = 0x101;
    /** Whether display format 3840x2160p 30hz is supported or not. */
    public       int ENC_FMT_3840X2160_30             = 0x102;
    /** Whether display format 3840x2160p 50hz is supported or not. */
    public       int ENC_FMT_3840X2160_50             = 0x103;
    /** Whether display format 3840x2160p 60hz is supported or not. */
    public       int ENC_FMT_3840X2160_60             = 0x104;
    /** Whether display format 4096x2160p 24hz is supported or not. */
    public       int ENC_FMT_4096X2160_24             = 0x105;
    /** Whether display format 4096x2160p 25hz is supported or not. */
    public       int ENC_FMT_4096X2160_25             = 0x106;
    /** Whether display format 4096x2160p 30hz is supported or not. */
    public       int ENC_FMT_4096X2160_30             = 0x107;
    /** Whether display format 4096x2160p 50hz is supported or not. */
    public       int ENC_FMT_4096X2160_50             = 0x108;
    /** Whether display format 4096x2160p 60hz is supported or not. */
    public       int ENC_FMT_4096X2160_60             = 0x109;

    /** Whether display format 3840x2160p 23.976hz is supported or not. */
    public       int ENC_FMT_3840X2160_23_976         = 0x10a;
    /** Whether display format 3840x2160p 29.97hz is supported or not. */
    public       int ENC_FMT_3840X2160_29_97          = 0x10b;
    /** Whether display format 720p59.94hz is supported or not. */
    public       int ENC_FMT_720P_59_94               = 0x10c;
    /** Whether display format 1080p59.94hz is supported or not. */
    public       int ENC_FMT_1080P_59_94              = 0x10d;
    /** Whether display format 1080p29.97hz is supported or not. */
    public       int ENC_FMT_1080P_29_97              = 0x10e;
    /** Whether display format 1080p23.976hz is supported or not. */
    public       int ENC_FMT_1080P_23_976             = 0x10f;
    /** Whether display format 1080i59.94hz is supported or not. */
    public       int ENC_FMT_1080i_59_94              = 0x110;

    /** Constructs a new empty DispFmt. */
    public DispFmt() {}

    /** Constructs a new DispFmt with given data. */
    public DispFmt(
             int is_support_3d,
             int ENC_FMT_1080P_60,
             int ENC_FMT_1080P_50,
             int ENC_FMT_1080P_30,
             int ENC_FMT_1080P_25,
             int ENC_FMT_1080P_24,
             int ENC_FMT_1080i_60,
             int ENC_FMT_1080i_50,
             int ENC_FMT_720P_60,
             int ENC_FMT_720P_50,
             int ENC_FMT_576P_50,
             int ENC_FMT_480P_60,
             int ENC_FMT_PAL,
             int ENC_FMT_PAL_N,
             int ENC_FMT_PAL_Nc,
             int ENC_FMT_NTSC,
             int ENC_FMT_NTSC_J,
             int ENC_FMT_NTSC_PAL_M,
             int ENC_FMT_SECAM_SIN,
             int ENC_FMT_SECAM_COS,
             int ENC_FMT_1080P_24_FRAME_PACKING,
             int ENC_FMT_720P_60_FRAME_PACKING,
             int ENC_FMT_720P_50_FRAME_PACKING,
             int ENC_FMT_861D_640X480_60,
             int ENC_FMT_VESA_800X600_60,
             int ENC_FMT_VESA_1024X768_60,
             int ENC_FMT_VESA_1280X720_60,
             int ENC_FMT_VESA_1280X800_60,
             int ENC_FMT_VESA_1280X1024_60,
             int ENC_FMT_VESA_1360X768_60,
             int ENC_FMT_VESA_1366X768_60,
             int ENC_FMT_VESA_1400X1050_60,
             int ENC_FMT_VESA_1440X900_60,
             int ENC_FMT_VESA_1440X900_60_RB,
             int ENC_FMT_VESA_1600X900_60_RB,
             int ENC_FMT_VESA_1600X1200_60,
             int ENC_FMT_VESA_1680X1050_60,
             int ENC_FMT_VESA_1680X1050_60_RB,
             int ENC_FMT_VESA_1920X1080_60,
             int ENC_FMT_VESA_1920X1200_60,
             int ENC_FMT_VESA_1920X1440_60,
             int ENC_FMT_VESA_2048X1152_60,
             int ENC_FMT_VESA_2560X1440_60_RB,
             int ENC_FMT_VESA_2560X1600_60_RB,
             int ENC_FMT_3840X2160_24,
             int ENC_FMT_3840X2160_25,
             int ENC_FMT_3840X2160_30,
             int ENC_FMT_3840X2160_50,
             int ENC_FMT_3840X2160_60,
             int ENC_FMT_4096X2160_24,
             int ENC_FMT_4096X2160_25,
             int ENC_FMT_4096X2160_30,
             int ENC_FMT_4096X2160_50,
             int ENC_FMT_4096X2160_60,
             int ENC_FMT_3840X2160_23_976,
             int ENC_FMT_3840X2160_29_97,
             int ENC_FMT_720P_59_94,
             int ENC_FMT_1080P_59_94,
             int ENC_FMT_1080P_29_97,
             int ENC_FMT_1080P_23_976,
             int ENC_FMT_1080i_59_94
             )
    {
        this.is_support_3d    = is_support_3d;
        this.ENC_FMT_1080P_60 = ENC_FMT_1080P_60;
        this.ENC_FMT_1080P_50 = ENC_FMT_1080P_50;
        this.ENC_FMT_1080P_30 = ENC_FMT_1080P_30;
        this.ENC_FMT_1080P_25 = ENC_FMT_1080P_25;
        this.ENC_FMT_1080P_24 = ENC_FMT_1080P_24;
        this.ENC_FMT_1080i_60 = ENC_FMT_1080i_60;
        this.ENC_FMT_1080i_50 = ENC_FMT_1080i_50;
        this.ENC_FMT_720P_60 = ENC_FMT_720P_60;
        this.ENC_FMT_720P_50 = ENC_FMT_720P_50;
        this.ENC_FMT_576P_50 = ENC_FMT_576P_50;
        this.ENC_FMT_480P_60 = ENC_FMT_480P_60;
        this.ENC_FMT_PAL = ENC_FMT_PAL;
        this.ENC_FMT_PAL_N = ENC_FMT_PAL_N;
        this.ENC_FMT_PAL_Nc = ENC_FMT_PAL_Nc;
        this.ENC_FMT_NTSC = ENC_FMT_NTSC;
        this.ENC_FMT_NTSC_J = ENC_FMT_NTSC_J;
        this.ENC_FMT_NTSC_PAL_M = ENC_FMT_NTSC_PAL_M;
        this.ENC_FMT_SECAM_SIN = ENC_FMT_SECAM_SIN;
        this.ENC_FMT_SECAM_COS = ENC_FMT_SECAM_COS;
        this.ENC_FMT_1080P_24_FRAME_PACKING = ENC_FMT_1080P_24_FRAME_PACKING;
        this.ENC_FMT_720P_60_FRAME_PACKING = ENC_FMT_720P_60_FRAME_PACKING;
        this.ENC_FMT_720P_50_FRAME_PACKING = ENC_FMT_720P_50_FRAME_PACKING;
        this.ENC_FMT_861D_640X480_60 = ENC_FMT_861D_640X480_60;
        this.ENC_FMT_VESA_800X600_60 = ENC_FMT_VESA_800X600_60;
        this.ENC_FMT_VESA_1024X768_60 = ENC_FMT_VESA_1024X768_60;
        this.ENC_FMT_VESA_1280X720_60 = ENC_FMT_VESA_1280X720_60;
        this.ENC_FMT_VESA_1280X800_60 = ENC_FMT_VESA_1280X800_60;
        this.ENC_FMT_VESA_1280X1024_60 = ENC_FMT_VESA_1280X1024_60;
        this.ENC_FMT_VESA_1360X768_60 = ENC_FMT_VESA_1360X768_60;
        this.ENC_FMT_VESA_1366X768_60 = ENC_FMT_VESA_1366X768_60;
        this.ENC_FMT_VESA_1400X1050_60 = ENC_FMT_VESA_1400X1050_60;
        this.ENC_FMT_VESA_1440X900_60 = ENC_FMT_VESA_1440X900_60;
        this.ENC_FMT_VESA_1440X900_60_RB = ENC_FMT_VESA_1440X900_60_RB;
        this.ENC_FMT_VESA_1600X900_60_RB = ENC_FMT_VESA_1600X900_60_RB;
        this.ENC_FMT_VESA_1600X1200_60 = ENC_FMT_VESA_1600X1200_60;

        this.ENC_FMT_VESA_1680X1050_60        = ENC_FMT_VESA_1680X1050_60;
        this.ENC_FMT_VESA_1680X1050_60_RB     = ENC_FMT_VESA_1680X1050_60_RB;
        this.ENC_FMT_VESA_1920X1080_60        = ENC_FMT_VESA_1920X1080_60;
        this.ENC_FMT_VESA_1920X1200_60        = ENC_FMT_VESA_1920X1200_60;

        this.ENC_FMT_VESA_1920X1440_60        = ENC_FMT_VESA_1920X1440_60;
        this.ENC_FMT_VESA_2048X1152_60        = ENC_FMT_VESA_2048X1152_60;
        this.ENC_FMT_VESA_2560X1440_60_RB     = ENC_FMT_VESA_2560X1440_60_RB;
        this.ENC_FMT_VESA_2560X1600_60_RB     = ENC_FMT_VESA_2560X1600_60_RB;

        this.ENC_FMT_3840X2160_24 = ENC_FMT_3840X2160_24;
        this.ENC_FMT_3840X2160_25 = ENC_FMT_3840X2160_25;
        this.ENC_FMT_3840X2160_30 = ENC_FMT_3840X2160_30;
        this.ENC_FMT_3840X2160_50 = ENC_FMT_3840X2160_50;
        this.ENC_FMT_3840X2160_60 = ENC_FMT_3840X2160_60;
        this.ENC_FMT_4096X2160_24 = ENC_FMT_4096X2160_24;
        this.ENC_FMT_4096X2160_25 = ENC_FMT_4096X2160_25;
        this.ENC_FMT_4096X2160_30 = ENC_FMT_4096X2160_30;
        this.ENC_FMT_4096X2160_50 = ENC_FMT_4096X2160_50;
        this.ENC_FMT_4096X2160_60 = ENC_FMT_4096X2160_60;

        this.ENC_FMT_3840X2160_23_976 = ENC_FMT_3840X2160_23_976;
        this.ENC_FMT_3840X2160_29_97 = ENC_FMT_3840X2160_29_97;
        this.ENC_FMT_720P_59_94 = ENC_FMT_720P_59_94;
        this.ENC_FMT_1080P_59_94 = ENC_FMT_1080P_59_94;
        this.ENC_FMT_1080P_29_97 = ENC_FMT_1080P_29_97;
        this.ENC_FMT_1080P_23_976 = ENC_FMT_1080P_23_976;
        this.ENC_FMT_1080i_59_94 = ENC_FMT_1080i_59_94;
    }

    /**
     * Flatten this object in to a Parcel.
     * <p>
     * Flatten this object in to a Parcel.<br>
     * <br>
     * @param out The Parcel in which the object should be written.
     * @param flags Additional flags about how the object should be written.
     */
    public void writeToParcel(Parcel out, int flags)
    {
        out.writeInt(is_support_3d);
        out.writeInt(ENC_FMT_1080P_60);
        out.writeInt(ENC_FMT_1080P_50);
        out.writeInt(ENC_FMT_1080P_30);
        out.writeInt(ENC_FMT_1080P_25);
        out.writeInt(ENC_FMT_1080P_24);
        out.writeInt(ENC_FMT_1080i_60);
        out.writeInt(ENC_FMT_1080i_50);
        out.writeInt(ENC_FMT_720P_60);
        out.writeInt(ENC_FMT_720P_50);
        out.writeInt(ENC_FMT_576P_50);
        out.writeInt(ENC_FMT_480P_60);
        out.writeInt(ENC_FMT_PAL);
        out.writeInt(ENC_FMT_PAL_N);
        out.writeInt(ENC_FMT_PAL_Nc);
        out.writeInt(ENC_FMT_NTSC);
        out.writeInt(ENC_FMT_NTSC_J);
        out.writeInt(ENC_FMT_NTSC_PAL_M);
        out.writeInt(ENC_FMT_SECAM_SIN);
        out.writeInt(ENC_FMT_SECAM_COS);
        out.writeInt(ENC_FMT_1080P_24_FRAME_PACKING);
        out.writeInt(ENC_FMT_720P_60_FRAME_PACKING);
        out.writeInt(ENC_FMT_720P_50_FRAME_PACKING);
        out.writeInt(ENC_FMT_861D_640X480_60);
        out.writeInt(ENC_FMT_VESA_800X600_60);
        out.writeInt(ENC_FMT_VESA_1024X768_60);
        out.writeInt(ENC_FMT_VESA_1280X720_60);
        out.writeInt(ENC_FMT_VESA_1280X800_60);
        out.writeInt(ENC_FMT_VESA_1280X1024_60);
        out.writeInt(ENC_FMT_VESA_1360X768_60);
        out.writeInt(ENC_FMT_VESA_1366X768_60);
        out.writeInt(ENC_FMT_VESA_1400X1050_60);
        out.writeInt(ENC_FMT_VESA_1440X900_60);
        out.writeInt(ENC_FMT_VESA_1440X900_60_RB);
        out.writeInt(ENC_FMT_VESA_1600X900_60_RB);
        out.writeInt(ENC_FMT_VESA_1600X1200_60);

        out.writeInt(ENC_FMT_VESA_1680X1050_60);
        out.writeInt(ENC_FMT_VESA_1680X1050_60_RB);
        out.writeInt(ENC_FMT_VESA_1920X1080_60);
        out.writeInt(ENC_FMT_VESA_1920X1200_60);

        out.writeInt(ENC_FMT_VESA_1920X1440_60);
        out.writeInt(ENC_FMT_VESA_2048X1152_60);
        out.writeInt(ENC_FMT_VESA_2560X1440_60_RB);
        out.writeInt(ENC_FMT_VESA_2560X1600_60_RB);

        out.writeInt(ENC_FMT_3840X2160_24);
        out.writeInt(ENC_FMT_3840X2160_25);
        out.writeInt(ENC_FMT_3840X2160_30);
        out.writeInt(ENC_FMT_3840X2160_50);
        out.writeInt(ENC_FMT_3840X2160_60);
        out.writeInt(ENC_FMT_4096X2160_24);
        out.writeInt(ENC_FMT_4096X2160_25);
        out.writeInt(ENC_FMT_4096X2160_30);
        out.writeInt(ENC_FMT_4096X2160_50);
        out.writeInt(ENC_FMT_4096X2160_60);

        out.writeInt(ENC_FMT_3840X2160_23_976);
        out.writeInt(ENC_FMT_3840X2160_29_97);
        out.writeInt(ENC_FMT_720P_59_94);
        out.writeInt(ENC_FMT_1080P_59_94);
        out.writeInt(ENC_FMT_1080P_29_97);
        out.writeInt(ENC_FMT_1080P_23_976);
        out.writeInt(ENC_FMT_1080i_59_94);
    }

    /** A public CREATOR field that generates instances of DispFmt class from a Parcel. */
    public static final Parcelable.Creator<DispFmt> CREATOR = new Parcelable.Creator<DispFmt>() {
        /**
         * Create a new instance of DispFmt class from the given Parcel.
         * <p>
         * Create a new instance of DispFmt class, instantiating it from the given Parcel.<br>
         * <br>
         * @param in The Parcel to read the object's data from.
         * @return Returns a new instance of DispFmt class.
         */
        public DispFmt createFromParcel(Parcel in) {
            DispFmt r = new DispFmt();
            r.readFromParcel(in);
            return r;
        }

        /**
         * Create a new array of DispFmt class.
         * <p>
         * Create a new array of DispFmt class with the specified size.<br>
         * <br>
         * @param size Size of the array.
         * @return Returns an array of DispFmt class.
         */
        public DispFmt[] newArray(int size) {
            return new DispFmt[size];
        }
    };

    /**
     * Expand this object from a Parcel.
     * <p>
     * Expand this object from a Parcel.<br>
     * <br>
     * @param in The Parcel from which the object should be read.
     */
    public void readFromParcel(Parcel in)
    {
        is_support_3d = in.readInt();
        ENC_FMT_1080P_60 = in.readInt();
        ENC_FMT_1080P_50 = in.readInt();
        ENC_FMT_1080P_30 = in.readInt();
        ENC_FMT_1080P_25 = in.readInt();
        ENC_FMT_1080P_24 = in.readInt();
        ENC_FMT_1080i_60 = in.readInt();
        ENC_FMT_1080i_50 = in.readInt();
        ENC_FMT_720P_60 = in.readInt();
        ENC_FMT_720P_50 = in.readInt();
        ENC_FMT_576P_50 = in.readInt();
        ENC_FMT_480P_60 = in.readInt();
        ENC_FMT_PAL = in.readInt();
        ENC_FMT_PAL_N = in.readInt();
        ENC_FMT_PAL_Nc = in.readInt();
        ENC_FMT_NTSC = in.readInt();
        ENC_FMT_NTSC_J = in.readInt();
        ENC_FMT_NTSC_PAL_M = in.readInt();
        ENC_FMT_SECAM_SIN = in.readInt();
        ENC_FMT_SECAM_COS = in.readInt();
        ENC_FMT_1080P_24_FRAME_PACKING = in.readInt();
        ENC_FMT_720P_60_FRAME_PACKING = in.readInt();
        ENC_FMT_720P_50_FRAME_PACKING = in.readInt();
        ENC_FMT_861D_640X480_60 = in.readInt();
        ENC_FMT_VESA_800X600_60 = in.readInt();
        ENC_FMT_VESA_1024X768_60 = in.readInt();
        ENC_FMT_VESA_1280X720_60 = in.readInt();
        ENC_FMT_VESA_1280X800_60 = in.readInt();
        ENC_FMT_VESA_1280X1024_60 = in.readInt();
        ENC_FMT_VESA_1360X768_60 = in.readInt();
        ENC_FMT_VESA_1366X768_60 = in.readInt();
        ENC_FMT_VESA_1400X1050_60 = in.readInt();
        ENC_FMT_VESA_1440X900_60 = in.readInt();
        ENC_FMT_VESA_1440X900_60_RB = in.readInt();
        ENC_FMT_VESA_1600X900_60_RB = in.readInt();
        ENC_FMT_VESA_1600X1200_60 = in.readInt();

        ENC_FMT_VESA_1680X1050_60 = in.readInt();
        ENC_FMT_VESA_1680X1050_60_RB = in.readInt();
        ENC_FMT_VESA_1920X1080_60 = in.readInt();
        ENC_FMT_VESA_1920X1200_60 = in.readInt();

        ENC_FMT_VESA_1920X1440_60 = in.readInt();
        ENC_FMT_VESA_2048X1152_60 = in.readInt();
        ENC_FMT_VESA_2560X1440_60_RB = in.readInt();
        ENC_FMT_VESA_2560X1600_60_RB = in.readInt();

        ENC_FMT_3840X2160_24 = in.readInt();
        ENC_FMT_3840X2160_25 = in.readInt();
        ENC_FMT_3840X2160_30 = in.readInt();
        ENC_FMT_3840X2160_50 = in.readInt();
        ENC_FMT_3840X2160_60 = in.readInt();
        ENC_FMT_4096X2160_24 = in.readInt();
        ENC_FMT_4096X2160_25 = in.readInt();
        ENC_FMT_4096X2160_30 = in.readInt();
        ENC_FMT_4096X2160_50 = in.readInt();
        ENC_FMT_4096X2160_60 = in.readInt();

        ENC_FMT_3840X2160_23_976 = in.readInt();
        ENC_FMT_3840X2160_29_97 = in.readInt();
        ENC_FMT_720P_59_94 = in.readInt();
        ENC_FMT_1080P_59_94 = in.readInt();
        ENC_FMT_1080P_29_97 = in.readInt();
        ENC_FMT_1080P_23_976 = in.readInt();
        ENC_FMT_1080i_59_94 = in.readInt();
    }
}
