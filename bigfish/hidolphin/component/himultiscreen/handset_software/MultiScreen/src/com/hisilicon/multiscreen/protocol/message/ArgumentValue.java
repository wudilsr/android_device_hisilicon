package com.hisilicon.multiscreen.protocol.message;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * The class defines parameter information of argument <br>
 * CN:本类定义了argument中的参数信息。
 */
public class ArgumentValue
{

    protected String mKey = null;

    protected Object mValue = null;

    private String mType = null;

    /**
     * Construct method. <br>
     * CN: 构造函数。
     * @param key parameter name. <br>
     *        CN: 参数名称。
     * @param type parameter type CN: 参数类型
     * @param value parameter value CN: 参数值
     */
    public ArgumentValue(String key, Object value)
    {
        this.mKey = key;
        this.mValue = value;
    }

    /**
     * Construct method. <br>
     * CN:构造函数。
     */
    public ArgumentValue()
    {

    }

    /**
     * Set method of parameter name. <br>
     * CN:设置参数名称。
     * @param key parameter name. <br>
     * CN:参数名称。
     */
    public void setKey(String key)
    {
        mKey = key;
    }

    /**
     * Get method of parameter name. <br>
     * CN:获取参数名称。
     * @return - parameter name.
     * CN:参数名称。
     */
    public String getKey()
    {
        return mKey;
    }

    /**
     * Set method of parameter value. <br>
     * CN:设置参数的值。
     * @param obj object according to the parameter. <br>
     * CN:参数值对应的对象。
     */
    public void setValue(Object obj)
    {
        mValue = obj;
    }

    /**
     * Get method of parameter value. <br>
     * CN:获取参数的值。
     * @return an object of parameter. <br>
     * CN:参数值对应的对象。
     */
    public Object getVaule()
    {
        return mValue;
    }

    /**
     * Set method of parameter type <br>
     * CN:设置参数类型
     * @param type parameter type, such as int,float and so on. <br>
     * CN:参数类型，比如 int,float等
     */
    public void setType(String type)
    {
        this.mType = type;
    }

    /**
     * Get the parameter type. <br>
     * CN:获取参数类型。
     * @return parameter type, such as int,float and so on. <br>
     * CN: 参数类型，例如int , float等其他类型。
     */
    public String getType()
    {
        if (mValue != null)
        {
            mType = mValue.getClass().getSimpleName();
        }

        return mType;
    }

    /**
     * Debug method of ArgumentValue. <br>
     * CN:ArgumentValue的Debug方法。
     */
    public void debugInfor()
    {
        if (mValue != null)
        {
            LogTool.v("key=" + mKey);
            LogTool.v("type=" + this.getType());
            LogTool.v("value=" + mValue.toString());
        }
        else
        {
            LogTool.e("ArgumentValue is null");
        }
    }

}
