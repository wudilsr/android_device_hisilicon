package com.hisilicon.multiscreen.protocol.message;

/**
 * Message type of G-sensor.<br>
 * CN:体感消息类.
 */
public class SensorMessage
{

    /**
     * Data type of sensor.<br>
     * When dataYpe is 0, that means accuracy is invalid; When it's 1, that
     * means x,y,z is invalid.<br>
     * CN:dataType=0; 表示sensor 数据获得 此时 accuracy 精度无效;dataType=1; 表示 sensor 精度改变
     * 此时 x ,y ,z 无效。
     */
    private short dataType = 0;

    /**
     * Type of sensor.<br>
     * CN:体感类型。
     */
    private short sensorType = 1; // 1:TYPE_ACCELEROMETER ,3:TYPE_ORIENTATION

    /**
     * Accuracy of sensor. CN:体感精度。
     */
    private short accuracy = 0;

    /**
     * Value of x-axis.<br>
     * CN:x轴值。
     */
    private float pointX;

    /**
     * Value of y-axis.<br>
     * CN:y轴值。
     */
    private float pointY;

    /**
     * Value of z-axis.<br>
     * CN:z轴值。
     */
    private float pointZ;

    /**
     * Get the data type.<br>
     * CN:获取数据类型。
     * @return - data type.<br>
     *         CN:数据类型。
     */
    public short getDataType()
    {
        return dataType;
    }

    /**
     * Set the data type.<br>
     * CN:设置数据类型。
     * @param dataType - data type.<br>
     *        CN:数据类型。
     */
    public void setDataType(short dataType)
    {
        this.dataType = dataType;
    }

    /**
     * Get the sensor type.<br>
     * CN:获取体感类型。
     * @return - sensor type.<br>
     *         CN:体感类型。
     */
    public short getSensorType()
    {
        return sensorType;
    }

    /**
     * Set the sensor type.<br>
     * CN:设置体感类型。
     * @param sensorType - sensor type.<br>
     *        CN:体感类型。
     */
    public void setSensorType(short sensorType)
    {
        this.sensorType = sensorType;
    }

    /**
     * Get accuracy of sensor.<br>
     * CN:获取sensor精度。
     * @return - accuracy of sensor.<br>
     *         CN:传感器精度。
     */
    public short getAccuracy()
    {
        return accuracy;
    }

    /**
     * Set accuracy of sensor.<br>
     * CN:设置sensor精度。
     * @param accuracy - accuracy of sensor.<br>
     *        CN:传感器的精度。
     */
    public void setAccuracy(short accuracy)
    {
        this.accuracy = accuracy;
    }

    /**
     * Get the value of x-axis.<br>
     * CN:获取x轴数值。
     * @return - value of x-axis.<br>
     *         CN:x轴数值。
     */
    public float getPointX()
    {
        return pointX;
    }

    /**
     * Set the value of x-axis.<br>
     * CN:设置x轴数值。
     * @param pointX - value of x-axis.<br>
     *        CN:x轴数值。
     */
    public void setPointX(float pointX)
    {
        this.pointX = pointX;
    }

    /**
     * Get the value of y-axis.<br>
     * CN:获取y轴数值。
     * @return - value of y-axis.<br>
     *         CN:y轴数值。
     */
    public float getPointY()
    {
        return pointY;
    }

    /**
     * Set the value of y-axis.<br>
     * CN:设置y轴数值。
     * @param pointY - value of y-axis.<br>
     *        CN:y轴数值。
     */
    public void setPointY(float pointY)
    {
        this.pointY = pointY;
    }

    /**
     * Get the value of z-axis.<br>
     * CN:获取z轴数值。
     * @return - value of z-axis.<br>
     *         CN:z轴数值。
     */
    public float getPointZ()
    {
        return pointZ;
    }

    /**
     * Set the value of z-axis.<br>
     * CN:设置z轴数值。
     * @param pointZ - value of z-axis.<br>
     *        CN:z轴数值。
     */
    public void setPointZ(float pointZ)
    {
        this.pointZ = pointZ;
    }

}
