package com.hisilicon.multiscreen.protocol.message;

/**
 * Class of text information special for virtual IME.<br>
 * CN:虚拟输入法专用文本信息类。
 */
public class VImeTextInfo
{
    public static final String TEXT_SEQUENCE = "sequence";

    public static final String INPUT_OPTION = "imeOptions";

    public static final String INPUT_TYPE = "inputType";

    public static final String INPUT_TEXT = "text";

    public static final String INPUT_CURSOR = "cursor";

    public static final String SRC_TEXT = "srcText";

    public static final String SRC_START_SELECTION = "srcStartSelection";

    public static final String SRC_END_SELECTION = "srcEndSelection";

    public static final String REAL_TEXT = "realText ";

    public static final String REAL_START_SELECTION = "realStartSelection";

    public static final String REAL_END_SELECTION = "realEndSelection";

    private int mInputType = 0;

    private int mImeOption = 0;

    private String mSrcText = "";

    private String mRealText = "";

    private int mSrcStartSelection = 0;

    private int mSrcEndSelection = 0;

    private int mRealStartSelection = 0;

    private int mRealEndSelection = 0;

    /**
     * Construct method of text Information relation to virtual IME.<br>
     * CN: 虚拟输入法文本消息构造方法。
     */
    public VImeTextInfo()
    {
        super();
    }

    /**
     * Construct method of text Information relation to virtual IME.<br>
     * CN: 虚拟输入法文本消息构造方法。
     * @param inputType the content type of editor field.<br>
     *        CN:编辑区域的内容类型。
     * @param imeOption the action attribute of editor field.<br>
     *        CN:编辑区域的动作属性。
     * @param realText the text in the editor field.<br>
     *        CN:编辑区域的文字。
     * @param realStartSelection the cursor position in the editor field.<br>
     *        CN:编辑区域的光标位置。
     */
    public VImeTextInfo(int inputType, int imeOption, String realText, int realStartSelection,
        int realEndSelection)
    {
        super();
        this.mInputType = inputType;
        this.mImeOption = imeOption;
        this.mRealText = realText;
        this.mRealStartSelection = realStartSelection;
        this.mRealEndSelection = realEndSelection;
    }

    /**
     * Construct method of text Information relation to virtual IME.<br>
     * CN: 虚拟输入法文本消息构造方法。
     * @param realText the text in the editor field.<br>
     *        CN:编辑区域的文字。
     * @param realStartSelection the cursor position in the editor field.<br>
     *        CN:编辑区域的光标位置。
     */
    public VImeTextInfo(String realText, int realStartSelection, int realEndSelection)
    {
        super();
        this.mRealText = realText;
        this.mRealStartSelection = realStartSelection;
        this.mRealEndSelection = realEndSelection;
    }

    /**
     * Construct method of text Information relation to virtual IME.<br>
     * CN: 虚拟输入法文本消息构造方法。
     * @param srcText the received text.<br>
     *        CN:接收到的文本。
     * @param srcStartSelection the received start selection position.<br>
     *        CN:接收到的光标起始位置。
     * @param srcEndSelection the received end selection position.<br>
     *        CN:接收到的光标结束位置。
     * @param realText the text in the editor field after commit received text.<br>
     *        CN:提交接收后文本之后，编辑区域的文字。
     * @param realStartSelection the start selection position in the editor
     *        field after commit received text.<br>
     *        CN:提交收到光标之后，编辑区域的起始光标位置。
     * @param realEndSelection the end selection position in the editor field
     *        after commit received text.<br>
     *        CN:提交收到光标之后，编辑区域的结束光标位置。
     */
    public VImeTextInfo(String srcText, int srcStartSelection, int srcEndSelection,
        String realText, int realStartSelection, int realEndSelection)
    {
        super();
        this.mSrcText = srcText;
        this.mSrcStartSelection = srcStartSelection;
        this.mSrcEndSelection = srcEndSelection;
        this.mRealText = realText;
        this.mRealStartSelection = realStartSelection;
        this.mRealEndSelection = realEndSelection;
    }

    /**
     * Get input type of text information.<br>
     * CN:获得文本消息的输入类型。
     * @return input type of text information.<br>
     *         CN:文本信息的输入类型。
     */
    public int getInputType()
    {
        return mInputType;
    }

    /**
     * Set input type of text information.<br>
     * CN:设置文本消息的输入类型。
     * @param inputType of text information.<br>
     *        CN:文本信息的输入类型。
     */
    public void setInputType(int inputType)
    {
        mInputType = inputType;
    }

    /**
     * Get action attribute of text information.<br>
     * CN:获得文本消息的动作属性。
     * @return action attribute of editor field.<br>
     *         CN:文本消息的动作属性。
     */
    public int getImeOption()
    {
        return mImeOption;
    }

    /**
     * Set action attribute of text information.<br>
     * CN:设置文本消息的动作属性。
     * @param imeOption - action attribute of editor field.<br>
     *        CN:文本消息的动作属性。
     */
    public void setImeOption(int imeOption)
    {
        mImeOption = imeOption;
    }

    /**
     * Get received text of text information.<br>
     * CN:获得接收到的文本。
     * @return the received text.<br>
     *         CN:获得接收到的文本。
     */
    public String getSrcText()
    {
        return mSrcText;
    }

    /**
     * Set received text of text information.<br>
     * CN:设置接收到的文本。
     * @param srcText - the received text.<br>
     *        CN:接收到文本。
     */
    public void setSrcText(String srcText)
    {
        mSrcText = srcText;
    }

    /**
     * Get received start selection position of text information.<br>
     * CN:获得文本信息中接收到的光标信息。
     * @return the received start selection position of text information.<br>
     *         CN:文本信息中接收到的光标信息。
     */
    public int getSrcStartSelection()
    {
        return mSrcStartSelection;
    }

    /**
     * Set received start selection position of text information.<br>
     * CN:设置接收到的光标位置。
     * @param srcStartCursor - the received start selection position.<br>
     *        CN:接收到的光标位置。
     */
    public void setSrcStartSelection(int srcStartCursor)
    {
        mSrcStartSelection = srcStartCursor;
    }

    /**
     * Get received end selection position of text information.<br>
     * CN：获得提交后的光标位置。
     * @return the committed cursor position.<br>
     *         CN：提交后的光标位置。
     */
    public int getSrcEndSelection()
    {
        return mSrcEndSelection;
    }

    /**
     * Set received end selection position of text information.<br>
     * CN:设置接收到的光标位置。
     * @param srcEndSelection - the received cursor position.<br>
     *        CN:接收到的光标位置。
     */
    public void setSrcEndSelection(int srcEndSelection)
    {
        this.mSrcEndSelection = srcEndSelection;
    }

    /**
     * Get committed text of text information.<br>
     * CN：得到提交后的文本。
     * @return the committed text.<br>
     *         CN:提交后的文本。
     */
    public String getRealText()
    {
        return mRealText;
    }

    /**
     * Set committed text of text information.<br>
     * CN：设置提交后的文本信息。
     * @param realText the committed text CN:提交后的文本。
     */
    public void setRealText(String realText)
    {
        this.mRealText = realText;
    }

    /**
     * Get committed start selection position of text information.<br>
     * CN：获得提交后的光标位置。
     * @return the committed cursor position.<br>
     *         CN：提交后的光标位置。
     */
    public int getRealStartSelection()
    {
        return mRealStartSelection;
    }

    /**
     * Set committed start selection position of text information.<br>
     * CN:设置提交后的光标位置。
     * @param realCursor a non-negative number.<br>
     *        CN:非负整数。
     */
    public void setRealStartSelection(int realStartSelection)
    {
        this.mRealStartSelection = realStartSelection;
    }

    /**
     * Get committed end selection position of text information.<br>
     * CN：获得提交后的光标位置。
     * @return the committed cursor position.<br>
     *         CN：提交后的光标位置。
     */
    public int getRealEndSelection()
    {
        return mRealEndSelection;
    }

    /**
     * Set committed end selection position of text information.<br>
     * CN:设置提交后的光标位置。
     * @param realCursor a non-negative number.<br>
     *        CN:非负整数。
     */
    public void setRealEndSelection(int realEndSelection)
    {
        this.mRealEndSelection = realEndSelection;
    }

}
