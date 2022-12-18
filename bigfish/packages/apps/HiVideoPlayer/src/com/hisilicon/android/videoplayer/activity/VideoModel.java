package com.hisilicon.android.videoplayer.activity;

import java.io.Serializable;
import java.util.Comparator;

import net.sourceforge.pinyin4j.PinyinHelper;
import net.sourceforge.pinyin4j.format.HanyuPinyinCaseType;
import net.sourceforge.pinyin4j.format.HanyuPinyinOutputFormat;
import net.sourceforge.pinyin4j.format.HanyuPinyinToneType;
import net.sourceforge.pinyin4j.format.exception.BadHanyuPinyinOutputFormatCombination;

import com.hisilicon.android.videoplayer.R;

public class VideoModel implements Serializable
{
    private static final long serialVersionUID = 1L;

    private int id;
    private String path;
    private String ISOpath;
    private String title;
    private long size;
    private int duration;
    private int rating;
    private long AddedTime;
    private String style;
    private String director;
    private String thumbnailPath;
    private String mimeType;

    public String getThumbnailPath()
    {
        return thumbnailPath;
    }

    public void setThumbnailPath(String thumbnailPath)
    {
        this.thumbnailPath = thumbnailPath;
    }

    public int getId()
    {
        return id;
    }

    public void setId(int id)
    {
        this.id = id;
    }

    public String getPath()
    {
        return path;
    }

    public void setPath(String path)
    {
        this.path = path;
    }

    public String getISOPath()
    {
        return ISOpath;
    }

    public void setISOPath(String ISOpath)
    {
        this.ISOpath = ISOpath;
    }

    public String getTitle()
    {
        return title;
    }

    public void setTitle(String title)
    {
        this.title = title;
    }

    public long getSize()
    {
        return size;
    }

    public void setSize(long size)
    {
        this.size = size;
    }

    public int getDuration()
    {
        return duration;
    }

    public void setDuration(int duration)
    {
        this.duration = duration;
    }

    public int getRating()
    {
        return rating;
    }

    public void setRating(int rating)
    {
        this.rating = rating;
    }

    public long getAddedTime()
    {
        return AddedTime;
    }

    public void setAddedTime(long addedTime)
    {
        AddedTime = addedTime;
    }

    public String getStyle()
    {
        return style;
    }

    public void setStyle(String style)
    {
        this.style = style;
    }

    public String getDirector()
    {
        return director;
    }

    public void setDirector(String director)
    {
        this.director = director;
    }

    public String getMimeType()
    {
        return mimeType;
    }

    public void setMimeType(String mimeType)
    {
        this.mimeType = mimeType;
    }

    private Comparator <VideoModel> sizeComparator = new Comparator <VideoModel>()
    {
        public int compare(VideoModel arg0, VideoModel arg1)
        {
            int res = 0;

            if (arg0.getSize() > arg1.getSize())
            {
                res = 1;
            }
            else if (arg0.getSize() < arg1.getSize())
            {
                res = -1;
            }

            return res;
        }
    };

    public Comparator <VideoModel> getSizeComparator()
    {
        return this.sizeComparator;
    }

    private Comparator <VideoModel> addedTimeComparator = new Comparator <VideoModel>()
    {
        public int compare(VideoModel arg0, VideoModel arg1)
        {
            int res = 0;

            if (arg0.getAddedTime() > arg1.getAddedTime())
            {
                res = 1;
            }
            else if (arg0.getAddedTime() < arg1.getAddedTime())
            {
                res = -1;
            }

            return res;
        }
    };

    public Comparator <VideoModel> getAddedTimeComparator()
    {
        return this.addedTimeComparator;
    }

    private Comparator <VideoModel> titleComparator = new Comparator <VideoModel>()
    {
        public int compare(VideoModel arg0, VideoModel arg1)
        {
            String s1 = converterToSpell(arg0.getTitle().toLowerCase());
            String s2 = converterToSpell(arg1.getTitle().toLowerCase());

            return s1.compareTo(s2);
        }
    };

    public Comparator <VideoModel> getTitleComparator()
    {
        return this.titleComparator;
    }

    private String converterToSpell(String chinese)
    {
        String pinyinName = "";

        char[] nameChar = chinese.toCharArray();
        HanyuPinyinOutputFormat defaultFormat = new HanyuPinyinOutputFormat();
        defaultFormat.setCaseType(HanyuPinyinCaseType.LOWERCASE);
        defaultFormat.setToneType(HanyuPinyinToneType.WITHOUT_TONE);
        for (int i = 0; i < nameChar.length; i++)
        {
            if (nameChar[i] > 128)
            {
                try
                {
                    pinyinName += PinyinHelper.toHanyuPinyinStringArray(nameChar[i], defaultFormat)[0];
                } catch (BadHanyuPinyinOutputFormatCombination e) {
                    e.printStackTrace();
                }
            }
            else
            {
                pinyinName += nameChar[i];
            }
        }

        return pinyinName;
    }
}
