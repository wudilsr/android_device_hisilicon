package com.hisilicon.multiscreen.server;

public class MultiScreenNativeCommand
{
    /**
     * Command id for set VIME's url.<br>
     * CN:设置VIME URL的命令id。
     */
    private static final int COMMAND_ID_SET_VIME_URL = 0;

    /**
     * Command id for start VIME control server.<br>
     * CN:启动VIME控制服务的命令id。
     */
    private static final int COMMAND_ID_START_VIME = 1;

    /**
     * Command id for stop VIME control server.<br>
     * CN:关闭VIME控制服务的命令id。
     */
    private static final int COMMAND_ID_STOP_VIME = 2;

    /**
     * Command id for start remote app server.<br>
     * CN:启动remote app 服务的命令id。
     */
    private static final int COMMAND_ID_START_REMOTE_APP = 3;

    /**
     * Command id for stop remote app server.<br>
     * CN:关闭remote app 服务的命令id。
     */
    private static final int COMMAND_ID_STOP_REMOTE_APP = 4;

    /**
     * Command id for stop remote app server.<br>
     * CN:关闭remote app 服务的命令id。
     */
    private static final int COMMAND_ID_NOTIFY_SUSPEND_QUIT = 5;

    /**
     * Return result after execute command successfully.<br>
     * CN:命令成功执行的返回值。
     */
    public static final int COMMAND_RET_SUCCESS = 0;

    /**
     * Return result after execute command failure.<br>
     * CN:命令执行失败的返回值。
     */
    public static final int COMMAND_RET_FAIL = -1;

    public enum NativeInvokeCommand
    {

        SET_VIME_URL(COMMAND_ID_SET_VIME_URL), START_VIME_CONTROL(COMMAND_ID_START_VIME), STOP_VIME_CONTROL(
            COMMAND_ID_STOP_VIME), START_REMOTE_APP(COMMAND_ID_START_REMOTE_APP), STOP_REMOTE_APP(
            COMMAND_ID_STOP_REMOTE_APP), NOTIFY_SUSPEND_QUIT(COMMAND_ID_NOTIFY_SUSPEND_QUIT);

        private int commandIdValue;

        private int getcommandIdValue()
        {
            return commandIdValue;
        }

        private NativeInvokeCommand(int id)
        {
            this.commandIdValue = id;
        }

        public static NativeInvokeCommand getCommand(int id)
        {
            for (NativeInvokeCommand command : NativeInvokeCommand.values())
            {
                if (command.getcommandIdValue() == id)
                {
                    return command;
                }
            }
            return null;
        }
    }
}
