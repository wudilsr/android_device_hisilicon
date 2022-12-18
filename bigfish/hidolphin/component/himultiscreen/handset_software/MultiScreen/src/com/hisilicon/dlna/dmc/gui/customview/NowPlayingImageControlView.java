package com.hisilicon.dlna.dmc.gui.customview;

import java.util.List;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.Gallery;
import android.widget.ImageView;
import android.widget.LinearLayout;

import com.hisilicon.dlna.dmc.processor.impl.PlaylistProcessorImpl;
import com.hisilicon.dlna.dmc.processor.impl.UpnpProcessorImpl;
import com.hisilicon.dlna.dmc.processor.interfaces.PlaylistProcessor;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem;
import com.hisilicon.dlna.dmc.processor.model.PlaylistItem.ViewMode;
import com.hisilicon.multiscreen.mybox.R;

public class NowPlayingImageControlView extends LinearLayout {
	private static final int SHOW_NEXT_IMAGE = 1;
	private static final int SLIDE_MILLISECOND = 5000;
	private LinearLayout rc_imagebottom_controlview;
	private ImageView rc_playorpause;
	private ImageView rc_thumbnail;
	private Gallery rc_image_thumbs;
	private PlayingImageAdapter m_adapter;
	private volatile boolean mIsSlideShowMode = false;

	public NowPlayingImageControlView(Context context) {
		super(context);
		initComponents();
	}

	public NowPlayingImageControlView(Context context, AttributeSet attrs) {
		super(context, attrs);
		initComponents();
	}

	private void initComponents() {
		((LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE)).inflate(R.layout.playingimage_control, this);

		rc_imagebottom_controlview = (LinearLayout) findViewById(R.id.rc_imagebottom_controlview);

		rc_playorpause = (ImageView) findViewById(R.id.rc_playorpause);
		rc_playorpause.setOnClickListener(onSlideShowClick);

		rc_thumbnail = (ImageView) findViewById(R.id.rc_thumbnail);
		rc_thumbnail.setOnClickListener(onThumbsClick);

		rc_image_thumbs = (Gallery) findViewById(R.id.rc_image_thumbs);
		m_adapter = new PlayingImageAdapter(getContext());
		rc_image_thumbs.setAdapter(m_adapter);
		rc_image_thumbs.setOnItemClickListener(m_itemClick);
		rc_image_thumbs.setOnItemSelectedListener(new OnItemSelectedListener() {

			@Override
			public void onItemSelected(AdapterView<?> parent, View view,
					int position, long id) {
				m_adapter.setCurrentPosition(position);
				m_adapter.notifyDataSetChanged();
			}

			@Override
			public void onNothingSelected(AdapterView<?> parent) {

			}
		});
	}

	private OnClickListener onSlideShowClick = new OnClickListener() {

		@Override
		public void onClick(View v) {
			if (mIsSlideShowMode)
			{
				stopSlideShow();
				rc_playorpause.setImageResource(R.drawable.rc_quick_pause);
			}
			else
			{
				startSlideShow();
				rc_playorpause.setImageResource(R.drawable.rc_quick_play);
			}
		}
	};

	private OnClickListener onThumbsClick = new OnClickListener() {

		@Override
		public void onClick(View v) {
			if (rc_image_thumbs.isShown())
			{
				hidethumbs();
			}
			else
			{
				showthumbs();
			}
		}
	};

	public void onDestroy() {
		if (mIsSlideShowMode)
			stopSlideShow();
	}

	public void onTab(boolean flage) {
//		System.out.println("come into tab:"+flage);
		onGoneThumb();

		if (isShown()) {
			setVisibility(View.GONE);
		} else {
			if(!flage)
				setVisibility(View.VISIBLE);
		}
	}

	public void onGoneThumb() {
		if (rc_image_thumbs.isShown()) {
			hidethumbs();
		}
	}

	public void startSlideShow()
	{
		mIsSlideShowMode = true;
		mHandler.removeMessages(SHOW_NEXT_IMAGE);
		mHandler.sendEmptyMessage(SHOW_NEXT_IMAGE);
	}

	public void stopSlideShow()
	{
		mIsSlideShowMode = false;
		mHandler.removeMessages(SHOW_NEXT_IMAGE);
	}

	private Handler mHandler = new Handler()
	{
		public void handleMessage(Message msg)
		{
			switch (msg.what)
			{
			case SHOW_NEXT_IMAGE:
				mHandler.removeMessages(SHOW_NEXT_IMAGE);
				showNextImage();
				mHandler.sendEmptyMessageDelayed(SHOW_NEXT_IMAGE, SLIDE_MILLISECOND);
				break;
			}
		}
	};

	private void showNextImage()
	{
		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
		if (playlistProcessor != null)
			playlistProcessor.next();
	}

	private void showthumbs() {
		rc_imagebottom_controlview.setBackgroundResource(R.drawable.rc_image_footer_thumb_check);
		rc_image_thumbs.setVisibility(View.VISIBLE);

		PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();

		if (playlistProcessor!= null ) {
			List list = playlistProcessor.getItemsByViewMode(ViewMode.IMAGE_ONLY);
			m_adapter.setItemList(list);

			int currentIndex = playlistProcessor.getCurrentItemIndex();
			rc_image_thumbs.setSelection(currentIndex);
		}
	}

	private void hidethumbs() {
		rc_imagebottom_controlview.setBackgroundResource(R.drawable.rc_image_footer_control_bg);
		rc_image_thumbs.setVisibility(View.GONE);
		m_adapter.setItemList(null);
	}

	private OnItemClickListener m_itemClick = new OnItemClickListener() {

		@SuppressWarnings("rawtypes")
		@Override
		public void onItemClick(AdapterView<?> adapter, View view, int position, long arg3) {

			PlaylistProcessor playlistProcessor = UpnpProcessorImpl.getSington().getPlaylistProcessor();
			if (null == playlistProcessor) {
				playlistProcessor = new PlaylistProcessorImpl();
				UpnpProcessorImpl.getSington().setPlaylistProcessor(playlistProcessor);
				List list = m_adapter.getItemList();
				playlistProcessor.setItems(list);
			}

			AdapterItem item = m_adapter.getItem(position);
			if (item instanceof PlaylistItem) {
				playlistProcessor.setCurrentItem((PlaylistItem) item);
				hidethumbs();
			}
		}
	};

}
