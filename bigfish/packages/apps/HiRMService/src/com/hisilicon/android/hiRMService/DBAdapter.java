package com.hisilicon.android.hiRMService;

import java.util.ArrayList;
import java.util.List;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DBAdapter {

    private final int DATABASE_VERSION = 1;
    private final String DATABASE_NAME = "AppUseCase.db";
    private final String DATABASE_TABLE = "app_use_case";
    private final String DATABASE_CREATE = "create table app_use_case"
            + "( _id integer primary key autoincrement, "
            + "package_name text unique not null, "
            + "launch_count integer not null, " + "usage_time integer);";

    private final String KEY_NAME = "package_name";
    private final String KEY_COUNT = "launch_count";
    private final String KEY_TIME = "usage_time";

    private DatabaseHelper DBHelper;
    private SQLiteDatabase db;

    public DBAdapter(Context context) {
        DBHelper = new DatabaseHelper(context);
    }

    private class DatabaseHelper extends SQLiteOpenHelper {

        DatabaseHelper(Context context) {
            super(context, DATABASE_NAME, null, DATABASE_VERSION);
        }

        @Override
        public void onCreate(SQLiteDatabase db) {
            try {
                db.execSQL(DATABASE_CREATE);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            db.execSQL("DROP TABLE IF EXISTS contacts");
            onCreate(db);
        }
    }

    /**
     * 打开数据库
     *
     * @return
     * @throws SQLException
     */
    public DBAdapter open() throws SQLException {
        db = DBHelper.getWritableDatabase();
        return this;
    }

    /**
     * 关闭数据库
     */
    public void close() {
        if (null != DBHelper)
            DBHelper.close();
    }

    /**
     * 保存应用使用情况
     *
     * @param changeStats
     */
    public void saveStats(List<AppEntity> changeStats) {
        for (AppEntity entity : changeStats) {
            AppEntity local_entity = getEntity(entity.packageName);
            if (null == local_entity) {
                insertEntity(entity);
            } else {
                local_entity.launchCount += entity.launchCount;
                local_entity.usageTime += entity.usageTime;
                updateEntity(local_entity);
            }
        }
    }

    /**
     * 插入一条信息
     *
     * @param entity
     * @return
     */
    public long insertEntity(AppEntity entity) {
        ContentValues values = new ContentValues();
        values.put(KEY_NAME, entity.packageName);
        values.put(KEY_COUNT, entity.launchCount);
        values.put(KEY_TIME, entity.usageTime);
        return db.insert(DATABASE_TABLE, null, values);
    }

    /**
     * 根据包名删除信息
     *
     * @param appName
     * @return
     */
    public boolean deleteEntity(String appName) {
        String where = KEY_NAME + "='" + appName + "'";
        return db.delete(DATABASE_TABLE, where, null) > 0;
    }

    /**
     * 修改数据库信息
     *
     * @param entity
     * @return
     */
    public boolean updateEntity(AppEntity entity) {
        ContentValues values = new ContentValues();
        values.put(KEY_NAME, entity.packageName);
        values.put(KEY_COUNT, entity.launchCount);
        values.put(KEY_TIME, entity.usageTime);
        int result = db.update(DATABASE_TABLE, values, KEY_NAME + "='"
                + entity.packageName + "'", null);
        return result > 0;
    }

    /**
     * 根据包名查询信息
     *
     * @param appName
     * @return
     * @throws SQLException
     */
    public AppEntity getEntity(String appName) throws SQLException {
        AppEntity entity = null;
        String where = KEY_NAME + "='" + appName + "'";
        Cursor mCursor = db.query(DATABASE_TABLE, null, where, null, null,
                null, null, null);
        if (mCursor != null && mCursor.moveToFirst()) {
            entity = getEntity(mCursor);
        }
        return entity;
    }

    /**
     * 根据游标查询信息
     *
     * @param mCursor
     * @return
     */
    private AppEntity getEntity(Cursor mCursor) {
        AppEntity entity = new AppEntity();
        entity.packageName = mCursor
                .getString(mCursor.getColumnIndex(KEY_NAME));
        entity.launchCount = mCursor.getInt(mCursor.getColumnIndex(KEY_COUNT));
        entity.usageTime = mCursor.getInt(mCursor.getColumnIndex(KEY_TIME));
        return entity;
    }

    /**
     * 查询所有信息
     *
     * @return
     */
    public ArrayList<AppEntity> getAllEntity() {
        ArrayList<AppEntity> entitys = null;
        Cursor mCursor = db.query(DATABASE_TABLE, null, null, null, null, null,
                null);
        if (mCursor != null) {
            entitys = new ArrayList<AppEntity>();
            while (mCursor.moveToNext()) {
                AppEntity entity = getEntity(mCursor);
                entitys.add(entity);
            }
        }
        return entitys;
    }

    /**
     * ContentProvider获取查询所有的游标
     *
     * @param projection
     * @param selection
     * @param selectionArgs
     * @param sortOrder
     * @return
     */
    public Cursor getQueryCursor(String[] projection, String selection,
            String[] selectionArgs, String sortOrder) {
        Cursor mCursor = db.query(DATABASE_TABLE, projection, selection,
                selectionArgs, null, null, null);
        return mCursor;
    }

}