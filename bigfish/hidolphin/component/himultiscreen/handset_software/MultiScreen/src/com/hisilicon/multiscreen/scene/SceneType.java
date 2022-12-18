package com.hisilicon.multiscreen.scene;

public enum SceneType
{
    BASE_SCENE("BASE_SCENE", SceneType.SCENE_INDEX_BASE), REMOTE_TOUCH("REMOTE_TOUCH",
        SceneType.SCENE_INDEX_REMOTE_TOUCH), REMOTE_AIRMOUSE("REMOTE_AIRMOUSE",
        SceneType.SCENE_INDEX_REMOTE_AIRMOUSE), MIRROR_SENSOR("MIRROR_SENSOR",
        SceneType.SCENE_INDEX_MIRROR_GSENSOR), MIRROR("MIRROR", SceneType.SCENE_INDEX_MIRROR);

    /**
     * Get type of index.
     * @param index - index of type.
     * @return type.
     */
    public static SceneType getType(int index)
    {
        for (SceneType status : SceneType.values())
        {
            if (status.getIndex() == index)
            {
                return status;
            }
        }
        return null;
    }

    /**
     * Get type of string index.<br>
     * @param strOfIndex
     * @return type
     */
    public static SceneType getType(String strOfIndex)
    {
        int index;
        try
        {
            index = Integer.parseInt(strOfIndex);
        }
        catch (NumberFormatException e)
        {
            return BASE_SCENE;
        }
        return getType(index);
    }

    public String getName()
    {
        return mName;
    }

    public int getIndex()
    {
        return mIndex;
    }

    public String getStrOfIndex()
    {
        return String.valueOf(mIndex);
    }

    private String mName;

    private int mIndex;

    /**
     * Set SceneType.
     * @param name - description of type.
     * @param index - index of type.
     */
    private SceneType(String name, int index)
    {
        this.mName = name;
        this.mIndex = index;
    }

    private static final int SCENE_INDEX_BASE = 0;

    private static final int SCENE_INDEX_REMOTE_TOUCH = SCENE_INDEX_BASE + 1;

    private static final int SCENE_INDEX_REMOTE_AIRMOUSE = SCENE_INDEX_BASE + 2;

    private static final int SCENE_INDEX_MIRROR_GSENSOR = SCENE_INDEX_BASE + 3;

    private static final int SCENE_INDEX_MIRROR = SCENE_INDEX_BASE + 4;
}
