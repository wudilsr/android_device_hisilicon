package com.hisilicon.dlna.player;

import android.app.Fragment;
import android.view.KeyEvent;

import com.hisilicon.dlna.dmr.action.BaseAction;
import com.hisilicon.dlna.file.FileType;

public abstract class PlayerSubWnd extends Fragment
{
    /*
     *  Type of network errors <br>
     *  CN: 网络错误类别定义  <br>
    */
    public enum enFormatMsgNetwork
    {
        /*
         *  unknown error <br>
         *  CN: 未知错误 <br>
        */
        FORMAT_MSG_NETWORK_ERROR_UNKNOWN,

        /*
         *  connection error <br>
         *  CN: 连接失败  <br>
        */
        FORMAT_MSG_NETWORK_ERROR_CONNECT_FAILED,

        /*
         *  operation timeout <br>
         *  CN: 读取超时 <br>
        */
        FORMAT_MSG_NETWORK_ERROR_TIMEOUT,
        /*
         *  net work disconnectr <br>
         *  CN: 断网  <br>
        */
        FORMAT_MSG_NETWORK_ERROR_DISCONNECT,

        /*
         *  file not found <br>
         *  CN: 资源不可用  <br>
        */
        FORMAT_MSG_NETWORK_ERROR_NOT_FOUND,

        /*
         *  status of network is normal <br>
         *  CN: 网络状态正常  <br>
        */
        FORMAT_MSG_NETWORK_NORMAL,
    }

    // 按键处理结果
    public enum KeyDoResult
    {
        // 已处理结束，无需父窗口处理后续处理
        DO_OVER,
        // 已处理，无需父窗口处理，但需要系统继续处理
        DO_DONE_NEED_SYSTEM,
        // 未处理
        DO_NOTHING,
    }

    public abstract KeyDoResult keyDownDispatch(int keyCode, KeyEvent event);

    public abstract KeyDoResult keyUpDispatch(int keyCode, KeyEvent event);

    public abstract KeyDoResult dispatchKeyEvent(KeyEvent event);

    public abstract FileType getSubWndType();

    public abstract void setBaseAction(BaseAction baseAction);

    public abstract void setContentType(String ContentType);

    public abstract void setContentLength(long length);

    // Set the main window interface.<br>
    // CN:设置主窗口接口.
    public abstract void setMainWnd(IPlayerMainWnd parent);

    public abstract boolean isInited();
}
