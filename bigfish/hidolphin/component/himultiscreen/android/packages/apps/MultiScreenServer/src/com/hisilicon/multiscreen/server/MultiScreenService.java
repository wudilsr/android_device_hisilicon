package com.hisilicon.multiscreen.server;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerConfigurationException;

import org.apache.http.util.EncodingUtils;
import org.json.JSONObject;
import org.xml.sax.SAXException;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.Notification;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.pm.ResolveInfo;
import android.content.res.Resources;
import android.content.res.Resources.Theme;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.IBinder;
import android.os.Looper;
import android.os.Message;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.net.ethernet.EthernetManager;
import android.provider.Settings;
import android.provider.Settings.Global;
import android.media.AudioManager;

import com.hisilicon.multiscreen.protocol.message.Action;
import com.hisilicon.multiscreen.protocol.message.Argument;
import com.hisilicon.multiscreen.protocol.message.ArgumentValue;
import com.hisilicon.multiscreen.protocol.message.DefaultResponseMessage;
import com.hisilicon.multiscreen.protocol.message.PlayMediaMessage;
import com.hisilicon.multiscreen.protocol.message.PushMessage;
import com.hisilicon.multiscreen.protocol.message.PushMessageHead;
import com.hisilicon.multiscreen.protocol.server.IPushMessageHandler;
import com.hisilicon.multiscreen.protocol.server.PushServer;
import com.hisilicon.multiscreen.protocol.server.ServerControl;
import com.hisilicon.multiscreen.protocol.utils.AppListTransmitter;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.MultiScreenIntentAction;
import com.hisilicon.multiscreen.protocol.utils.PronounceCoverter;
import com.hisilicon.multiscreen.protocol.utils.SaxXmlUtil;
import com.hisilicon.multiscreen.server.speech.DialogUtil;
import com.hisilicon.multiscreen.server.speech.SpeechDialog;
import com.hisilicon.multiscreen.server.speech.SpeechRecognitionHelper;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage;

/**
 * MultiScreen service class.<br>
 * CN:多屏服务类。
 */
public class MultiScreenService extends Service implements IPushMessageHandler
{

    /**
     * Intent Action, DLNA PlayerBroadcastReceiver.<br>
     * CN:启动DLNA播放器的Intent。
     */
    public static final String BROADCAST_ACTION_DLNA_PLAYER =
        "com.hisilicon.dlna.dmr.action.player";

    /**
     * Path of 3D mode notice file.<br>
     * CN:3D模式提示图片文件路径。
     */
    private static final String NOTICE_3D_MODE_FILE_PATH =
        "data/data/com.hisilicon.multiscreen.server/cache/mirror_3d_mode.jpg";

    /**
     * Path of h264 compatible device list.<br>
     * CN: h264传输兼容性列表文件路径。
     */
    private static final String COMPATIABLE_H264_LIST_FILE_PATH =
        "data/data/com.hisilicon.multiscreen.server/cache/compath264list.xml";

    /**
     * Notify enter smart suspend.<br>
     * CN: 进入浅待机广播。
     */
    private static final String SMART_SUSPEND_ENTER = "smart_suspend_broadcast_enter";

    /**
     * Notify quit smart suspend.<br>
     * CN: 退出浅待机广播。
     */
    private static final String SMART_SUSPEND_QUIT = "smart_suspend_broadcast_quit";

    /**
     * Wifi net interface card name.<br>
     */
    private static final String WIFI_NIC_NAME = "wlan0";

    /**
     * Default Net interface card name.<br>
     */
    private static final String NIC_DEFAULT_NAME = "unknow";

    private final static String DEFAULT_USE_ADAPTER_WIFI_ETHERNET = "eth";

    /**
     * Message id of start all server.<br>
     * CN:启动所有服务的消息ID。
     */
    private static final int MSG_RESTART_MULTISCREEN = 0x100;

    /**
     * Message id of stop all server.<br>
     * CN:停止所有服务的消息ID。
     */
    private static final int MSG_STOP_MULTISCREEN = 0x101;

    /**
     * Message id of start speech.<br>
     * CN:开始语音的消息ID。
     */
    private static final int MSG_START_SPEECH = 0x102;

    /**
     * Time of delay handling message.<br>
     * CN:消息处理延迟。
     */
    private final long DELAY_MILLIS_HANDLE = 300;

    /**
     * Time of delay stopping services to notify client if STB is manual off.<br>
     * CN:手动关闭STB时，延迟停止服务的时长，保证客户端收到消息。
     */
    private final long DELAY_MILLIS_MANUAL_OFF = 2000;

    /**
     * Default sender id.<br>
     * CN:默认的消息发送者ID。
     */
    private static final int SENDER_DEFAULT = 0;

    /**
     * Sender id of network change.<br>
     * CN:网络变更的消息发送者ID。
     */
    private static final int SENDER_NETWORK_CHANGE = SENDER_DEFAULT + 1;

    /**
     * Sender id of manual switch.<br>
     * CN:手动开关的消息发送者ID。
     */
    private static final int SENDER_MANUAL_SWITCH = SENDER_DEFAULT + 2;

    /**
     * Remote app's server port for receive client's data.<br>
     * CN:接收客户端请求的。
     */
    private final int PUSHSERVER_SERVICE_PORT = 8867;

    /**
     * Max buffer size for allocate byte[].<br>
     * CN:byte 数组的最大size。
     */
    private final int MAX_BYTE_BUFFER_SIZE = 2048;

    /**
     * Class for jni call.<br>
     * CN:用于jni调用的类。
     */
    private static MultiScreenNative mMultiScreenNative = null;

    /**
     * Service's context.<br>
     * CN:服务的上下文。
     */
    private Context mContext = null;

    /**
     * Flag for VIME control server start or stop.<br>
     * CN:remote app 是否启动的标志位。
     */
    private boolean mIsVIMEControlServerStart = false;

    /**
     * Flag for remote app start or stop.<br>
     * CN:remote app 是否启动的标志位。
     */
    private boolean mIsRemoteAppServerStart = false;

    /**
     * Switch state manager.<br>
     * CN:HiMultiScreen开关状态管理器。
     */
    private SwitchStateManager stateManager = null;

    /**
     * Register or unregister mNetworkChangeReceiver when switch changes.<br>
     * CN:开关变化时，重启网络状态广播接收。
     */
    private BroadcastReceiver mSwitchChangeReceiver = null;

    /**
     * Restart or stop discovery server when network status changes.<br>
     * CN:服务端网络变更，重启设备发现服务。
     */
    private BroadcastReceiver mNetworkChangeReceiver = null;

    private BroadcastReceiver mPowerReceiver = null;

    /**
     * Is upnp stack open.<br>
     * CN:upnp协议栈开启。
     */
    private static boolean isUpnpStackOpen = false;

    /**
     * Handler of message.<br>
     * CN:消息处理者。
     */
    private MyHandler myHandler = null;

    /**
     * Thread of handler.<br>
     * CN:消息处理线程。
     */
    private HandlerThread mHandlerThread = null;

    /**
     * Enum of network status.<br>
     * CN:网络状态枚举。
     */
    enum NetStatus
    {
        NetworkOn, NetworkOff
    }

    /**
     * Active net interface name.<br>
     * CN:激活网卡的名称。
     */
    private String mActiveNetType = NIC_DEFAULT_NAME;

    /**
     * Status of network.<br>
     * CN:网络状态。
     */
    private static NetStatus netOldState = NetStatus.NetworkOff;

    /**
     * PushServer.<br>
     * CN:PushServer成员。
     */
    private PushServer mPushServer = null;

    /**
     * Previous app package name.<br>
     * CN:前一个app的包名。
     */
    private String mPrevAppPackageName = null;

    /**
     * VIme control class.<br>
     * CN:VIme 控制类。
     */
    private VImeControl mVImeControl = null;

    /**
     * xml解析工具类.<br>
     * CN:xml解析工具类。
     */
    private SaxXmlUtil mSaxXmlTool = null;

    /**
     * the helper class for speech. CN:语音辅助类。
     */
    // private SpeechRecognitionHelper mRecognitionHelper = null;

    /**
     * speech Dialog.<br>
     * CN: 语音dialog.
     */
    private SpeechDialog mSpeechDialog = null;

    /**
     * Callback class.<br>
     * CN:回调类.<br>
     */
    private MultisScreenNativeCallback mNativeCallback = new MultisScreenNativeCallback()
    {
        @Override
        public int nativeInvoke(int comandId, String param, String reservePara)
        {
            int result = MultiScreenNativeCommand.COMMAND_RET_FAIL;
            MultiScreenNativeCommand.NativeInvokeCommand command =
                MultiScreenNativeCommand.NativeInvokeCommand.getCommand(comandId);
            if (null == command)
            {
                LogTool.e("command is null");
                return result;
            }
            switch (command)
            {
                case START_VIME_CONTROL:
                {
                    result = startVIMEControl();
                    break;
                }

                case STOP_VIME_CONTROL:
                {
                    result = stopVIMEControl();
                    break;
                }

                case SET_VIME_URL:
                {
                    result = setVIMEClientURL(param);
                    break;
                }

                case START_REMOTE_APP:
                {
                    result = startRemoteApp();
                    break;
                }

                case STOP_REMOTE_APP:
                {
                    result = stopRemoteApp();
                    break;
                }
                case NOTIFY_SUSPEND_QUIT:
                {
                    result = notifySuspendQuit();
                    break;
                }
                default:
                {
                    LogTool.e("native invoke invalide command");
                    result = MultiScreenNativeCommand.COMMAND_RET_FAIL;
                    break;
                }
            }
            LogTool.i("call command result " + result);
            return result;
        }
    };

    /**
     * Speech msg deal helper.<br>
     * CN:语音消息处理辅助类。<br>
     */
    private ISpeechMsgDealHelper mSpeechMsgDealHelper = new ISpeechMsgDealHelper()
    {

        @Override
        public void speechMsgDeal(String msg)
        {
            LogTool.i("");
            String keyword = PronounceCoverter.getInstance().getPingYin(msg);
            String Data = "page=search&keyword=" + keyword;
            LogTool.i("keyword " + Data);
            String ReturnMode = "0";
            Intent intent = new Intent();
            intent.setAction("moretv.action.applaunch"); // action 名称 必选
            intent.putExtra("Data", Data); // Date 透传字段，必选
            intent.putExtra("ReturnMode", ReturnMode); // ReturnMode 返回方式 0:
                                                       // 返回时退出MoreTV应用 1:
                                                       // 返回时返回MoreTV上层页面 非必选参数
            intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            startActivity(intent);
        }
    };

    @Override
    public IBinder onBind(Intent intent)
    {
        return null;
    }

    @Override
    public void onCreate()
    {
        super.onCreate();
        LogTool.d("onCreate.");

        mContext = this;
        initModules();
        registerReceivers();
        setServiceForeground();
    }

    /**
     * Stop services on destroy.<br>
     * CN:注销时关闭服务。
     */
    public void onDestroy()
    {
        super.onDestroy();
        LogTool.d("onDestroy.");

        unregisterReceivers();
        deinitModules();
        stopUpnpStack();
    }

    private void deinitModules()
    {
        deinitMessageHandler();
        deinitSwitchStateManager();
    }

    /**
     * Init modules.<br>
     * CN:模块初始化。
     */
    private void initModules()
    {
        initSwitchStateManager();

        // Push server service. CN:媒体应用服务。
        initPushServer();

        // Virtual IME control server. CN:虚拟输入法控制服务。
        initVIMEControlServer();

        // Init mirror 3D mode notice file. CN:初始化传屏3D模式提示文件。
        initMirror3DModeNoticeFile();

        // Init compatable list file
        initMirrorCompatListFile();

        // Initialize MultiScreen Native.
        initMultiScreenNative();

        // Initialize network change handler.
        initMessageHandler();

        initSpeechModule();

        initServerControlModule();
    }

    /**
     * Register receivers.<br>
     * Invoke it after initMultiScreenNative.<br>
     * CN:注册广播接收者。<br>
     * CN:注意在initMultiScreenNative后执行。
     */
    private void registerReceivers()
    {
        // CN:开关广播。
        registerSwitchReceiver();

        // CN:开机启动时，若上次为开启，则注册网络广播接收者。
        if (stateManager.isOpen())
        {
            registerNetworkBroadcastReceiver();
            registerPowerBroadcastReceiver();
        }
        else
        {
            LogTool.d("Switch is closed when MultiScreenService on create.");
        }
    }

    /**
     * Unregister receivers.<br>
     * CN:反注册广播接收者。
     */
    private void unregisterReceivers()
    {
        unregisterSwitchReceiver();
        unregisterNetworkBroadcastReceiver();
        unregisterPowerReceiver();
    }

    private void initSwitchStateManager()
    {
        stateManager = SwitchStateManager.getInstance(this);
        stateManager.init();
    }

    private void deinitSwitchStateManager()
    {
        stateManager.deinit();
    }

    private void initMessageHandler()
    {
        mHandlerThread = new HandlerThread("multiscreen_service_handlerthread");
        mHandlerThread.start();
        myHandler = new MyHandler(mHandlerThread.getLooper());
    }

    private void deinitMessageHandler()
    {
        if (myHandler != null)
        {
            clearMessages();
            myHandler = null;
        }

        if (mHandlerThread != null)
        {
            mHandlerThread.getLooper().quit();
        }
    }

    private void initSpeechModule()
    {

    }

    private void initServerControlModule()
    {
        ServerControl sc = new ServerControl(this);
        sc.init();
    }

    private String readFriendlyName()
    {
        // // Put the switch in system setting.
        // SharedPreferences prefrence =
        // getSharedPreferences(MultiScreenServerActivity.MULTISCREEN_SETTING_FILE_NAME,
        // Context.MODE_PRIVATE);
        // return
        // prefrence.getString(MultiScreenServerActivity.MULTISCREEN_FRIENDLY_KEY_NAME,
        // MultiScreenServerActivity.DEFAULT_FRIENDLY_NAME);

        String devicename =
            Settings.Global.getString(getContentResolver(), getSystemSettingDeviceNameKey());
        if (null == devicename)
        {
            devicename = getString(R.string.default_device_name);
        }

        return devicename;
    }

    private String getSystemSettingDeviceNameKey()
    {
        String key = "device_name";
        try
        {
            Field deviceNameField = Settings.Global.class.getField("DEVICE_NAME");
            key = (String) deviceNameField.get(null);
        }
        catch (NoSuchFieldException e)
        {
            LogTool.e(e.getMessage());
        }
        catch (SecurityException e)
        {
            LogTool.e(e.getMessage());
        }
        catch (IllegalArgumentException e)
        {
            LogTool.e(e.getMessage());
        }
        catch (IllegalAccessException e)
        {
            LogTool.e(e.getMessage());
        }
        return key;
    }

    /**
     * Set service foreground.<br>
     * CN:设置本服务为前台服务。
     */
    private void setServiceForeground()
    {
        Notification notification =
            new Notification(R.drawable.muap_server, getText(R.string.himultiscreen_is_running),
                System.currentTimeMillis());
        notification.setLatestEventInfo(this, getText(R.string.FriendlyName),
            getText(R.string.himultiscreen_is_running), null);
        startForeground(R.string.himultiscreen_is_running, notification);
    }

    @Override
    public PushMessage handle(PushMessage msg)
    {
        int type = msg.getHead().getType();
        PushMessage responseMessage;
        switch (type)
        {
            case PushMessageHead.PLAY_MEDIA:
            {
                PlayMediaMessage playMediaReq = (PlayMediaMessage) msg;
                int mediaType = playMediaReq.getMediaType();
                String url = playMediaReq.getUrl();
                LogTool.v("RECV_MEDIA_URL: " + Integer.toString(mediaType) + "/" + url);
                responseMessage = playMedia(playMediaReq);
                break;
            }
            default:
            {
                DefaultResponseMessage res = new DefaultResponseMessage();
                res.setCode(0);
                responseMessage = res;
                break;
            }
        }

        return responseMessage;
    }

    @Override
    public String handleByteArray(byte[] msg) throws ParserConfigurationException, SAXException,
        IOException
    {
        Action responseAction = null;
        /*
         * Analysis httpReq
         */
        Action receiveAction = mSaxXmlTool.parse(msg);

        if (receiveAction != null)
        {
            switch (receiveAction.getId())
            {
            /* Get application list. */
                case Action.ACTION_ID_REMOTE_APP_UPDATE_LIST:
                {
                    responseAction = new Action();
                    responseAction.setId(Action.ACTION_ID_REMOTE_APP_RET_UPDATE_LIST);
                    responseAction.setName("retGetAppList");
                    responseAction =
                        AppListTransmitter.toTransmitPacket(responseAction,
                            this.getPackageManager());
                    if (responseAction != null)
                    {
                        responseAction.setResponseFlag("no");
                        responseAction.setResponseId(Action.ACTION_ID_NO_RESPONSE);
                    }
                    break;
                }

                /* Launch application. */
                case Action.ACTION_ID_REMOTE_APP_LAUNCH:
                {
                    Argument recvArg = receiveAction.getArgument(0);
                    if (null == recvArg)
                    {
                        LogTool.e("app launch action's argument is null");
                        break;
                    }

                    ArgumentValue recvArgVal = recvArg.getArgumentValue(0);
                    if (null == recvArgVal)
                    {
                        LogTool.e("app launch action's argument value is null");
                        break;
                    }
                    Object pkgName = recvArgVal.getVaule();
                    if (pkgName == null)
                    {
                        LogTool.e("app launch action's argument value object is null.");
                        break;
                    }
                    ApplicationRunThread t = new ApplicationRunThread(this, pkgName.toString());
                    t.setName("ApplicationRunThread");
                    t.setDaemon(true);
                    t.start();

                    responseAction = new Action();
                    responseAction.setId(Action.ACTION_ID_REMOTE_APP_RET_LAUNCH);
                    responseAction.setName("retLaunchAPP");
                    responseAction.setResponseFlag("no");
                    responseAction.setResponseId(Action.ACTION_ID_NO_RESPONSE);
                    break;
                }

                case Action.ACTION_ID_SPEECH_TEXT_SEND:
                {
                    LogTool.d("receive speech text");
                    Argument recvArg = receiveAction.getArgument(0);
                    if (null == recvArg)
                    {
                        LogTool.e("send speech info action's argument is null");
                        break;
                    }

                    ArgumentValue recvArgVal = recvArg.getArgumentValue(0);
                    if (null == recvArgVal)
                    {
                        LogTool.e("send speech info action's argument value is null");
                        break;
                    }

                    ArgumentValue recvArgType = recvArg.getArgumentValue(1);
                    if (null == recvArgType)
                    {
                        LogTool.e("send speech info action's argument value is null");
                        break;
                    }

                    int resultType = (Integer) recvArgType.getVaule();
                    LogTool.i("received speech result type " + resultType);
                    String resultJson = (String) recvArgVal.getVaule();
                    LogTool.i("received orignal json result " + resultJson);

                    if ((mSpeechDialog != null) && (mSpeechDialog.isShowing()))
                    {
                        mSpeechDialog.dealMscRespMsg(resultJson, resultType);
                    }

                    responseAction = new Action();
                    responseAction.setId(Action.ACTION_ID_SPEECH_TEXT_RET_SEND);
                    responseAction.setName("retSendSpeechInfo");
                    responseAction.setResponseFlag("no");
                    responseAction.setResponseId(Action.ACTION_ID_NO_RESPONSE);
                    break;
                }

                case Action.ACTION_ID_START_SPEAKING:
                {
                    myHandler.sendEmptyMessage(MSG_START_SPEECH);
                    LogTool.d("start speaking");
                    responseAction = new Action();
                    responseAction.setId(Action.ACTION_ID_RET_START_SPEAKING);
                    responseAction.setName("retStartSpeaking");
                    responseAction.setResponseFlag("no");
                    responseAction.setResponseId(Action.ACTION_ID_NO_RESPONSE);
                    break;
                }

                case Action.ACTION_ID_SPEECH_ERROR:
                {
                    myHandler.sendEmptyMessage(SpeechDialog.MSG_SPEECH_ERROR);
                    LogTool.d("speech error");
                    responseAction = new Action();
                    responseAction.setId(Action.ACTION_ID_SPEECH_ERROR_RET_SEND);
                    responseAction.setName("retSpeechError");
                    responseAction.setResponseFlag("no");
                    responseAction.setResponseId(Action.ACTION_ID_NO_RESPONSE);
                    break;
                }
                default:
                {
                    /* id of action received is not defined */
                    LogTool.e("Request action id is error, so it will send default response!");
                    break;
                }
            }
        }

        if (responseAction == null)
        {
            // default content of response is null.
            responseAction = new Action();
            responseAction.setId(Action.ACTION_ID_NO_RESPONSE);
            responseAction.setName("defaultResponse");
            responseAction.setResponseFlag("no");
            responseAction.setResponseId(Action.ACTION_ID_NO_RESPONSE);
        }

        String responseString;
        try
        {
            responseString = mSaxXmlTool.serialize(responseAction);
        }
        catch (TransformerConfigurationException e)
        {
            responseString = null;
            LogTool.e(e.getMessage());
        }

        return responseString;
    }

    /**
     * Get upnp stack state.<br>
     * CN:UPNP协议栈开启状态。
     * @return true if opened.
     */
    public static boolean isStackOpen()
    {
        return isUpnpStackOpen;
    }

    /**
     * Init file of 3D mode notice picture on STB.<br>
     * CN:在STB端初始化3D模式提示图片文件。
     */
    private void initMirror3DModeNoticeFile()
    {
        File file = new File(NOTICE_3D_MODE_FILE_PATH);
        // file = new File(Environment.getExternalStorageDirectory().getPath() +
        // "/mirror_3dmode.jpg");

        // CN:获取资源。
        Resources res = getResources();
        Bitmap bmp = BitmapFactory.decodeResource(res, R.drawable.mirror_3d_mode);
        if (null == bmp)
        {
            LogTool.e("decode resource mirror_3d_mode failed");
            return;
        }
        // CN:转换JPEG
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        bmp.compress(Bitmap.CompressFormat.JPEG, 100, baos);
        // CN:写入文件。
        byte[] data = baos.toByteArray();
        if (false == writeFile(file.getPath(), data))
        {
            LogTool.e("Write file of 3D mode notice fail!");
        }

        // recycle.
        bmp.recycle();
        try
        {
            baos.close();
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
        }
    }

    /**
     * Init Mirror compat list file.<br>
     * CN:初始化Mirror兼容性列表。
     */
    private void initMirrorCompatListFile()
    {
        // CN:获取资源。
        Resources res = getResources();
        InputStream istream = res.openRawResource(R.raw.compath264list);
        byte[] buffer = new byte[MAX_BYTE_BUFFER_SIZE];
        int readLen;
        try
        {
            readLen = istream.read(buffer);
        }
        catch (IOException e)
        {
            readLen = -1;
            LogTool.e(e.getMessage());
        }
        try
        {
            istream.close();
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
        }

        if (-1 != readLen)
        {
            String compatFile = EncodingUtils.getString(buffer, "UTF-8");
            File xmlFile = new File(COMPATIABLE_H264_LIST_FILE_PATH);
            if (xmlFile.exists())
            {
                LogTool.i("file is already exist not override files");
                return;
            }
            writeFile(COMPATIABLE_H264_LIST_FILE_PATH, compatFile);
        }
        else
        {
            LogTool.e("read compatlist file failed");
        }
    }

    private void writeFile(String fileName, String writestr)
    {
        FileOutputStream fout;
        try
        {
            fout = new FileOutputStream(fileName);
        }
        catch (FileNotFoundException e)
        {
            LogTool.e(e.getMessage());
            return;
        }

        byte[] bytes = writestr.getBytes();
        try
        {
            fout.write(bytes);
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
        }
        try
        {
            fout.close();
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
        }
    }

    /**
     * Write file on STB.<br>
     * CN:写入文件。
     * @param fileName - filepath
     * @param data - date to write
     * @return - true if success.
     */
    private boolean writeFile(String fileName, byte[] data)
    {
        FileOutputStream fout;
        try
        {
            fout = new FileOutputStream(fileName);
        }
        catch (FileNotFoundException e1)
        {
            LogTool.e(e1.getMessage());
            return false;
        }
        try
        {
            fout.write(data);
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
        }

        try
        {
            fout.close();
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
        }
        return true;
    }

    /**
     * Play media of pushing URL.<br>
     * CN:播放媒体推送的内容。
     * @param msg - media message.<br>
     *        CN:媒体推送信息。
     */
    private PushMessage playMedia(PlayMediaMessage msg)
    {
        Uri uri = null;
        int type = msg.getMediaType();
        ImageUrlSave saveImg = new ImageUrlSave();
        /*
         * Get MIME of URL. image will not be opened if exact type is used.
         * CN:获取URL的MIME，FIXME 如果用精确的MIME类型，推送TIF时，图库程序不会出现在应用列表中。
         */
        String MIME = saveImg.getMIME(msg.getUrl());
        LogTool.v("MIME = " + MIME);
        // Check URL.CN:URL有效性检查。
        if (MIME != null)
        {
            switch (type)
            {
                case PlayMediaMessage.MEDIA_TYPE_VEDIO:
                    MIME = "video/*";
                    uri = Uri.parse(msg.getUrl());
                    break;

                case PlayMediaMessage.MEDIA_TYPE_AUDIO:
                    MIME = "audio/*";
                    uri = Uri.parse(msg.getUrl());
                    break;

                case PlayMediaMessage.MEDIA_TYPE_IMAGE:
                    MIME = "image/*";
                    /*
                     * Down load the image file first and return URI. it has
                     * been replaced by DLNA player!
                     * CN：根据推送的URL下载图片，并返回URI，现在使用DLNA播放。
                     */
                    uri = saveImg.getImagePath(msg.getUrl());
                    break;

                default:
                    break;
            }

            if (uri != null)
            {
                Intent i = new Intent();
                i.setAction(Intent.ACTION_VIEW);
                i.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                i.setDataAndType(uri, MIME);
                LogTool.v("start activity to open url");
                startActivity(i);
            }
        }
        else
        {
            LogTool.e("URL received is not correct!");
        }

        // respond client.CN:响应客户端
        DefaultResponseMessage res = new DefaultResponseMessage();
        PushMessageHead head = new PushMessageHead();
        head.setType(PushMessageHead.DEFAULT_RESPONSE);
        res.setHead(head);
        res.setCode(0); // 0 means no error
        return res;
    }

    /**
     * Application running control thread.<br>
     * CN:应用程序运行控制线程。
     */
    private class ApplicationRunThread extends Thread
    {
        private Context mContext;

        private String mPackageName;

        public ApplicationRunThread(Context context, String pkgName)
        {
            this.mContext = context;
            this.mPackageName = pkgName;
        }

        public void run()
        {
            try
            {
                if (mPackageName == null || (mPackageName.trim().length() == 0))
                {
                    return;
                }

                /*
                 * List all applications, and find out by package name.<br>
                 * CN:列出所有应用，根据包名找出所需启动的应用。
                 */
                Intent i = new Intent(Intent.ACTION_MAIN, null);
                i.addCategory(Intent.CATEGORY_LAUNCHER);
                List<ResolveInfo> mAppsList = getPackageManager().queryIntentActivities(i, 0);

                if (mAppsList == null)
                {
                    mAppsList = new ArrayList<ResolveInfo>();
                }

                String pkgClassName = null;
                for (Iterator<ResolveInfo> it = mAppsList.iterator(); it.hasNext();)
                {
                    ResolveInfo app = it.next();
                    if (app.activityInfo.packageName.equalsIgnoreCase(mPackageName))
                    {
                        pkgClassName = app.activityInfo.name;
                        break;
                    }
                }

                if (null == pkgClassName)
                {
                    LogTool.e("Not found class name by package name:" + mPackageName);
                    return;
                }

                LogTool.v("Package:" + mPackageName + " / Class:" + pkgClassName);

                // Now Kill Previous APP.<br> CN:关闭前一个应用。
                if ((mPrevAppPackageName != null) && (mPrevAppPackageName.length() > 0))
                {
                    if (mPrevAppPackageName.equals("com.hisilicon.multiscreen.server") == false)
                    {
                        LogTool.v("Kill previous application by package name:"
                            + mPrevAppPackageName);
                        killProcessByPkgName(mPrevAppPackageName);
                    }
                    else
                    {
                        LogTool.v("preserve MultiScreen Server");
                    }
                }

                Intent intent = new Intent(Intent.ACTION_MAIN);
                intent.addCategory(Intent.CATEGORY_LAUNCHER);
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                ComponentName component = new ComponentName(mPackageName, pkgClassName);
                intent.setComponent(component);
                mContext.startActivity(intent);

                /*
                 * Remember Last APK Name,So that it can be killed On Next
                 * PUSH.<br>保存启动过的应用包名，下一次启动其他应用时关闭已经启动的应用。
                 */
                mPrevAppPackageName = mPackageName;

            }
            catch (Exception e)
            {
                LogTool.e(e.getMessage());
            }

        }

        /**
         * Kill process by package name.<br>
         * CN:根据包名关闭应用。
         * @param pkgName - package name
         * @return - true if success
         */
        private boolean killProcessByPkgName(String pkgName)
        {
            try
            {
                Class<?> c = Class.forName("android.app.ActivityManagerNative");
                Method getDefaultMethod = c.getMethod("getDefault");
                getDefaultMethod.setAccessible(true);
                Object nativeManager = getDefaultMethod.invoke(null);
                c = nativeManager.getClass();
                Method forceStopPackageMethod = c.getMethod("forceStopPackage", String.class);
                forceStopPackageMethod.setAccessible(true);
                forceStopPackageMethod.invoke(nativeManager, pkgName);
            }
            catch (Exception e)
            {
                LogTool.e(e.getMessage());
                return false;
            }
            return true;
        }

        /**
         * Stop thread.<br>
         * CN:关闭线程。
         */
        public void destroy()
        {
            if (this.isAlive())
            {
                this.interrupt();
            }
        }
    }

    /**
     * Broadcast switch state for MultiScreenServerActivity.<br>
     * CN:发送服务启停广播，让多屏活动界面更新。
     * @param isOpen
     */
    private void broadcastSwitchState(boolean isOpen)
    {
        Intent intent;
        if (isOpen)
        {
            intent = new Intent(MultiScreenIntentAction.MULITSCREEN_SERVER_START);
        }
        else
        {
            intent = new Intent(MultiScreenIntentAction.MULITSCREEN_SERVER_STOP);
        }
        sendBroadcast(intent);
    }

    /**
     * Register switch change receiver.<br>
     * CN:注册开关变化广播接收者。
     */
    private void registerSwitchReceiver()
    {
        IntentFilter filter = new IntentFilter();
        filter.addAction(MultiScreenIntentAction.MULITSCREEN_SWITCH_OPEN);
        filter.addAction(MultiScreenIntentAction.MULITSCREEN_SWITCH_CLOSE);
        if (mSwitchChangeReceiver == null)
        {
            mSwitchChangeReceiver = new BroadcastReceiver()
            {
                @Override
                public void onReceive(Context context, Intent intent)
                {
                    String action = intent.getAction();
                    if (MultiScreenIntentAction.MULITSCREEN_SWITCH_OPEN.equalsIgnoreCase(action))
                    {
                        // CN:界面开关开启。
                        registerNetworkBroadcastReceiver();
                        broadcastSwitchState(true);
                    }
                    else if (MultiScreenIntentAction.MULITSCREEN_SWITCH_CLOSE
                        .equalsIgnoreCase(action))
                    {
                        // CN:界面开关关闭。
                        unregisterNetworkBroadcastReceiver();
                        stopMultiScreenAll(SENDER_MANUAL_SWITCH);
                        broadcastSwitchState(false);
                    }
                }
            };
        }

        registerReceiver(mSwitchChangeReceiver, filter);
    }

    /**
     * Unregister switch change receiver.<br>
     * CN:反注册开关变化广播接收者。
     */
    private void unregisterSwitchReceiver()
    {
        if (mSwitchChangeReceiver != null)
        {
            unregisterBroadcastReceiver(mSwitchChangeReceiver);
            mSwitchChangeReceiver = null;
        }
    }

    /**
     * Register network change broadcast receiver.<br>
     * CN:注册网络状态变化广播接收者。<br>
     * Restart or stop discovery server according to network status.<br>
     * CN:根据网络状态，启动或关闭设备发现服务。
     */
    private void registerNetworkBroadcastReceiver()
    {
        resetNetworkStateVariable();
        IntentFilter filter = new IntentFilter(WifiManager.WIFI_AP_STATE_CHANGED_ACTION);
        filter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);

        mNetworkChangeReceiver = new BroadcastReceiver()
        {
            public void onReceive(Context context, Intent intent)
            {
                if (WifiManager.WIFI_AP_STATE_CHANGED_ACTION.equalsIgnoreCase(intent.getAction())
                    || ConnectivityManager.CONNECTIVITY_ACTION.equalsIgnoreCase(intent.getAction()))
                {
                    // CN:网络变更广播。
                    LogTool.d("Receive broadcast: " + intent.getAction());

                    boolean networkstatus = isNetworkEnable();
                    if (networkstatus == true)
                    {
                        // Network on.
                        LogTool.d("network status on.");
                        netOldState = NetStatus.NetworkOn;
                        restartMultiScreenAll(SENDER_NETWORK_CHANGE);
                    }
                    else
                    {
                        // Network off.
                        LogTool.d("network status off");
                        netOldState = NetStatus.NetworkOff;
                        stopMultiScreenAll(SENDER_NETWORK_CHANGE);
                    }
                }
            }
        };

        registerReceiver(mNetworkChangeReceiver, filter);
    }

    /**
     * Unregister receiver of network status changing.<br>
     * CN:反注册网络状态监控。
     */
    private void unregisterNetworkBroadcastReceiver()
    {
        if (mNetworkChangeReceiver != null)
        {
            unregisterBroadcastReceiver(mNetworkChangeReceiver);
            mNetworkChangeReceiver = null;
        }
        resetNetworkStateVariable();
    }

    private void registerPowerBroadcastReceiver()
    {
        IntentFilter powerIntentFilter = new IntentFilter();
        powerIntentFilter.addAction(SMART_SUSPEND_ENTER);
        // powerIntentFilter.addAction(SMART_SUSPEND_QUIT);
        mPowerReceiver = new BroadcastReceiver()
        {
            @Override
            public void onReceive(Context context, Intent intent)
            {
                LogTool.d("receive action " + intent.getAction());
                if (SMART_SUSPEND_ENTER.equalsIgnoreCase(intent.getAction()))
                {
                    mMultiScreenNative.MultiScreenNativeSuspend();
                }
            }
        };
        registerReceiver(mPowerReceiver, powerIntentFilter);
    }

    private void unregisterPowerReceiver()
    {
        if (mPowerReceiver != null)
        {
            unregisterBroadcastReceiver(mPowerReceiver);
            mPowerReceiver = null;
        }
    }

    /**
     * Reset variable of network state.<br>
     * CN:重置网络状态变量。
     */
    private void resetNetworkStateVariable()
    {
        netOldState = NetStatus.NetworkOff;
    }

    /**
     * Initial PushServer.<br>
     * CN:初始化PushServer。
     */
    private void initPushServer()
    {
        mSaxXmlTool = new SaxXmlUtil();
        mPushServer = new PushServer(PUSHSERVER_SERVICE_PORT);
        mPushServer.setMessageHandler(this);
    }

    /**
     * Initial VIMEControlServer.<br>
     * CN:初始化VIMEControlServer。
     */
    private void initVIMEControlServer()
    {
        mVImeControl =
            new VImeControl(mContext,
                (InputMethodManager) this.getSystemService(Context.INPUT_METHOD_SERVICE));
    }

    /**
     * Initial MultiScreenNative.<br>
     * CN:初始化MultiScreenNative。
     */
    private void initMultiScreenNative()
    {
        mMultiScreenNative = MultiScreenNative.getInstance();
        mMultiScreenNative.setCallback(mNativeCallback);
        mMultiScreenNative.MultiScreenNativeInit();
    }

    /**
     * Restart upnp stack.<br>
     * @return result.
     */
    private int restartUpnpStack()
    {
        stopUpnpStack();
        int retValue = startUpnpStack();
        return retValue;
    }

    /**
     * Start UPNP stack.<br>
     * @return result.
     */
    private int startUpnpStack()
    {
        int retValue = 0;

        if ((isUpnpStackOpen == false) && (netOldState == NetStatus.NetworkOn))
        {
            LogTool.d("startUpnpStack.");
            isUpnpStackOpen = true;
            LogTool.i("start with net type " + mActiveNetType);
            retValue =
                mMultiScreenNative.MultiScreenDeviceStart(
                    UpnpMultiScreenDeviceInfo.defaultServiceList(), readFriendlyName(),
                    mActiveNetType);
        }

        return retValue;
    }

    /**
     * Stop UPNP stack.<br>
     * @return result.
     */
    private int stopUpnpStack()
    {
        LogTool.d("stopUpnpStack.");
        isUpnpStackOpen = false;
        int retValue = mMultiScreenNative.MultiScreenDeviceStop();
        return retValue;
    }

    /**
     * Notify client that server is manual off.
     * @return result
     */
    private int notifyManualOff()
    {
        LogTool.d("Notify client that server is manual off.");
        int retValue = mMultiScreenNative.MultiScreenNotifyManualOff();
        return retValue;
    }

    /**
     * Start VIME Control server.<br>
     * CN:开启VIME 控制服务。
     * @return result O means execute method success,-1 means execute method
     *         failure.<br>
     *         CN:0代表方法执行成功，-1代表方法执行失败。
     */
    private int startVIMEControl()
    {
        if (!mIsVIMEControlServerStart)
        {
            LogTool.d("startVIMEControl");
            mVImeControl.startControl();
            mIsVIMEControlServerStart = true;
        }
        else
        {
            LogTool.i("VIME Control server has started");
        }
        return MultiScreenNativeCommand.COMMAND_RET_SUCCESS;
    }

    /**
     * Stop VIME Control Server.<br>
     * CN:关闭VIME的控制服务。
     * @return result O means execute method success,-1 means execute method
     *         failure.<br>
     *         CN:0代表方法执行成功，-1代表方法执行失败。
     */
    private int stopVIMEControl()
    {
        if (mIsVIMEControlServerStart)
        {
            LogTool.d("stop VIMEControl");
            mVImeControl.stopControl();
            mIsVIMEControlServerStart = false;
        }
        else
        {
            LogTool.i("VIME Control server has stopped");
        }
        return MultiScreenNativeCommand.COMMAND_RET_SUCCESS;
    }

    /**
     * Set VIME Client's url <br>
     * CN:设置VIME Client‘s url.
     * @param url VIME client's url.<br>
     *        CN:VIME客户端的url。
     * @return result O means execute method success,-1 means execute method
     *         failure.<br>
     *         CN:0代表方法执行成功，-1代表方法执行失败。
     */
    private int setVIMEClientURL(String url)
    {
        LogTool.d("setVIMEClientURL");
        mVImeControl.setClientURL(url);
        return MultiScreenNativeCommand.COMMAND_RET_SUCCESS;
    }

    /**
     * Start remote app server.<br>
     * CN:关闭remote app 服务。
     * @return result O means execute method success,-1 means execute method
     *         failure.<br>
     *         CN:0代表方法执行成功，-1代表方法执行失败。
     */
    private int startRemoteApp()
    {
        if (!mIsRemoteAppServerStart)
        {
            mPushServer.start();
            mIsRemoteAppServerStart = true;
            LogTool.d("remote app started");
        }
        else
        {
            LogTool.i("RemoteApp server has stopped");
        }
        return MultiScreenNativeCommand.COMMAND_RET_SUCCESS;
    }

    /**
     * Stop remote app server.<br>
     * CN:关闭remote app 服务。
     * @return result O means execute method success,-1 means execute method
     *         failure.<br>
     *         CN:0代表方法执行成功，-1代表方法执行失败。
     */
    private int stopRemoteApp()
    {
        if (mIsRemoteAppServerStart)
        {
            mPushServer.stop();
            mIsRemoteAppServerStart = false;
            LogTool.d("remote app stopped");
        }
        else
        {
            LogTool.i("RemoteApp server has stopped");
        }
        return MultiScreenNativeCommand.COMMAND_RET_SUCCESS;
    }

    private int notifySuspendQuit()
    {
        LogTool.d("notifySuspendQuit");
        Intent intent = new Intent(SMART_SUSPEND_QUIT);
        mContext.sendBroadcast(intent);
        return MultiScreenNativeCommand.COMMAND_RET_SUCCESS;
    }

    /**
     * Return whether the network is up. 判断网络是否连通
     */
    private boolean isNetworkEnable()
    {
        ConnectivityManager networkManager =
            (ConnectivityManager) mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
        if (networkManager == null)
        {
            LogTool.e("get connectivityManager is null");
            mActiveNetType = NIC_DEFAULT_NAME;
            return false;
        }
        EthernetManager ethManager =
            (EthernetManager) mContext.getSystemService(Context.ETHERNET_SERVICE);
        if (ethManager == null)
        {
            LogTool.e("get ethernetManager is null");
            mActiveNetType = NIC_DEFAULT_NAME;
            return false;
        }
        mActiveNetType = NIC_DEFAULT_NAME;


        WifiManager wifiManager = (WifiManager) mContext.getSystemService(Context.WIFI_SERVICE);
        if ( (wifiManager != null)&& (wifiManager.getWifiApState() == WifiManager.WIFI_AP_STATE_ENABLED))
        {
            LogTool.i("AP is open");
            mActiveNetType = WIFI_NIC_NAME;
        }

        if (networkManager.getActiveDefaultNetwork() == ConnectivityManager.TYPE_WIFI)
        {
            LogTool.i("wifi is open");
            mActiveNetType = WIFI_NIC_NAME;
        }
        else if (networkManager.getActiveDefaultNetwork() == ConnectivityManager.TYPE_ETHERNET) {
            NetworkInfo ni = networkManager.getWifiStateWithoutDisguise();
            if(ni.isConnected() == true) {
            //wifi和ethernet都打开
                LogTool.i("both ethernet and wifi is open");
                if(DEFAULT_USE_ADAPTER_WIFI_ETHERNET.contains("wlan"))
                {
                   mActiveNetType = WIFI_NIC_NAME;
                }
                else
                {
                   mActiveNetType = getActiveNetType(ethManager);
                }

            } else {
            //只有ethernet打开
                LogTool.i("ethernet is open");
                mActiveNetType = getActiveNetType(ethManager);//"eth0";
            }
        }

        LogTool.i("mActiveNetType " + mActiveNetType);

        if (mActiveNetType.equalsIgnoreCase(NIC_DEFAULT_NAME))
            return false;
        else
            return true;
    }

    /**
     * Get active net type.<br>
     * @return
     */
    private String getActiveNetType(EthernetManager ethManager)
    {
        String netType = NIC_DEFAULT_NAME;
        Method method = null;
        Class<?> c = null;
        try
        {
            c = Class.forName("android.net.ethernet.EthernetManager");
        }
        catch (ClassNotFoundException e)
        {
            LogTool.e(e.getMessage());
            return netType;
        }

        try
        {
            method = c.getMethod("getDatabaseInterfaceName");
        }
        catch (NoSuchMethodException e)
        {
            LogTool.e(e.getMessage());
            try
            {
                method = c.getMethod("getInterfaceName");
            }
            catch (NoSuchMethodException e1)
            {
                LogTool.e(e1.getMessage());
            }
        }

        if (method != null)
        {
            try
            {
                // netType = (String) method.invoke(c.newInstance());
                netType = (String) method.invoke(ethManager);
            }
            catch (InvocationTargetException e)
            {
                LogTool.e(e.getMessage());
            }
            catch (IllegalAccessException e)
            {
                LogTool.e(e.getMessage());
            }
        }

        return netType;
    }

    private void restartMultiScreenAll(int senderId)
    {
        clearMessages();
        if (myHandler != null)
        {
            Message msg = myHandler.obtainMessage();
            if (msg == null)
            {
                LogTool.e("Obtain msg failed.");
                return;
            }
            msg = myHandler.obtainMessage();
            msg.what = MSG_RESTART_MULTISCREEN;
            myHandler.sendMessageDelayed(msg, DELAY_MILLIS_HANDLE);
        }
    }

    private void stopMultiScreenAll(int senderId)
    {
        clearMessages();
        if (myHandler != null)
        {
            Message msg = myHandler.obtainMessage();
            if (msg == null)
            {
                LogTool.e("Obtain msg failed.");
                return;
            }
            else
            {
                msg.what = MSG_STOP_MULTISCREEN;
            }

            switch (senderId)
            {
                case SENDER_NETWORK_CHANGE:
                {
                    myHandler.sendMessageDelayed(msg, DELAY_MILLIS_HANDLE);
                }
                    break;

                case SENDER_MANUAL_SWITCH:
                {
                    notifyManualOff();
                    myHandler.sendMessageDelayed(msg, DELAY_MILLIS_MANUAL_OFF);
                }
                    break;

                default:
                    break;
            }
        }
    }

    private void clearMessages()
    {
        if (myHandler != null)
        {
            if (myHandler.hasMessages(MSG_RESTART_MULTISCREEN))
                myHandler.removeMessages(MSG_RESTART_MULTISCREEN);

            if (myHandler.hasMessages(MSG_STOP_MULTISCREEN))
                myHandler.removeMessages(MSG_STOP_MULTISCREEN);
        }
    }

    private class MyHandler extends Handler
    {
        public MyHandler(Looper looper)
        {
            super(looper);
        }

        @Override
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
                case MSG_RESTART_MULTISCREEN:
                {
                    if (stateManager.isOpen())
                    {
                        restartUpnpStack();
                    }
                }
                    break;

                case MSG_STOP_MULTISCREEN:
                {
                    stopUpnpStack();
                }
                    break;

                case MSG_START_SPEECH:
                {
                    showSpeechDialog();
                }
                    break;

                case SpeechDialog.MSG_UPDATE_SPEECH_VIEW:
                {
                    updateSpeechContent();
                }
                    break;

                case SpeechDialog.MSG_UPDATE_WEATHER_VIEW:
                {
                    Bundle data = msg.getData();
                    String msgValue = data.getString("value");

                    updateWeatherContent(msgValue);
                }
                    break;

                case SpeechDialog.MSG_KEYDOWN_BACK:
                case SpeechDialog.MSG_DIALOG_TIMEOUT:
                case SpeechDialog.MSG_SPEECH_ERROR:
                case SpeechDialog.MSG_SPEECH_DIALOG_DISMISS:
                {
                    dismissSpeechDialog();
                }
                    break;
                default:
                    break;
            }
        }
    }

    /**
     * Unregister receiver of broadcast.<br>
     * CN:反注册广播接收者。
     * @param receiver broadcast receiver.
     */
    private void unregisterBroadcastReceiver(BroadcastReceiver receiver)
    {
        try
        {
            unregisterReceiver(receiver);
        }
        catch (IllegalArgumentException e)
        {
            LogTool.d("the receiver was already unregistered or was not registered.");
        }
    }

    /**
     * Is soft AP enable.<br>
     * CN: 软AP是否开启。
     * @return true，ap
     */
    private boolean isSoftAPEnable()
    {
        WifiManager wifiMgr = (WifiManager) getSystemService(Context.WIFI_SERVICE);
        if (null == wifiMgr)
        {
            LogTool.e("wifiManager is null");
            return false;
        }
        LogTool.d("isWifiApEnabled: " + wifiMgr.isWifiApEnabled());
        if (wifiMgr.isWifiApEnabled())
        {
            return true;
        }
        return false;
    }

    /**
     * Show speech Dialog.
     */
    private void showSpeechDialog()
    {
        if (mSpeechDialog == null)
        {
            mSpeechDialog = new SpeechDialog(mContext, R.style.SpeechDialogStyle, myHandler);
        }

        DialogUtil.showServiceDialog(mSpeechDialog);
    }

    /**
     * Dismiss speech Dialog.
     */
    private void dismissSpeechDialog()
    {
        if (mSpeechDialog != null)
        {
            mSpeechDialog.dismiss();
        }
    }

    /**
     * Update speech content.
     */
    private void updateSpeechContent()
    {
        if (mSpeechDialog != null)
        {
            mSpeechDialog.updateSpeechAdapter();
        }
    }

    /**
     * Update weather content.
     */
    private void updateWeatherContent(String msgValue)
    {
        if (mSpeechDialog != null)
        {
            mSpeechDialog.updateWeatherData(msgValue);
        }
    }
}
