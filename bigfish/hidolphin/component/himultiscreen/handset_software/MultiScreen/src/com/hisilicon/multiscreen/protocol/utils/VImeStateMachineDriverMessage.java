package com.hisilicon.multiscreen.protocol.utils;

/**
 * Message of VIME state machine driver.<br>
 * CN:虚拟输入法状态机驱动消息。
 * @since MultiScreen V2.0.1.1 2013/01/11: first create
 */
public enum VImeStateMachineDriverMessage
{
    // Driver message of VIME state machine on client.
    OPEN_VIME("client_open_vime", 0x001), CLOSE_VIME("client_close_vime", 0x002), CHECK_OK(
        "client_check_ok", 0x003), NETWORK_EXCEPTION("client_network_exception", 0x004), CHECK_FAIL(
        "client_check_fail", 0x005), CALL_INPUT("server_call_input", 0x006), END_INPUT("end_input",
        0x007);

    private String mMessageName;

    private final int mIndex;

    /**
     * Constructor of VIME state machine driver message.<br>
     * @param name - name of driver message
     * @param index - index of driver message
     */
    private VImeStateMachineDriverMessage(String name, int index)
    {
        this.mMessageName = name;
        this.mIndex = index;
    }

    /**
     * Get driver message by index.<br>
     * @param index - index of driver message
     * @return driver message
     */
    public static VImeStateMachineDriverMessage getState(int index)
    {
        for (VImeStateMachineDriverMessage status : VImeStateMachineDriverMessage.values())
        {
            if (status.getIndex() == index)
            {
                return status;
            }
        }
        return null;
    }

    /**
     * Get name of driver message by index.<br>
     * @param index - index of driver message
     * @return name of driver message in the index
     */
    public static String getName(int index)
    {
        for (VImeStateMachineDriverMessage status : VImeStateMachineDriverMessage.values())
        {
            if (status.getIndex() == index)
            {
                return status.mMessageName;
            }
        }
        return null;
    }

    /**
     * Get name of driver message.<br>
     * @return name of driver message
     */
    public String getName()
    {
        return mMessageName;
    }

    /**
     * Set name of driver message.<br>
     * @deprecated
     * @param name - name of driver message
     */
    public void setName(String name)
    {
        this.mMessageName = name;
    }

    /**
     * Get index of driver message.<br>
     * @return index of driver message
     */
    public int getIndex()
    {
        return mIndex;
    }
}
