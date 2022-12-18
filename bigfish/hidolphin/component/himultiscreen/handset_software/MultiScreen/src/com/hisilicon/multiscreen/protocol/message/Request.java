package com.hisilicon.multiscreen.protocol.message;

/**
 * Abstract class of Request.<br>
 * CN:请求抽象类.
 *
 */
public abstract class Request {

    protected MSGHeadObject head;

    //protected static final short headLen = 12;// head message length

    /**
     * Constructor, initial head.<br>
     * CN:构造函数，初始化类成员变量head.
     */
    public Request() {
        head = new MSGHeadObject();
    }

//    public void setHead(MSGHeadObject msgHead){
//        head.setSendModlueName(msgHead.getSendModlueName());
//        head.setRcvModlueName(msgHead.getRcvModlueName());
//        head.setMsgType(msgHead.getMsgType());
//        head.setMsgLen(msgHead.getMsgLen());
//        head.setRsv(msgHead.getRsv());
//        head.setRsvTwo(msgHead.getRsvTwo());
//    }

    /**
     * Get the member variable head of request.<br>
     * CN:获取请求的头.
     */
    public MSGHeadObject getHead(){
        return head ;
    }

    /**
     * Get the byte array of the Object.<br>
     * CN:获取对象的字节数组.
     * @return - byte array.<br>
     * CN:字节数组.
     */
    public abstract byte[] getBytes();
}