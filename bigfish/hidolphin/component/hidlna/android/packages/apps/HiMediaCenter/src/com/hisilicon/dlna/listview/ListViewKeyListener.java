package com.hisilicon.dlna.listview;

import android.view.KeyEvent;

public interface ListViewKeyListener
{
    void onListViewKeyDown(int keyCode, KeyEvent keyEvent);

    void onListViewKeyUp(int keyCode, KeyEvent keyEvent);

    void onListViewKeyMultiple(int keyCode, int repeatCount, KeyEvent event);
}
