package com.hisilicon.dlna.dmc.processor.impl;

import java.util.ArrayList;
import java.util.List;

import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;

import com.hisilicon.dlna.dmc.data.PlaylistProvider;
import com.hisilicon.dlna.dmc.data.PlaylistSQLiteHelper;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem.Type;
import com.hisilicon.multiscreen.mybox.MyApp;

public class PlaylistManager {

	public static List<PlaylistItem> getAllPlaylistItem() {
		System.out.println("Come into getAllPlaylistItem--><");
		try {
			List<PlaylistItem> result = new ArrayList<PlaylistItem>();
			Cursor itemsCursor = MyApp.getResolver().query(PlaylistProvider.PLAYLIST_ITEM_URI,
					PlaylistSQLiteHelper.PLALYLISTITEM_ALLCOLUMNS, null, null, null);
			try {
				if (itemsCursor != null && itemsCursor.moveToFirst()) {
					do {
						result.add(cursorToPlaylistItem(itemsCursor));
					} while (itemsCursor.moveToNext());
				}
			} finally {
				if (itemsCursor != null)
					itemsCursor.close();
			}
			return result;
		} catch (Exception ex) {
			return null;
		}
	}

	private static PlaylistItem cursorToPlaylistItem(Cursor cursor) {
		try {
			PlaylistItem playlistItem = new PlaylistItem();
			
			long id = cursor.getLong(cursor.getColumnIndex(PlaylistSQLiteHelper.COL_ID));
			String title = cursor.getString(cursor.getColumnIndex(PlaylistSQLiteHelper.COL_TITLE));
			String url = cursor.getString(cursor.getColumnIndex(PlaylistSQLiteHelper.COL_URL));
			String type = cursor.getString(cursor.getColumnIndex(PlaylistSQLiteHelper.COL_TYPE));
			String metadata = cursor.getString(cursor.getColumnIndex(PlaylistSQLiteHelper.COL_METADATA));
			
			playlistItem.setId(id + "");
			playlistItem.setTitle(title);
			playlistItem.setType(Type.valueOf(type));
			playlistItem.setUrl(url);
			playlistItem.setMetaData(metadata);
			
			if (playlistItem.fromLocalType()) {
				playlistItem.setUrl(playlistItem.getUrl());
			}

			return playlistItem;
		} catch (Exception ex) {
			ex.printStackTrace();
			return null;
		}
	}

	public static boolean insertPlaylistItem(PlaylistItem playlistItem) {
		if (contains(playlistItem))
			return true;
		try {
			ContentValues values = new ContentValues();
			
			values.put(PlaylistSQLiteHelper.COL_TITLE, playlistItem.getTitle());
			values.put(PlaylistSQLiteHelper.COL_URL, playlistItem.getUrl());
			values.put(PlaylistSQLiteHelper.COL_TYPE, playlistItem.getType().toString());
			values.put(PlaylistSQLiteHelper.COL_METADATA, playlistItem.getMetaData());
			
			Uri uri = MyApp.getResolver().insert(PlaylistProvider.PLAYLIST_ITEM_URI, values);
			
			if (uri == null)
				return false;
			
			String newId = uri.getQueryParameter("newid");
			playlistItem.setId(newId);
			
			return true;
		} catch (Exception ex) {
			ex.printStackTrace();
			return false;
		}
	}
	
	private static boolean contains(PlaylistItem currentItem) {
		PlaylistItem playlistItem = new PlaylistItem();
		playlistItem.setTitle(currentItem.getTitle());
		playlistItem.setType(currentItem.getType());
		playlistItem.setUrl(currentItem.getUrl());
		playlistItem.setMetaData(currentItem.getMetaData());
		
		List<PlaylistItem> playlistItems = PlaylistManager.getAllPlaylistItem();
		for (PlaylistItem item : playlistItems) {
			if (item.equals(playlistItem))
					return true;
		}
		return false;
	}

	public static boolean deletePlaylistItem(long id) {
		return 1 == MyApp.getResolver().delete(PlaylistProvider.PLAYLIST_ITEM_URI, PlaylistSQLiteHelper.COL_ID + " = ?",
				new String[] { String.valueOf(id) });
	}

	public static void clearAllPlaylistItem() {
		MyApp.getResolver().delete(PlaylistProvider.PLAYLIST_ITEM_URI, null, null);
	}

}
