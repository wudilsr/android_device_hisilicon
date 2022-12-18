package com.hisilicon.multiscreen.protocol.utils;

/**
 * Special char disposable utility class <br>
 * CN:特殊字符处理的工具类
 */

public class SpecialCharUtil
{

/**
     * Convert escape sequence into real sequence, such as "&lt;" represent '<', "&amp;" represent '&',
     * and so on <br>
     * CN: 从转义字符中获得实际输入的字符，比如 “ &lt; ” 代表 ‘ < ’, “ &gl; ”代表‘ > ’, “ &amp; ”代表‘ & ’等等
     * @param inputText string has escape sequence
     * CN: 带有转义字符的字符串
     * @return converted real string
     * CN: 转换后的实际字符串
     */
    public static String getSpecialChar(String inputText)
    {
        String outPutText = null;
        if (inputText == null)
        {
            return null;
        }

        outPutText = inputText.replaceAll("&lt;", "<");
        outPutText = outPutText.replaceAll("&gt;", ">");
        outPutText = outPutText.replaceAll("&amp;", "&");
        return outPutText;

    }

}
