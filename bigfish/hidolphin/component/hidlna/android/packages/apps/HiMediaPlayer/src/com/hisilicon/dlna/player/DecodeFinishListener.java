package com.hisilicon.dlna.player;

import android.graphics.Bitmap;

import com.hisilicon.dlna.player.DecodeImageThread.DecodeError;

public interface DecodeFinishListener
{
    public void onDecodeFinish(Bitmap bitmap, ImageInfo info, DecodeError error);
}
