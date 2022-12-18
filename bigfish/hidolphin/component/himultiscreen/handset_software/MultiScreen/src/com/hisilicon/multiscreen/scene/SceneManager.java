package com.hisilicon.multiscreen.scene;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

public class SceneManager
{
    private static boolean mIsOpened = false;

    private static SceneType mSceneType = SceneType.BASE_SCENE;

    /**
     * Listener of STB scene.<br>
     * CN:STB场景识别监听。
     */
    private ISceneListener mSceneListener = null;

    /**
     * Constructor.<br>
     */
    public SceneManager()
    {
        setScene(mSceneType);
    }

    public static boolean isOpen()
    {
        return mIsOpened;
    }

    public static void setSwitch(boolean status)
    {
        mIsOpened = status;
    }

    /**
     * Set scene listener<br>
     * @param listener
     */
    public void setListener(ISceneListener listener)
    {
        mSceneListener = listener;
    }

    /**
     * Renew scene type of manager.<br>
     * @param sceneType
     */
    public void renew(SceneType sceneType)
    {
        if (isOpen() && changeScene(sceneType))
        {
            LogTool.d("Scene of STB changes.");
            if (mSceneListener != null)
            {
                mSceneListener.sceneChanged(sceneType);
            }
        }
    }

    public static SceneType getScene()
    {
        return mSceneType;
    }

    private void setScene(SceneType sceneType)
    {
        mSceneType = sceneType;
    }

    /**
     * True if scene changes.<br>
     * @param sceneType
     * @return result
     */
    private boolean changeScene(SceneType sceneType)
    {
        if (getScene() != sceneType)
        {
            setScene(sceneType);
            return true;
        }
        return false;
    }
}
