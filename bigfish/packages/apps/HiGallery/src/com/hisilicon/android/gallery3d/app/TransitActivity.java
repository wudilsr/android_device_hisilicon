package com.hisilicon.android.gallery3d.app;


import android.app.Activity;
import android.content.ContentUris;
import android.content.Intent;
import android.content.UriMatcher;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.provider.MediaStore.Images;
import android.provider.MediaStore.Images.ImageColumns;


public class TransitActivity extends Activity {
    private static final String TAG = "TransitActivity";
    private static final boolean DEBUG = false;
    private final Uri mBaseUri = Images.Media.EXTERNAL_CONTENT_URI;
    private static final int NO_MATCH = -1;
    private final UriMatcher mUriMatcher = new UriMatcher(NO_MATCH);
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d(DEBUG, "TransitActivity", "onCreate");
        // Jump to the gallery shows the current image
        String curPath = getIntent().getData().getPath();
        Log.d(DEBUG, TAG, "file curPath = " + curPath+" getIntent().getData()="+getIntent().getData());
        String filePath = getFilePath(getIntent());
        Log.d(DEBUG, TAG, "content filePath="+filePath);
        if(!filePath.equals("")){
            curPath = filePath;
        }
        Intent intent = new Intent();
        intent.setClassName("com.hisilicon.android.gallery3d",
                "com.hisilicon.android.gallery3d.list.ImageFileListService");
        intent.putExtra("path", "");
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.setDataAndType(Uri.parse("file://"+curPath), "image/*");
        startService(intent);
        TransitActivity.this.finish();
    }

    public String getFilePath(Intent intent){
        String filePath = "";
        long personid = -1;
        Uri uri = Uri.parse(getIntent().getData().toString());
        mUriMatcher.addURI(MediaStore.AUTHORITY,"external/images/media/#", 0);
        if(mUriMatcher.match(uri)!=-1){
            personid = ContentUris.parseId(uri);
        }
        if(personid!=-1){
            String mWhereClause = ImageColumns._ID + " = ?";
            Cursor cursor = this.getContentResolver().query(mBaseUri,
                     new String[] { ImageColumns.DATA }, mWhereClause,
                     new String[] { String.valueOf(personid) }, null);
            if (cursor != null && cursor.moveToNext()) {
                filePath = cursor.getString(0);
                if (filePath != null && !filePath.equals("")) {
                   return filePath;
                }
            }
        }
        return filePath;
    }
}
