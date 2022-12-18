package com.hisilicon.dlna.dmc.utility;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.media.ExifInterface;
import android.media.ThumbnailUtils;
import android.net.Uri;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.provider.MediaStore.Images;
import android.provider.MediaStore.Video;
import android.provider.MediaStore.Video.Thumbnails;

import com.hisilicon.dlna.dmc.processor.interfaces.ImageCallback;
import com.hisilicon.multiscreen.mybox.MyApp;

public class ThumbnailGenerator {
	private static ThumbnailGenerator instance;
	private ThreadPoolExecutor threadPool = null;

	private ThumbnailGenerator() {
		threadPool = new ThreadPoolExecutor(4, 10, 3, TimeUnit.SECONDS,new LinkedBlockingQueue<Runnable>(), new ThreadPoolExecutor.DiscardOldestPolicy());
	}

	public static ThumbnailGenerator getInstance(){
		if(null == instance)
			instance = new ThumbnailGenerator();
		return instance;
	}

	public void addThread(Thread thread){
		threadPool.execute(thread);
	}

	/**
	 * 
	 * decode 图片文件为Bitmap 并保存到Cache
	 */
	public Bitmap decodeFileBitmap(File file) throws MyException {
		try {
			Bitmap bitmap = GlobalCache.getBitmap(file.getAbsolutePath());
			if (null != bitmap && !bitmap.isRecycled()){
				return bitmap;
			}

			bitmap = decodeFileBitmap(file, Utility.getImageDimension(), Utility.getImageDimension());

			if (null != bitmap && !bitmap.isRecycled()){
				GlobalCache.putToCache(file.getAbsolutePath(), bitmap);
				return bitmap;
			}
		} catch (Exception ex) {
			throw new MyException(ex);
		} catch (Error ex) {
			System.gc();
			throw new MyException(ex);
		}
		return null;
	}

	/**
	 * 
	 * decode 图片文件为Bitmap，不保存到Cache
	 */
	public Bitmap decodeFileBitmap(File file, int width, int height) throws MyException {
		try {
			BitmapFactory.Options opts = new BitmapFactory.Options();
			opts.inDither = false;
			opts.inPurgeable = true;
			opts.inInputShareable = true;
			opts.inPreferredConfig = Bitmap.Config.ARGB_8888;

			// 获取这个图片的宽和高
			opts.inJustDecodeBounds = true;
			BitmapFactory.decodeFile(file.getAbsolutePath(), opts);
			opts.inJustDecodeBounds = false;

			int pictureW = opts.outWidth;
			int pictureH = opts.outHeight;

			int sampleSize = 1;

			int sampleSizeW = (int) Math.ceil(pictureW / width);
			int sampleSizeH = (int) Math.ceil(pictureH / height);

			if (sampleSizeW > 1 || sampleSizeH > 1) {
				sampleSize = Math.max(sampleSizeW, sampleSizeH);
			}

			opts.inSampleSize = sampleSize;

			Bitmap bitmap = BitmapFactory.decodeFile(file.getAbsolutePath(), opts);

			if (null != bitmap && !bitmap.isRecycled()){
				return bitmap;
			}
		} catch (Exception ex) {
			throw new MyException(ex);
		} catch (Error ex) {
			System.gc();
			throw new MyException(ex);
		}
		return null;
	}

	/**
	 * 
	 * 获取本地图片旋转角度
	 */
	public static int getPhotoDegree(String path) {
		int degree = 0;
		try {
			ExifInterface exifInterface = new ExifInterface(path);
			int orientation = exifInterface.getAttributeInt(
					ExifInterface.TAG_ORIENTATION,
					ExifInterface.ORIENTATION_NORMAL);
			switch (orientation) {
			case ExifInterface.ORIENTATION_ROTATE_90:
				degree = 90;
				break;
			case ExifInterface.ORIENTATION_ROTATE_180:
				degree = 180;
				break;
			case ExifInterface.ORIENTATION_ROTATE_270:
				degree = 270;
				break;
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		return degree;
	}

	/**
	 * 
	 * 旋转 Bitmap
	 * @param degress 旋转角度
	 */
	public static Bitmap rotateBitmap(Bitmap bitmap, float degress) throws MyException {
		try {
			int bmpW = bitmap.getWidth();
			int bmpH = bitmap.getHeight();

			Matrix mt = new Matrix();
			mt.setRotate(degress);

			return Bitmap.createBitmap(bitmap, 0, 0, bmpW, bmpH, mt, true);
		} catch (Exception e) {
			throw new MyException(e);
		} catch (Error e) {
			throw new MyException(e);
		}
	}

	private Bitmap decodeFileBitmap(InputStream stream){
		if(stream!=null){  
			return BitmapFactory.decodeStream(stream);  
		}  
		else {  
			return null;  
		}  

	}

	private Bitmap decodeFileBitmap1(byte[] bytes) throws MyException {
		if (null == bytes)
			throw new MyException("bytes is null");

		try {
			BitmapFactory.Options options = new BitmapFactory.Options();
			options.inDither = false;
			options.inPurgeable = true;
			options.inInputShareable = true;
			options.inPreferredConfig = Bitmap.Config.ARGB_8888;

			// 获取这个图片的宽和高
			options.inJustDecodeBounds = true;
			BitmapFactory.decodeByteArray(bytes, 0, bytes.length, options);
			options.inJustDecodeBounds = false;

			int pictureW = options.outWidth;
			int pictureH = options.outHeight;

			int sampleSize = 1;

			int sampleSizeW = (int)Math.ceil(pictureW / Utility.getImageDimension());
			int sampleSizeH = (int)Math.ceil(pictureH / Utility.getImageDimension());

			if (sampleSizeW > 1 || sampleSizeH > 1) {
				sampleSize = Math.max(sampleSizeW, sampleSizeH);
			}

			options.inSampleSize = sampleSize;
			return BitmapFactory.decodeByteArray(bytes, 0, bytes.length, options);
		} catch (Exception ex) {
			ex.printStackTrace();
			throw new MyException(ex);
		} catch (Error ex) {
			ex.printStackTrace();
			System.gc();
			throw new MyException(ex);
		}
	}

	public Bitmap returnBitMap(final String strImagLink, final ImageCallback callback) {
		if (null == strImagLink || !strImagLink.endsWith("")) {
			return null;
		}

		Bitmap bitmap = GlobalCache.getBitmap(strImagLink);
		if (null != bitmap && !bitmap.isRecycled()){
			return bitmap;
		}

		final Handler handler = new Handler() {
			public void handleMessage(Message msg) {
				if(0 == msg.what){
					callback.imageLoaded((Bitmap) msg.obj, strImagLink);
				}else{
					callback.imageLoaded(null, null);
				}
			}
		};

		threadPool.execute(new getImagThread(strImagLink, handler));

		return null;
	}

	class getImagThread implements Runnable {
		private String strImagLink;
		private Handler handler;

		public getImagThread(String url, Handler hd) {
			this.strImagLink = url;
			this.handler = hd;
		}

		@Override
		public void run() {
			try {
				Bitmap bitmap = getBitmapFromURL(strImagLink);

				if (null != bitmap && !bitmap.isRecycled()) {
					handler.sendMessage(handler.obtainMessage(0, bitmap));
				} else {
					handler.sendMessage(handler.obtainMessage(1, null));
				}

				Thread.currentThread().interrupt();
			} catch (Exception e) {
				e.printStackTrace();
				Thread.currentThread().interrupt();
			}
		}

	}

	private Object lock = new Object();

	private volatile boolean mAllowLoad = true;

	private volatile boolean firstLoad = true;

	private volatile int mStartLoadLimit = 0;

	private volatile int mStopLoadLimit = 0;

	final Handler handler = new Handler();

	public interface OnImageLoadListener {
		public void onImageLoad(Integer t, Bitmap bitmap);
		public void onError(Integer t);
	}

	public void setLoadLimit(int startLoadLimit,int stopLoadLimit){
		if(startLoadLimit > stopLoadLimit){
			return;
		}
		mStartLoadLimit = startLoadLimit;
		mStopLoadLimit = stopLoadLimit;
	}

	public void restore(){
		mAllowLoad = true;
		firstLoad = true;
		mStartLoadLimit = 0;
		mStopLoadLimit = 0;
		unlock();
	}

	public void lock(){
		mAllowLoad = false;
		firstLoad = false;
	}

	public void unlock(){
		mAllowLoad = true;
		synchronized (lock) {
			lock.notifyAll();
		}
	}

	/**
	 * 
	 * unlock 后加载远端图片
	 */
	public void returnImage(final int position, final String imageUrl, final ImageCallback imageCallback) {
		if (null == imageUrl || "".equals(imageUrl) )
			return;

		threadPool.execute(new Runnable() {

			@Override
			public void run() {
				if(!mAllowLoad){
					synchronized (lock) {
						try {
							lock.wait();
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					}
				}

				if(mAllowLoad && firstLoad){
					loadImage(position, imageUrl, imageCallback);
				}

				if(mAllowLoad && position >= mStartLoadLimit && position <= mStopLoadLimit){
					loadImage(position, imageUrl, imageCallback);
				}
			}

		});
	}

	private void loadImage(final int position, final String imageUrl, final ImageCallback imageCallback){
		final Bitmap bitmap = GlobalCache.getBitmap(imageUrl);
		//		final Bitmap bitmap = NativeImageLoader.getInstance().getBitmapFromMemCache(imageUrl);
		if (null != bitmap && !bitmap.isRecycled()){
			handleBitmap(position, imageUrl, bitmap, imageCallback);
			return;
		}

		try {
			final Bitmap bitmapFromUrl = getBitmapFromURL(imageUrl);
			handleBitmap(position, imageUrl, bitmapFromUrl, imageCallback);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public Bitmap getBitmapFromURL(String imageUrl) throws MyException {
		if (null == imageUrl || "".equals(imageUrl))
			return null;
		try {
			InputStream inputStream = new URL(imageUrl).openStream();
			//Bitmap bitmap = decodeFileBitmap(Utility.readStreamAsByte(inputStream));//decodeFileBitmap(tmpFile, Utility.getBaseWidth(), Utility.getBaseHeight())
			Bitmap bitmap = decodeFileBitmap(inputStream);
//			System.out.println("22The bitmap width:" + bitmap.getWidth() + "  height:" + bitmap.getHeight());
			inputStream.close();

			if (null != bitmap && !bitmap.isRecycled()) {
				//				NativeImageLoader.getInstance().addBitmapToMemoryCache(imageUrl, bitmap);
				GlobalCache.putToCache(imageUrl, bitmap);
				return bitmap;
			}
		} catch (MalformedURLException e) {
			throw new MyException(e);
		} catch (IOException e) {
			throw new MyException(e);
		} catch (Exception e) {
			throw new MyException(e);
		} catch (Error e) {
			throw new MyException(e);
		}
		return null;
	}

	/**
	 * 
	 * unlock 后加载远端图片
	 */
	public void returnThumbImage(final int position, final String imageUrl, final ImageCallback imageCallback) {
		if (null == imageUrl || "".equals(imageUrl) )
			return;

		threadPool.execute(new Runnable() {

			@Override
			public void run() {
				if(!mAllowLoad){
					synchronized (lock) {
						try {
							lock.wait();
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					}
				}

				if(mAllowLoad && firstLoad){
					loadImage(position, imageUrl, 130, 130, imageCallback);
				}

				if(mAllowLoad && position >= mStartLoadLimit && position <= mStopLoadLimit){
					loadImage(position, imageUrl, 130, 130, imageCallback);
				}
			}

		});
	}

	private void loadImage(final int position, final String imageUrl, final int width, final int height, final ImageCallback imageCallback){
		final Bitmap bitmap = GlobalCache.getBitmap(imageUrl);
		if (null != bitmap && !bitmap.isRecycled()){
			handleBitmap(position, imageUrl, bitmap, imageCallback);
			return;
		}

		try {
			final Bitmap bitmapFromUrl = getBitmapFromURL(imageUrl, width, height);
			if (null != bitmap && !bitmap.isRecycled()) {
				GlobalCache.putToCache(imageUrl, bitmap);
			}
			handleBitmap(position, imageUrl, bitmapFromUrl, imageCallback);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * 
	 * 从 URL 获取图片 Bitmap， 不保存 Cache
	 */
	public Bitmap getBitmapFromURL(String imageUrl, int width, int height) throws MyException
	{
		if (null == imageUrl || "".equals(imageUrl))
			return null;

		try
		{
			InputStream inputStream = new URL(imageUrl).openStream();

			File tmp = new File(Utility.CACHE_ROOT + File.separator + imageUrl.lastIndexOf("/"));

			writeToFile(inputStream, tmp);

			try
			{
				if (null != inputStream) 
					inputStream.close();
			}
			catch (IOException ioe)
			{
			}

			Bitmap bitmap = decodeFileBitmap(tmp, width, height);

			tmp.delete();

			if (null != bitmap && !bitmap.isRecycled())
			{
				return bitmap;
			}
		}
		catch (Exception e)
		{
			throw new MyException(e);
		}
		catch (Error e)
		{
			System.gc();
			throw new MyException(e);
		}

		return null;
	}

	/**
	 * 将图片Stream 写入File
	 * 
	 */
	public void writeToFile(InputStream inputstream, File file) throws MyException
	{
		if (inputstream == null)
			throw new MyException("stream is null");

		BufferedInputStream inputBuffer = null;
		BufferedOutputStream outputBuffer = null;

		try{
			inputBuffer = new BufferedInputStream(inputstream);

			if (file.exists())
			{
				file.delete();
				file.createNewFile();
			}
			else
			{
				file.createNewFile();
			}

			outputBuffer = new BufferedOutputStream(new FileOutputStream(file));

			byte[] arrayOfByte = new byte[524288];

			int len = -1;

			while((len = inputBuffer.read(arrayOfByte)) != -1){
				outputBuffer.write(arrayOfByte, 0, len);
			}

			outputBuffer.flush();
		}
		catch(Exception ex)
		{
			throw new MyException(ex);
		}
		catch(Error err)
		{
			System.gc();
			throw new MyException(err);
		}
		finally
		{
			try {
				if (null != outputBuffer) 
					outputBuffer.close();
			} catch (IOException ioe) {
			}

			try {
				if(null != inputBuffer)
					inputBuffer.close();
			} catch (IOException ioe) {
			}
		}
	}

	/**
	 * 
	 * 加载远端图片
	 */
	public void returnImage(final String imageUrl, final ImageCallback imageCallback) {
		if (null == imageUrl || "".equals(imageUrl) )
			return;

		threadPool.execute(new Runnable() {

			@Override
			public void run() {
				final Bitmap bitmap = GlobalCache.getBitmap(imageUrl);
				if (null != bitmap && !bitmap.isRecycled()){
					handler.post(new Runnable() {
						@Override
						public void run() {
							imageCallback.imageLoaded(bitmap, imageUrl);
						}
					});
					return;
				}

				try {
					final Bitmap bitmapFromUrl = getBitmapFromURL(imageUrl);
					handler.post(new Runnable() {
						@Override
						public void run() {
							imageCallback.imageLoaded(bitmapFromUrl, imageUrl);
						}
					});
				} catch (Exception e) {
					e.printStackTrace();
				}
			}

		});
	}

	/**
	 * 
	 * unlock 后加载本地图片
	 */
	public void returnLocalImageThumb(final int position, final long videoId, final String imageUrl, final ImageCallback imageCallback){
		threadPool.execute(new Runnable() {

			@Override
			public void run() {
				if (!mAllowLoad) {
					synchronized (lock) {
						try {
							lock.wait();
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					}
				}

				if (mAllowLoad && firstLoad) {
					loadLocalImageThumb(position, videoId, imageUrl, imageCallback);
				}

				if (mAllowLoad && position >= mStartLoadLimit && position <= mStopLoadLimit) {
					loadLocalImageThumb(position, videoId, imageUrl, imageCallback);
				}
			}
		});
	}

	private void loadLocalImageThumb(final int position, long videoId, final String imageUrl, final ImageCallback imageCallback){
		final Bitmap bitmap = GlobalCache.getBitmap(imageUrl);
		if (null != bitmap && !bitmap.isRecycled()){
			handleBitmap(position, imageUrl, bitmap, imageCallback);
			return;
		}

		try {
			final Bitmap bitmapFromUrl = getLocalImageThumb(imageUrl, videoId, Images.Thumbnails.MICRO_KIND);
			handleBitmap(position, imageUrl, bitmapFromUrl, imageCallback);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public synchronized Bitmap getLocalImageThumb(String imageUrl, long id, int kind) {
		try {
			Bitmap bitmap = MediaStore.Images.Thumbnails.getThumbnail(MyApp.getApplication().getContentResolver(), id, kind, null);
			if (null != bitmap && !bitmap.isRecycled()) {
				GlobalCache.putToCache(imageUrl, bitmap);
				return bitmap;
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		} catch (Error ex) {
			ex.printStackTrace();
		}
		return null; 
	}

	/**
	 * 
	 * 加载本地视频缩略图
	 */
	public void returnLocalVideoThumb(final long videoId, final String imageUrl, final ImageCallback imageCallback){
		if (null == imageUrl || "".equals(imageUrl))
			return;

		threadPool.execute(new Runnable() {

			@Override
			public void run() {
				final Bitmap bitmap = GlobalCache.getBitmap(imageUrl);
				if (null != bitmap && !bitmap.isRecycled()){
					handler.post(new Runnable() {
						@Override
						public void run() {
							imageCallback.imageLoaded(bitmap, imageUrl);
						}
					});
					return;
				}

				try {
					final Bitmap bitmapFromLocal =  getLocalVideoThumb(imageUrl, videoId, Video.Thumbnails.MICRO_KIND);
					handler.post(new Runnable() {
						@Override
						public void run() {
							imageCallback.imageLoaded(bitmapFromLocal, imageUrl);
						}
					});
				} catch (Exception e) {
					e.printStackTrace();
				}
			}

		});
	}

	/**
	 * 
	 * unlock 后加载本地视频缩略图
	 */
	public void returnLocalVideoThumb(final int position, final long videoId, final String imageUrl, final ImageCallback imageCallback){
		threadPool.execute(new Runnable() {

			@Override
			public void run() {
				if(!mAllowLoad){
					synchronized (lock) {
						try {
							lock.wait();
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					}
				}

				if(mAllowLoad && firstLoad){
					loadLocalVideoThumb(position, videoId, imageUrl,imageCallback);
				}

				if(mAllowLoad && position >= mStartLoadLimit && position <= mStopLoadLimit){
					loadLocalVideoThumb(position, videoId, imageUrl, imageCallback);
				}
			}

		});
	}

	private void loadLocalVideoThumb(final int position, long videoId, final String imageUrl, final ImageCallback imageCallback){
		if (null == imageUrl || "".equals(imageUrl))
			return;

		final Bitmap bitmap = GlobalCache.getBitmap(imageUrl);
		if (null != bitmap && !bitmap.isRecycled()){
			handleBitmap(position, imageUrl, bitmap, imageCallback);
			return;
		}

		try {
			final Bitmap bitmapFromLocal =  getLocalVideoThumb(imageUrl, videoId, Video.Thumbnails.MICRO_KIND);
			handleBitmap(position, imageUrl, bitmapFromLocal, imageCallback);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public synchronized Bitmap getLocalVideoThumb(String strImagLink, long id, int kind) {
		try {
			Bitmap bitmap = MediaStore.Video.Thumbnails.getThumbnail(MyApp.getApplication().getContentResolver(), id, kind, null);
			if (null != bitmap && !bitmap.isRecycled()) {
				GlobalCache.putToCache(strImagLink, bitmap);
				return bitmap;
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		} catch (Error ex) {
			ex.printStackTrace();
		}
		return null;
	}

	/**
	 * 
	 * 加载远端视频缩略图
	 */
	public void returnVideoThumbFromURL(final int position, final String imageUrl, final ImageCallback imageCallback){
		if (null == imageUrl || "".equals(imageUrl) )
			return ;

		threadPool.execute(new Runnable() {

			@Override
			public void run() {
				if(!mAllowLoad){
					synchronized (lock) {
						try {
							lock.wait();
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					}
				}

				if(mAllowLoad && firstLoad){
					loadVideoThumbFromURL(position, imageUrl, imageCallback);
				}

				if(mAllowLoad && position >= mStartLoadLimit && position <= mStopLoadLimit){
					loadVideoThumbFromURL(position, imageUrl, imageCallback);
				}
			}

		});
	}

	private void loadVideoThumbFromURL(final int position, final String imageUrl, final ImageCallback imageCallback){
		final Bitmap bitmap = GlobalCache.getBitmap(imageUrl);
		if (null != bitmap && !bitmap.isRecycled()){
			handleBitmap(position, imageUrl, bitmap, imageCallback);
			return;
		}

		try {
			final Bitmap d = getVideoThumbnailBitmapFromURL(imageUrl);
			handleBitmap(position, imageUrl, d, imageCallback);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public Bitmap getVideoThumbnailBitmapFromURL(String imageUrl) throws MalformedURLException, IOException {
		if (null == imageUrl || "".equals(imageUrl))
			return null;

		try {

			Bitmap bitmap = ThumbnailUtils.createVideoThumbnail(imageUrl, Thumbnails.MICRO_KIND);

			if (null != bitmap && !bitmap.isRecycled()) {
				GlobalCache.putToCache(imageUrl, bitmap);
				return bitmap;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}

	private void handleBitmap(final Integer mt, final String strImagLink, final Bitmap bitmap, final ImageCallback imageCallback) {
		handler.post(new Runnable() {
			@Override
			public void run() {
				if(firstLoad ||(mt >= mStartLoadLimit && mt <= mStopLoadLimit))
				{
					imageCallback.imageLoaded(bitmap, strImagLink);
				}
			}
		});
	}

	public String[] queryImageThumbIdAndData(String[] selectionArgs) {
		Uri uri = MediaStore.Images.Thumbnails.EXTERNAL_CONTENT_URI;
		String[] projection = new String[]{
				MediaStore.Images.Thumbnails._ID,
				MediaStore.Images.Thumbnails.DATA,
		};
		String selection = MediaStore.Images.Thumbnails.IMAGE_ID + "=?";
		String[] str = queryThumbnail(uri, projection, selection, selectionArgs);
		return str;
	}

	public String[] queryVideoThumbIdAndData(String[] selectionArgs) {
		Uri uri = MediaStore.Video.Thumbnails.EXTERNAL_CONTENT_URI;
		String[] projection = new String[]{
				MediaStore.Video.Thumbnails._ID,
				MediaStore.Video.Thumbnails.DATA,
		};
		String selection = MediaStore.Video.Thumbnails.VIDEO_ID + "=?";
		String[] str = queryThumbnail(uri, projection, selection, selectionArgs);
		return str;
	}

	public String[] queryAudioThumbIdAndData(String[] selectionArgs) {
		Uri uri = MediaStore.Audio.Albums.EXTERNAL_CONTENT_URI;
		String[] projection = new String[]{
				MediaStore.Audio.Albums._ID,
				MediaStore.Audio.Albums.ALBUM_ART,
		};
		String selection = MediaStore.Audio.Albums._ID + "=?";
		String[] str = queryThumbnail(uri, projection, selection, selectionArgs);
		return str;
	}

	public String[] queryThumbnail(Uri uri, String[] projection, String selection, String[] selectionArgs) {
		Cursor thumbCursor = MyApp.getResolver().query(uri, projection, selection, selectionArgs, null);
		String[] str = new String[2];
		if (thumbCursor != null && thumbCursor.getCount() != 0) {
			thumbCursor.moveToFirst();

			int columnId = thumbCursor.getColumnIndex(projection[0]);
			int columnData = thumbCursor.getColumnIndex(projection[1]);
			str[0] = thumbCursor.getLong(columnId) + "";
			str[1] = thumbCursor.getString(columnData);
		}
		if(null != thumbCursor)
			thumbCursor.close();
		return str;
	}
}
