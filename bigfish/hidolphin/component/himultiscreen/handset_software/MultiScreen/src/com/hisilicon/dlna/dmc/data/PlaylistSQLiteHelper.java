package com.hisilicon.dlna.dmc.data;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class PlaylistSQLiteHelper extends SQLiteOpenHelper {

	public static final String TABLE_PLAYLIST_ITEMS = "PlaylistItems";
	public static final String COL_ID = "_id";
	public static final String COL_TITLE = "title";
	public static final String COL_URL = "url";
	public static final String COL_TYPE = "type";
	public static final String COL_METADATA = "metadata";

	private static final String DATABASE_NAME = "playlists.db";
	private static final int DATABASE_VERSION = 1;

	private static final String DATABASE_CREATE_PLAYLIST_ITEM = "create table " + TABLE_PLAYLIST_ITEMS + "( " + COL_ID
			+ " integer primary key autoincrement, " + COL_TITLE + " text not null, " + COL_URL + " text not null, "
			+ COL_TYPE + " text not null, " + COL_METADATA + " text not null);";

	public static String[] PLALYLISTITEM_ALLCOLUMNS = { COL_ID, COL_TITLE, COL_URL, COL_TYPE, COL_METADATA };

	public PlaylistSQLiteHelper(Context context) {
		super(context, DATABASE_NAME, null, DATABASE_VERSION);
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
		db.execSQL(DATABASE_CREATE_PLAYLIST_ITEM);
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		db.execSQL("DROP TABLE IF EXISTS " + TABLE_PLAYLIST_ITEMS);
		onCreate(db);
	}

}
