/**
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

package com.hisilicon.android.inputmethod.latin;

import android.util.Log;

public class ComposingStateManager {
    private static final String TAG = ComposingStateManager.class.getSimpleName();
    private static final ComposingStateManager sInstance = new ComposingStateManager();
    private boolean mAutoCorrectionIndicatorOn;
    private boolean mIsComposing;

    public static ComposingStateManager getInstance() {
        return sInstance;
    }

    private ComposingStateManager() {
        mAutoCorrectionIndicatorOn = false;
        mIsComposing = false;
    }

    public synchronized void onStartComposingText() {
        if (!mIsComposing) {
            if (LatinImeLogger.sDBG) {
                Log.i(TAG, "Start composing text.");
            }
            mAutoCorrectionIndicatorOn = false;
            mIsComposing = true;
        }
    }

    public synchronized void onFinishComposingText() {
        if (mIsComposing) {
            if (LatinImeLogger.sDBG) {
                Log.i(TAG, "Finish composing text.");
            }
            mAutoCorrectionIndicatorOn = false;
            mIsComposing = false;
        }
    }

    public synchronized boolean isAutoCorrectionIndicatorOn() {
        return mAutoCorrectionIndicatorOn;
    }

    public synchronized void setAutoCorrectionIndicatorOn(boolean on) {
        // Auto-correction indicator should be specified only when the current state is "composing".
        if (!mIsComposing) return;
        if (LatinImeLogger.sDBG) {
            Log.i(TAG, "Set auto correction Indicator: " + on);
        }
        mAutoCorrectionIndicatorOn = on;
    }
}
