package com.explorer.common;

import java.io.File;
import java.lang.ref.SoftReference;
import java.util.HashMap;
import java.util.List;
import android.util.Log;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.text.TextUtils.TruncateAt;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;
import java.io.FileDescriptor;
import java.io.FileOutputStream;
import com.explorer.R;
import android.graphics.BitmapFactory.Options;
import android.graphics.Bitmap.Config;
import android.os.ParcelFileDescriptor;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import android.os.Handler;

/**
 * data adapter
 * @author liu_tianbao Provide data for the list or thumbnail
 */
public class FileAdapter extends BaseAdapter {
	// filder
	private Bitmap folder_File;

	// music file
	private Bitmap music_File_mp3;

	// other file
	private Bitmap other_File;

	// vedio file
	private Bitmap vedio_File;

	// bd file
	private Bitmap bd_File;

    // dvd file
	private Bitmap dvd_File;

	// APK file
	private Bitmap apk_File;

	// picturn file
	private Bitmap img_File;

	// file list
	private List<File> list;

	// layout file ID
	private int layout = 0;

	private Handler handler = new Handler();

    private ExecutorService executorService = Executors.newFixedThreadPool(1);

	/**
	 * @brief : Eliminating redundant code
	 */

	LayoutInflater inflater;

	CommonActivity context;

	String fileLength = null;

	/**
	 * @param context
	 *            page
	 * @param list
	 *            collection of files
	 * @param fileString
	 *            file path
	 * @param layout
	 *            data layout
	 */
	// public FileAdapter(Activity context, List<File> list, int layout) {
	public FileAdapter(CommonActivity context, List<File> list, int layout) {
		/**
		 * Initialization parameters
		 */
		this.list = list;
		this.layout = layout;
		inflater = LayoutInflater.from(context);
		this.context = context;
        this.imageCache = new HashMap<String, SoftReference<Bitmap>>();

		/*
		 * According to the different file types together with the different
		 * picture
		 */
		/* CNcomment: 根据不同的文件类型配以不同的图片显示 */

		other_File = BitmapFactory.decodeResource(context.getResources(),
		R.drawable.otherfile);
		apk_File = BitmapFactory.decodeResource(context.getResources(),
		R.drawable.list);
		vedio_File = BitmapFactory.decodeResource(context.getResources(),
		R.drawable.vediofile);
		bd_File = BitmapFactory.decodeResource(context.getResources(),
		R.drawable.bdfile);
        dvd_File = BitmapFactory.decodeResource(context.getResources(),
		R.drawable.dvdfile);
		music_File_mp3 = BitmapFactory.decodeResource(context.getResources(),
		R.drawable.mp3file);
		folder_File = BitmapFactory.decodeResource(context.getResources(),
		R.drawable.folder_file);
		img_File = BitmapFactory.decodeResource(context.getResources(),
		R.drawable.imgfile);


	}

	/* he number of data containers */
	/* CNcomment: 获得容器中数据的数目 */

	public int getCount() {
		return list.size();
	}

	public void addFile(File file) {
		this.list.add(file);
	}

	public void addDir(int location, File file) {
		this.list.add(location, file);
	}

	/* For each option object container */
	/* CNcomment: 获得容器中每个选项对象 */

	public Object getItem(int position) {
		return position;
	}

	/* Access to each option in the container object */
	/* CNcomment: 获得容器中每个选项对象的ID */

	public long getItemId(int position) {
		return position;
	}

	public List<File> getFiles() {
		return list;
	}

	/* Assignment for each option object */
	/* CNcomment: 为每个选项对象赋值 */

	public View getView(final int position, View convertView, ViewGroup parent) {
		return getMyView(convertView, position);
	}

    private View getMyView(View convertView, final int position) {
		// Control container
		final ViewHolder holder;

		/*
		 * According to the view whether there is to initialize the controls in
		 * each data container
		 */
		/* CNcomment: 根据视图是否存在 初始化每个数据容器中的控件 */

		if (convertView == null) {
		holder = new ViewHolder();
		convertView = inflater.inflate(layout, null);
		holder.text = (TextView) convertView.findViewById(R.id.text);
		holder.sizetext = (TextView) convertView
		.findViewById(R.id.sizeText);
		holder.icon = (ImageView) convertView.findViewById(R.id.image_Icon);
		convertView.setTag(holder);
		} else {
		holder = (ViewHolder) convertView.getTag();
		}

		final File f;
		// f = list.get(position);
		f = list.get(position);
        final String f_type = FileUtil.getMIMEType(f, context);
		// get the type of file
		if (f.isFile()) {
		if ("audio/*".equals(f_type)) {
		holder.icon.setImageBitmap(music_File_mp3);
		} else if ("video/*".equals(f_type) || "video/iso".equals(f_type)) {
		holder.icon.setImageBitmap(vedio_File);
		} else if ("apk/*".equals(f_type)) {
		holder.icon.setImageBitmap(apk_File);
		} else if ("image/*".equals(f_type)) {
		holder.icon.setImageBitmap(img_File);
		} else if ("video/dvd".equals(f_type)) {
		holder.icon.setImageBitmap(vedio_File);
		} else {
		holder.icon.setImageBitmap(other_File);
		}
		} else {
		if ("video/bd".equals(f_type)) {
		holder.icon.setImageBitmap(bd_File);
		} else if("video/dvd".equals(f_type)) {
		    holder.icon.setImageBitmap(dvd_File);
            } else {
		holder.icon.setImageBitmap(folder_File);
		}
		}

		// Judge the thumbnail display format of the text
		// CNcomment:判断缩略图时文字的显示格式
		if (layout == R.layout.gridfile_row) {
		if (holder.text.getPaint().measureText(f.getName()) >= holder.text
		.getLayoutParams().width) {
		holder.text.setEllipsize(TruncateAt.MARQUEE);
		holder.text
		.setMarqueeRepeatLimit(android.R.attr.marqueeRepeatLimit);
		holder.text.setHorizontallyScrolling(true);
		} else {
		holder.text.setGravity(Gravity.CENTER_HORIZONTAL);
		}
		holder.icon.setTag(f.getName());
		 if ("image/*".equals(f_type)) {

                if (imageCache.containsKey(f.getName())) {
                    SoftReference<Bitmap> cache = imageCache.get(f.getName());
                    Bitmap bitmap = cache.get();

                    if (bitmap != null) {
                        holder.icon.setImageBitmap(bitmap);
                    }
					else{
						new MyAsyncTask().execute(holder.icon, f);
					}

                } else {
                    new MyAsyncTask().execute(holder.icon, f);
                }

		 }
		} else {
		if (f.isFile()) {
		fileLength = FileUtil.fileSizeMsg(f);
		holder.sizetext.setText(fileLength);
		} else {
		holder.sizetext.setText("");
		}
		}

		holder.text.setText(f.getName());
		return convertView;
	}

	/**
	 * the type of control container
	 * @author qian_wei save control
	 */
	private static class ViewHolder {
		private TextView text;
		private TextView sizetext;
		private ImageView icon;
	}

    private synchronized Bitmap buildThum(File f) {
		Log.i("liangguofu","****buildThum in ");
        String paths = f.getPath();
		Bitmap bitmap = null;
		ParcelFileDescriptor fd = null;
		try{
		fd = ParcelFileDescriptor.open(f,ParcelFileDescriptor.MODE_READ_ONLY);
		}
		catch(Exception e){

		}
		if(fd!=null)
		{
		try{
		Options options = new Options();
		options.inPreferredConfig = Config.ARGB_8888;
		options.inDither = true;
		options.inPurgeable = true;
		options.inInputShareable = false;
		options.inPreferredConfig = null;

		bitmap = DecodeUtils.decodeThumbnail(fd.getFileDescriptor(),options,200);
		}catch (OutOfMemoryError err) {

		}
		Utils.closeSilently(fd);
		}
        return bitmap;
    }

    private HashMap<String, SoftReference<Bitmap>> imageCache;

    public class MyAsyncTask extends AsyncTask<Object, Integer, Bitmap> {

        private ImageView imageView;
        private File file;

        public MyAsyncTask() {
            if (null == imageCache)
                imageCache = new HashMap<String, SoftReference<Bitmap>>();
        }

        @Override
        protected Bitmap doInBackground(Object... arg0) {
            file = (File) arg0[1];
            imageView = (ImageView) arg0[0];
            Bitmap bitmap = null;
            String key = file.getName();
            if (null != key) {
                bitmap = buildThum(file);
            }
            return bitmap;

        }

        @Override
        protected void onPostExecute(Bitmap result) {
			if (null != result)
			{
				imageCache.put(file.getName(), new SoftReference<Bitmap>(result));
				if (null != imageView&&file.getName().equals(imageView.getTag()))
					imageView.setImageBitmap(result);
			}
            imageView = null;
        }
    }
}
