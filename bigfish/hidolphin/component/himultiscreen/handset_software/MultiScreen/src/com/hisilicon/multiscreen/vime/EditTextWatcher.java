package com.hisilicon.multiscreen.vime;

/**
 * Edit text watcher.<br>
 * CN:文本编辑框观察者。
 */
public interface EditTextWatcher
{
    /**
     * On text changed.<br>
     * CN:文字变化。
     * @param text CN:文字
     * @param start CN:开始
     * @param lengthBefore CN:原有长度
     * @param lengthAfter CN:变化后长度
     */
    void onTextChanged(CharSequence text, int start, int lengthBefore, int lengthAfter);

    /**
     * Selection change.<br>
     * CN:光标变化。
     * @param selStart CN:开始位置。
     * @param selEnd CN:结束位置。
     */
    void onSelectionChanged(int selStart, int selEnd);
}
