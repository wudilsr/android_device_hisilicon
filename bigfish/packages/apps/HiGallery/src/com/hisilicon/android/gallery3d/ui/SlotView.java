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

package com.hisilicon.android.gallery3d.ui;

import android.content.Context;
import android.graphics.Rect;
import android.os.Handler;
import android.util.Log;
import android.view.GestureDetector;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.animation.DecelerateInterpolator;
import android.widget.Button;

import com.hisilicon.android.gallery3d.anim.Animation;
import com.hisilicon.android.gallery3d.common.Utils;
import com.hisilicon.android.gallery3d.ui.PositionRepository.Position;
import com.hisilicon.android.gallery3d.util.GalleryUtils;
import com.hisilicon.android.gallery3d.util.LinkedNode;

import java.util.ArrayList;
import java.util.HashMap;

public class SlotView extends GLView {
    @SuppressWarnings("unused")
    private static final String TAG = "SlotView";

    private static final boolean WIDE = true;

    private static final int INDEX_NONE = -1;

    public interface Listener {
        public void onDown(int index);

        public void onUp();

        public void onSingleTapUp(int index);

        public void onLongTap(int index);

        public void onScrollPositionChanged(int position, int total);
    }

    public static class SimpleListener implements Listener {
        public void onDown(int index) {
        }

        public void onUp() {
        }

        public void onSingleTapUp(int index) {
        }

        public void onLongTap(int index) {
        }

        public void onScrollPositionChanged(int position, int total) {
        }
    }

    public interface MyKeyListener {
        public void onKeyUp();

        public void onKeyDown(int index);

        public void onKeyCenter(int index);

    }

    public static class SimpleKeyListener implements MyKeyListener {

        @Override
        public void onKeyUp() {
            Log.e("SimpleListener", "onKeyUp  ");

        }

        @Override
        public void onKeyDown(int index) {
            Log.e("SimpleListener", "onKeyDown = " + index);

        }

        @Override
        public void onKeyCenter(int index) {
            Log.e("SimpleListener", "onKeyCenter = " + index);

        }

    }

    private final GestureDetector mGestureDetector;
    private CustomKeyDetector customKeyDetector;
    private final ScrollerHelper mScroller;
    private final Paper mPaper = new Paper();

    private Listener mListener;
    private SimpleKeyListener simpleKeyListener;
    private UserInteractionListener mUIListener;

    // Use linked hash map to keep the rendering order
    private final HashMap<DisplayItem, ItemEntry> mItems = new HashMap<DisplayItem, ItemEntry>();

    public LinkedNode.List<ItemEntry> mItemList = LinkedNode.newList();

    // This is used for multipass rendering
    private ArrayList<ItemEntry> mCurrentItems = new ArrayList<ItemEntry>();
    private ArrayList<ItemEntry> mNextItems = new ArrayList<ItemEntry>();

    private boolean mMoreAnimation = false;
    private MyAnimation mAnimation = null;
    private final Position mTempPosition = new Position();
    private final Layout mLayout = new Layout();
    private PositionProvider mPositions;
    private int mStartIndex = INDEX_NONE;

    // whether the down action happened while the view is scrolling.
    private boolean mDownInScrolling;
    private int mOverscrollEffect = OVERSCROLL_3D;
    private final Handler mHandler;

    public static final int OVERSCROLL_3D = 0;
    public static final int OVERSCROLL_SYSTEM = 1;
    public static int sUnitCount = 2;
    public static int sSlotCount = 0;
    public static final int OVERSCROLL_NONE = 2;
    int firstBufferedVisibleSlot = mLayout.getVisibleStart();
    int lastBufferedVisibleSlot = mLayout.getVisibleEnd();
    boolean leftAlignment = true;
    boolean rightAlignment = false;
    private GLRootView mglRootView;

    public SlotView(Context context) {
        mGestureDetector = new GestureDetector(context, new MyGestureListener());
        mScroller = new ScrollerHelper(context);
        mHandler = new Handler(context.getMainLooper());
        customKeyDetector = new CustomKeyDetector();
        mCurrentFocusSlotIndex = firstBufferedVisibleSlot - 1;
    }

    public void setCenterIndex(int index) {
        int slotCount = mLayout.mSlotCount;
        if (index < 0 || index >= slotCount) {
            return;
        }
        Rect rect = mLayout.getSlotRect(index);
        int position = WIDE ? (rect.left + rect.right - getWidth()) / 2
                : (rect.top + rect.bottom - getHeight()) / 2;
        setScrollPosition(position);
    }

    public void makeSlotVisible(int index) {
        Rect rect = mLayout.getSlotRect(index);
        int visibleBegin = WIDE ? mScrollX : mScrollY;
        int visibleLength = WIDE ? getWidth() : getHeight();
        int visibleEnd = visibleBegin + visibleLength;
        int slotBegin = WIDE ? rect.left : rect.top;
        int slotEnd = WIDE ? rect.right : rect.bottom;

        int position = visibleBegin;
        if (visibleLength < slotEnd - slotBegin) {
            position = visibleBegin;
        } else if (slotBegin < visibleBegin) {
            position = slotBegin;
        } else if (slotEnd > visibleEnd) {
            position = slotEnd - visibleLength;
        }

        setScrollPosition(position);
    }

    public void setScrollPosition(int position) {
        position = Utils.clamp(position, 0, mLayout.getScrollLimit());
        mScroller.setPosition(position);
        updateScrollPosition(position, false);
    }

    public void setSlotSpec(Spec spec) {
        mLayout.setSlotSpec(spec);
    }

    @Override
    public void addComponent(GLView view) {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean removeComponent(GLView view) {
        throw new UnsupportedOperationException();
    }

    @Override
    protected void onLayout(boolean changeSize, int l, int t, int r, int b) {
        if (!changeSize)
            return;

        // Make sure we are still at a resonable scroll position after the size
        // is changed (like orientation change). We choose to keep the center
        // visible slot still visible. This is arbitrary but reasonable.
        int visibleIndex = (mLayout.getVisibleStart() + mLayout.getVisibleEnd()) / 2;
        mLayout.setSize(r - l, b - t);
        makeSlotVisible(visibleIndex);

        onLayoutChanged(r - l, b - t);
        if (mOverscrollEffect == OVERSCROLL_3D) {
            mPaper.setSize(r - l, b - t);
        }
    }

    protected void onLayoutChanged(int width, int height) {
    }

    public void startTransition(PositionProvider position) {
        mPositions = position;
        mAnimation = new MyAnimation();
        mAnimation.start();
        if (mItems.size() != 0)
            invalidate();
    }

    public void savePositions(PositionRepository repository) {
        repository.clear();
        LinkedNode.List<ItemEntry> list = mItemList;
        ItemEntry entry = list.getFirst();
        Position position = new Position();
        while (entry != null) {
            position.set(entry.target);
            position.x -= mScrollX;
            position.y -= mScrollY;
            repository.putPosition(entry.item.getIdentity(), position);
            entry = list.nextOf(entry);
        }
    }

    private void updateScrollPosition(int position, boolean force) {
        if (!force && (WIDE ? position == mScrollX : position == mScrollY))
            return;
        if (WIDE) {
            mScrollX = position;
        } else {
            mScrollY = position;
        }
        mLayout.setScrollPosition(position);
        onScrollPositionChanged(position);
    }

    protected void onScrollPositionChanged(int newPosition) {
        int limit = mLayout.getScrollLimit();
        mListener.onScrollPositionChanged(newPosition, limit);
    }

    public void putDisplayItem(Position target, Position base, DisplayItem item) {
        item.setBox(mLayout.getSlotWidth(), mLayout.getSlotHeight());
        ItemEntry entry = new ItemEntry(item, target, base);
        mItemList.insertLast(entry);
        mItems.put(item, entry);
    }

    public void removeDisplayItem(DisplayItem item) {
        ItemEntry entry = mItems.remove(item);
        if (entry != null)
            entry.remove();
    }

    public Rect getSlotRect(int slotIndex) {
        return mLayout.getSlotRect(slotIndex);
    }

    public int getSlotWidth() {
        return mLayout.getSlotWidth();
    }

    public int getSlotHeight() {
        return mLayout.getSlotHeight();
    }

    public int getFirstBufferedVisibleSlot() {
        return mLayout.getVisibleStart();
    }

    public int getLastBufferedVisibleSlot() {
        return mLayout.getVisibleEnd();
    }

    public int getmSlotGap() {
        return mLayout.getmSlotGap();
    }

    public int getmWidth() {
        return mLayout.getmWidth();
    }

    public int getmHeight() {
        return mLayout.getmHeight();
    }

    @Override
    protected boolean onTouch(GLRootView glRootView, MotionEvent event) {
        GalleryUtils.setGlRootViewFocus(glRootView, true);
        if (mUIListener != null)
            mUIListener.onUserInteraction();
        mGestureDetector.onTouchEvent(event);
        switch (event.getAction()) {
        case MotionEvent.ACTION_DOWN:
            mDownInScrolling = !mScroller.isFinished();
            mScroller.forceFinished();
            break;
        case MotionEvent.ACTION_UP:
            mPaper.onRelease();
            invalidate();
            break;
        }
        initCurrentFocusSlotIndex();
        return true;
    }

    public void initCurrentFocusSlotIndex() {
        // After the mouse to click to reposition the key position
        leftAlignment = true;
        rightAlignment = false;
        mCurrentFocusSlotIndex = mLayout.getVisibleStart() + sNumRows;
        if (simpleKeyListener != null) {
            simpleKeyListener.onKeyUp();
        }
    }

    // add remote control keyDown process
    @Override
    protected boolean onKeyDown(GLRootView glRootView, KeyEvent event) {
        this.mglRootView = glRootView;
        if (mUIListener != null)
            mUIListener.onUserInteraction();
        if (event.getAction() == KeyEvent.ACTION_UP) {
            return customKeyDetector.onKey(glRootView, event.getKeyCode(),
                    event);
        }
        return super.onKeyDown(glRootView, event);
    }

    public void setListener(Listener listener) {
        mListener = listener;
    }

    public void setSimpleKeyListener(SimpleKeyListener cListener) {
        simpleKeyListener = cListener;
    }

    public void setUserInteractionListener(UserInteractionListener listener) {
        mUIListener = listener;
    }

    public void setOverscrollEffect(int kind) {
        mOverscrollEffect = kind;
        mScroller.setOverfling(kind == OVERSCROLL_SYSTEM);
    }

    @Override
    protected void render(GLCanvas canvas) {
        super.render(canvas);

        long currentTimeMillis = canvas.currentAnimationTimeMillis();
        boolean more = mScroller.advanceAnimation(currentTimeMillis);
        int oldX = mScrollX;
        updateScrollPosition(mScroller.getPosition(), false);

        boolean paperActive = false;
        if (mOverscrollEffect == OVERSCROLL_3D) {
            // Check if an edge is reached and notify mPaper if so.
            int newX = mScrollX;
            int limit = mLayout.getScrollLimit();
            if (oldX > 0 && newX == 0 || oldX < limit && newX == limit) {
                float v = mScroller.getCurrVelocity();
                if (newX == limit)
                    v = -v;

                // I don't know why, but getCurrVelocity() can return NaN.
                if (!Float.isNaN(v)) {
                    mPaper.edgeReached(v);
                }
            }
            paperActive = mPaper.advanceAnimation();
        }

        more |= paperActive;

        float interpolate = 1f;
        if (mAnimation != null) {
            more |= mAnimation.calculate(currentTimeMillis);
            interpolate = mAnimation.value;
        }

        if (WIDE) {
            canvas.translate(-mScrollX, 0, 0);
        } else {
            canvas.translate(0, -mScrollY, 0);
        }

        LinkedNode.List<ItemEntry> list = mItemList;
        for (ItemEntry entry = list.getLast(); entry != null;) {
            int r = renderItem(canvas, entry, interpolate, 0, paperActive);
            if ((r & DisplayItem.RENDER_MORE_PASS) != 0) {
                mCurrentItems.add(entry);
            }
            more |= ((r & DisplayItem.RENDER_MORE_FRAME) != 0);
            entry = list.previousOf(entry);
        }

        int pass = 1;
        while (!mCurrentItems.isEmpty()) {
            for (int i = 0, n = mCurrentItems.size(); i < n; i++) {
                ItemEntry entry = mCurrentItems.get(i);
                int r = renderItem(canvas, entry, interpolate, pass,
                        paperActive);
                if ((r & DisplayItem.RENDER_MORE_PASS) != 0) {
                    mNextItems.add(entry);
                }
                more |= ((r & DisplayItem.RENDER_MORE_FRAME) != 0);
            }
            mCurrentItems.clear();
            // swap mNextItems with mCurrentItems
            ArrayList<ItemEntry> tmp = mNextItems;
            mNextItems = mCurrentItems;
            mCurrentItems = tmp;
            pass += 1;
        }

        if (WIDE) {
            canvas.translate(mScrollX, 0, 0);
        } else {
            canvas.translate(0, mScrollY, 0);
        }

        if (more)
            invalidate();

        final UserInteractionListener listener = mUIListener;
        if (mMoreAnimation && !more && listener != null) {
            mHandler.post(new Runnable() {
                @Override
                public void run() {
                    listener.onUserInteractionEnd();
                }
            });
        }
        mMoreAnimation = more;
    }

    private int renderItem(GLCanvas canvas, ItemEntry entry, float interpolate,
            int pass, boolean paperActive) {
        canvas.save(GLCanvas.SAVE_FLAG_ALPHA | GLCanvas.SAVE_FLAG_MATRIX);
        Position position = entry.target;
        if (mPositions != null) {
            position = mTempPosition;
            position.set(entry.target);
            position.x -= mScrollX;
            position.y -= mScrollY;
            Position source = mPositions.getPosition(entry.item.getIdentity(),
                    position);
            source.x += mScrollX;
            source.y += mScrollY;
            position = mTempPosition;
            Position.interpolate(source, entry.target, position, interpolate);
        }
        canvas.multiplyAlpha(position.alpha);
        if (paperActive) {
            canvas.multiplyMatrix(mPaper.getTransform(position, entry.base,
                    mScrollX, mScrollY), 0);
        } else {
            canvas.translate(position.x, position.y, position.z);
        }
        canvas.rotate(position.theta, 0, 0, 1);
        int more = entry.item.render(canvas, pass);
        canvas.restore();
        return more;
    }

    public static class MyAnimation extends Animation {
        public float value;

        public MyAnimation() {
            setInterpolator(new DecelerateInterpolator(4));
            setDuration(1500);
        }

        @Override
        protected void onCalculate(float progress) {
            value = progress;
        }
    }

    private static class ItemEntry extends LinkedNode {
        public DisplayItem item;
        public Position target;
        public Position base;

        public ItemEntry(DisplayItem item, Position target, Position base) {
            this.item = item;
            this.target = target;
            this.base = base;
        }
    }

    // This Spec class is used to specify the size of each slot in the SlotView.
    // There are two ways to do it:
    //
    // (1) Specify slotWidth and slotHeight: they specify the width and height
    // of each slot. The number of rows and the gap between slots will be
    // determined automatically.
    // (2) Specify rowsLand, rowsPort, and slotGap: they specify the number
    // of rows in landscape/portrait mode and the gap between slots. The
    // width and height of each slot is determined automatically.
    //
    // The initial value of -1 means they are not specified.
    public static class Spec {
        public int slotWidth = -1;
        public int slotHeight = -1;

        public int rowsLand = -1;
        public int rowsPort = -1;
        public int slotGap = -1;

        static Spec newWithSize(int width, int height) {
            Spec s = new Spec();
            s.slotWidth = width;
            s.slotHeight = height;
            return s;
        }

        static Spec newWithRows(int rowsLand, int rowsPort, int slotGap) {
            Spec s = new Spec();
            s.rowsLand = rowsLand;
            s.rowsPort = rowsPort;
            s.slotGap = slotGap;
            return s;
        }
    }

    public static class Layout {

        private int mVisibleStart;
        private int mVisibleEnd;

        private int mSlotCount;
        private int mSlotWidth;
        private int mSlotHeight;
        private int mSlotGap;

        private Spec mSpec;

        private int mWidth;
        private int mHeight;

        private int mUnitCount;
        private int mContentLength;
        private int mScrollPosition;

        private int mVerticalPadding;
        private int mHorizontalPadding;

        public void setSlotSpec(Spec spec) {
            mSpec = spec;
        }

        public boolean setSlotCount(int slotCount) {
            mSlotCount = slotCount;
            sSlotCount = mSlotCount;
            int hPadding = mHorizontalPadding;
            int vPadding = mVerticalPadding;
            initLayoutParameters();
            return vPadding != mVerticalPadding
                    || hPadding != mHorizontalPadding;
        }

        public Rect getSlotRect(int index) {
            int col, row;
            if (WIDE) {
                col = index / mUnitCount;
                row = index - col * mUnitCount;
            } else {
                row = index / mUnitCount;
                col = index - row * mUnitCount;
            }

            int x = mHorizontalPadding + col * (mSlotWidth + mSlotGap);
            int y = mVerticalPadding + row * (mSlotHeight + mSlotGap);
            return new Rect(x, y, x + mSlotWidth, y + mSlotHeight);
        }

        public int getSlotWidth() {
            return mSlotWidth;
        }

        public int getSlotHeight() {
            return mSlotHeight;
        }

        public int getContentLength() {
            return mContentLength;
        }

        public int getmSlotGap() {
            return mSlotGap;
        }

        public int getmWidth() {
            return mWidth;
        }

        public int getmHeight() {
            return mHeight;
        }

        // Calculate
        // (1) mUnitCount: the number of slots we can fit into one column (or
        // row).
        // (2) mContentLength: the width (or height) we need to display all the
        // columns (rows).
        // (3) padding[]: the vertical and horizontal padding we need in order
        // to put the slots towards to the center of the display.
        //
        // The "major" direction is the direction the user can scroll. The other
        // direction is the "minor" direction.
        //
        // The comments inside this method are the description when the major
        // directon is horizontal (X), and the minor directon is vertical (Y).
        private void initLayoutParameters(int majorLength, int minorLength, /*
                                                                             * The
                                                                             * view
                                                                             * width
                                                                             * and
                                                                             * height
                                                                             */
        int majorUnitSize, int minorUnitSize, /* The slot width and height */
        int[] padding) {
            int unitCount = (minorLength + mSlotGap)
                    / (minorUnitSize + mSlotGap);
            if (unitCount == 0)
                unitCount = 1;
            mUnitCount = unitCount;
            sUnitCount = mUnitCount;
            if (mUnitCount > 1) {
                GLView.sNumRows = sUnitCount;
            }
            // We put extra padding above and below the column.
            int availableUnits = Math.min(mUnitCount, mSlotCount);
            int usedMinorLength = availableUnits * minorUnitSize
                    + (availableUnits - 1) * mSlotGap;
            padding[0] = (minorLength - usedMinorLength) / 2;

            // Then calculate how many columns we need for all slots.
            int count = ((mSlotCount + mUnitCount - 1) / mUnitCount);
            mContentLength = count * majorUnitSize + (count - 1) * mSlotGap;

            // If the content length is less then the screen width, put
            // extra padding in left and right.
            padding[1] = Math.max(0, (majorLength - mContentLength) / 2);
        }

        private void initLayoutParameters() {
            // Initialize mSlotWidth and mSlotHeight from mSpec
            if (mSpec.slotWidth != -1) {
                mSlotGap = 0;
                mSlotWidth = mSpec.slotWidth;
                mSlotHeight = mSpec.slotHeight;
            } else {
                int rows = (mWidth > mHeight) ? mSpec.rowsLand : mSpec.rowsPort;
                mSlotGap = mSpec.slotGap;
                mSlotHeight = Math.max(1, (mHeight - (rows - 1) * mSlotGap)
                        / rows);
                mSlotWidth = mSlotHeight;
            }

            int[] padding = new int[2];
            if (WIDE) {
                initLayoutParameters(mWidth, mHeight, mSlotWidth, mSlotHeight,
                        padding);
                mVerticalPadding = padding[0];
                mHorizontalPadding = padding[1];
            } else {
                initLayoutParameters(mHeight, mWidth, mSlotHeight, mSlotWidth,
                        padding);
                mVerticalPadding = padding[1];
                mHorizontalPadding = padding[0];
            }
            updateVisibleSlotRange();
        }

        public void setSize(int width, int height) {
            mWidth = width;
            mHeight = height;
            initLayoutParameters();
        }

        private void updateVisibleSlotRange() {
            int position = mScrollPosition;

            if (WIDE) {
                int startCol = position / (mSlotWidth + mSlotGap);
                int start = Math.max(0, mUnitCount * startCol);
                int endCol = (position + mWidth + mSlotWidth + mSlotGap - 1)
                        / (mSlotWidth + mSlotGap);
                int end = Math.min(mSlotCount, mUnitCount * endCol);
                setVisibleRange(start, end);
            } else {
                int startRow = position / (mSlotHeight + mSlotGap);
                int start = Math.max(0, mUnitCount * startRow);
                int endRow = (position + mHeight + mSlotHeight + mSlotGap - 1)
                        / (mSlotHeight + mSlotGap);
                int end = Math.min(mSlotCount, mUnitCount * endRow);
                setVisibleRange(start, end);
            }
        }

        public void setScrollPosition(int position) {
            if (mScrollPosition == position)
                return;
            mScrollPosition = position;
            updateVisibleSlotRange();
        }

        private void setVisibleRange(int start, int end) {
            if (start == mVisibleStart && end == mVisibleEnd)
                return;
            if (start < end) {
                mVisibleStart = start;
                mVisibleEnd = end;
            } else {
                mVisibleStart = mVisibleEnd = 0;
            }
        }

        public int getVisibleStart() {
            return mVisibleStart;
        }

        public int getVisibleEnd() {
            return mVisibleEnd;
        }

        public int getSlotIndexByPosition(float x, float y) {
            int absoluteX = Math.round(x) + (WIDE ? mScrollPosition : 0);
            int absoluteY = Math.round(y) + (WIDE ? 0 : mScrollPosition);

            absoluteX -= mHorizontalPadding;
            absoluteY -= mVerticalPadding;

            if (absoluteX < 0 || absoluteY < 0) {
                return INDEX_NONE;
            }

            int columnIdx = absoluteX / (mSlotWidth + mSlotGap);
            int rowIdx = absoluteY / (mSlotHeight + mSlotGap);

            if (!WIDE && columnIdx >= mUnitCount) {
                return INDEX_NONE;
            }

            if (WIDE && rowIdx >= mUnitCount) {
                return INDEX_NONE;
            }

            if (absoluteX % (mSlotWidth + mSlotGap) >= mSlotWidth) {
                return INDEX_NONE;
            }

            if (absoluteY % (mSlotHeight + mSlotGap) >= mSlotHeight) {
                return INDEX_NONE;
            }

            int index = WIDE ? (columnIdx * mUnitCount + rowIdx) : (rowIdx
                    * mUnitCount + columnIdx);

            return index >= mSlotCount ? INDEX_NONE : index;
        }

        public int getScrollLimit() {
            int limit = WIDE ? mContentLength - mWidth : mContentLength
                    - mHeight;
            return limit <= 0 ? 0 : limit;
        }
    }

    public class CustomKeyDetector {
        public boolean onKey(GLRootView glRootView, int keyCode, KeyEvent event) {
            int col, row;
            if (!GalleryUtils.isGLRootFocus
                    && event.getKeyCode() != KeyEvent.KEYCODE_DPAD_DOWN) {
                return false;
            }
            int numRows = sUnitCount;
            if (numRows == 1) {
                return false;
            }
            firstBufferedVisibleSlot = mLayout.getVisibleStart();
            lastBufferedVisibleSlot = mLayout.getVisibleEnd();
            // Remember photo the index of the higher level position
            if (GLView.mCurrrentPhotoSlotIndex != INDEX_NONE
                    && GalleryUtils.isGLRootFocus) {
                mCurrentFocusSlotIndex = GLView.mCurrrentPhotoSlotIndex;
                GLView.mCurrrentPhotoSlotIndex = INDEX_NONE;
            }
            if (GLView.mCurrrentPhotoSlotIndex != INDEX_NONE
                    && !GalleryUtils.isGLRootFocus) {
                if (leftAlignment == true) {
                    mCurrentFocusSlotIndex = firstBufferedVisibleSlot;
                } else {
                    mCurrentFocusSlotIndex = firstBufferedVisibleSlot + numRows;
                }
                GLView.mCurrrentPhotoSlotIndex = INDEX_NONE;
            }
            if (simpleKeyListener == null) {
                return false;
            }
            switch (keyCode) {
            case KeyEvent.KEYCODE_DPAD_LEFT:
                mCurrentFocusSlotIndex -= numRows;

                // When slotView to the first visible, page turning
                if (mCurrentFocusSlotIndex < firstBufferedVisibleSlot + numRows
                        && exceedScreen()) {
                    slotPageOver(leftAlignment, keyCode, event);
                    rightAlignment = false;
                    leftAlignment = true;
                }
                // if the first column
                if (mCurrentFocusSlotIndex < 0) {
                    mCurrentFocusSlotIndex += numRows;
                    return true;
                }
                break;
            case KeyEvent.KEYCODE_DPAD_RIGHT:
                // if first show view be index++
                if (mCurrentFocusSlotIndex <= INDEX_NONE) {
                    mCurrentFocusSlotIndex = 0;
                } else {
                    mCurrentFocusSlotIndex += numRows;
                }

                // When slotView to the last visible, page turning
                if (mCurrentFocusSlotIndex >= lastBufferedVisibleSlot - numRows
                        && exceedScreen()) {
                    slotPageOver(rightAlignment, keyCode, event);
                    rightAlignment = true;
                    leftAlignment = false;
                }
                // If the last column
                if (mCurrentFocusSlotIndex > sSlotCount - 1) {
                    mCurrentFocusSlotIndex -= numRows;
                    return true;
                }

                // if( mCurrentFocusSlotIndex >= sSlotCount - numRows &&
                // rightAlignment && !firstMoveNull){
                //
                // }

                break;
            case KeyEvent.KEYCODE_DPAD_UP:
                if (WIDE) {
                    col = mCurrentFocusSlotIndex / numRows;
                    row = mCurrentFocusSlotIndex - col * numRows;
                } else {
                    row = mCurrentFocusSlotIndex / numRows;
                    col = mCurrentFocusSlotIndex - row * numRows;
                }
                // if Actionbar gain focus && glRootView lost focus
                if (row == 0 && glRootView != null
                        && GalleryUtils.isGLRootFocus) {
                    cancelKeyDown();
                    GalleryUtils.setGlRootViewFocus(glRootView, false);
                    if (leftAlignment == true) {
                        mCurrentFocusSlotIndex = firstBufferedVisibleSlot;
                    } else {
                        mCurrentFocusSlotIndex = firstBufferedVisibleSlot
                                + numRows;
                    }
                    if (offlineButton != null
                            && !GalleryUtils.isFooterContentFocus) {
                        offlineButton.clearFocus();
                        offlineButton.setFocusable(false);
                        GalleryUtils.isFooterContentFocus = false;
                    }
                    return true;
                }
                --mCurrentFocusSlotIndex;
                break;
            case KeyEvent.KEYCODE_DPAD_DOWN:
                if (WIDE) {
                    col = mCurrentFocusSlotIndex / numRows;
                    row = mCurrentFocusSlotIndex - col * numRows;
                } else {
                    row = mCurrentFocusSlotIndex / numRows;
                    col = mCurrentFocusSlotIndex - row * numRows;
                }
                if (row < numRows - 1 && GalleryUtils.isGLRootFocus) {
                    ++mCurrentFocusSlotIndex;
                } else if (!GalleryUtils.isGLRootFocus) {
                    if (leftAlignment == true) {
                        mCurrentFocusSlotIndex = firstBufferedVisibleSlot;
                    } else {
                        mCurrentFocusSlotIndex = firstBufferedVisibleSlot
                                + numRows;
                    }
                    GalleryUtils.isGLRootFocus = true;
                    GalleryUtils.isFooterContentFocus = false;
                }
                // if offline
                if (row == (numRows - 1) && GalleryUtils.isGLRootFocus) {
                    if (offlineButton != null) {
                        GalleryUtils.setGlRootViewFocus(glRootView, false);
                        // offline button get focus
                        offlineButton.setFocusable(true);
                        offlineButton.requestFocus();
                        GalleryUtils.isFooterContentFocus = true;
                        cancelKeyDown();
                        return true;
                    }
                }
                break;
            case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_DPAD_CENTER:
                if (mCurrentFocusSlotIndex > INDEX_NONE) {
                    simpleKeyListener.onKeyCenter(mCurrentFocusSlotIndex);
                    if (exceedScreen()
                            && mCurrentFocusSlotIndex > getScreenSlotCount()) {
                        leftAlignment = false;
                        rightAlignment = true;
                    } else {
                        leftAlignment = true;
                        rightAlignment = false;
                    }
                }
                return true;
            }
            if (mCurrentFocusSlotIndex < firstBufferedVisibleSlot) {
                mCurrentFocusSlotIndex = firstBufferedVisibleSlot;
            }
            if (mCurrentFocusSlotIndex > sSlotCount - 1) {
                mCurrentFocusSlotIndex = sSlotCount - 1;
            }
            if (mCurrentFocusSlotIndex < 0) {
                mCurrentFocusSlotIndex = 0;
            }
            if ((keyCode == KeyEvent.KEYCODE_DPAD_UP
                    || keyCode == KeyEvent.KEYCODE_DPAD_DOWN
                    || keyCode == KeyEvent.KEYCODE_DPAD_LEFT || keyCode == KeyEvent.KEYCODE_DPAD_RIGHT)
                    && mCurrentFocusSlotIndex != INDEX_NONE) {
                simpleKeyListener.onKeyDown(mCurrentFocusSlotIndex);
                return true;
            }
            return false;
        }

        private void cancelKeyDown() {
            simpleKeyListener.onKeyUp();
        }
    }

    // Get the screen can show the complete Slot number
    private int getScreenSlotCount() {
        int screenCol = 0;
        int actualSlotCount = 0;
        if (WIDE) {
            screenCol = getWidth() / (getSlotWidth() + getmSlotGap());
        } else {
            screenCol = getWidth() / (getSlotHeight() + getmSlotGap());
        }
        return actualSlotCount = screenCol * sNumRows;
    }

    // If more than one screen calculation
    private boolean exceedScreen() {
        int screenCol = 0;
        int actual = 0;
        if (WIDE) {
            screenCol = getWidth() / (getSlotWidth() + getmSlotGap());
        } else {
            screenCol = getWidth() / (getSlotHeight() + getmSlotGap());
        }
        if (sSlotCount % sUnitCount == 0) {
            actual = sSlotCount / sUnitCount;
        } else {
            actual = sSlotCount / sUnitCount + 1;
        }

        return actual > screenCol;

    }

    private int getMoveWidth() {
        int screenCol;
        int noFullSlotWidth;
        int moveWidth;
        if (WIDE) {
            screenCol = getWidth() / (getSlotWidth() + getmSlotGap());
            noFullSlotWidth = getWidth()
                    - (screenCol * (getSlotWidth() + getmSlotGap()));
            moveWidth = (getSlotWidth() + (getmSlotGap())) - noFullSlotWidth;
        } else {
            screenCol = getHeight() / (getSlotHeight() + getmSlotGap());
            noFullSlotWidth = getHeight()
                    - (screenCol * (getSlotHeight() + getmSlotGap()));
            moveWidth = (getSlotHeight() + (getmSlotGap())) - noFullSlotWidth;
        }
        return moveWidth;
    }

    public void slotPageOver(boolean alignment, int keyCode, KeyEvent event) {
        // before
        mDownInScrolling = !mScroller.isFinished();
        mScroller.forceFinished();
        int distance = getSlotHeight();
        if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode) {
            if (WIDE) {
                if (alignment) {
                    distance = -(getSlotWidth() + getmSlotGap());
                } else {
                    distance = -(getMoveWidth());
                }
            }
        } else {
            if (WIDE) {
                if (alignment) {
                    distance = getSlotWidth() + getmSlotGap();
                } else {
                    distance = getMoveWidth();
                }
            }
        }
        int overDistance = mScroller.startScroll(Math.round(distance), 0,
                mLayout.getScrollLimit());
        if (mOverscrollEffect == OVERSCROLL_3D && overDistance != 0) {
            mPaper.overScroll(overDistance);
        }
        // after
        mPaper.onRelease();
        invalidate();
    }

    private class MyGestureListener implements
            GestureDetector.OnGestureListener {
        private boolean isDown;

        // We call the listener's onDown() when our onShowPress() is called and
        // call the listener's onUp() when we receive any further event.
        @Override
        public void onShowPress(MotionEvent e) {
            if (isDown)
                return;
            int index = mLayout.getSlotIndexByPosition(e.getX(), e.getY());
            if (index != INDEX_NONE) {
                isDown = true;
                mListener.onDown(index);
            }
        }

        private void cancelDown() {
            if (!isDown)
                return;
            isDown = false;
            mListener.onUp();
        }

        @Override
        public boolean onDown(MotionEvent e) {
            return false;
        }

        @Override
        public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX,
                float velocityY) {
            cancelDown();
            int scrollLimit = mLayout.getScrollLimit();
            if (scrollLimit == 0)
                return false;
            float velocity = WIDE ? velocityX : velocityY;
            mScroller.fling((int) -velocity, 0, scrollLimit);
            if (mUIListener != null)
                mUIListener.onUserInteractionBegin();
            invalidate();
            return true;
        }

        @Override
        public boolean onScroll(MotionEvent e1, MotionEvent e2,
                float distanceX, float distanceY) {
            cancelDown();
            float distance = WIDE ? distanceX : distanceY;
            int overDistance = mScroller.startScroll(Math.round(distance), 0,
                    mLayout.getScrollLimit());
            if (mOverscrollEffect == OVERSCROLL_3D && overDistance != 0) {
                mPaper.overScroll(overDistance);
            }
            invalidate();
            return true;
        }

        @Override
        public boolean onSingleTapUp(MotionEvent e) {
            cancelDown();
            if (mDownInScrolling)
                return true;
            int index = mLayout.getSlotIndexByPosition(e.getX(), e.getY());
            if (index != INDEX_NONE)
                mListener.onSingleTapUp(index);
            return true;
        }

        @Override
        public void onLongPress(MotionEvent e) {
            cancelDown();
            if (mDownInScrolling)
                return;
            lockRendering();
            try {
                int index = mLayout.getSlotIndexByPosition(e.getX(), e.getY());
                if (index != INDEX_NONE)
                    mListener.onLongTap(index);
            } finally {
                unlockRendering();
            }
        }
    }

    public void setStartIndex(int index) {
        mStartIndex = index;
    }

    // Return true if the layout parameters have been changed
    public boolean setSlotCount(int slotCount) {
        boolean changed = mLayout.setSlotCount(slotCount);

        // mStartIndex is applied the first time setSlotCount is called.
        if (mStartIndex != INDEX_NONE) {
            setCenterIndex(mStartIndex);
            mStartIndex = INDEX_NONE;
        }
        updateScrollPosition(WIDE ? mScrollX : mScrollY, true);
        return changed;
    }

    public int getVisibleStart() {
        return mLayout.getVisibleStart();
    }

    public int getVisibleEnd() {
        return mLayout.getVisibleEnd();
    }

    public int getScrollX() {
        return mScrollX;
    }

    public int getScrollY() {
        return mScrollY;
    }

    // start Allow offline use of the download
    private Button offlineButton;

    public void setDoneButton(Button doneButton) {
        this.offlineButton = doneButton;
    }
    // end
}
