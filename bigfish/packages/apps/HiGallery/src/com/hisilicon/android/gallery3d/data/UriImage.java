/*
 * Copyright (C) 2010 The Android Open Source Project
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

package com.hisilicon.android.gallery3d.data;

import com.hisilicon.android.gallery3d.app.GalleryApp;
import com.hisilicon.android.gallery3d.common.BitmapUtils;
import com.hisilicon.android.gallery3d.common.Utils;
import com.hisilicon.android.gallery3d.util.ThreadPool.CancelListener;
import com.hisilicon.android.gallery3d.util.ThreadPool.Job;
import com.hisilicon.android.gallery3d.util.ThreadPool.JobContext;

import android.database.Cursor;

import android.content.ContentResolver;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory.Options;
import android.graphics.BitmapRegionDecoder;
import android.net.Uri;
import android.os.ParcelFileDescriptor;
import android.webkit.MimeTypeMap;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.net.URI;
import java.net.URL;

public class UriImage extends MediaItem {
    private static final String TAG = "UriImage";

    private static final int STATE_INIT = 0;
    private static final int STATE_DOWNLOADING = 1;
    private static final int STATE_DOWNLOADED = 2;
    private static final int STATE_ERROR = -1;

    private final Uri mUri;
    private final String mContentType;

    private DownloadCache.Entry mCacheEntry;
//    private ParcelFileDescriptor mFileDescriptor;
    private int mState = STATE_INIT;
    private int mWidth;
    private int mHeight;
    private int mRotation;

    private GalleryApp mApplication;

    public UriImage(GalleryApp application, Path path, Uri uri) {
        super(path, nextVersionNumber());
        mUri = uri;
        mApplication = Utils.checkNotNull(application);
        mContentType = getMimeType(uri);
    }

    private String getMimeType(Uri uri) {
		//BEGIN Pictures special characters
        String extension = "";
        if (ContentResolver.SCHEME_FILE.equals(uri.getScheme())) {
             extension =MimeTypeMap.getFileExtensionFromUrl(uri.toString());
            if(extension.equals("")){
                String fileUri = uri.toString();
                int dotPos = uri.toString().lastIndexOf('.');
                if (dotPos >= 0) {
                    extension = fileUri.substring(dotPos + 1);
                }
            }
            String type = MimeTypeMap.getSingleton()
                    .getMimeTypeFromExtension(extension.toLowerCase());
            if (type != null) return type;
        }
        return extension;
		//END
    }

    @Override
    public Job<Bitmap> requestImage(int type) {
        return new BitmapJob(type);
    }

    @Override
    public Job<BitmapRegionDecoder> requestLargeImage() {
        return new RegionDecoderJob();
    }

    private void openFileOrDownloadTempFile(JobContext jc) {
        /*int state = openOrDownloadInner(jc);
        synchronized (this) {
            mState = state;
            if (mState != STATE_DOWNLOADED) {
                if (mFileDescriptor != null) {
                    Utils.closeSilently(mFileDescriptor);
                    mFileDescriptor = null;
                }
            }
            notifyAll();
        }*/
    }

    private ParcelFileDescriptor openOrDownloadInner(JobContext jc) {
        ParcelFileDescriptor mFileDescriptor = null;
        String scheme = mUri.getScheme();
        if (ContentResolver.SCHEME_CONTENT.equals(scheme)
                || ContentResolver.SCHEME_ANDROID_RESOURCE.equals(scheme)
                || ContentResolver.SCHEME_FILE.equals(scheme)) {
            try {
                if (MIME_TYPE_JPEG.equalsIgnoreCase(mContentType)) {
                    InputStream is = mApplication.getContentResolver()
                            .openInputStream(mUri);
                    mRotation = Exif.getOrientation(is);
                    Utils.closeSilently(is);
                }
                mFileDescriptor = mApplication.getContentResolver()
                        .openFileDescriptor(mUri, "r");
                if (jc.isCancelled()){
                    mState = STATE_INIT;
                    return null;
                 }
                mState = STATE_DOWNLOADED;
                return mFileDescriptor;
            } catch (FileNotFoundException e) {
                Log.w(TAG, "fail to open: " + mUri, e);
                mState =  STATE_ERROR;
                return null;
            }
        } else {
            try {
                URL url = new URI(mUri.toString()).toURL();
                mCacheEntry = mApplication.getDownloadCache().download(jc, url);
                if (jc.isCancelled()){
                    mState = STATE_INIT;
                    return null;
                 }
                if (mCacheEntry == null) {
                    Log.w(TAG, "download failed " + url);
                    mState =  STATE_ERROR;
                    return null;
                }
                if (MIME_TYPE_JPEG.equalsIgnoreCase(mContentType)) {
                    InputStream is = new FileInputStream(mCacheEntry.cacheFile);
                    mRotation = Exif.getOrientation(is);
                    Utils.closeSilently(is);
                }
                mFileDescriptor = ParcelFileDescriptor.open(
                        mCacheEntry.cacheFile, ParcelFileDescriptor.MODE_READ_ONLY);
                mState = STATE_DOWNLOADED;
                return mFileDescriptor;
            } catch (Throwable t) {
                Log.w(TAG, "download error", t);
                mState =  STATE_ERROR;
                return null;
            }
        }
    }

    private ParcelFileDescriptor prepareInputFile(JobContext jc) {
//        jc.setCancelListener(new CancelListener() {
//            public void onCancel() {
//                synchronized (this) {
//                    notifyAll();
//                }
//            }
//        });
//
//        while (true) {
//            synchronized (this) {
//                if (jc.isCancelled()) return false;
//                if (mState == STATE_INIT) {
//                    mState = STATE_DOWNLOADING;
//                    // Then leave the synchronized block and continue.
//                } else if (mState == STATE_ERROR) {
//                    return false;
//                } else if (mState == STATE_DOWNLOADED) {
//                    return true;
//                } else /* if (mState == STATE_DOWNLOADING) */ {
//                    try {
//                        wait();
//                    } catch (InterruptedException ex) {
//                        // ignored.
//                    }
//                    continue;
//                }
//            }
//            // This is only reached for STATE_INIT->STATE_DOWNLOADING
//            openFileOrDownloadTempFile(jc);
//        }
        if(jc.isCancelled()){
            return null;
        }
        return openOrDownloadInner(jc);
    }

    private class RegionDecoderJob implements Job<BitmapRegionDecoder> {
        public BitmapRegionDecoder run(JobContext jc) {
            ParcelFileDescriptor mFileDescriptor = prepareInputFile(jc);
            if (mFileDescriptor ==null) return null;
            BitmapRegionDecoder decoder = DecodeUtils.requestCreateBitmapRegionDecoder(
                    jc, mFileDescriptor.getFileDescriptor(), false);
            if(decoder!=null){
                mWidth = decoder.getWidth();
                mHeight = decoder.getHeight();
            }
            if (mFileDescriptor != null) {
                Utils.closeSilently(mFileDescriptor);
            }
            return decoder;
        }
    }

    private class BitmapJob implements Job<Bitmap> {
        private int mType;

        protected BitmapJob(int type) {
            mType = type;
        }

        public Bitmap run(JobContext jc) {
            ParcelFileDescriptor mFileDescriptor = prepareInputFile(jc);
            Bitmap bitmap = null;
            if (mFileDescriptor ==null) {
                return null;
            }
            int targetSize = LocalImage.getTargetSize(mType);
            Options options = new Options();
            options.inPreferredConfig = Config.ARGB_8888;
            options.inDither = true;
            options.inPurgeable = true;
            options.inInputShareable = false;
            options.inPreferredConfig = null;

            if((mContentType.toLowerCase().equals("image/tiff") && mContentType.toLowerCase().endsWith("tiff"))
                        || (mContentType.toLowerCase().equals("image/tif") && mContentType.toLowerCase().endsWith("tif")))
            {
                bitmap = DecodeUtils.requestDecode(jc,getTiffPath() , options, targetSize);
            }
            else
            {
                bitmap = DecodeUtils.decodeThumbnail(jc,
                        mFileDescriptor.getFileDescriptor(), options, targetSize, mType);
                if (jc.isCancelled() || bitmap == null) {
                    if (mFileDescriptor != null) {
                        Utils.closeSilently(mFileDescriptor);
                    }
                     return null;
                }

                if (mType == MediaItem.TYPE_MICROTHUMBNAIL) {
                    bitmap = BitmapUtils.resizeDownAndCropCenter(bitmap,
                            targetSize, true);
                } else {
                    bitmap = BitmapUtils.resizeDownBySideLength(bitmap,
                            targetSize, true);
                }
            }
            if (mFileDescriptor != null) {
                Utils.closeSilently(mFileDescriptor);
            }
            return bitmap;
        }
    }

    private String getTiffPath()
    {
        Cursor cursor = null;
        String filePath = null;
        String uri = mUri.toString();
        try
        {
            cursor = mApplication.getContentResolver().query(
                    Uri.parse(uri.substring(0, uri.lastIndexOf("/"))),
                    new String[] {"_data"},
                    "_id="+uri.substring(uri.lastIndexOf("/") + 1),
                    null, null);

            if (cursor != null && cursor.moveToFirst())
            {
                filePath = cursor.getString(0);
            }
            else
            {
                filePath = Uri.parse(uri.substring(0, uri.lastIndexOf("/"))).getPath();
                filePath += uri.substring(uri.lastIndexOf("/"));
            }
        }
        catch (Exception e)
        {
        }
        finally
        {
            if (cursor != null)
                cursor.close();
        }
        return filePath;
    }

    @Override
    public int getSupportedOperations() {
        int supported = SUPPORT_EDIT | SUPPORT_SETAS;
        if (isSharable()) supported |= SUPPORT_SHARE;
        if (BitmapUtils.isSupportedByRegionDecoder(mContentType)) {
            supported |= SUPPORT_FULL_IMAGE;
        }
        return supported;
    }

    private boolean isSharable() {
        // We cannot grant read permission to the receiver since we put
        // the data URI in EXTRA_STREAM instead of the data part of an intent
        // And there are issues in MediaUploader and Bluetooth file sender to
        // share a general image data. So, we only share for local file.
        return ContentResolver.SCHEME_FILE.equals(mUri.getScheme());
    }

    @Override
    public int getMediaType() {
        return MEDIA_TYPE_IMAGE;
    }

    @Override
    public Uri getContentUri() {
        return mUri;
    }

    @Override
    public MediaDetails getDetails() {
        MediaDetails details = super.getDetails();
        if (mWidth != 0 && mHeight != 0) {
            details.addDetail(MediaDetails.INDEX_WIDTH, mWidth);
            details.addDetail(MediaDetails.INDEX_HEIGHT, mHeight);
        }
        if (mContentType != null) {
            details.addDetail(MediaDetails.INDEX_MIMETYPE, mContentType);
        }
        if (ContentResolver.SCHEME_FILE.equals(mUri.getScheme())) {
            String filePath = mUri.getPath();
            details.addDetail(MediaDetails.INDEX_PATH, filePath);
            MediaDetails.extractExifInfo(details, filePath);
        }
        return details;
    }

    @Override
    public String getMimeType() {
        return mContentType;
    }

    @Override
    protected void finalize() throws Throwable {
        try {
            /*if (mFileDescriptor != null) {
                Utils.closeSilently(mFileDescriptor);
            }*/
        } finally {
            super.finalize();
        }
    }

    @Override
    public int getWidth() {
        return 0;
    }

    @Override
    public int getHeight() {
        return 0;
    }

    @Override
    public int getRotation() {
        return mRotation;
    }
}
