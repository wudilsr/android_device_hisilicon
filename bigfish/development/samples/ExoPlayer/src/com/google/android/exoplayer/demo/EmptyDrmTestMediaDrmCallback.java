package com.google.android.exoplayer.demo;

import java.util.UUID;

import android.media.MediaDrm.KeyRequest;
import android.media.MediaDrm.ProvisionRequest;

import com.google.android.exoplayer.drm.MediaDrmCallback;

public class EmptyDrmTestMediaDrmCallback implements MediaDrmCallback {
    private final byte[] emptyResponse = new byte[1];

    @Override
    public byte[] executeProvisionRequest(UUID uuid, ProvisionRequest request)
            throws Exception {
        // TODO Auto-generated method stub
        return emptyResponse;
    }

    @Override
    public byte[] executeKeyRequest(UUID uuid, KeyRequest request)
            throws Exception {
        // TODO Auto-generated method stub
        return emptyResponse;
    }

}
