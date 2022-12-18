package com.hisilicon.multiscreen.vime;

import java.util.Timer;
import java.util.TimerTask;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.TextView.BufferType;

import com.hisilicon.multiscreen.mybox.BaseActivity;
import com.hisilicon.multiscreen.mybox.MultiScreenControlService;
import com.hisilicon.multiscreen.mybox.R;
import com.hisilicon.multiscreen.protocol.message.VImeTextInfo;
import com.hisilicon.multiscreen.protocol.remote.VImeClientTransfer;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.MultiScreenIntentAction;

/**
 * Content input activity of VIME.<br>
 * CN:虚拟输入法的内容输入页面。
 * @since MultiScreen V2.0.1.1 2013/01/11: first create
 */
public class ContentInputActivity extends BaseActivity
{
    /**
     * Activity is on top.<br>
     * CN:页面在顶层。
     */
    private static final boolean IS_ON_TOP = true;

    /**
     * Message of sync cursor.<br>
     * CN:同步光标消息。
     */
    public static final int MSG_SEND_CURSOR_DELAY = 0x101;

    /**
     * Delay of handling cursor message.<br>
     * CN:光标同步消息处理的延迟。
     */
    private static final long SEND_CURSOR_DELAY = 500;

    /**
     * Sequence index of send text.<br>
     * CN:文本消息的发送序列。
     */
    private static final int SEND_TEXT_INIT_SEQUENCE = 0;

    /**
     * Key of text in message data.<br>
     * CN:消息数据中文字的键值。
     */
    private static final String MSG_KEY_TEXT = "MSG_KEY_TEXT";

    /**
     * Key of start selection in message data.<br>
     * CN:消息数据中起始光标的键值。
     */
    private static final String MSG_KEY_START_SELECION = "MSG_START_SELECTION";

    /**
     * Key of end selection in message data.<br>
     * CN:消息数据中结束光标的键值。
     */
    private static final String MSG_KEY_END_SELECION = "MSG_END_SELECTION";

    /**
     * Sequence index of send text.<br>
     * CN:文本消息的发送序列。
     */
    private int mSendTextSeq = SEND_TEXT_INIT_SEQUENCE;

    /**
     * VIme client transfer class.<br>
     * CN:虚拟输入法客户端传输类实例。
     */
    private VImeClientTransfer mVimeClientTransfer = null;

    /**
     * VIme client control Service instance.<br>
     * CN:虚拟输入法客户端控制服务实例。
     */
    private VImeClientControlService mVImeClientControlService = null;

    /**
     * Edit text of input content.<br>
     * CN:可编辑输入框。
     */
    private VIMEEditText mEtInputText = null;

    /**
     * Input complete button.<br>
     * CN:输入完成按钮。
     */
    private Button mBtnComplete = null;

    /**
     * Ime option.<br>
     * CN:输入法设置。
     */
    private VImeOption mImeOption = null;

    /**
     * Type of end input.<br>
     * CN:结束输入的类型。
     */
    private EndInputType mEndInputType = null;

    /**
     * Timer of open keyboard.<br>
     * CN:开启键盘的定时器。
     */
    private Timer openKeyboardTimer = null;

    /**
     * Enumeration type of end input.<br>
     * CN:结束输入的枚举类型。
     */
    private enum EndInputType
    {
        BUTTON_COMPLETE, STB, OTHERS
    };

    /**
     * Handler of sync text message.<br>
     * CN:同步文字消息处理者。
     */
    private SyncTextHandler myHandler = null;

    /**
     * Thread of handler.<br>
     * CN:消息处理线程。
     */
    private HandlerThread mHandlerThread = null;

    /**
     * Latest text in edit text.<br>
     * CN:编辑框中最新文字。
     */
    private String mLatestText = "";

    /**
     * BroadcastReceiver for finishing the activity.<br>
     * CN:广播接受者，用于结束当前活动页。
     */
    private BroadcastReceiver mVImeBroadcastReceiver = new BroadcastReceiver()
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            String intentAction = intent.getAction();

            if (intentAction.equals(MultiScreenIntentAction.END_INPUT_BY_STB))
            {
                mEndInputType = EndInputType.STB;
            }
            else if (intentAction.equals(MultiScreenIntentAction.END_INPUT_BY_PHONE))
            {
                mEndInputType = EndInputType.OTHERS;
            }

            LogTool.d("name of VIME broadcast: " + intentAction);
            ContentInputActivity.this.finish();
        }
    };

    /**
     * Complete button click listener.<br>
     * CN:完成按钮点击监听者.
     */
    private OnClickListener mBtnCompleteClickListener = new OnClickListener()
    {
        public void onClick(View v)
        {
            mEndInputType = EndInputType.BUTTON_COMPLETE;
            ContentInputActivity.this.finish();
        }
    };

    /**
     * Edit text watcher.<br>
     * CN:文本编辑框监听者。
     */
    private EditTextWatcher mEtWatcher = new EditTextWatcher()
    {
        @Override
        public void onTextChanged(CharSequence text, int start, int lengthBefore, int lengthAfter)
        {
            SendTextRunnable mSendTextRunnable =
                new SendTextRunnable(text.toString(), start + lengthAfter, start + lengthAfter);
            new Thread(mSendTextRunnable).start();
            mLatestText = text.toString();
        }

        @Override
        public void onSelectionChanged(int selStart, int selEnd)
        {
            sendTextDelay(mLatestText, selStart, selEnd, SEND_CURSOR_DELAY);
        }
    };

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        LogTool.d("on create");

        super.onCreate(savedInstanceState);
        processExtraData();
    }

    @Override
    protected void onNewIntent(Intent intent)
    {
        LogTool.d("onNewIntent");
        super.onNewIntent(intent);
        // Must store the new intent unless getIntent() will return the old one.
        setIntent(intent);
        processExtraData();
    }

    /**
	 *
	 */
    private void processExtraData()
    {
        mVImeClientControlService = VImeClientControlService.getInstance();
        mVImeClientControlService.setInputActivityTopStatus(IS_ON_TOP);

        if (isInputStatusOnClient())
        {
            Intent intent = getIntent();
            initView();
            initData(intent);
            openKeyboard();
            registerVImeReceiver(mVImeBroadcastReceiver);
        }
        else
        {
            LogTool.d("Create fail, to finish activity.");
            ContentInputActivity.this.finish();
        }
    }

    @Override
    protected void onRestart()
    {
        LogTool.d("on Restart");
        super.onRestart();

        if (mHandlerThread == null)
        {
            ContentInputActivity.this.finish();
        }
    }

    @Override
    protected void onStart()
    {
        LogTool.d("onStart.");
        super.onStart();
    }

    @Override
    protected void onResume()
    {
        LogTool.d("on Resume.");
        super.onResume();
    }

    @Override
    protected void onPause()
    {
        LogTool.d("on pause.");
        super.onPause();
        /* text should be sent if activity is hidden. */
        unregisterVImeReceiver(mVImeBroadcastReceiver);
        finishContentInput(mEndInputType);
        deinitHandler();
        if (mVImeClientControlService != null)
        {
            mVImeClientControlService.setInputActivityTopStatus(!IS_ON_TOP);
        }
        unregisterVImeReceiver(mVImeBroadcastReceiver);
    }

    @Override
    protected void onStop()
    {
        LogTool.d("on stop.");
        super.onStop();
    }

    @Override
    protected void onDestroy()
    {
        LogTool.d("on destroy.");
        super.onDestroy();
    }

    /**
     * Return true if it's input status in VIme state machine.<br>
     * CN:如果客户端VIme状态机是输入状态则返回真。
     * @return - true if it's input status.
     */
    private boolean isInputStatusOnClient()
    {
        // VIme client control Service instance.<br> CN:虚拟输入法客户端控制类实例。
        VImeClientControlService mVImeClientControlService = VImeClientControlService.getInstance();

        if (mVImeClientControlService == null)
        {
            // CN:服务可能被kill掉。
            LogTool.d("mVImeClientControlService is null");
            return false;
        }
        else
        {
            return mVImeClientControlService.isInputStatusOnClient();
        }
    }

    /**
     * End input when activity on destroy.<br>
     * CN: 页面关闭时结束输入。
     * @param endInputType - end input type.
     */
    private void finishContentInput(EndInputType endInputType)
    {
        clearMessages();
        cancelKeyboard();

        switch (endInputType)
        {
            case BUTTON_COMPLETE:
            {
                // CN:发送完成按钮信息（STB可能跳到下一个输入框）。
                mVimeClientTransfer.endInput(mImeOption.getIndex());
                break;
            }

            case STB:
            {
                // CN:由STB发起的结束，手机端不再发送结束输入消息。
                break;
            }

            case OTHERS:
            {
                // CN:单纯隐藏STB键盘。
                mVimeClientTransfer.endInput(VImeOption.HIDE_KEYBOARD.getIndex());
                break;
            }

            default:
            {
                LogTool.e("No default end input type");
                break;
            }
        }
    }

    /**
     * Initialize view of activity.<br>
     * CN:初始化页面的视图。
     */
    private void initView()
    {
        setContentView(R.layout.input);
        mEtInputText = (VIMEEditText) findViewById(R.id.et_input_text);
        mBtnComplete = (Button) findViewById(R.id.button);
    }

    /**
     * Initialize input status of activity.<br>
     * CN:初始化输入内容。
     * @param intent - received intent of activity
     */
    private void initData(Intent intent)
    {
        initHandler();

        int inputType = 0;
        String text = "";
        int startSelection = 0;
        int endSelection = 0;
        mEndInputType = EndInputType.OTHERS;
        // get extras of intent, and initialize input content
        Bundle bundle = intent.getExtras();

        // get arguments of VIME
        mImeOption = VImeOption.getOption(bundle.getInt(VImeTextInfo.INPUT_OPTION));
        inputType = bundle.getInt(VImeTextInfo.INPUT_TYPE);
        text = bundle.getString(VImeTextInfo.INPUT_TEXT);
        startSelection = bundle.getInt(VImeTextInfo.SRC_START_SELECTION);
        endSelection = bundle.getInt(VImeTextInfo.SRC_END_SELECTION);
        // initialize data of views
        initCompleteButton(mImeOption);
        mEtInputText.setInputType(inputType);
        mEtInputText.setText(text, BufferType.EDITABLE);
        mLatestText = text;

        mEtInputText.setSelection(startSelection, endSelection);
        mSendTextSeq = SEND_TEXT_INIT_SEQUENCE;
        // // CN:Editable继承了Spannable，可以转换。
        // Spannable inputText = (Spannable) mEtInputText.getText();
        // Selection.setSelection(inputText, startSelection,endSelection);
        mEtInputText.addWatcher(mEtWatcher);

        // initialize VimeClientTransfer
        mVimeClientTransfer =
            VImeClientTransfer.getInstance(MultiScreenControlService.getInstance().getHiDevice());
    }

    /**
     * Initialize handler.<br>
     */
    private void initHandler()
    {
        mHandlerThread = new HandlerThread("multiscreen_contentinput_handlerthread");
        mHandlerThread.start();
        myHandler = new SyncTextHandler(mHandlerThread.getLooper());
    }

    /**
     * DeInitialize handler.<br>
     */
    private void deinitHandler()
    {
        if (mHandlerThread != null)
        {
            clearMessages();
            mHandlerThread.getLooper().quit();
            mHandlerThread = null;
        }
    }

    /**
     * Initialize the label on end input button.<br>
     * CN:初始化结束输入按钮的标签。
     * @param imeOption - options of IME
     */
    private void initCompleteButton(VImeOption imeOption)
    {
        // mBtnComplete.setText(imeOption.getName());
        mBtnComplete.setOnClickListener(mBtnCompleteClickListener);
    }

    /**
     * Open keyboard with timer.<br>
     * CN:用定时器打开键盘。
     */
    private void openKeyboard()
    {
        final long DELAY_TIME = 500L;
        openKeyboardTimer = new Timer();

        openKeyboardTimer.schedule(new TimerTask()
        {
            @Override
            public void run()
            {
                InputMethodManager imm =
                    (InputMethodManager) getSystemService(INPUT_METHOD_SERVICE);
                imm.showSoftInput(mEtInputText, InputMethodManager.RESULT_UNCHANGED_SHOWN);
            }
        }, DELAY_TIME);
    }

    /**
     * Cancel timer explicitly if keyboard is closed.<br>
     * CN:关闭键盘时,显式销毁定时器。
     */
    private void cancelKeyboard()
    {
        if (openKeyboardTimer != null)
        {
            // 显式销毁定时器
            openKeyboardTimer.cancel();
            openKeyboardTimer = null;
        }

        InputMethodManager imm = (InputMethodManager) getSystemService(INPUT_METHOD_SERVICE);
        View focusView = getCurrentFocus();
        if ((focusView != null) && (imm != null))
        {
            imm.hideSoftInputFromWindow(focusView.getWindowToken(),
                InputMethodManager.HIDE_NOT_ALWAYS);
        }
    }

    /**
     * Register receiver of broadcast for VIME.<br>
     * CN: 注册虚拟输入法的广播接收者。
     * @param receiver - VIME broadcast receiver
     */
    private void registerVImeReceiver(BroadcastReceiver receiver)
    {
        IntentFilter filter = new IntentFilter();
        filter.addAction(MultiScreenIntentAction.END_INPUT_BY_STB);
        filter.addAction(MultiScreenIntentAction.END_INPUT_BY_PHONE);

        registerBroadcastReceiver(receiver, filter);
    }

    /**
     * Unregister receiver of broadcast for VIME.<br>
     * CN: 解注册虚拟输入法的广播接收者。
     * @param receiver - VIME broadcast receiver
     */
    private void unregisterVImeReceiver(BroadcastReceiver receiver)
    {
        unregisterBroadcastReceiver(receiver);
    }

    /**
     * Clear messages.<br>
     * CN:清空消息队列。
     */
    private void clearMessages()
    {
        if (myHandler.hasMessages(MSG_SEND_CURSOR_DELAY))
        {
            myHandler.removeMessages(MSG_SEND_CURSOR_DELAY);
        }
    }

    /**
     * Send new message.<br>
     * CN:发送消息。
     * @param text latest text
     * @param start start selection.
     * @param end end selection.
     * @param delayMillis delay time.
     */
    private void sendTextDelay(String text, int start, int end, long delayMillis)
    {
        clearMessages();

        Message msg = myHandler.obtainMessage();
        msg.what = MSG_SEND_CURSOR_DELAY;
        Bundle data = new Bundle();
        data.putString(MSG_KEY_TEXT, text);
        data.putInt(MSG_KEY_START_SELECION, start);
        data.putInt(MSG_KEY_END_SELECION, end);
        msg.setData(data);
        myHandler.sendMessageDelayed(msg, delayMillis);
    }

    /**
     * Handler of message.<br>
     * CN:消息处理者。
     */
    private class SyncTextHandler extends Handler
    {
        public SyncTextHandler()
        {

        }

        public SyncTextHandler(Looper looper)
        {
            super(looper);
        }

        @Override
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
                case MSG_SEND_CURSOR_DELAY:
                {
                    Bundle data = msg.getData();
                    String text = data.getString(MSG_KEY_TEXT);
                    if (text == null)
                    {
                        text = "";
                        LogTool.e("Get string form data fail, and it will send blank.");
                    }
                    sendText(text, data.getInt(MSG_KEY_START_SELECION, 0),
                        data.getInt(MSG_KEY_END_SELECION, 0));
                }
                    break;
                default:
                    break;
            }
        }
    }

    /**
     * Send text.<br>
     * CN:发送文字光标。
     * @param text current text.
     * @param start current start selection.
     * @param end current end selection.
     */
    private void sendText(String text, int start, int end)
    {
        mSendTextSeq++;
        mVimeClientTransfer.sendText(mSendTextSeq, text, start, end);
    }

    /**
     * Runnable of sending text.<br>
     * CN:发送文字的可运行类。
     */
    private class SendTextRunnable implements Runnable
    {
        private String mCurrentText = null;

        private int mStartSelection = 0;

        private int mEndSelection = 0;

        public SendTextRunnable(String currentText, int start, int end)
        {
            mCurrentText = currentText;
            mStartSelection = start;
            mEndSelection = end;
        }

        @Override
        public void run()
        {
            sendText(mCurrentText, mStartSelection, mEndSelection);
        }
    };
}
