package com.hisilicon.multiscreen.protocol.message;

import java.io.DataInputStream;
import java.io.IOException;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * CN:未使用该类（媒体信息类）
 * @deprecated
 */
public class MediaInfo
{
    private String mUrl;

    private String mProgramCode;

    private String mItemName;

    private String mBKImage1;

    private String mBKImage2;

    private String mDescription;

    private String mActor;

    private String mDirector;

    private String mRegion;

    private String mLanguage;

    private String mCategoryCode;

    private String mDuration;

    private int mRatingLevel;

    private int mItemType;

    private int mPosition;

    private int mStatus;

    // private int msgType;
    final static String Tag = "MEDIA_INFO";

    /**
     * Get URL.<br>
     * CN:获取媒体url.
     * @return - url.<br>
     *         CN:媒体url
     */
    public String getUrl()
    {
        return mUrl;
    }

    /**
     * 设置媒体url
     * @param url
     */
    public void setUrl(String url)
    {
        mUrl = url;
    }

    /**
     * 获取ProgramCode
     * @return - ProgramCode
     */
    public String getProgramCode()
    {
        return mProgramCode;
    }

    private final static int MAX_PROGRAM_CODE = 128;

    /**
     * Set Program CN:设置ProgramCode。
     * @param programCode - ProgramCode
     */
    public void setProgramCode(String programCode)
    {
        if (programCode.length() > MAX_PROGRAM_CODE)
            LogTool.e("programCode exceed max length");
        mProgramCode = programCode.substring(0, MAX_PROGRAM_CODE);
    }

    /**
     * Get Item name.<br>
     * CN:获取事项名称.
     * @return - Item name.<br>
     *         CN:事项名称.
     */
    public String getItemName()
    {
        return mItemName;
    }

    private final static int MAX_ITEMNAME_CODE = 128;

    /**
     * Set item name.<br>
     * CN:设置事项名称.
     * @param itemName - item name.<br>
     *        CN:事项名称.
     */
    public void setItem_name(String itemName)
    {
        if (itemName.length() > MAX_ITEMNAME_CODE)
            LogTool.e("itemName exceed max length");
        mItemName = itemName.substring(0, MAX_ITEMNAME_CODE);
    }

    /**
     * 获取BKImage1
     * @return - BKImage1
     */
    public String getBKImage1()
    {
        return mBKImage1;
    }

    private final static int MAX_BKIMAGE_CODE = 1024;

    /**
     * CN:设置BKImage1
     * @param BKImage1 - BKImage1
     */
    public void setBKImage1(String BKImage1)
    {
        if (BKImage1.length() > MAX_BKIMAGE_CODE)
            LogTool.e("BKImage1 exceed max length");
        mBKImage1 = BKImage1.substring(0, MAX_BKIMAGE_CODE);
    }

    /**
     * Get BKImage2.<br>
     * CN:获取BKImage2
     * @return - BKImage2
     */
    public String getBKImage2()
    {
        return mBKImage2;
    }

    /**
     * Set BKImage2.<br>
     * CN:设置BKImage2
     * @param BKImage2 - BKImage2
     */
    public void setBKImage2(String BKImage2)
    {
        if (BKImage2.length() > MAX_BKIMAGE_CODE)
            LogTool.e("BKImage2 exceed max length");
        mBKImage2 = BKImage2.substring(0, MAX_BKIMAGE_CODE);
    }

    /**
     * Get Description.<br>
     * CN:获取描述信息.
     * @return - 描述信息
     */
    public String getDescription()
    {
        return mDescription;
    }

    private final static int MAX_DESCRIPTION_CODE = 1024;

    /**
     * Set description.<br>
     * CN:设置描述信息
     * @param Description - 描述信息
     */
    public void setDescription(String Description)
    {
        if (Description.length() > MAX_DESCRIPTION_CODE)
            LogTool.e("Description exceed max length");
        mDescription = Description.substring(0, MAX_DESCRIPTION_CODE);
    }

    /**
     * Get actor's information.<br>
     * CN:获取演员信息
     * @return - 演员信息
     */
    public String getActor()
    {
        return mActor;
    }

    private final static int MAX_ACTOR_CODE = 1024;

    /**
     * Set actor's information.<br>
     * CN:设置演员信息
     * @param Actor - actor's information.<br>
     *        CN:演员信息
     */
    public void setActor(String Actor)
    {
        if (Actor.length() > MAX_ACTOR_CODE)
            LogTool.e("Actor exceed max length");
        mActor = Actor.substring(0, MAX_ACTOR_CODE);
    }

    /**
     * 获取导演信息
     * @return - 导演信息
     */
    public String getDirector()
    {
        return mDirector;
    }

    private final static int MAX_DIRECTOR = 256;

    /**
     * 设置导演信息
     * @param Director - 导演信息
     */
    public void setDirector(String Director)
    {
        if (Director.length() > MAX_DIRECTOR)
            LogTool.e("Director exceed max length");
        mDirector = Director.substring(0, MAX_DIRECTOR);
    }

    /**
     * 获取地区信息
     * @return - 地区信息
     */
    public String getRegion()
    {
        return mRegion;
    }

    private final static int MAX_REGION = 128;

    /**
     * 设置地区信息
     * @param Region - 地区信息
     */
    public void setRegion(String Region)
    {
        if (Region.length() > MAX_REGION)
            LogTool.e("Region exceed max length");
        mRegion = Region.substring(0, MAX_REGION);
    }

    /**
     * 获取语言信息
     * @return - 语言信息
     */
    public String getLanguage()
    {
        return mLanguage;
    }

    private final static int MAX_LANGUAGE = 32;

    /**
     * Set language information.<br>
     * CN:设置语言信息
     * @param Language - language information.<br>
     *        CN:语言
     */
    public void setLanguage(String Language)
    {
        if (Language.length() > MAX_LANGUAGE)
            LogTool.e("Language exceed max length");
        mLanguage = Language.substring(0, MAX_LANGUAGE);
    }

    /**
     * Get category code.<br>
     * CN:获取种类编码
     * @return - category code.<br>
     *         CN:种类编码
     */
    public String getCategoryCode()
    {
        return mCategoryCode;
    }

    private final static int MAX_CATEGORY_CODE = 128;

    /**
     * Set category code.<br>
     * CN:设置种类编码
     * @param CategoryCode - category code.<br>
     *        CN:种类编码
     */
    public void setCategoryCode(String CategoryCode)
    {
        if (CategoryCode.length() > MAX_CATEGORY_CODE)
            LogTool.e("CategoryCode exceed max length");
        mCategoryCode = CategoryCode.substring(0, MAX_CATEGORY_CODE);
    }

    /**
     * Get duration.<br>
     * CN:获取时长
     * @return - duration.<br>
     *         CN:时长
     */
    public String getDuration()
    {
        return mDuration;
    }

    private final static int MAX_DURATION = 32;

    /**
     * Set duration.<br>
     * CN:设置时长
     * @param Duration - duration.<br>
     *        CN:时长
     */
    public void setDuration(String Duration)
    {
        if (Duration.length() > MAX_DURATION)
            LogTool.e("Duration exceed max length");
        mDuration = Duration.substring(0, MAX_DURATION);
    }

    /**
     * Get rating level.<br>
     * CN:获取评价等级
     * @return - rating level.<br>
     *         CN:评价等级
     */
    public int getRatingLevel()
    {
        return mRatingLevel;
    }

    /**
     * Set rating level.<br>
     * CN:设置评价等级
     * @param RatingLevel - rating level.<br>
     *        CN:评价等级
     */
    public void setRatingLevel(int RatingLevel)
    {
        mRatingLevel = RatingLevel;
    }

    /**
     * Get type.<br>
     * CN:获取类型
     * @return - type.<br>
     *         CN:类型
     */
    public int getItemType()
    {
        return mItemType;
    }

    /**
     * Set type.<br>
     * CN:设置类型
     * @param ItemType - type.<br>
     *        CN:类型
     */
    public void setItemType(int ItemType)
    {
        mItemType = ItemType;
    }

    /**
     * Get position.<br>
     * CN:获取位置
     * @return - position.<br>
     *         CN:位置
     */
    public int getPosition()
    {
        return mPosition;
    }

    /**
     * Set position.<br>
     * CN:设置位置
     * @param Position - position.<br>
     *        CN:位置
     */
    public void setPosition(int Position)
    {
        mPosition = Position;
    }

    /**
     * Get status.<br>
     * CN:获取状态
     * @return - status.<br>
     *         CN:状态
     */
    public int getStatus()
    {
        return mStatus;
    }

    /**
     * Set status.<br>
     * CN:设置状态
     * @param Status - status.<br>
     *        CN:状态
     */
    public void setStatus(int Status)
    {
        mStatus = Status;
    }

    protected void readMediaInfo(DataInputStream in)
    {
        try
        {
            mStatus = in.readInt();
            int programCodeLen = in.readInt();
            if (programCodeLen > 0)
            {
                byte[] buf = new byte[programCodeLen];
                in.read(buf);
                mProgramCode = new String(buf);
            }

            mItemType = in.readInt();
            int itemNameLen = in.readInt();
            if (itemNameLen > 0)
            {
                byte[] buf = new byte[itemNameLen];
                in.read(buf);
                mItemName = new String(buf);
            }

            int BKImage1Len = in.readInt();
            if (BKImage1Len > 0)
            {
                byte[] buf = new byte[BKImage1Len];
                in.read(buf);
                mBKImage1 = new String(buf);
            }

            int BKImage2Len = in.readInt();
            if (BKImage2Len > 0)
            {
                byte[] buf = new byte[BKImage2Len];
                in.read(buf);
                mBKImage2 = new String(buf);
            }

            mRatingLevel = in.readInt();

            int DescriptionLen = in.readInt();
            if (DescriptionLen > 0)
            {
                byte[] buf = new byte[DescriptionLen];
                in.read(buf);
                mDescription = new String(buf);
            }

            int ActorLen = in.readInt();
            if (ActorLen > 0)
            {
                byte[] buf = new byte[ActorLen];
                in.read(buf);
                mActor = new String(buf);
            }

            int DirectorLen = in.readInt();
            if (DirectorLen > 0)
            {
                byte[] buf = new byte[DirectorLen];
                in.read(buf);
                mDirector = new String(buf);
            }

            int RegionLen = in.readInt();
            if (RegionLen > 0)
            {
                byte[] buf = new byte[RegionLen];
                in.read(buf);
                mRegion = new String(buf);
            }

            int LanguageLen = in.readInt();
            if (LanguageLen > 0)
            {
                byte[] buf = new byte[LanguageLen];
                in.read(buf);
                mLanguage = new String(buf);
            }

            int CategoryCodeLen = in.readInt();
            if (CategoryCodeLen > 0)
            {
                byte[] buf = new byte[CategoryCodeLen];
                in.read(buf);
                mCategoryCode = new String(buf);
            }

            int DurationLen = in.readInt();
            if (DurationLen > 0)
            {
                byte[] buf = new byte[DurationLen];
                in.read(buf);
                mDuration = new String(buf);
            }

            mPosition = in.readInt();
        }
        catch (IOException e)
        {
            LogTool.e(e.getMessage());
        }

    }

    /**
     * Print media info.<br>
     */
    protected void mediaInfoPrint()
    {
        LogTool.v("recv media info status:" + mStatus);
        LogTool.v("programCode:" + mProgramCode);
        LogTool.v("ItemType:" + mItemType);
        LogTool.v("itemName:" + mItemName);
        LogTool.v("BKImage1:" + mBKImage1);
        LogTool.v("BKImage2:" + mBKImage2);
        LogTool.v("Description:" + mDescription);
        LogTool.v("Actor:" + mActor);
        LogTool.v("Director:" + mDirector);
        LogTool.v("Region:" + mRegion);
        LogTool.v("Language" + mLanguage);
        LogTool.v("Duration" + mDuration);
        LogTool.v("Position" + mPosition);
        LogTool.v("RatingLevel:" + mRatingLevel);
        LogTool.v("CategoryCode:" + mCategoryCode);
    }

}
