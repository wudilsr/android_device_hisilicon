package com.HiMediaSample;


import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.Window;
import android.util.Log;
import android.util.TypedValue;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnKeyListener;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.HashMap;

import android.graphics.Color;
import android.view.View;
import android.view.ViewGroup;
import android.view.LayoutInflater;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.ScrollView;
import android.widget.TimePicker;

import android.widget.BaseAdapter;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;
import android.widget.RelativeLayout;


/**
 * for test switch channel
 */

public class SwitchChannel extends Activity {

    private String LOG_TAG = "SwitchChannel";
    private static int urlIndex = 0;
    private List<String> urlLists;

    private static final int MEDIA_INFO_FIRST_FRAME_AFTER_SEEK = 1014;
    private static final int MSG_PLAY = 100;
    private static final int MSG_PAUSE_RESUME = 101;
    private static final int MSG_STOP = 102;
    private static final int MSG_DESTROY = 103;
    private static final int MSG_PLAY_NEXT = 104;
    private static final int MSG_PLAY_PREV = 105;
    private static final int MSG_SEEK  = 106;

    private int fileDuration = 0;

    private int hour = 0;

    private int minute = 0;

    public int limitHour = 0;

    public int limitMinute = 0;

    public int limitSeconds = 0;

    private TimePicker timePicker;

	Handler playHandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case MSG_PLAY:
			//	urlIndex ++;
				if (urlIndex >= urlLists.size()) {
					urlIndex = 0;
				} else if (urlIndex < 0) {
					urlIndex = urlLists.size() - 1;
				}
				if (mAdapter != null) {
					mAdapter.setSelectItem(urlIndex);
					mAdapter.notifyDataSetInvalidated();
				}
				videoView.setVideoPath(urlLists.get(urlIndex));
				break;
			case MSG_PLAY_NEXT:
				urlIndex ++;
				if (urlIndex >= urlLists.size()) {
					urlIndex = 0;
				} else if (urlIndex < 0) {
					urlIndex = urlLists.size() - 1;
				}
				if (mAdapter != null) {
					mAdapter.setSelectItem(urlIndex);
					mAdapter.notifyDataSetInvalidated();
				}
				videoView.setVideoPath(urlLists.get(urlIndex));
				break;
			case MSG_PLAY_PREV:
				urlIndex --;
				if (urlIndex >= urlLists.size()) {
					urlIndex = 0;
				} else if (urlIndex < 0) {
					urlIndex = urlLists.size() - 1;
				}
				if (mAdapter != null) {
					mAdapter.setSelectItem(urlIndex);
					mAdapter.notifyDataSetInvalidated();
				}
				videoView.setVideoPath(urlLists.get(urlIndex));
				break;
			case MSG_PAUSE_RESUME:
			    if(videoView.isPlaying())
			    {
			        videoView.pause();
			    }
			    else
			    {
			        videoView.resume();
			    }
			    break;

			case MSG_STOP:
	        case MSG_DESTROY:
	            videoView.stopPlayback();
	             break;
			case MSG_SEEK:
				Log.v("SEEK2", "Jump to seek dialog...");
				setJumpToDialog(R.string.jumpto, videoView.getCurrentPosition(), videoView);
				break;
			}
		}
	};

	private void setSeekInfo(boolean isStart, int seekSeconds)
	{
		if (isStart) {
			mSeekStartTimeInMs = System.currentTimeMillis();
			mSeekInfo = "[SEEK2] " + mSeekStartTimeInMs + " start seek to " + seekSeconds + " seconds...duration=" + fileDuration + "ms.\n";
			if (dynamicInfoView != null) {
			//	Log.v("SEEK2", "" + mSeekInfo);
				dynamicInfoView.setText(mSeekInfo);
			}
			Log.v("SEEK2", "" + mSeekStartTimeInMs + " start seek to " + seekSeconds + " seconds...duration=" + fileDuration + "ms.");
		} else {
			mSeekEndTimeInMs = System.currentTimeMillis();
			mSeekInfo += "[SEEK2] " + mSeekEndTimeInMs + " first video frame received after seek, seek consume " + (mSeekEndTimeInMs - mSeekStartTimeInMs) + "ms.\n";
			dynamicInfoView.setText(mSeekInfo);
			Log.v("SEEK2", "" + mSeekEndTimeInMs + " first video frame received after seek, seek consume " + (mSeekEndTimeInMs - mSeekStartTimeInMs));
		}

	}

    private void setJumpToDialog(final int title, int miniTime, final ChannelVideoView videoView)
    {
        int m = miniTime / 1000 / 60;

        minute = m % 60;
        hour = m / 60;
        final AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle(title);
        LayoutInflater inflater = this.getLayoutInflater();
        RelativeLayout linear = (RelativeLayout)inflater.inflate(R.layout.jumpto, null);
        timePicker = (TimePicker)linear.findViewById(R.id.timePicker);
        timePicker.setIs24HourView(true);
        timePicker.setCurrentHour(hour);
        timePicker.setCurrentMinute(minute);
        timePicker.setOnTimeChangedListener(new TimePicker.OnTimeChangedListener()
                                            {
                                                public void onTimeChanged(TimePicker view, int hourOfDay, int minute)
                                                {
                                                    if (view.getCurrentHour() > limitHour)
                                                    {
                                                        view.setCurrentHour(limitHour);
                                                    }

                                                    if (view.getCurrentHour() > 0)
                                                    {
                                                        int timeMinute = limitMinute % 60;
                                                        if (view.getCurrentMinute() > timeMinute)
                                                        {
                                                            view.setCurrentMinute(timeMinute);
                                                        }
                                                    }

                                                    if (view.getCurrentMinute() > limitMinute)
                                                    {
                                                        view.setCurrentMinute(limitMinute);
                                                    }

                                                    hour = view.getCurrentHour();
                                                    SwitchChannel.this.minute = view.getCurrentMinute();
                                                }
                                            });
        builder.setView(linear);
        builder.setPositiveButton(R.string.confirm, new DialogInterface.OnClickListener()
                                  {
                                      public void onClick(DialogInterface dialog, int which)
                                      {
                                          timePicker.clearFocus();
                                          hour = timePicker.getCurrentHour();
                                          minute = timePicker.getCurrentMinute();
                                          if (!((hour > limitHour) || (minute > limitMinute)))
                                          {
                                              Log.v("SEEK2", "Confirm Seekto hour=" + hour + " minute=" + minute);
                                              setSeekInfo(true, hour * 60 * 60 + minute * 60);
                                              videoView.seekTo(hour * 60 * 60 * 1000 + minute * 60 * 1000);
                                          }
                                      }
                                  });

        AlertDialog dialog = builder.create();
        dialog.setOnKeyListener(new OnKeyListener()
        {
            @Override
            public boolean onKey(DialogInterface dialog, int keyCode, KeyEvent event)
            {
                if (keyCode == KeyEvent.KEYCODE_ENTER || keyCode == KeyEvent.KEYCODE_DPAD_CENTER)
                {
                    if (!((hour > limitHour) || (minute > limitMinute)))
                    {
                        Log.v("SEEK2", "onKey Seekto hour=" + hour + " minute=" + minute);
                        setSeekInfo(true, hour * 60 * 60 + minute * 60);
                        videoView.seekTo(hour * 60 * 60 * 1000 + minute * 60 * 1000);
                        dialog.dismiss();
                    }
                }
                return false;
            }
        });
        dialog.show();
        dialog.getButton(DialogInterface.BUTTON_POSITIVE).requestFocus();
    }

	/* Initialization play url list */
	private void initVideoLists() {
		urlLists = new ArrayList<String>();

		for (int i = 0;; i++) {
			String configVideoPath = PropertyManager.getInstance()
					.getConfigProperty("url" + i);

			if (null != configVideoPath && !"".equals(configVideoPath)) {
				urlLists.add(configVideoPath);
			}
			else {
				break;
			}

		}

		Log.d(LOG_TAG, "## initVideoLists URL Lists = " + urlLists.size()
			+ " " + urlLists);
	}

	private void prepareChannelListView() {
		mList = new ArrayList<Map<String, Object>>();
		channelListView = (ListView)findViewById(R.id.channellist_view);

		int len, start;
		String shortName;

		if (mAdapter == null) {
			mAdapter = new MyAdapter(this);
		}

		if (channelListView == null || mList == null || mAdapter == null) {
			return;
		}

		for (int i=0; i < urlLists.size(); i++) {
			String url = urlLists.get(i);

			start = 0;
			len = url.length();
			if (len > 120) {
				start = len - 120;
		    }
			shortName = url.substring(start);

			Map<String, Object> map = new HashMap<String, Object>();
			String channlNum = Integer.toString(i) + "   ";
			map.put("title", channlNum);
			map.put("url",  shortName);
			mList.add(map);
		}

		mAdapter.setSelectItem(urlIndex);
		channelListView.setAdapter(mAdapter);
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.v(LOG_TAG, "## SwitchChannel start ");
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		ChannelVideoView.create();
		setContentView(R.layout.switch_channel);
		initVideoLists();
		videoView = ((ChannelVideoView) findViewById(R.id.videoView));
		videoView.setOnPreparedListener(mPreparedListener);
		videoView.setOnCompletionListener(mCompletionListener);
		videoView.setOnErrorListener(mOnErrorListener);
		videoView.setOnInfoListener(mOnInfoListener);
		videoView.setSeekCompleteListener(mOnSeekCompleteListener);

		prepareChannelListView();
		dynamicInfoView = (TextView)findViewById(R.id.dynamicinfo_view);
		//dynamicInfoView.setTextColor(0xff0000);
		playHandler.sendEmptyMessage(MSG_PLAY);
		mSwitchStartTimeInMs = System.currentTimeMillis();
		mSwitchInfo = "[SWC] " + mSwitchStartTimeInMs + " Start play first channel!\n";
		if (dynamicInfoView != null) {
			Log.v("SWC", "" + mSwitchInfo);
			dynamicInfoView.setText(mSwitchInfo);
		}
	}

	private ChannelVideoView videoView = null;
	private ListView channelListView = null;
	private List<Map<String, Object>> mList = null;
	MyAdapter mAdapter = null;

	private TextView dynamicInfoView = null;
	private String mSwitchInfo;
	private long mSwitchStartTimeInMs = 0;
	private long mSwitchEndTimeInMs = 0;
	private long mSeekStartTimeInMs = 0;
	private long mSeekEndTimeInMs = 0;
	private String mSeekInfo;

	private MediaPlayer.OnPreparedListener mPreparedListener = new MediaPlayer.OnPreparedListener() {
		public void onPrepared(MediaPlayer paramMediaPlayer) {
			int temp;
			// playerHandler.sendEmptyMessage(uiAction.MEDIAPLAYER_ONPREPAREED);
			videoView.start();

			fileDuration = videoView.getDuration();

			temp = fileDuration / 1000 / 60;
			limitHour   = temp / 60;
			limitMinute = temp;
			if (limitHour <= 0 && limitMinute <= 0) {
				limitSeconds = fileDuration/1000;
			} else {
				limitSeconds = 59;
			}
			Log.v("[SEEK2]", "Meida Prepared, duration=" + fileDuration + ", limitHour=" + limitHour + " limitMinute=" + limitMinute);
			//channelListView.start();
			//dynamicInfoView.start();
		}
	};

	private MediaPlayer.OnCompletionListener mCompletionListener = new MediaPlayer.OnCompletionListener() {
		public void onCompletion(MediaPlayer paramMediaPlayer) {
			// playerHandler.sendEmptyMessage(uiAction.MEDIAPLAYER_ONCOMPLET);
		}
	};
	private MediaPlayer.OnErrorListener mOnErrorListener = new MediaPlayer.OnErrorListener() {
		public boolean onError(MediaPlayer paramMediaPlayer, int paramInt1, int paramInt2) {
			// playerHandler.sendEmptyMessage(uiAction.MEDIAPLAYER_ONERROE);
			return false;
		}
	};
	private MediaPlayer.OnInfoListener mOnInfoListener = new MediaPlayer.OnInfoListener() {
		public boolean onInfo(MediaPlayer mp, int what, int extra) {
			Log.v("SWC", "Info/Warning what= " + what +" extra= " + extra);
			switch (what) {
				case MediaPlayer.MEDIA_INFO_VIDEO_RENDERING_START:
					mSwitchEndTimeInMs = System.currentTimeMillis();
					mSwitchInfo += "[SWC] " + mSwitchEndTimeInMs + " MEDIA_INFO_VIDEO_RENDERING_START received, switch consume " + (mSwitchEndTimeInMs - mSwitchStartTimeInMs) + "ms."  + " duration=" + fileDuration + "ms.\n";
					dynamicInfoView.setText(mSwitchInfo);
					Log.v("SWC", "" + mSwitchEndTimeInMs + " MEDIA_INFO_VIDEO_RENDERING_START recevied, switch consume " + (mSwitchEndTimeInMs - mSwitchStartTimeInMs) + " duration=" + fileDuration + "ms.");
					break;
				case ChannelVideoView.MEDIAINFO_PLAYER_DESTROYED:
					{
					long destroyTime = System.currentTimeMillis();
					mSwitchInfo += "[SWC] " + destroyTime + " MediaPlayer destroyed,  consume " + (destroyTime - mSwitchStartTimeInMs) + "ms.\n";
					dynamicInfoView.setText(mSwitchInfo);
					Log.v("SWC", "" + mSwitchEndTimeInMs + " MediaPlayer destroyed,  consume " + (destroyTime - mSwitchStartTimeInMs));
					}
					break;
				case MEDIA_INFO_FIRST_FRAME_AFTER_SEEK:
					setSeekInfo(false, 0);
				default:;
			}


			return true;
		}
	};

	private MediaPlayer.OnSeekCompleteListener mOnSeekCompleteListener = new MediaPlayer.OnSeekCompleteListener() {
		public void onSeekComplete(MediaPlayer mp) {
		}
	};

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		return true;
	}

	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (event.getAction() == KeyEvent.ACTION_DOWN) {
			switch (keyCode) {

			case KeyEvent.KEYCODE_DPAD_DOWN:
				mSwitchStartTimeInMs = System.currentTimeMillis();
				mSwitchInfo = "[SWC] " + mSwitchStartTimeInMs + " Button Down Down,switch to prev channel...\n";
				if (dynamicInfoView != null) {
					Log.v("SWC", "" + mSwitchInfo);
					dynamicInfoView.setText(mSwitchInfo);

				}
				playHandler.sendEmptyMessage(MSG_PLAY_PREV);
				Log.v("SWC", "" + mSwitchStartTimeInMs + " Button Down Down,switch to prev channel...");
				break;
			case KeyEvent.KEYCODE_DPAD_UP:
				mSwitchStartTimeInMs = System.currentTimeMillis();
				mSwitchInfo = "[SWC] " + mSwitchStartTimeInMs + " Button Up Down ,switch to next channel...\n";
				if (dynamicInfoView != null) {
					Log.v("SWC", "" + mSwitchInfo);
					dynamicInfoView.setText(mSwitchInfo);
				}
				playHandler.sendEmptyMessage(MSG_PLAY_NEXT);
				Log.v("SWC", "" + mSwitchStartTimeInMs + " Button Up Down ,switch to next channel...");
				break;

			case KeyEvent.KEYCODE_DPAD_CENTER:
			    playHandler.sendEmptyMessage(MSG_PAUSE_RESUME);
			    break;

			case KeyEvent.KEYCODE_BACK:
			    playHandler.sendEmptyMessage(MSG_DESTROY);
			    break;
			case KeyEvent.KEYCODE_DPAD_LEFT:
			case KeyEvent.KEYCODE_DPAD_RIGHT:
				Log.v("SEEK2", "Button Left/Right down, send MSG_SEEK....");
			    playHandler.sendEmptyMessage(MSG_SEEK);
			    break;

			}
		}
		return super.onKeyDown(keyCode, event);

	}

public final class ViewHolder {
        public TextView titleText;
        public TextView urlText;
    }
    public class MyAdapter extends BaseAdapter {
        private LayoutInflater mInflater;
        public MyAdapter(Context context) {
            this.mInflater = LayoutInflater.from(context);
        }
        public int getCount() {
            // TODO Auto-generated method stub
            return mList.size();
        }
        public Object getItem(int arg0) {
            // TODO Auto-generated method stub
            return mList.get(arg0);
        }
        public long getItemId(int arg0) {
            // TODO Auto-generated method stub
            return arg0;
        }
        public View getView(int position, View convertView, ViewGroup parent) {
            ViewHolder holder = null;
            if (convertView == null) {
                holder = new ViewHolder();
                convertView = mInflater.inflate(R.layout.chanlist, null);
                holder.titleText = (TextView) convertView.findViewById(R.id.title);
                holder.urlText = (TextView) convertView.findViewById(R.id.url);

                convertView.setTag(holder);
            } else {
                holder = (ViewHolder) convertView.getTag();
            }

			Map<String, Object> map = mList.get(position);
			String title = (String)map.get("title");
			String url = (String)map.get("url");
            holder.titleText.setText(title);
            holder.urlText.setText(url);

            if (position == selectItem) {
                convertView.setBackgroundColor(Color.BLUE);
            }
            else {
                convertView.setBackgroundColor(Color.TRANSPARENT);
            }

            //convertView.getBackground().setAlpha(80);

            return convertView;
        }
        public  void setSelectItem(int selectItem) {
             this.selectItem = selectItem;
        }
        private int  selectItem=0;
    }

}
