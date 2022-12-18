package com.hisilicon.dlna.dmc.data;

import android.content.ContentProvider;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.util.Log;

public class PlaylistProvider extends ContentProvider {
	private static final String AUTHORITY = "com.hisilicon.native.dmc.data.playlistprovider";
	public static final Uri PLAYLIST_ITEM_URI = Uri.parse("content://" + AUTHORITY + "/playlist_item");
	private static final int PLAYLIST_ITEM = 1;

	private PlaylistSQLiteHelper dbPlaylistHelper;

	private static final UriMatcher uriMatcher;
	private static final String TAG = PlaylistProvider.class.getName();
	
	static {
		uriMatcher = new UriMatcher(UriMatcher.NO_MATCH);
		uriMatcher.addURI(AUTHORITY, "playlist_item", PLAYLIST_ITEM);
	}

	@Override
	public int delete(Uri uri, String selection, String[] selectionArgs) {
		Log.e(TAG, "update database");
		switch (uriMatcher.match(uri)) {
		case PLAYLIST_ITEM: {
			Log.i(TAG, "Delete item, id = " + selectionArgs[0]);
			SQLiteDatabase database = dbPlaylistHelper.getWritableDatabase();
			int deleted = -1;
			try {
				deleted = database.delete(PlaylistSQLiteHelper.TABLE_PLAYLIST_ITEMS, selection, selectionArgs);
				Log.i(TAG, "Delete item count = " + deleted);
			} finally {
				if (database != null)
					database.close();
			}

			return deleted;
		}
		}
		return -1;
	}

	@Override
	public String getType(Uri uri) {
		return String.valueOf(uriMatcher.match(uri));
	}

	@Override
	public Uri insert(Uri uri, ContentValues values) {
		Log.e(TAG, "insert database");
		switch (uriMatcher.match(uri)) {
		case PLAYLIST_ITEM: {
			Log.i(TAG, "Insert playlist item " + values.toString());
			SQLiteDatabase database = dbPlaylistHelper.getWritableDatabase();
			try {
				long newId = database.insert(PlaylistSQLiteHelper.TABLE_PLAYLIST_ITEMS, null, values);
				return Uri.parse(PLAYLIST_ITEM_URI.toString() + "/?newid=" + newId);
			} finally {
				if (database != null)
					database.close();
			}
		}
		default:
			return null;
		}
	}

	@Override
	public int bulkInsert(Uri uri, ContentValues[] values) {
		Log.e(TAG, "bulk insert");
		switch (uriMatcher.match(uri)) {
		case PLAYLIST_ITEM: {
			Log.i(TAG, "Insert list of item playlist item " + values.toString());
			int insertCount = 0;
			SQLiteDatabase database = dbPlaylistHelper.getWritableDatabase();
			try {
				database.beginTransaction();
				try {
					for (ContentValues cv : values) {
						long newID = database.insertOrThrow(PlaylistSQLiteHelper.TABLE_PLAYLIST_ITEMS, null, cv);
						if (newID <= 0) {
							break;
						} else {
							++insertCount;
						}
					}
					if (insertCount == values.length)
						database.setTransactionSuccessful();
				} catch (Exception ex) {
					ex.printStackTrace();
				} finally {
					database.endTransaction();
				}
			} finally {
				if (database != null)
					database.close();
			}
			return insertCount;
		}
		default:
			return 0;
		}
	}

	@Override
	public boolean onCreate() {
		dbPlaylistHelper = new PlaylistSQLiteHelper(getContext());
		return true;
	}

	@Override
	public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs, String sortOrder) {
		Cursor result = null;
		switch (uriMatcher.match(uri)) {
		case PLAYLIST_ITEM: {
			Log.i(TAG, "query all playlist item, selection = " + selection);
			SQLiteDatabase database = dbPlaylistHelper.getReadableDatabase();
			result = database.query(PlaylistSQLiteHelper.TABLE_PLAYLIST_ITEMS, projection, selection, selectionArgs,
					null, null, null);
			break;
		}
		default:
			break;
		}
		return result;
	}

	@Override
	public int update(Uri uri, ContentValues values, String selection, String[] selectionArgs) {
		Log.e(TAG, "update database");
		int count = -1;
		switch (uriMatcher.match(uri)) {
		case PLAYLIST_ITEM: {
			Log.i(TAG, "UpdateItem = " + values.toString());
			SQLiteDatabase database = dbPlaylistHelper.getWritableDatabase();
			try {
				count = database.update(PlaylistSQLiteHelper.TABLE_PLAYLIST_ITEMS, values, selection, selectionArgs);
			} finally {
				if (database != null)
					database.close();
			}
			break;
		}
		default:
			break;
		}
		return count;
	}
}
