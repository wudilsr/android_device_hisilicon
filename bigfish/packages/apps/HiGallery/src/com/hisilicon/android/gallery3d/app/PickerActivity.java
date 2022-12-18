/*
 * Copyright (C) 2011 The Android Open Source Project
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

package com.hisilicon.android.gallery3d.app;

import com.hisilicon.android.gallery3d.R;
import com.hisilicon.android.gallery3d.ui.GLRoot;
import com.hisilicon.android.gallery3d.ui.GLRootView;
import com.hisilicon.android.gallery3d.util.GalleryUtils;

import android.os.Bundle;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;

public class PickerActivity extends AbstractGalleryActivity
        implements OnClickListener {

    public static final String KEY_ALBUM_PATH = "album-path";
    private GLRootView glRootView;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // We show the picker in two ways. One smaller screen we use a full
        // screen window with an action bar. On larger screen we use a dialog.
        boolean isDialog = getResources().getBoolean(R.bool.picker_is_dialog);

        if (!isDialog) {
            requestWindowFeature(Window.FEATURE_ACTION_BAR);
            requestWindowFeature(Window.FEATURE_ACTION_BAR_OVERLAY);
        }

        setContentView(R.layout.dialog_picker);

        if (isDialog) {
            // In dialog mode, we don't have the action bar to show the
            // "cancel" action, so we show an additional "cancel" button.
            View view = findViewById(R.id.cancel);
            view.setOnClickListener(this);
            view.setVisibility(View.VISIBLE);

            // We need this, otherwise the view will be dimmed because it
            // is "behind" the dialog.
            ((GLRootView) findViewById(R.id.gl_root_view)).setZOrderOnTop(true);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.pickup, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == R.id.action_cancel) {
            finish();
            return true;
        }
        return false;
    }

    @Override
    public void onBackPressed() {
        // send the back event to the top sub-state
        GLRoot root = getGLRoot();
        root.lockRenderThread();
        try {
            getStateManager().getTopState().onBackPressed();
        } finally {
            root.unlockRenderThread();
        }
    }

    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.cancel) finish();
    }

    // BEGIN: focus from remote control to glRootView keydown distributed
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (getGLRoot() != null) {
            if (keyCode == KeyEvent.KEYCODE_DPAD_DOWN
                    && !GalleryUtils.isGLRootFocus) {
                glRootView = (GLRootView) getGLRoot();
                glRootView.setFocusable(true);
                glRootView.requestFocus();
            }
        }
        // if ActionBar drop-down menu.size() == 0 else reurn true
        if (keyCode == KeyEvent.KEYCODE_MENU) {
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }
}
