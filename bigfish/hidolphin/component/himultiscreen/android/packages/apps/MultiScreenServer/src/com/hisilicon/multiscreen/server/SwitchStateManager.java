package com.hisilicon.multiscreen.server;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;

public class SwitchStateManager
{
    /**
     * Key of switch state in shared preferences.<br>
     */
    private static final String SWITCH_STATE_KEY = "SwitchStateKey";

    private Context mContext = null;

    private SharedPreferences checkStatePreferences = null;

    private SharedPreferences.Editor editor = null;

    /**
     * Construction of SwitchStateManager.<br>
     * @param context
     */
    private SwitchStateManager(Context context)
    {
        mContext = context;
    }

    /**
     * Get instance of SwitchStateManager.<br>
     * @param context
     * @return
     */
    public static SwitchStateManager getInstance(Context context)
    {
        return new SwitchStateManager(context);
    }

    public void init()
    {
        checkStatePreferences = PreferenceManager.getDefaultSharedPreferences(mContext);
        editor = checkStatePreferences.edit();
    }

    public void deinit()
    {
    }

    public boolean isOpen()
    {
        return checkStatePreferences.getBoolean(SWITCH_STATE_KEY, true);
    }

    public void open()
    {
        editor.putBoolean(SWITCH_STATE_KEY, true);
        editor.commit();
    }

    public void close()
    {
        editor.putBoolean(SWITCH_STATE_KEY, false);
        editor.commit();
    }

    public void setState(boolean isOpen)
    {
        editor.putBoolean(SWITCH_STATE_KEY, isOpen);
        editor.commit();
    }
}
