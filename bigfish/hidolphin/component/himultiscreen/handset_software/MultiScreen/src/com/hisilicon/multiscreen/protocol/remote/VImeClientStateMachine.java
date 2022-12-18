package com.hisilicon.multiscreen.protocol.remote;

import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.VImeStateMachineDriverMessage;
import com.hisilicon.multiscreen.protocol.utils.VImeStatusDefine;

/**
 * Status machine of VIME.<br>
 * CN:虚拟输入法状态机。
 * @see VImeStatusDefine
 * @see VImeStateMachineDriverMessage
 * @since MultiScreen V2.0.1.1 2013/01/11: first create.
 */
public class VImeClientStateMachine
{
    /**
     * Instance of VImeClientStateMachine.<br>
     */
    private static VImeClientStateMachine mVimeClientStateMachine = null;

    /**
     * Status value of VIME.<br>
     * initial value of it is DIINIT_STATUS_VIME_CLIENT.
     */
    private VImeStatusDefine.VimeStatus mVimeStatusValue =
        VImeStatusDefine.VimeStatus.DEINIT_STATUS_VIME_CLIENT;

    /**
     * State machine handler.<br>
     */
    private IVImeClientStateMachineHandler mVimeStatusMachineHandler =
        new IVImeClientStateMachineHandler()
        {

            @Override
            public boolean initVimeMachine(VImeStateMachineDriverMessage driver)
            {
                if (mVimeStatusValue == VImeStatusDefine.VimeStatus.DEINIT_STATUS_VIME_CLIENT)
                {
                    mVimeStatusValue = VImeStatusDefine.VimeStatus.INIT_STATUS_VIME_CLIENT;
                    return true;
                }

                return false;
            }

            @Override
            public synchronized VImeStatusDefine.VimeStatus updateVimeStatus(
                VImeStateMachineDriverMessage driver)
            {
                if (driver == null)
                {
                    return mVimeStatusValue;
                }

                switch (mVimeStatusValue)
                {
                    case INIT_STATUS_VIME_CLIENT:
                    {
                        if (driver == VImeStateMachineDriverMessage.CHECK_OK)
                        {
                            mVimeStatusValue = VImeStatusDefine.VimeStatus.READY_STATUS_VIME_CLIENT;
                        }
                        else if (driver == VImeStateMachineDriverMessage.CHECK_FAIL)
                        {
                            mVimeStatusValue = VImeStatusDefine.VimeStatus.SETUP_STATUS_VIME_CLIENT;
                        }
                        else if (driver == VImeStateMachineDriverMessage.CLOSE_VIME)
                        {
                            mVimeStatusValue =
                                VImeStatusDefine.VimeStatus.DEINIT_STATUS_VIME_CLIENT;
                            LogTool.e("To close vime when it is in init status.");
                        }
                        else
                        {
                            LogTool.e("state machine: INIT_STATUS_VIME_CLIENT, being driven by "
                                + driver.getName());
                        }
                        break;
                    }
                    case DEINIT_STATUS_VIME_CLIENT:
                    {
                        if (driver == VImeStateMachineDriverMessage.OPEN_VIME)
                        {
                            mVimeStatusValue = VImeStatusDefine.VimeStatus.INIT_STATUS_VIME_CLIENT;
                        }
                        else
                        {
                            LogTool.e("state machine: DEINIT_STATUS_VIME_CLIENT, being driven by "
                                + driver.getName());
                        }
                        break;
                    }

                    case SETUP_STATUS_VIME_CLIENT:
                    {
                        if (driver == VImeStateMachineDriverMessage.CHECK_OK)
                        {
                            mVimeStatusValue = VImeStatusDefine.VimeStatus.READY_STATUS_VIME_CLIENT;
                        }
                        else if (driver == VImeStateMachineDriverMessage.CHECK_FAIL)
                        {
                            mVimeStatusValue =
                                VImeStatusDefine.VimeStatus.DEINIT_STATUS_VIME_CLIENT;
                        }
                        else if (driver == VImeStateMachineDriverMessage.CLOSE_VIME)
                        {
                            mVimeStatusValue =
                                VImeStatusDefine.VimeStatus.DEINIT_STATUS_VIME_CLIENT;
                        }
                        else
                        {
                            LogTool.e("state machine: SETUP_STATUS_VIME_CLIENT, being driven by "
                                + driver.getName());
                        }
                        break;
                    }

                    case READY_STATUS_VIME_CLIENT:
                    {
                        if (driver == VImeStateMachineDriverMessage.CALL_INPUT)
                        {
                            mVimeStatusValue = VImeStatusDefine.VimeStatus.INPUT_STATUS_VIME_CLIENT;
                        }
                        else if (driver == VImeStateMachineDriverMessage.CHECK_FAIL)
                        {
                            mVimeStatusValue = VImeStatusDefine.VimeStatus.SETUP_STATUS_VIME_CLIENT;
                        }
                        else if (driver == VImeStateMachineDriverMessage.CLOSE_VIME)
                        {
                            mVimeStatusValue =
                                VImeStatusDefine.VimeStatus.DEINIT_STATUS_VIME_CLIENT;
                        }
                        else if (driver == VImeStateMachineDriverMessage.CHECK_OK)
                        {
                            // it is ok
                        }
                        else
                        {
                            LogTool.w("state machine: READY_STATUS_VIME_CLIENT, being driven by "
                                + driver.getName());
                        }
                        break;
                    }

                    case INPUT_STATUS_VIME_CLIENT:
                    {
                        if (driver == VImeStateMachineDriverMessage.END_INPUT)
                        {
                            mVimeStatusValue = VImeStatusDefine.VimeStatus.READY_STATUS_VIME_CLIENT;
                        }
                        else if (driver == VImeStateMachineDriverMessage.CHECK_FAIL)
                        {
                            mVimeStatusValue = VImeStatusDefine.VimeStatus.SETUP_STATUS_VIME_CLIENT;
                        }
                        else if (driver == VImeStateMachineDriverMessage.CLOSE_VIME)
                        {
                            mVimeStatusValue =
                                VImeStatusDefine.VimeStatus.DEINIT_STATUS_VIME_CLIENT;
                            LogTool.e("To close VIME when it is in input status.");
                        }
                        else if (driver == VImeStateMachineDriverMessage.CHECK_OK)
                        {
                            // it is ok
                        }
                        else
                        {
                            LogTool.e("state machine: INPUT_STATUS_VIME_CLIENT, being driven by "
                                + driver.getName());
                        }
                        break;
                    }
                    default:
                        break;
                }

                return mVimeStatusValue;
            }

            @Override
            public synchronized VImeStatusDefine.VimeStatus getVimeStatus()
            {
                return mVimeStatusValue;
            }

        };

    /**
     * Get instance of class VimeClientStateMachine.<br>
     * @return - instance of class VimeClientStateMachine
     */
    public static VImeClientStateMachine getInstance()
    {
        if (mVimeClientStateMachine == null)
        {
            mVimeClientStateMachine = new VImeClientStateMachine();
        }
        return mVimeClientStateMachine;
    }

    /**
     * Initialize VIME client.<br>
     * @return - true while successfully
     */
    public boolean initVimeClient(VImeStateMachineDriverMessage driver)
    {
        return mVimeStatusMachineHandler.initVimeMachine(driver);
    }

    /**
     * DeInit VIME client.<br>
     */
    public void deInitVimeClient()
    {
        mVimeStatusValue = VImeStatusDefine.VimeStatus.DEINIT_STATUS_VIME_CLIENT;
    }

    /**
     * Update status of VIME machine.<br>
     * @param driver - driver message
     * @return - status of VIME
     */
    public VImeStatusDefine.VimeStatus updateStatus(VImeStateMachineDriverMessage driver)
    {
        return mVimeStatusMachineHandler.updateVimeStatus(driver);
    }

    /**
     * Get index of VIME status.<br>
     * @return - index of VIME state machine
     */
    public int getStatusIndex()
    {
        return mVimeStatusValue.getIndex();
    }

    /**
     * Get status of state machine.<br>
     * @return VimeStatus
     */
    public VImeStatusDefine.VimeStatus getStatus()
    {
        return mVimeStatusValue;
    }

    /**
     * Set VimeStatusMachineHandler.<br>
     * @param vimeStatusMachineHandler - VimeStatusMachineHandler
     * @deprecated
     */
    public void setVimeStatusMachineHandler(IVImeClientStateMachineHandler vimeStatusMachineHandler)
    {
        mVimeStatusMachineHandler = vimeStatusMachineHandler;
    }
}
