package com.hisilicon.multiscreen.vime;

import android.view.inputmethod.EditorInfo;

/**
 * VIME option define.<br>
 * 虚拟输入法参数定义。
 * @since MultiScreen V2.0.1.1
 */
public enum VImeOption
{
    ACTION_DONE("DONE", EditorInfo.IME_ACTION_DONE)
    , ACTION_GO("GO",EditorInfo.IME_ACTION_GO)
    , ACTION_NEXT("NEXT",EditorInfo.IME_ACTION_NEXT)
    , ACTION_NONE("EndInput",EditorInfo.IME_ACTION_NONE)
    , ACTION_SEARCH("SEARCH",EditorInfo.IME_ACTION_SEARCH)
    , ACTION_SEND("SEND",EditorInfo.IME_ACTION_SEND)
    , ACTION_UNSPECIFIED("UNSPECIFIED",EditorInfo.IME_ACTION_UNSPECIFIED)
    , FLAG_NO_ACCESSORY_ACTION("EndInput",EditorInfo.IME_FLAG_NO_ACCESSORY_ACTION)
    , FLAG_NO_ENTER_ACTION("EndInput",EditorInfo.IME_FLAG_NO_ENTER_ACTION)
    , HIDE_KEYBOARD("FinishKeyboard", -1);

    private final String mOptionName;

    private final int mOptionIndex;

    private VImeOption(String name, int index)
    {
        this.mOptionName = name;
        this.mOptionIndex = index;
    }

    public static VImeOption getOption(int index)
    {
        for (VImeOption option : VImeOption.values())
        {
            if (option.getIndex() == index)
            {
                return option;
            }
        }
        return null;
    }

    public String getName()
    {
        return mOptionName;
    }

    public int getIndex()
    {
        return mOptionIndex;
    }

}
