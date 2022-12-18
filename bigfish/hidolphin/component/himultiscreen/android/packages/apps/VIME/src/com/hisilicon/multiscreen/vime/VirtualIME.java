/*
 * filename： VirtualIME.java
 * 文件名：VirtualIME.java
 * 描述：虚拟输入法服务实现文件
 * description：implementation file of virtual input method service
 */

package com.hisilicon.multiscreen.vime;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.lang.ref.SoftReference;
import java.util.List;

import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningServiceInfo;
import android.content.Context;
import android.inputmethodservice.InputMethodService;
import android.inputmethodservice.KeyboardView;
import android.os.Handler;
import android.os.Message;
import android.text.InputType;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.ExtractedText;
import android.view.inputmethod.ExtractedTextRequest;
import android.view.inputmethod.InputConnection;
import android.view.inputmethod.InputMethodInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.Toast;

import com.hisilicon.multiscreen.http.HiHttpClient;
import com.hisilicon.multiscreen.http.HiHttpRecvMsgListener;
import com.hisilicon.multiscreen.http.HiHttpResponse;
import com.hisilicon.multiscreen.http.HiHttpServer;
import com.hisilicon.multiscreen.http.HiHttpStatusCode;
import com.hisilicon.multiscreen.protocol.message.Action;
import com.hisilicon.multiscreen.protocol.message.Argument;
import com.hisilicon.multiscreen.protocol.message.ArgumentValue;
import com.hisilicon.multiscreen.protocol.message.VImeTextInfo;
import com.hisilicon.multiscreen.protocol.server.IMultiScreenManagerVIme;
import com.hisilicon.multiscreen.protocol.server.VImeServerTransfer;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.SaxXmlUtil;
import com.hisilicon.multiscreen.protocol.utils.VImeStatusDefine;
import com.hisilicon.multiscreen.protocol.utils.VImeStatusDefine.VimeStatus;

/**
 * VirtualIME class is implementation of the virtual IME. The Class is
 * responsible for listening for the events of key, initialize UI of input view
 * and exchanging message with hand device. <br>
 * CN:SoftKeyboard 类是虚拟输入法服务的实现类 ，该类监听按键事件，输入法键盘布局以及完成与手持设备侧的文字消息交互。
 * @version
 */
public class VirtualIME extends InputMethodService
{

    private static final String LATIN_IME_ID = "com.android.inputmethod.latin/.LatinIME";

    /**
     * Virtual IME’s string Id.<br>
     * CN:虚拟输入法的字符串ID。
     */
    private static final String VIRTUAL_IME_NAME = "com.hisilicon.multiscreen.vime/.VirtualIME";

    /**
     * Multiscreen service name. <br>
     * CN:多屏服务名
     */
    private static final String MULTISCREEN_SERVICE_NAME =
        "com.hisilicon.multiscreen.server.MultiScreenService";

    /**
     * Http server port of Virtual IME. <br>
     * CN:虚拟输入法Http服务端口。
     */
    private static final int IME_TRANSFER_SERVER_PORT = 2019;

    /**
     * Index of first argument in message. <br>
     * CN:消息中第一个参数的索引。
     */
    private static final int FIRST_ARGUMENT_INDEX = 0;

    /**
     * Index of second argument in message. <br>
     * CN:消息中第二个参数的索引。
     */
    private static final int SECOND_ARGUMENT_INDEX = 1;

    /**
     * Index of third argument in message. <br>
     * CN:消息中第三个参数的索引。
     */
    private static final int THIRD_ARGUMENT_INDEX = 2;

    /**
     * Index of fourth argument in message.<br>
     * CN:消息中的第四个参数的索引。
     */
    private static final int FOURTH_ARGUMENT_INDEX = 3;

    /**
     * Initial sequence index of send text.<br>
     * CN:文字初始序号。
     */
    private static final int SEND_TEXT_INIT_SEQUENCE = 0;

    /**
     * Overflow protection of sequence index.<br>
     * CN:序号的溢出保护。
     */
    private static final int TEXT_SEQUENCE_REVERSE_TORLENCE = -1000;

    /**
     * IME Option value for irregular hiding input view. <br>
     * CN:非正常关闭输入界面的IME option的值。
     */
    private static final int OPTION_HIDE_SELF = -1;

    /**
     * Wait time for getting remote IP.<br>
     * CN:获得远端ip地址的等待时间。
     */
    private static final long TIME_WAIT_FOR_REMOTE_IP = 1000;

    /**
     * Message id  for check enable.<br>
     * CN:检查虚拟输入法启动是否是enable引起的消息id。
     */
    private static final int CHECK_IF_ENABLE = 30;

    /**
     * Wait time for start check task.<br>
     * CN:启动check任务的等待时间。
     */
    private static final int CHECK_TASK_DELAY = 2000;

    /**
     * Text field is protected,commit text mode.<br>
     * CN:文本区域收保护时提交模式。
     */
    private static final int PROTECTED_COMMIT_MODE = 1;

    /**
     * Text field is not protected,commit text mode.<br>
     * CN:文本区域非保护时的提交模式。
     */
    private static final int UNPROTECTED_COMMIT_MODE = 0;

    /**
     * Default IME ID <br>
     * CN:默认输入法id
     */
    private String mDefaultIMEId = null;

    /**
     * Keyboard view of Virtual IME. <br>
     * CN:虚拟输入法键盘视图。
     */
    private KeyboardView mInputView = null;

    /**
     * Tip keyboard of Virtual IME. <br>
     * CN:虚拟输入法的提示键盘。
     */
    private VImeKeyboard mTipKeyboard = null;

    /**
     * Http server for receive message form client. <br>
     * CN: Http 服务器用于接收客户端的消息。
     */
    private HiHttpServer mVImeHttpServer = null;

    /**
     * Flag for http server start<br>
     * CN:VIME http server start success.
     */
    private boolean mIsHttpServerStart = false;

    /**
     * Http client for send message to hand devices. <br>
     * CN:用于向手持设备发送消息的http客户端。
     */
    private HiHttpClient mVImeHiHttpClient = null;

    /**
     * Timeout for send message to hand devices. <br>
     * CN:向手持设备发送消息的超时。
     */
    private int mTimeOut = 2000;

    /**
     * Input type of editor field. <br>
     * CN:编辑区域的输入类型。
     */
    private int mInputType = EditorInfo.TYPE_NULL;

    /**
     * Action attribute of editor field. <br>
     * CN:编辑区域的动作属性。
     */
    private int mImeOption = EditorInfo.IME_ACTION_NONE;

    /**
     * The count of start input view. <br>
     * CN:启动输入界面的计数器。
     */
    private int mStartInputCount = 0;

    /**
     * VIME Status. <br>
     * CN:VIME的状态。
     */
    private VImeStatusDefine.VimeStatus mVImeStatus =
        VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_INIT;

    /**
     * Flag for mask some hard key. <br>
     * CN：是否屏蔽某些按键的标示符。
     */
    private boolean mIsMaskHardKey = false;

    /**
     * Report the virtual IME's current status. <br>
     * CN:虚拟输入法当前状态报告的类。
     */
    private VImeStatReport mStatReport = null;

    /**
     * The object Construct virtual IME's transfer message. <br>
     * CN:虚拟输入法传输消息构造的对象。
     */
    private VImeServerTransfer mTransfer = null;

    /**
     * Input method manager object.<br>
     * CN:输入法管理对象。
     */
    private InputMethodManager mInputManager = null;

    /**
     * Virtual IME service context. <br>
     * CN:虚拟输入法上下文环境。
     */
    private Context mContext = null;

    /**
     * Flag for showing "vime start" and "vime stop" tip. <br>
     * CN:显示“vime start” and “vime stop” 的标志值。
     */
    private boolean mIsShowTip = true;

    /**
     * Index of last commit text sequence.<br>
     * CN:上一次提交文本的序列号。
     */
    private int mLastCommitSequence = SEND_TEXT_INIT_SEQUENCE;

    /**
     * Flag indicates VIME start from enable.<br>
     * CN:VIME是否来自客户端的enable消息。
     */
    private boolean mIsEnable = false;

    /**
     * Handler for deal inner message.<br>
     * CN:处理VIME内部消息的handler。
     */
    private VIMEDealHandler mVIMEDealHandler = null;

    /**
     * commit text mode.<br>
     * CN:commit mode type。
     */
    private int mCommitMode  = UNPROTECTED_COMMIT_MODE ;

    /**
     * VIME's inner message deal handler.<br>
     * CN:VIME内部消息处理的handler。
     */
    private static class VIMEDealHandler extends Handler
    {

        SoftReference<VirtualIME> mServiceReference = null;

        VIMEDealHandler(VirtualIME service)
        {
            mServiceReference = new SoftReference<VirtualIME>(service);
        }

        public void handleMessage(Message msg)
        {
            if (mServiceReference == null)
            {
                return;
            }
            VirtualIME service = mServiceReference.get();

            super.handleMessage(msg);

            switch (msg.what)
            {
                case CHECK_IF_ENABLE:
                {
                    LogTool.v("check if enable");
                    service.startCheck();
                    break;
                }
                default:
                    break;
            }
        }
    }

    /**
     * Listener for receive and deal message. <br>
     * CN:接收和处理消息的监听。
     */
    private HiHttpRecvMsgListener mHttpRecvMsgListener = new HiHttpRecvMsgListener()
    {

        @Override
        public String onHttpMsgReceived(byte[] msg, String remoteIP)
        {
            Action recvAction = null;
            SaxXmlUtil saxTools = new SaxXmlUtil();
            try
            {
                recvAction = saxTools.parse(msg);
            }
            catch (Exception e)
            {

                LogTool.e("sax byte msg fail");
            }

            String retStr;
            if (null == recvAction)
            {
                LogTool.e("recvAction is null");
                retStr = mTransfer.retDefaultMsgResponse();
            }
            else
            {
                switch (recvAction.getId())
                {

                    case Action.ACTION_ID_VIME_SEND_TEXT:
                    {
                        LogTool.i("receive send text msg");
                        VImeTextInfo textInfo = commitRecvText(recvAction);
                        if (null == textInfo)
                        {
                            LogTool.i("commit failed");
                            retStr = mTransfer.retDefaultMsgResponse();
                        }
                        else
                        {
                            retStr = mTransfer.retSendText(textInfo);
                        }
                        break;
                    }

                    case Action.ACTION_ID_VIME_ENDINPUT_FROM_PHONE:
                    {
                        LogTool.i("receive end input msg");
                        if (mVImeStatus != VimeStatus.VIME_SERVER_STATUS_INPUT)
                        {
                            LogTool.e("vime status is not input");
                            return mTransfer.retDefaultMsgResponse();
                        }
                        InputConnection ic = getCurrentInputConnection();
                        if (null == ic)
                        {
                            LogTool.e("get input connection failure");
                            throw new RuntimeException("get input connection failure");
                        }
                        retStr = mTransfer.retEndInputFromPhone(mImeOption);
                        Argument optArg = recvAction.getArgument(FIRST_ARGUMENT_INDEX);
                        if (optArg == null)
                        {
                            LogTool.e("get first arg failed");
                            break;
                        }
                        ArgumentValue optArgVal = optArg.getArgumentValue(FIRST_ARGUMENT_INDEX);
                        if (null == optArgVal)
                        {
                            LogTool.e("get ime option arg value is null");
                            break;
                        }

                        int imeOpt = (Integer) optArgVal.getVaule();
                        mStartInputCount--;

                        if (imeOpt == OPTION_HIDE_SELF)
                        {
                            requestHideSelf(0);
                        }
                        else
                        {
                            ic.performEditorAction(imeOpt);
                        }
                        break;
                    }

                    default:
                    {
                        LogTool.e("received other msg id" + recvAction.getId());
                        retStr = mTransfer.retDefaultMsgResponse();
                        break;
                    }
                }

            }
            LogTool.v("response string:" + retStr);
            return retStr;
        }
    };

    /**
     * The interface implementation of multiScreen control VIME. <br>
     * CN:多屏服务控制VIME的接口实现。
     */
    private IMultiScreenManagerVIme mIMultiScreenManagerVIme = new IMultiScreenManagerVIme()
    {

        @Override
        public void closeKeyboard()
        {
            if (mVImeStatus == VimeStatus.VIME_SERVER_STATUS_INPUT)
            {
                mStartInputCount--;
                requestHideSelf(0);
            }
        }

        @Override
        public void switchToDefaultIME()
        {
            showUserTip(R.string.abnormal_start_vime_tip);
            mIsShowTip = false;
            mInputManager =
                (InputMethodManager) mContext.getSystemService(Context.INPUT_METHOD_SERVICE);
            mInputManager.setInputMethod(null, mDefaultIMEId);
        }

        @Override
        public void enableVIMENotify()
        {
            LogTool.v("enable vime notify");
            mIsEnable = true;
            if ((mIsHttpServerStart == false) && (mVImeHttpServer != null))
            {
                mIsHttpServerStart = startTransferServer();
                if (mIsHttpServerStart == false)
                {
                    LogTool.e("start http server failed");
                }
            }
        }
    };

    /**
     * Override this to control the input method runs in not fullscreen mode. <br>
     * CN:重写该方法控制输入法以非全屏模式运行。
     */
    @Override
    public boolean onEvaluateFullscreenMode()
    {

        // make sure the input method runs in not fullscreen
        // 确保输入法以非全屏模式运行
        return false;
    }

    /**
     * Re-evaluate whether the input method should be running in fullscreen
     * mode, and update its UI.<br>
     * CN:重新评估输入法是否以全屏模式运行，并更新输入法UI的状态 。<br>
     */

    @Override
    public void updateFullscreenMode()
    {

        super.updateFullscreenMode();

        // 以非全屏模式运行输入法
        // run the input method in not fullscreen
        boolean isFullscreen = false;

        InputConnection ic = getCurrentInputConnection();
        if (ic != null)
        {
            ic.reportFullscreenMode(isFullscreen);
        }
    }

    /**
     * Main initialization of the virtual IME service. <br>
     * CN: 虚拟输入法初始化。
     */
    @Override
    public void onCreate()
    {
        LogTool.d("on Create");
        super.onCreate();
        mContext = this;
        mInputManager = (InputMethodManager) this.getSystemService(Context.INPUT_METHOD_SERVICE);
        mDefaultIMEId = getDefaultIME(mInputManager);

        initTransferServer();

        mStatReport = new VImeStatReport(this, mIMultiScreenManagerVIme);
        mStatReport.startReport();
        mStatReport.responseCheck(VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_READY);
        mVImeStatus = VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_READY;

        initTransferClient();

        try
        {
            Thread.sleep(TIME_WAIT_FOR_REMOTE_IP);
        }
        catch (InterruptedException e)
        {
            LogTool.e(e.getMessage());
        }

        mVIMEDealHandler = new VIMEDealHandler(this);
        mVIMEDealHandler.sendEmptyMessageDelayed(CHECK_IF_ENABLE, CHECK_TASK_DELAY);
    }

    /**
     * This is the point where you can do all of virtual IME's UI
     * initialization. It is called after creation and any configuration change.<br>
     * CN:该方法完成虚拟输入法的UI初始化，在虚拟输入法创建与配置改变时调用。
     */
    @Override
    public void onInitializeInterface()
    {
        LogTool.d("onInitializeInterface");
        if (mIsShowTip)
        {
            showUserTip(R.string.vime_start_tip);
        }
        mTipKeyboard = new VImeKeyboard(this, R.xml.vimetip);
    }

    /**
     * Called by the framework when your view for creating input needs to be
     * generated, this will be called the first time your input method is
     * displayed. <br>
     * CN:当创建输入视图时被输入法框架调用，在输入法第一次显示时将会被调用。<br>
     */
    @Override
    public View onCreateInputView()
    {

        LogTool.d("onCreateInputView");
        mInputView = (KeyboardView) getLayoutInflater().inflate(R.layout.input, null);
        // mInputView.setOnKeyboardActionListener(this);
        mInputView.setKeyboard(mTipKeyboard);
        return mInputView;
    }

    /**
     * Called by the framework when your view for showing candidates needs to be
     * generated. <br>
     * 创建候选区域时被输入法框架调用。
     */
    @Override
    public View onCreateCandidatesView()
    {
        LogTool.d("onCreateCandidatesView");
        return super.onCreateCandidatesView();
    }

    /**
     * It is called when virtual IME is bound to the client, and are now
     * receiving all of the detailed information about the target of our edits.<br>
     * CN:该方法是在输入法绑定到客户端时被调用，并且接受关于编辑目标的详细信息。
     * @param attibute editor info of editor field. <br>
     *        CN:输入区域的属性。
     * @param restarting set to true if we are restarting input on the same text
     *        field as before. <br>
     *        CN:若在相同的区域重新启动输入例如输入区域文字变化，置为true,false则表明会话是该编辑区域新的会话。
     */
    @Override
    public void onStartInput(EditorInfo attribute, boolean restarting)
    {
        if(attribute.inputType == InputType.TYPE_NULL &&
                attribute.imeOptions == attribute.IME_NULL)
        {
            requestHideSelf(0);
            return ;
        }
        super.onStartInput(attribute, restarting);

        LogTool.d("onStartInput");

        mTipKeyboard.setImeOptions(getResources(), attribute.imeOptions);

        // 输入目标区域的输入类型
        // input type of target editor
        mInputType = attribute.inputType;

        // 输入目标区域的动作属性
        // IME ACTION attribute of target editor
        mImeOption = attribute.imeOptions & EditorInfo.IME_MASK_ACTION;

        LogTool.v("inputType: " + mInputType);
        LogTool.v("ImeOptions: " + mImeOption);

    }

    /**
     * Called when the input view is being shown and input has started on a new
     * editor. This will always be called after {@link #onStartInput}. <br>
     * CN:当输入视图被显示或者输入法在一个新的编辑区域启动时被调用，该方法通常是在 {@link #onStartInput}之后被调用。<br>
     * @param attribute editor info of editor field. CN:编辑区域属性描述。
     * @param restarting -true CN:如果输入法在与之前相同的输入区域重启动，则设置为true。
     */
    @Override
    public void onStartInputView(EditorInfo attribute, boolean restarting)
    {
        if(attribute.inputType == InputType.TYPE_NULL &&
                attribute.imeOptions == attribute.IME_NULL)
        {
            requestHideSelf(0);
            return ;
        }

        super.onStartInputView(attribute, restarting);
        // Apply the selected keyboard to the input view.
        LogTool.d("onStartInputView");
        mInputView.setKeyboard(mTipKeyboard);
        mInputView.closing();

        if (VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_READY == mVImeStatus)
        {
            mStartInputCount = 0;
        }
        else
        {
            mStartInputCount = 1;
        }

        LogTool.v("startCount = " + mStartInputCount);
        // 输入法获取当前绑定的输入区域的文本信息
        // IME obtains the information about text in current editor field
        VImeTextInfo textInfo = getRealTextInfo();
        if (null == textInfo)
        {
            LogTool.e("cannot editor hide keyboard ");
            requestHideSelf(0);
            return;
        }

        mIsMaskHardKey = true;
        textInfo.setImeOption(mImeOption);
        textInfo.setInputType(mInputType);

        if (mStatReport.getRemoteIP() == null)
        {
            LogTool.e("RemoteIP is null.");
        }

        mVImeHiHttpClient.setHostIp(mStatReport.getRemoteIP());
        mVImeHiHttpClient.setPort(mStatReport.getRemotePort());

        LogTool.v("RemoteIP is" + mStatReport.getRemoteIP());

        final String sendMsg = mTransfer.callInputModule(textInfo);

        Thread callInputThread = new Thread()
        {
            public void run()
            {
                // fix for send callInput after finishInputView
                if ((VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_READY == mVImeStatus)
                    && (mIsMaskHardKey))
                {
                    mLastCommitSequence = SEND_TEXT_INIT_SEQUENCE;
                    HiHttpResponse hiHttpResponse = mVImeHiHttpClient.sendRequest(sendMsg);
                    Action retAction = parseHttpRes(hiHttpResponse);

                    LogTool.v("send CallInput Msg" + sendMsg);
                    LogTool.v("receive the call Input return msg"
                        + hiHttpResponse.getResponseMessage());

                    if (!isCallInputSuccess(retAction))
                    {
                        LogTool.e("call input fail");
                        requestHideSelf(0);
                    }
                    else
                    {
                        mStartInputCount++;
                        mVImeStatus = VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_INPUT;
                        LogTool.i("call input success");
                        LogTool.i("startCount = " + mStartInputCount);
                    }
                }
            }
        };
        callInputThread.setName("callInputMsgSendThread");
        callInputThread.start();
        // end modified.
        mStatReport.responseCheck(VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_INPUT);
    }

    /**
     * Called when the input view is being hidden from the user.<br>
     * CN:输入区域隐藏时被调用。
     * @param finishingInput true {@link #onFinishInput} will be called
     *        immediately. <br>
     *        CN:若为true, {@link #onFinishInput}会被立即调用。
     */
    @Override
    public void onFinishInputView(boolean finishingInput)
    {
        super.onFinishInputView(finishingInput);
        LogTool.d("onFinishInputView");

        mStartInputCount--;
        mLastCommitSequence = SEND_TEXT_INIT_SEQUENCE;

        LogTool.i("startCount = " + mStartInputCount);
        mCommitMode = UNPROTECTED_COMMIT_MODE;
        if ((0 == mStartInputCount)
            && (VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_INPUT == mVImeStatus))
        {

            // FIXME should handle in thread
            final String sendMsg = mTransfer.endInputFromSTB(mImeOption);

            Thread endInputThread = new Thread()
            {
                public void run()
                {
                    HiHttpResponse hiHttpResponse = mVImeHiHttpClient.sendRequest(sendMsg);
                    dealHiHttpResponse(hiHttpResponse);
                }
            };
            endInputThread.setName("endInputSendMsgThread");
            endInputThread.start();

            LogTool.i("send end input");
            LogTool.v(sendMsg);
        }

        mVImeStatus = VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_READY;
        mStatReport.responseCheck(VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_READY);

        mIsMaskHardKey = false;
    }

    /**
     * This is called when the user is done editing a field. <br>
     * CN:用户结束一个区域的输入时被调用。<br>
     */
    @Override
    public void onFinishInput()
    {
        super.onFinishInput();
        LogTool.d("onFinishInput");
        setCandidatesViewShown(false);

        if (null != mInputView)
        {
            mInputView.closing();
        }
    }

    /**
     * Called when the virtual IME service destroyed. <br>
     * CN:当虚拟输入法服务销毁时被调用。
     */
    @Override
    public void onDestroy()
    {
        super.onDestroy();
        LogTool.d("onDestroy");


        if (mIsShowTip)
        {
            showUserTip(R.string.vime_stop_tip);
        }

        mStatReport.responseCheck(VImeStatusDefine.VimeStatus.VIME_SERVER_STATUS_DEINIT); // FIXME
                                                                                          // DEINIT
        mVImeHttpServer.stopServer();
        // mVImeHttpServer.destroyServer(); //FIXME 没有destroy了
        mStatReport.stopReport();

    }

    /**
     * Use this to monitor key events of Remote control being delivered to the
     * application.<br>
     * CN:该方法监控遥控器键盘事件，并提交到应用程序。
     * @param keyCode key code of hard key. <br>
     *        CN:键盘事件的键值。
     * @param event description of key event. <br>
     *        CN:键盘事件描述。
     * @return If you return true, the method process the event, pass the event
     *         to other application return false. <br>
     *         CN:如果在该方法中处理了事件event,返回true,若在向交给其他的接受者处理，则返回false。
     */
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {

        if (mIsMaskHardKey)
        {

            if ((keyCode >= KeyEvent.KEYCODE_0) && (keyCode <= KeyEvent.KEYCODE_9))
            {
                LogTool.i("key code 0~9");
                return true;
            }
            if ((keyCode >= KeyEvent.KEYCODE_A) && (keyCode <= KeyEvent.KEYCODE_Z))
            {
                return true;
            }
        }
        switch (keyCode)
        {
            case KeyEvent.KEYCODE_BACK:
                // The InputMethodService already takes care of the back
                if (event.getRepeatCount() == 0 && mInputView != null)
                {
                    if (mInputView.handleBack())
                    {
                        return true;
                    }
                }
                break;

            case KeyEvent.KEYCODE_DEL:
            case KeyEvent.KEYCODE_DPAD_LEFT:
            case KeyEvent.KEYCODE_DPAD_RIGHT:
            case KeyEvent.KEYCODE_DPAD_UP:
            case KeyEvent.KEYCODE_DPAD_DOWN:
            case KeyEvent.KEYCODE_ENTER:
                if (mIsMaskHardKey)
                {
                    return true;
                }
                else
                {
                    return false;
                }

            default:

                return false;
        }
        return super.onKeyDown(keyCode, event);
    }

    /**
     * Get current editor field's VImeTextInfo include text and cursor. <br>
     * CN:获得当前的编辑区域的VImeTextInfo，包括文本和光标。
     * @return VImeTextInfo obtained VImeTextInfo from current editor field. <br>
     *         CN:从当前编辑框获得VImeTextInfo的消息。
     */
    private VImeTextInfo getRealTextInfo()
    {
        InputConnection ic = getCurrentInputConnection();
        VImeTextInfo textInfo;
        if(null == ic)
        {
            LogTool.i("input connection is null");
            return null;
        }
        ExtractedText extraText =
            ic.getExtractedText(new ExtractedTextRequest(),0);
        if (null != extraText)
        {
            String realText = extraText.text.toString();
            int realStartSelection = extraText.selectionStart + extraText.startOffset;
            int realEndSelection = extraText.selectionEnd + extraText.startOffset;
            LogTool.i("realStartSelection" + realStartSelection);
            LogTool.i("realEndSelection" + realEndSelection);
            textInfo = new VImeTextInfo(realText, realStartSelection, realEndSelection);

        }
        else
        {
            // 目标区域为非编辑输入区域
            // target field cannot get editor info,construct default VImeTextInfo
            LogTool.i("cannot get info from editor field");
            mCommitMode = PROTECTED_COMMIT_MODE;
            textInfo = new VImeTextInfo();
        }
        return textInfo;
    }

    /**
     * Show tip to user. <br>
     * CN:显示提示给用户。
     * @param tips displayed tip's id. <br>
     *        CN:所要显示的tip的id。
     */
    private void showUserTip(int tips)
    {
        // comment toast show
        // Toast.makeText(VirtualIME.this, tips, Toast.LENGTH_SHORT).show();
        if (tips == R.string.abnormal_start_vime_tip)
        {
            Toast.makeText(VirtualIME.this, tips, Toast.LENGTH_SHORT).show();
        }
    }

    /**
     * Commit the received text to editor field. <br>
     * CN: 提交收到文本信息到输入区域。
     * @param action received text message. <br>
     *        CN:收到的文本消息。
     * @return the obtained VImeTextInfo after commit. <br>
     *         CN:提交之后获得的 VImeTextInfo。
     */
    private synchronized VImeTextInfo commitRecvText(Action action)
    {
        if (mVImeStatus != VimeStatus.VIME_SERVER_STATUS_INPUT)
        {
            LogTool.i("vime status is not input");
            return null;
        }

        if (null != action.getArgumentList())
        {
            Argument seqArg = action.getArgument(FIRST_ARGUMENT_INDEX);
            if ( null == seqArg)
            {
                LogTool.e("seq arg is null");
                return null;
            }

            ArgumentValue seqArgVal = seqArg.getArgumentValue(FIRST_ARGUMENT_INDEX);
            if (null == seqArgVal)
            {
                LogTool.e("seq arg value is null");
                return null;
            }
            int recvSeq = (Integer) seqArgVal.getVaule();
            LogTool.v("commit recvSeq" + recvSeq);
            if (isRecvTextSequenceValid(recvSeq) == false)
            {
                LogTool.e("sequence is invalid not commit");
                return null;
            }

            mLastCommitSequence = recvSeq;

            InputConnection ic = getCurrentInputConnection();
            if (null == ic)
            {
                LogTool.e("InputConnection is null");
                return null;
            }

            VImeTextInfo textInfo = getRealTextInfo();
            if (null == textInfo)
            {
                LogTool.e("cannot editor field");
                return null;
            }

            Argument srcTexArg = action.getArgument(FIRST_ARGUMENT_INDEX);
            if ( null == srcTexArg)
            {
                LogTool.e("srcTexArg is null");
                return null;
            }
            ArgumentValue srcTexArgVal = srcTexArg.getArgumentValue(SECOND_ARGUMENT_INDEX);
            if (null == srcTexArgVal)
            {
                LogTool.e("src text value is null");
                return null;
            }
            String srcText = (String) srcTexArgVal.getVaule();

            Argument srcStartSelectionArg = action.getArgument(FIRST_ARGUMENT_INDEX);
            if ( null == srcStartSelectionArg)
            {
                LogTool.e("src start selection arg is null");
                return null;
            }
            ArgumentValue srcStartSelectionArgVal = srcStartSelectionArg.getArgumentValue(THIRD_ARGUMENT_INDEX);
            if (null == srcStartSelectionArgVal)
            {
                LogTool.e("src start selection arg value is null");
                return null;
            }
            int srcStartSelection = (Integer) srcStartSelectionArgVal.getVaule();

            Argument srcEndSelectionArg = action.getArgument(FIRST_ARGUMENT_INDEX);
            if ( null == srcEndSelectionArg)
            {
                LogTool.e("src end selection arg is null");
                return null;
            }
            ArgumentValue srcEndSelectionArgVal = srcEndSelectionArg.getArgumentValue(FOURTH_ARGUMENT_INDEX);
            if (null == srcEndSelectionArgVal)
            {
                LogTool.e("src end selection arg value is null");
                return null;
            }
            int srcEndSelection = (Integer) srcEndSelectionArgVal.getVaule();

            String realText = textInfo.getRealText();

            int realEndSelection = textInfo.getRealEndSelection();

            ic.beginBatchEdit();
            if (null == srcText)
            {
                srcText = "";
            }

            if (null != realText)
            {
                if (PROTECTED_COMMIT_MODE == mCommitMode)
                {
                    //clear all text in edit field.
                    ic.deleteSurroundingText(Integer.MAX_VALUE / 2, Integer.MAX_VALUE / 2);
                    ic.commitText(srcText, 1);
                }
                else
                {

                    if (realText.equals(srcText))
                    {
                        LogTool.v("only selection changed");
                    }
                    else
                    {
                        LogTool.v("text changed");
                        //clear all text in text field
                        ic.deleteSurroundingText(Integer.MAX_VALUE / 2, Integer.MAX_VALUE / 2);
                        ic.commitText(srcText, 1);
                    }
                }
            }

            LogTool.v("srcStartSelection" + srcStartSelection);
            LogTool.v("srcEndSelection" + srcEndSelection);
            boolean result = ic.setSelection(srcStartSelection, srcStartSelection);
            LogTool.v("set selection result" + result);
            ic.endBatchEdit();
            if (srcEndSelection != srcStartSelection)
            {
                ic.beginBatchEdit();
                ic.setSelection(srcStartSelection, srcEndSelection);
                ic.endBatchEdit();
            }

            VImeTextInfo retTextInfo = getRealTextInfo();

            if (retTextInfo == null)
            {
                LogTool.v("getRealTextInfo failed");
                return null;
            }

            retTextInfo.setSrcText(srcText);
            retTextInfo.setSrcStartSelection(srcStartSelection);
            retTextInfo.setSrcEndSelection(srcEndSelection);
            return retTextInfo;
        }

        LogTool.e("action.getArgumentList is null");
        return null;
    }

    /**
     * Initial some parameters relate to transfer server. <br>
     * CN: 初始化传输服务的相关变量。
     */
    private void initTransferServer()
    {
        mTransfer = new VImeServerTransfer();
        mVImeHttpServer = new HiHttpServer();
        mVImeHttpServer.setServerPort(IME_TRANSFER_SERVER_PORT);
        mVImeHttpServer.setHttpRecvMsgListener(mHttpRecvMsgListener);
    }

    /**
     * Initial some parameters relate to transfer client.<br>
     * CN:初始化传输客户端的相关变量。
     */
    private void initTransferClient()
    {
        mVImeHiHttpClient =
            new HiHttpClient(mStatReport.getRemoteIP(), mStatReport.getRemotePort(), mTimeOut);
    }

    /**
     * Start transfer http server.<br>
     * CN:打开http传输监听服务.<br>
     */
    private boolean startTransferServer()
    {
        LogTool.v("start transfer http Server");
        return mVImeHttpServer.startServer();
    }

    /**
     * Return call input module's result. <br>
     * CN:返回调出小屏是否成功的消息。
     * @param action the received response action. <br>
     *        CN:收到回应的action。
     * @return true means call input module is success; false means call input
     *         module is fail. <br>
     *         CN:true表示调出输入模块成功；false表示调出输入模块失败。
     */
    private boolean isCallInputSuccess(Action action)
    {
        boolean isSuccess = false;
        if (null == action)
        {
            LogTool.e("retCallInput action is null");
        }
        else if (Action.ACTION_ID_VIME_RET_CALL_INPUT == action.getId())
        {
            Argument callInputArg = action.getArgument(0);
            if (null == callInputArg)
            {
                LogTool.e("call input arg is null");
                return false;
            }
            ArgumentValue callInputArgVal = callInputArg.getArgumentValue(0);
            if (null == callInputArgVal)
            {
                LogTool.e("call input arg value is null");
                return isSuccess;
            }
            int result = (Integer) callInputArgVal.getVaule();
            if (Action.ACTION_ID_VIME_SUCCESS_FLAG == result) // FIXME FLAG
            {
                isSuccess = true;
            }
            else
            {
                LogTool.e("call input fail");
            }
        }
        else
        {
            LogTool.e("received other  response msg");
        }
        return isSuccess;
    }

    /**
     * Parse http's response into action. <br>
     * CN:http响应解析为action。
     * @param response received response. <br>
     *        CN:接收到的响应。
     * @return action the parsed action. <br>
     *         CN：解析后的对象。
     */
    private Action parseHttpRes(HiHttpResponse hiHttpRes)
    {
        SaxXmlUtil saxTool = new SaxXmlUtil();
        Action action = null;

        String response = dealHiHttpResponse(hiHttpRes);

        if (null == response)
        {
            LogTool.e("response content is null");
            return null;
        }

        try
        {
            action = saxTool.parse(response.getBytes(SaxXmlUtil.ENCODE_UTF_8));
        }
        catch (UnsupportedEncodingException e)
        {
            LogTool.e("UnsupportedEncodingException");
        }
        catch (ParserConfigurationException e)
        {
            LogTool.e("ParserConfigurationException");
        }
        catch (SAXException e)
        {

            LogTool.e("SAXException");
        }
        catch (IOException e)
        {
            LogTool.e("IOException");
        }
        return action;

    }

    /**
     * Deal HiHttpResponse and get the response‘s body message .<br>
     * CN:处理HiHttpResponse并得到响应的消息体。
     * @param hiHttpRes http response. <br>
     *        CN： http 响应。
     * @return message body, null means response irregular, other means response
     *         normal. <br>
     *         CN：消息体，null表示不正常响应，其他标示响应正常。
     */
    private String dealHiHttpResponse(HiHttpResponse hiHttpRes)
    {
        String respString = null;

        if (HiHttpStatusCode.OK == hiHttpRes.getStatusCode())
        {
            LogTool.v(HiHttpStatusCode.code2String(hiHttpRes.getStatusCode()));
            respString = hiHttpRes.getResponseMessage();
        }
        else
        {
            LogTool.e(HiHttpStatusCode.code2String(hiHttpRes.getStatusCode()));
        }

        return respString;
    }

    /**
     * Is Multiscreen service running. <br>
     * 多屏服务是否运行 。<br>
     * @param context CN:上下文。
     * @return ture, means multiscreen service is running; false means
     *         multiscreen service is not running.<br>
     *         CN:ture表示多屏服务在运行，false表示多屏服务不在运行。
     */
    private boolean isMultiscreenServiceRunnig(Context context)
    {
        boolean result = false;
        ActivityManager mActivityManager =
            (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        List<RunningServiceInfo> appList = mActivityManager.getRunningServices(Integer.MAX_VALUE);
        if (appList == null)
        {
            LogTool.e("service list is null");
            return false;
        }
        for (RunningServiceInfo runningService : appList)
        {
            if (runningService.service.getClassName().equalsIgnoreCase(MULTISCREEN_SERVICE_NAME))
            {
                LogTool.v("multiscreen service is running");
                result = true;
                break;
            }
            else
            {
                continue;
            }
        }
        return result;
    }

    /**
     * Is received text’s sequence valid.<br>
     * CN:接收到文本序号是否是有效的。
     * @param recvSeq text's sequence. CN:文本序号。
     * @return true means text's sequence is valid; false means invalid.<br>
     *         CN:true 表示文本序号是合理的，false表示文本序号是不合理的。
     */
    private boolean isRecvTextSequenceValid(int recvSeq)
    {
        if (recvSeq == (SEND_TEXT_INIT_SEQUENCE + 1))
        {
            return true;
        }

        if (((recvSeq - mLastCommitSequence) > 0)
            || ((recvSeq - mLastCommitSequence) < TEXT_SEQUENCE_REVERSE_TORLENCE))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * Get default IME's id.<br>
     * CN:获得默认输入法的id。
     * @param inputManager input method manager.<br>
     *        CN:输入法管理对象。
     * @return default IME's id.<br>
     *         CN:默认输入法id。
     */
    private String getDefaultIME(InputMethodManager inputManager)
    {
        List<InputMethodInfo> imeList = inputManager.getInputMethodList();
        String retIMEId ;
        String noVIMEId = null;
        for (int i = 0; i < imeList.size(); i++)
        {
            InputMethodInfo imeInfo = imeList.get(i);
            retIMEId = imeInfo.getId();
            if (retIMEId.equals(VIRTUAL_IME_NAME) == false)
            {
                noVIMEId = retIMEId;
                if (retIMEId.equals(LATIN_IME_ID) == true)
                {
                    return retIMEId;
                }
            }
        }
        if (noVIMEId == null)
        {
            retIMEId = VIRTUAL_IME_NAME;
        }
        else
        {
            retIMEId = noVIMEId;
        }
        return retIMEId;
    }

    /**
     * Start check that is VIME start from enable.<br>
     * 检查输入法是否是由enable消息启动的。
     */
    private void startCheck()
    {
        LogTool.v("mIsEnable= " + mIsEnable);
        LogTool.v("mDefaultIMEId is " + mDefaultIMEId);
        if (((!isMultiscreenServiceRunnig(mContext)) || (!mIsEnable))
            && (!VIRTUAL_IME_NAME.equalsIgnoreCase(mDefaultIMEId)))
        {
            LogTool.e("multiscreen is not running");
            showUserTip(R.string.abnormal_start_vime_tip);
            mIsShowTip = false;
            mIMultiScreenManagerVIme.closeKeyboard();
            mInputManager.setInputMethod(null, mDefaultIMEId);
        }
    }
}
