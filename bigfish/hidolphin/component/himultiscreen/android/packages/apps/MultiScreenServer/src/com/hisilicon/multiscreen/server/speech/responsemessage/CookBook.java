package com.hisilicon.multiscreen.server.speech.responsemessage;

import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.protocol.utils.LogTool;


/**
 * the response message about cookbook .<br>
 * CN:返回的菜谱信息
 *
 */
public class CookBook extends SemanticSlot {


    private static final long serialVersionUID = 1L;
    private String mKeyWord;
    private String mDishName;
    private String mIngredient;

    public CookBook(JSONObject jo)
    {
        try {
            mKeyWord = jo.getString("keyword");
            LogTool.i("keyword="+mKeyWord);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mDishName = jo.getString("dishName");
            LogTool.i("dishName="+mDishName);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        try {
            mIngredient = jo.getString("ingredient");
            LogTool.i("ingredient="+mIngredient);
        }
        catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public String getKeyword()
    {
        return mKeyWord;
    }

    public String getDishName()
    {
        return mDishName;
    }

    public String getIngredient()
    {
        return mIngredient;
    }

}
