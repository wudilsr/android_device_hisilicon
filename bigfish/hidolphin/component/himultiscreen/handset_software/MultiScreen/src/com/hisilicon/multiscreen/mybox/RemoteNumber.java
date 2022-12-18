package com.hisilicon.multiscreen.mybox;

import android.app.Activity;
import android.graphics.drawable.BitmapDrawable;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
/**
 * CN:遥控器数字键盘界面。
 */
public class RemoteNumber extends PopupWindow implements OnTouchListener {

	/**
	 * CN:f1按钮。
	 */
	public Button mRemote_number_f1;
	
	/**
	 * CN:f2按钮。
	 */
	public Button mRemote_number_f2;
	
	/**
	 * CN:f3按钮。
	 */
	public Button mRemote_number_f3;
	
	/**
	 * CN:f4按钮。
	 */
	public Button mRemote_number_f4;
	
	/**
	 * CN:1按钮。
	 */
	public Button mRemote_number_one;
	
	/**
	 * CN:2按钮。
	 */
	public Button mRemote_number_two;
	
	/**
	 * CN:3按钮。
	 */
	public Button mRemote_number_three;
	
	/**
	 * CN:4按钮。
	 */
	public Button mRemote_number_four;
	
	/**
	 * CN:5按钮。
	 */
	public Button mRemote_number_five;
	
	/**
	 * CN:6按钮。
	 */
	public Button mRemote_number_six;
	
	/**
	 * CN:7按钮。
	 */
	public Button mRemote_number_seven;
	
	/**
	 * CN:8按钮。
	 */
	public Button mRemote_number_eight;
	
	/**
	 * CN:9按钮。
	 */
	public Button mRemote_number_nine;
	
	/**
	 * CN:确认按钮。
	 */
	public Button mRemote_number_ok;
	
	/**
	 * CN:0按钮。
	 */
	public Button mRemote_number_zero;
	
	/**
	 * CN:删除按钮。
	 */
	public Button mRemote_number_del;
	
	/**
	 * CN:待用按钮。
	 */
	public Button mRemote_number_stay;

	private LinearLayout mRemote_number_layout;

	private View view;

	int[] location = new int[2];
	int x1, y1;

	/**
	 * init view.
	 */
	public RemoteNumber(Activity context) {
		super(context);

		view = LayoutInflater.from(context).inflate(
				R.layout.mybox_remote_number, null);

		mRemote_number_layout = (LinearLayout) view.findViewById(R.id.remote_number_layout);

		mRemote_number_f1 = (Button) view.findViewById(R.id.remote_number_f1);
		mRemote_number_f1.setOnTouchListener(this);

		mRemote_number_f2 = (Button) view.findViewById(R.id.remote_number_f2);
		mRemote_number_f2.setOnTouchListener(this);

		mRemote_number_f3 = (Button) view.findViewById(R.id.remote_number_f3);
		mRemote_number_f3.setOnTouchListener(this);

		mRemote_number_f4 = (Button) view.findViewById(R.id.remote_number_f4);
		mRemote_number_f4.setOnTouchListener(this);


		mRemote_number_one = (Button) view.findViewById(R.id.remote_number_ones);
		mRemote_number_one.setOnTouchListener(this);

		mRemote_number_two = (Button) view.findViewById(R.id.remote_number_twos);
		mRemote_number_two.setOnTouchListener(this);

		mRemote_number_three = (Button) view.findViewById(R.id.remote_number_threes);
		mRemote_number_three.setOnTouchListener(this);

		mRemote_number_four = (Button) view.findViewById(R.id.remote_number_fours);
		mRemote_number_four.setOnTouchListener(this);

		mRemote_number_five = (Button) view.findViewById(R.id.remote_number_fives);
		mRemote_number_five.setOnTouchListener(this);

		mRemote_number_six = (Button) view.findViewById(R.id.remote_number_sixs);
		mRemote_number_six.setOnTouchListener(this);

		mRemote_number_seven = (Button) view.findViewById(R.id.remote_number_sevens);
		mRemote_number_seven.setOnTouchListener(this);

		mRemote_number_eight = (Button) view.findViewById(R.id.remote_number_eights);
		mRemote_number_eight.setOnTouchListener(this);

		mRemote_number_nine = (Button) view.findViewById(R.id.remote_number_nines);
		mRemote_number_nine.setOnTouchListener(this);

		mRemote_number_ok = (Button) view.findViewById(R.id.remote_number_ok);
		mRemote_number_ok.setOnTouchListener(this);

		mRemote_number_zero = (Button) view.findViewById(R.id.remote_number_zeros);
		mRemote_number_zero.setOnTouchListener(this);

		mRemote_number_del = (Button) view.findViewById(R.id.remote_number_del);
		mRemote_number_del.setOnTouchListener(this);

		mRemote_number_stay = (Button) view.findViewById(R.id.remote_number_stay);
		mRemote_number_stay.setOnTouchListener(this);

		this.setContentView(view);
		this.setWidth(LayoutParams.FILL_PARENT);
		this.setHeight(LayoutParams.FILL_PARENT);
		this.setFocusable(true);
		this.setTouchable(true);
		this.setOutsideTouchable(true);
		this.update();
		this.setBackgroundDrawable(new BitmapDrawable());

		view.setOnTouchListener(new View.OnTouchListener() {

			public boolean onTouch(View v, MotionEvent event) {

				mRemote_number_layout.getLocationInWindow(location);
				x1 = location[0];
				y1 = location[1];

				int x = (int) event.getX();
				int y = (int) event.getY();
				if (event.getAction() == MotionEvent.ACTION_UP) {
					if (y < y1 || y > y1 + mRemote_number_layout.getHeight()|| x < x1|| x > x1 + mRemote_number_layout.getWidth()) {
						dismiss();
					}
				}
				return true;
			}
		});

	}

	
	/**
	 * CN:OnTouch() 事件控件监听者。
	 */
	@Override
	public boolean onTouch(View v, MotionEvent event) {
		// TODO Auto-generated method stub
		switch (v.getId()) {

		case R.id.remote_number_f1:
			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_f1.setBackgroundResource(R.drawable.remote_number_f1_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_f1.setBackgroundResource(R.drawable.remote_number_f1);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_F1);
			}

			break;

		case R.id.remote_number_f2:
			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_f2.setBackgroundResource(R.drawable.remote_number_f2_foucs);

			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_f2.setBackgroundResource(R.drawable.remote_number_f2);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_F2);
			}

			break;

		case R.id.remote_number_f3:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_f3.setBackgroundResource(R.drawable.remote_number_f3_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_f3.setBackgroundResource(R.drawable.remote_number_f3);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_F3);
			}

			break;

		case R.id.remote_number_f4:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_f4.setBackgroundResource(R.drawable.remote_number_f4_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_f4.setBackgroundResource(R.drawable.remote_number_f4);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_F4);
			}

			break;

		case R.id.remote_number_ones:
			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_one.setBackgroundResource(R.drawable.remote_number_one_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_one.setBackgroundResource(R.drawable.remote_number_one);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_ONE);
			}

			break;

		case R.id.remote_number_twos:
			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_two.setBackgroundResource(R.drawable.remote_number_two_foucs);

			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_two.setBackgroundResource(R.drawable.remote_number_two);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_TWO);
			}

			break;

		case R.id.remote_number_threes:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_three.setBackgroundResource(R.drawable.remote_number_three_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_three.setBackgroundResource(R.drawable.remote_number_three);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_THREE);
			}

			break;

		case R.id.remote_number_fours:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_four.setBackgroundResource(R.drawable.remote_number_four_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_four.setBackgroundResource(R.drawable.remote_number_four);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_FOUR);
			}

			break;

		case R.id.remote_number_fives:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_five.setBackgroundResource(R.drawable.remote_number_five_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_five.setBackgroundResource(R.drawable.remote_number_five);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_FIVE);
			}

			break;

		case R.id.remote_number_sixs:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_six.setBackgroundResource(R.drawable.remote_number_six_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_six.setBackgroundResource(R.drawable.remote_number_six);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_SIX);
			}

			break;

		case R.id.remote_number_sevens:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_seven.setBackgroundResource(R.drawable.remote_number_seven_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_seven.setBackgroundResource(R.drawable.remote_number_seven);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_SEVEN);
			}

			break;

		case R.id.remote_number_eights:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_eight.setBackgroundResource(R.drawable.remote_number_eight_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_eight.setBackgroundResource(R.drawable.remote_number_eight);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_EIGHT);
			}

			break;

		case R.id.remote_number_nines:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_nine.setBackgroundResource(R.drawable.remote_number_nine_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_nine.setBackgroundResource(R.drawable.remote_number_nine);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_NINE);
			}

			break;

		case R.id.remote_number_ok:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_ok.setBackgroundResource(R.drawable.remote_number_ok_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_ok.setBackgroundResource(R.drawable.remote_number_ok);
//				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_OK);
				dismiss();
			}

			break;

		case R.id.remote_number_zeros:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_zero.setBackgroundResource(R.drawable.remote_number_zero_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_zero.setBackgroundResource(R.drawable.remote_number_zero);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_ZERO);
			}

			break;

		case R.id.remote_number_del:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_del.setBackgroundResource(R.drawable.remote_number_del_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_del.setBackgroundResource(R.drawable.remote_number_del);
				RemoteActivity.doKeyboard(RemoteActivity.REMOTE_NUMEBR_DEL);
			}

			break;

		case R.id.remote_number_stay:

			if (event.getAction() == MotionEvent.ACTION_DOWN) {
				mRemote_number_stay.setBackgroundResource(R.drawable.remote_number_empty_foucs);
			} else if (event.getAction() == MotionEvent.ACTION_UP) {
				mRemote_number_stay.setBackgroundResource(R.drawable.remote_number_empty);
				RemoteActivity.doKeyboard(0);
			}

			break;

		default:
			break;
		}

		return true;
	}

}
