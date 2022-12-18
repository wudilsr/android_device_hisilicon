package com.hisilicon.multiscreen.protocol.remote;

import com.hisilicon.multiscreen.protocol.utils.VImeStateMachineDriverMessage;
import com.hisilicon.multiscreen.protocol.utils.VImeStatusDefine;

/**
 * interface of handler of VIME status machine.<br>
 * CN:虚拟输入法状态机处理接口。
 * @since MultiScreen V2.0.1.1
 */
public interface IVImeClientStateMachineHandler
{
    /**
     * initialize VIME Machine
     * @return true if initialization is successful
     */
    public boolean initVimeMachine(VImeStateMachineDriverMessage driver);

    /**
     * Update status of VIME.<br>
     * @param driver - driver message of VIme.
     * @return true while the status sets successfully.
     */
    public VImeStatusDefine.VimeStatus updateVimeStatus(VImeStateMachineDriverMessage driver);

    /**
     * get status of VIME
     * @return the status value of VIME
     */
    public VImeStatusDefine.VimeStatus getVimeStatus();
}
