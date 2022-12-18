package com.hisilicon.multiscreen.protocol.utils;

/**
 * Defines of VIME's status.<br>
 * CN:虚拟输入法状态定义。
 * @since MultiScreen V2.0.1.1 2013/01/11: first create.
 */
public class VImeStatusDefine
{
    /**
     * Enumeration of VIme status.
     */
    public enum VimeStatus
    {
        // Status of VIME on client.
        INIT_STATUS_VIME_CLIENT("client_init", VImeStatusDefine.INIT_STATUS_VIME_CLIENT), SETUP_STATUS_VIME_CLIENT(
            "client_setup", VImeStatusDefine.SETUP_STATUS_VIME_CLIENT), READY_STATUS_VIME_CLIENT(
            "client_ready", VImeStatusDefine.READY_STATUS_VIME_CLIENT), INPUT_STATUS_VIME_CLIENT(
            "client_input", VImeStatusDefine.INPUT_STATUS_VIME_CLIENT), DEINIT_STATUS_VIME_CLIENT(
            "client_close", VImeStatusDefine.DEINIT_STATUS_VIME_CLIENT)
        // status of VIME on server
        , VIME_SERVER_STATUS_INIT("server_init", VImeStatusDefine.VIME_SERVER_STATUS_INIT), VIME_SERVER_STATUS_READY(
            "server_ready", VImeStatusDefine.VIME_SERVER_STATUS_READY), VIME_SERVER_STATUS_INPUT(
            "server_input", VImeStatusDefine.VIME_SERVER_STATUS_INPUT), VIME_SERVER_STATUS_DEINIT(
            "server_deinit", VImeStatusDefine.VIME_SERVER_STATUS_DEINIT);

        private String name;

        private int index;

        /**
         * Get status of index.
         * @param index - index of status.
         * @return status.
         */
        public static VimeStatus getStatus(int index)
        {
            for (VimeStatus status : VimeStatus.values())
            {
                if (status.getIndex() == index)
                {
                    return status;
                }
            }
            return null;
        }

        /**
         * Get name of VimeStatus by index.
         * @param index - index of VimeStatus.
         * @return name of VimeStatus.
         */
        public static String getName(int index)
        {
            for (VimeStatus status : VimeStatus.values())
            {
                if (status.getIndex() == index)
                {
                    return status.name;
                }
            }
            return null;
        }

        /**
         * Get name of VimeStatus.
         * @return name of VimeStatus.
         */
        public String getName()
        {
            return name;
        }

        /**
         * Reset name of VimeStatus.
         * @param name - name of VimeStatus.
         */
        public void setName(String name)
        {
            this.name = name;
        }

        /**
         * Get index of VimeStatus.
         * @return index of VimeStatus.
         */
        public int getIndex()
        {
            return index;
        }

        /**
         * Reset index of VimeStatus.
         * @param index - index of VimeStatus.
         * @deprecated - if you want modify index of VimeStatus, see class
         *             VimeStatusDefine please.
         */
        public void setIndex(int index)
        {
            this.index = index;
        }

        /**
         * Set VimeStatus.
         * @param name - description of status.
         * @param index - index of status.
         */
        private VimeStatus(String name, int index)
        {
            this.name = name;
            this.index = index;
        }
    }

    /**
     * Client initialization status.<br>
     * CN:客户端初始化状态。
     */
    private static final int INIT_STATUS_VIME_CLIENT = 0x001;

    /**
     * Client setup status.<br>
     * CN:客户端准备状态。
     */
    private static final int SETUP_STATUS_VIME_CLIENT = 0x002;

    /**
     * Client ready status.<br>
     * CN:客户端就绪状态。
     */
    private static final int READY_STATUS_VIME_CLIENT = 0x003;

    /**
     * Client input status.<br>
     * CN:客户端输入状态。
     */
    private static final int INPUT_STATUS_VIME_CLIENT = 0x004;

    /**
     * Client close status.<br>
     * CN:客户端关闭状态。
     */
    private static final int DEINIT_STATUS_VIME_CLIENT = 0x005;

    /**
     * Server initialization status.<br>
     * CN:服务端初始化状态。
     */
    private static final int VIME_SERVER_STATUS_INIT = 0x050;

    /**
     * Server ready status.<br>
     * CN:服务端就绪状态。
     */
    private static final int VIME_SERVER_STATUS_READY = 0x051;

    /**
     * Server input status.<br>
     * CN:服务端输入状态。
     */
    private static final int VIME_SERVER_STATUS_INPUT = 0x052;

    /**
     * Server DEInit status.<br>
     * CN:服务端关闭状态。
     */
    private static final int VIME_SERVER_STATUS_DEINIT = 0x053;
}
