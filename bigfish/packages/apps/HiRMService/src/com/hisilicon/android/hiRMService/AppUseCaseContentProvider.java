package com.hisilicon.android.hiRMService;

import android.content.ContentProvider;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.net.Uri;

public class AppUseCaseContentProvider extends ContentProvider {

    public static final String AUTOHORITY = "com.hisilicon.hirmservice.appprovider";
    public static final String REQUEST_GET_ALL = "getAll";
    public static final int RESULT_GET_ALL = 1;

    private static final UriMatcher sMatcher;
    private static DBAdapter adapter;

    static {
        sMatcher = new UriMatcher(UriMatcher.NO_MATCH);
        sMatcher.addURI(AUTOHORITY, REQUEST_GET_ALL, RESULT_GET_ALL);
    }

    @Override
    public int delete(Uri arg0, String arg1, String[] arg2) {
        return 0;
    }

    @Override
    public String getType(Uri arg0) {
        return null;
    }

    @Override
    public Uri insert(Uri arg0, ContentValues arg1) {
        return null;
    }

    @Override
    public boolean onCreate() {
        adapter = new DBAdapter(getContext());
        adapter.open();
        return true;
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String selection,
            String[] selectionArgs, String sortOrder) {
        int mat = sMatcher.match(uri);
        switch (mat) {

        case RESULT_GET_ALL:
            Cursor cursor = adapter.getQueryCursor(projection, selection,
                    selectionArgs, sortOrder);
            cursor.setNotificationUri(getContext().getContentResolver(), uri);
            return cursor;
        }
        return null;
    }

    @Override
    public int update(Uri arg0, ContentValues arg1, String arg2, String[] arg3) {
        return 0;
    }

}