package com.hisilicon.android;

import android.os.Parcel;
import android.os.Parcelable;

public class DispFmt
{
    public       int is_support_3d                    = 0;
    public       int ENC_FMT_1080P_60                 = 0;
    public       int ENC_FMT_1080P_50                 = 1;
    public       int ENC_FMT_1080P_30                 = 2;
    public       int ENC_FMT_1080P_25                 = 3;
    public       int ENC_FMT_1080P_24                 = 4;
    public       int ENC_FMT_1080i_60                 = 5;
    public       int ENC_FMT_1080i_50                 = 6;
    public       int ENC_FMT_720P_60                  = 7;
    public       int ENC_FMT_720P_50                  = 8;
    public       int ENC_FMT_576P_50                  = 9;
    public       int ENC_FMT_480P_60                  = 10;
    public       int ENC_FMT_PAL                      = 11;
    public       int ENC_FMT_PAL_N                    = 12;
    public       int ENC_FMT_PAL_Nc                   = 13;
    public       int ENC_FMT_NTSC                     = 14;
    public       int ENC_FMT_NTSC_J                   = 15;
    public       int ENC_FMT_NTSC_PAL_M               = 16;
    public       int ENC_FMT_SECAM_SIN                = 17;
    public       int ENC_FMT_SECAM_COS                = 18;

    public       int ENC_FMT_1080P_24_FRAME_PACKING   = 19;
    public       int ENC_FMT_720P_60_FRAME_PACKING    = 20;
    public       int ENC_FMT_720P_50_FRAME_PACKING    = 21;
    public       int ENC_FMT_861D_640X480_60          = 22;

    public       int ENC_FMT_VESA_800X600_60          = 23;
    public       int ENC_FMT_VESA_1024X768_60         = 24;
    public       int ENC_FMT_VESA_1280X720_60         = 25;
    public       int ENC_FMT_VESA_1280X800_60         = 26;
    public       int ENC_FMT_VESA_1280X1024_60        = 27;
    public       int ENC_FMT_VESA_1360X768_60         = 28;
    public       int ENC_FMT_VESA_1366X768_60         = 29;
    public       int ENC_FMT_VESA_1400X1050_60        = 30;
    public       int ENC_FMT_VESA_1440X900_60         = 31;
    public       int ENC_FMT_VESA_1440X900_60_RB      = 32;
    public       int ENC_FMT_VESA_1600X900_60_RB      = 33;
    public       int ENC_FMT_VESA_1600X1200_60        = 34;
    public       int ENC_FMT_VESA_1680X1050_60        = 35;
    public       int ENC_FMT_VESA_1680X1050_60_RB     = 36;
    public       int ENC_FMT_VESA_1920X1080_60        = 37;
    public       int ENC_FMT_VESA_1920X1200_60        = 38;
    public       int ENC_FMT_VESA_1920X1440_60        = 39;
    public       int ENC_FMT_VESA_2048X1152_60        = 40;
    public       int ENC_FMT_VESA_2560X1440_60_RB     = 41;
    public       int ENC_FMT_VESA_2560X1600_60_RB     = 42;

    public       int ENC_FMT_3840X2160_24             = 0x100;
    public       int ENC_FMT_3840X2160_25             = 0x101;
    public       int ENC_FMT_3840X2160_30             = 0x102;
    public       int ENC_FMT_3840X2160_50             = 0x103;
    public       int ENC_FMT_3840X2160_60             = 0x104;

    public       int ENC_FMT_4096X2160_24             = 0x105;
    public       int ENC_FMT_4096X2160_25             = 0x106;
    public       int ENC_FMT_4096X2160_30             = 0x107;
    public       int ENC_FMT_4096X2160_50             = 0x108;
    public       int ENC_FMT_4096X2160_60             = 0x109;

    public       int ENC_FMT_3840X2160_23_976         = 0x10a;
    public       int ENC_FMT_3840X2160_29_97          = 0x10b;
    public       int ENC_FMT_720P_59_94               = 0x10c;
    public       int ENC_FMT_1080P_59_94              = 0x10d;
    public       int ENC_FMT_1080P_29_97              = 0x10e;
    public       int ENC_FMT_1080P_23_976             = 0x10f;
    public       int ENC_FMT_1080i_59_94              = 0x110;

    public DispFmt() {}

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

    public static final Parcelable.Creator<DispFmt> CREATOR = new Parcelable.Creator<DispFmt>() {
        /**
         * Return a new rectangle from the data in the specified parcel.
         */
        public DispFmt createFromParcel(Parcel in) {
            DispFmt r = new DispFmt();
            r.readFromParcel(in);
            return r;
        }

        /**
         * Return an array of rectangles of the specified size.
         */
        public DispFmt[] newArray(int size) {
            return new DispFmt[size];
        }
    };
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
