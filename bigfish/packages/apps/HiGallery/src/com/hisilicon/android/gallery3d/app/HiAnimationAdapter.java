package com.hisilicon.android.gallery3d.app;

import java.util.LinkedList;
import java.util.concurrent.atomic.AtomicBoolean;

import android.graphics.Bitmap;
import android.util.Log;

import com.hisilicon.android.gallery3d.app.HiAnimationActivity.Slide;
import com.hisilicon.android.gallery3d.data.ContentListener;
import com.hisilicon.android.gallery3d.data.MediaItem;
import com.hisilicon.android.gallery3d.data.MediaObject;
import com.hisilicon.android.gallery3d.data.Path;
import com.hisilicon.android.gallery3d.util.Future;
import com.hisilicon.android.gallery3d.util.FutureListener;
import com.hisilicon.android.gallery3d.util.ThreadPool;
import com.hisilicon.android.gallery3d.util.ThreadPool.Job;
import com.hisilicon.android.gallery3d.util.ThreadPool.JobContext;

public class HiAnimationAdapter implements HiAnimationActivity.Model{
	private static final int IMAGE_QUEUE_CAPACITY = 3;
	private static final String TAG = "HiAnimationAdapter";
    public interface ShowSource {
        public void addContentListener(ContentListener listener);
        public void removeContentListener(ContentListener listener);
        public long reload();
        public MediaItem getMediaItem(int index);
        public int findItemIndex(Path path, int hint);
    }

    private final ShowSource mSource;

    private int mLoadIndex = 0;
    private int mNextOutput = 0;
    private boolean mIsActive = false;
    private boolean mNeedReset;
    private boolean mDataReady;
    private Path mInitialPath;

    private final LinkedList<Slide> mImageQueue = new LinkedList<Slide>();

    private Future<Void> mReloadTask;
    private final ThreadPool mThreadPool;

    private long mDataVersion = MediaObject.INVALID_DATA_VERSION;
    private final AtomicBoolean mNeedReload = new AtomicBoolean(false);
    private final SourceListener mSourceListener = new SourceListener();

    // The index is just a hint if initialPath is set
    public HiAnimationAdapter(GalleryContext context, ShowSource source, int index,
            Path initialPath) {
        mSource = source;
        mInitialPath = initialPath;
        mLoadIndex = index;
        mNextOutput = index;
        mThreadPool = context.getThreadPool();
    }

    private MediaItem loadItem() {
        if (mNeedReload.compareAndSet(true, false)) {
            long v = mSource.reload();
            if (v != mDataVersion) {
                mDataVersion = v;
                mNeedReset = true;
                return null;
            }
        }
        int index = mLoadIndex;
        if (mInitialPath != null) {
            index = mSource.findItemIndex(mInitialPath, index);
            mInitialPath = null;
        }
        return mSource.getMediaItem(index);
    }

    private class ReloadTask implements Job<Void> {
        public Void run(JobContext jc) {
            while (true) {
		Log.d(TAG, "ReloadTask");
                synchronized (HiAnimationAdapter.this) {
                    while (mIsActive && (!mDataReady
                            || mImageQueue.size() >= IMAGE_QUEUE_CAPACITY)) {
                        try {
		HiAnimationAdapter.this.wait();
                        } catch (InterruptedException ex) {
                            // ignored.
                        }
                        continue;
                    }
                }
                if (!mIsActive) return null;
                mNeedReset = false;
                Log.d(TAG, "ReloadTask1111");
                MediaItem item = loadItem();
                Log.d(TAG, "ReloadTask2222");
                if (mNeedReset) {
                    synchronized (HiAnimationAdapter.this) {
                        mImageQueue.clear();
                        mLoadIndex = mNextOutput;
                    }
                    continue;
                }
                Log.d(TAG, "ReloadTask3333");
                if (item == null) {
                    synchronized (HiAnimationAdapter.this) {
                        if (!mNeedReload.get()) mDataReady = false;
                        HiAnimationAdapter.this.notifyAll();
                    }
                    continue;
                }

                Bitmap bitmap = item
                        .requestImage(MediaItem.TYPE_THUMBNAIL)
                        .run(jc);

                if (bitmap != null) {
		Log.d(TAG, "ReloadTask44444");
                    synchronized (HiAnimationAdapter.this) {
                        mImageQueue.addLast(
                                new Slide(item, mLoadIndex, bitmap));
                        if (mImageQueue.size() == 1) {
		HiAnimationAdapter.this.notifyAll();
                        }
                    }
                }
                ++mLoadIndex;
            }
        }
    }

    private class SourceListener implements ContentListener {
        public void onContentDirty() {
            synchronized (HiAnimationAdapter.this) {
                mNeedReload.set(true);
                mDataReady = true;
                HiAnimationAdapter.this.notifyAll();
            }
        }
    }

    private synchronized Slide innerNextBitmap() {
        while (mIsActive && mDataReady && mImageQueue.isEmpty()) {
            try {
                wait();
            } catch (InterruptedException t) {
                throw new AssertionError();
            }
        }
        if (mImageQueue.isEmpty()) return null;
        mNextOutput++;
        this.notifyAll();
        return mImageQueue.removeFirst();
    }

    public Future<Slide> nextSlide(FutureListener<Slide> listener) {
        return mThreadPool.submit(new Job<Slide>() {
            public Slide run(JobContext jc) {
                jc.setMode(ThreadPool.MODE_NONE);
                return innerNextBitmap();
            }
        }, listener);
    }

    public void pause() {
        synchronized (this) {
            mIsActive = false;
            notifyAll();
        }
        mSource.removeContentListener(mSourceListener);
        mReloadTask.cancel();
        mReloadTask.waitDone();
        mReloadTask = null;
    }

    public synchronized void resume() {
		Log.d(TAG, "resume()");
        mIsActive = true;
        mSource.addContentListener(mSourceListener);
        mNeedReload.set(true);
        mDataReady = true;
        mReloadTask = mThreadPool.submit(new ReloadTask());
    }

}
