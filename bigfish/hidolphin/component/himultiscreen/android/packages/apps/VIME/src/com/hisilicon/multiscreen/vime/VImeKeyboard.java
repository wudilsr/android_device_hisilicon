package com.hisilicon.multiscreen.vime;

import android.content.Context;
import android.content.res.Resources;
import android.content.res.XmlResourceParser;
import android.inputmethodservice.Keyboard;

/**
 * The class is the implementation keyboard of virtual IME. <br>
 * CN:该类是虚拟输入法的键盘的实现。
 */
public class VImeKeyboard extends Keyboard
{

    private Key mEnterKey;

    public VImeKeyboard(Context context, int xmlLayoutResId)
    {
        super(context, xmlLayoutResId);

    }

    public VImeKeyboard(Context context, int layoutTemplateResId, CharSequence characters,
        int columns, int horizontalPadding)
    {
        super(context, layoutTemplateResId, characters, columns, horizontalPadding);
    }

    @Override
    protected Key createKeyFromXml(Resources res, Row parent, int x, int y, XmlResourceParser parser)
    {
        Key key = new LatinKey(res, parent, x, y, parser);
        if (key.codes[0] == 10)
        {
            mEnterKey = key;
        }
        return key;
    }

    /**
     * This looks at the ime options given by the current editor, to set the
     * appropriate label on the keyboard's enter key. <br>
     * CN:根据当前输入框的ime options，在enter键上显示的标签。
     */
    void setImeOptions(Resources res, int options)
    {
        if (mEnterKey == null)
        {
            return;
        }
        // mEnterKey.icon = res.getDrawable(R.drawable.sym_keyboard_return);
        mEnterKey.label = null;
    }

    static class LatinKey extends Keyboard.Key
    {

        public LatinKey(Resources res, Keyboard.Row parent, int x, int y, XmlResourceParser parser)
        {
            super(res, parent, x, y, parser);
        }

        /**
         * Overriding this method so that we can reduce the target area for the
         * key that closes the keyboard. <br>
         * CN:继承该方法是为了确保减小目标区域，使得键能紧密在显示在键盘中
         */
        @Override
        public boolean isInside(int x, int y)
        {
            return super.isInside(x, codes[0] == KEYCODE_CANCEL ? y - 10 : y);
        }
    }

}
