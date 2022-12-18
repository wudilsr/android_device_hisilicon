package com.hisilicon.dlna.dmc.utility;

import java.lang.ref.SoftReference;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

import android.graphics.Bitmap;

public class Cache
{
	private int CACHE_CAPACITY_OF_FOCUS = 20;

	private LinkedList<String> mImageUrlList = null;

	private Map<String, SoftReference<Bitmap>> mImageCache = null;

	public Cache(int CACHE_CAPACITY)
	{
		CACHE_CAPACITY_OF_FOCUS = CACHE_CAPACITY;
		
		mImageUrlList = new LinkedList<String>();
		
		mImageCache = Collections.synchronizedMap(new HashMap<String, SoftReference<Bitmap>>(CACHE_CAPACITY));
	}

	public Bitmap getBitmap(String imageUrl)
	{
		if (imageUrl == null || imageUrl.trim().equals(""))
			return null;

		Bitmap bitmap = get(imageUrl);
		
		if (bitmap != null && !bitmap.isRecycled())
		{
			updateUrlList(imageUrl);
		}

		return bitmap;
	}

	private Bitmap get(String imageUrl)
	{
		SoftReference<Bitmap> softReference = mImageCache.get(imageUrl);

		if (null != softReference)
		{
			Bitmap bitmap = softReference.get();

			if (null != bitmap && !bitmap.isRecycled())
			{
				return bitmap;
			}
		}

		return null;
	}

	private void updateUrlList(String imageUrl)
	{
		synchronized (mImageUrlList)
		{
			if(mImageUrlList.contains(imageUrl))
				mImageUrlList.remove(imageUrl);

			mImageUrlList.addLast(imageUrl);
		}
	}

	public void putToCache(String imageUrl, Bitmap bitmap)
	{
		if (imageUrl == null || imageUrl.trim().equals(""))
			return;

		updateUrlList(imageUrl);

		putToImageCache(imageUrl, bitmap);

		recycleBitamps();
	}

	private void putToImageCache(String imageUrl, Bitmap bitmap)
	{
		synchronized (mImageCache)
		{
			mImageCache.put(imageUrl, new SoftReference<Bitmap>(bitmap));
		}
	}

	private void recycleBitamps()
	{
		int size = mImageUrlList.size();

		if (size > CACHE_CAPACITY_OF_FOCUS)
		{
			for (int i = 0; i < size - CACHE_CAPACITY_OF_FOCUS; i++)
			{
				recycleFirst();
			}

			System.gc();
		}
	}

	private void recycleFirst()
	{
		String imageUrl = getFirstUrl();

		SoftReference<Bitmap> softRef = removeFromImageCache(imageUrl);

		removeFirstUrl();//先 rcycle Cache 中 Bitmap，再移除 UrlList中连接

		if(null != softRef)
		{
			Bitmap	bitmap = softRef.get();

			if (null != bitmap && !bitmap.isRecycled())
				bitmap.recycle();

			bitmap = null;
		}
	}

	private String getFirstUrl()
	{
		return mImageUrlList.getFirst();
	}
	
	private String removeFirstUrl()
	{
		synchronized (mImageUrlList)
		{
			return mImageUrlList.removeFirst();
		}
	}
	
	private SoftReference<Bitmap> removeFromImageCache(String imageUrl)
	{
		synchronized (mImageCache)
		{
			return mImageCache.remove(imageUrl);
		}
	}

	public synchronized void clear()
	{
		mImageCache.clear();
		mImageUrlList.clear();
		System.gc();
	}

}
