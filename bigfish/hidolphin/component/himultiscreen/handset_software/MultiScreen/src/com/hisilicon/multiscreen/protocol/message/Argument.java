package com.hisilicon.multiscreen.protocol.message;

import java.util.ArrayList;

/**
 * Parameters list in Action message <br>
 * CN: Action消息的参数列表。
 */

public class Argument
{
    /**
     * Number of parameters in Argument <br>
     * CN: Argument的参数数目
     */
    private int mValueNum = 0;

    /**
     * List of ArgumentValue <br>
     * Argument的参数列表
     */
    private ArrayList<ArgumentValue> mValueList = new ArrayList<ArgumentValue>();

    /**
     * Constructor method of Argument <br>
     * CN: Argument 的构造方法
     */
    public Argument()
    {

    }

    /**
     * Set method of parameters' number in argument<br>
     * CN:Argument 中参数数目的Set方法
     * @param valueNum number of parameters in Argument <br>
     *        CN: Argument 中参数数目
     */
    public void setArgumentValueNum(int valueNum)
    {
        mValueNum = valueNum;
    }

    /**
     * Get method of parameters' number in argument<br>
     * CN:Argument 中参数数目的Get方法
     * @return a non negative number <br>
     *         CN:非负整数
     */
    public int getArgumentValueNum()
    {
        return mValueNum;
    }

    /**
     * Add parameter method of argument <br>
     * CN:Argument 中添加参数的方法
     * @param value an ArgumentValue object <br>
     *        CN: ArgumentValue 对象
     */
    public void addArgumentValue(ArgumentValue value)
    {
        if (mValueList == null)
        {
            mValueList = new ArrayList<ArgumentValue>();
        }
        mValueList.add(value);
    }

    /**
     * Remove parameter method of argument <br>
     * CN: 删除argument中的参数
     * @param index the removed parameter's index <br>
     *        CN:删除参数的序号
     * @return true means remove success; false means remove fail <br>
     *         CN: true 表示删除成功，false表示删除失败
     */
    public boolean removeArgumentValue(int index)
    {
        if (mValueList == null)
        {
            return false;
        }

        if (index >= mValueList.size())
        {
            return false;
        }

        mValueList.remove(index);

        return true;
    }

    /**
     * Remove parameter method of argument <br>
     * CN: 删除argument中的参数
     * @param argumentValue the parameter to remove <br>
     * @return true means remove success; false means remove fail <br>
     *         CN: true 表示删除成功，false表示删除失败
     */
    public boolean removeArgumentValue(ArgumentValue argumentValue)
    {
        if (mValueList == null)
        {
            return false;
        }

        if (mValueList.size() <= 0)
        {
            return false;
        }

        if (mValueList.contains(argumentValue))
        {
            mValueList.remove(argumentValue);

            return true;
        }
        return false;
    }

    /**
     * Get parameter method of argument <br>
     * CN:在argument中的Get 参数的方法
     * @param index the index of parameter to get <br>
     *        CN: 获取参数的序号
     * @return a ArgumentValue object <br>
     *         ArgumentValue 对象
     */
    public ArgumentValue getArgumentValue(int index)
    {
        if (mValueList == null)
        {
            return null;
        }

        if (index >= mValueList.size())
        {
            return null;
        }

        return mValueList.get(index);
    }

    /**
     * Get the parameters list in Argument<br>
     * CN:获得Argument的参数列表
     * @return list of parameters in Argument <br>
     *         CN: Argument中的参数列表
     */
    public ArrayList<ArgumentValue> getArgumentValueList()
    {
        return mValueList;
    }

    /**
     * Count the parameters in Argument <br>
     * CN: 计算Argument的参数数目
     * @return a non negative number <br>
     */
    public int countArgumentValueNum()
    {
        // TODO Auto-generated method stub
        return mValueList.size();
    }
}
