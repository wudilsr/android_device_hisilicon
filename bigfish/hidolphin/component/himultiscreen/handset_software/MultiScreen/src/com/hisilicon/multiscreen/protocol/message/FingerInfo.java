package com.hisilicon.multiscreen.protocol.message;

/**
 * Finger Information used for touch.<br>
 * CN:触摸手指信息类.
 */
public class FingerInfo
{
    private int mX;

    private int mY;

    private boolean mIsPressed;

    /**
     * Set the x coordinate of touch.<br>
     * CN:设置触摸的x坐标.
     * @param x - x coordinate of touch.<br>
     *        CN:触摸的x坐标.
     */
    public void setX(int x)
    {
        mX = x;
    }

    /**
     * Get the x coordinate of touch.<br>
     * CN:获取触摸的x坐标.
     * @return - x coordinate of touch.<br>
     *         CN:触摸的x坐标.
     */
    public int getX()
    {
        return mX;
    }

    /**
     * Set the y coordinate of touch.<br>
     * CN:设置触摸的y坐标.
     * @param y - y coordinate of touch.<br>
     *        CN:触摸的y坐标.
     */
    public void setY(int y)
    {
        mY = y;
    }

    /**
     * Get the y coordinate of touch.<br>
     * CN:获取触摸的y坐标.
     * @return - y coordinate of touch.<br>
     *         CN:触摸的y坐标.
     */
    public int getY()
    {
        return mY;
    }

    /**
     * Set press status of touch.<br>
     * CN:设置触摸的按压状态.
     * @param press - press status of touch.<br>
     *        CN:触摸的按压状态.
     */
    public void setPress(boolean press)
    {
        mIsPressed = press;
    }

    /**
     * Get press status of touch.<br>
     * CN:返回触摸的按压状态
     * @return - press status of touch.<br>
     *         CN:触摸的按压状态.
     */
    public boolean getPress()
    {
        return mIsPressed;
    }
}
