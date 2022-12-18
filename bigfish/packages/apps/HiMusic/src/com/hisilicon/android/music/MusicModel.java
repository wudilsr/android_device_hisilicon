package com.hisilicon.android.music;

import java.io.Serializable;
import java.util.Comparator;

import net.sourceforge.pinyin4j.PinyinHelper;
import net.sourceforge.pinyin4j.format.HanyuPinyinCaseType;
import net.sourceforge.pinyin4j.format.HanyuPinyinOutputFormat;
import net.sourceforge.pinyin4j.format.HanyuPinyinToneType;
import net.sourceforge.pinyin4j.format.exception.BadHanyuPinyinOutputFormatCombination;

/**
 * Music Model class
 * @author
 */
public class MusicModel implements Serializable {

    /**
     * serialVersionUID
     */
    private static final long serialVersionUID = 1L;

    private int id;
    private String path;
    private String title;
    private long size;
    private int duration;
    private int rating;
    private long AddedTime;
    private String style;
    private String director;
    private String thumbnailPath;
    private String mimeType;

    /**
     * thumbnailPath
     * @return
     */
    public String getThumbnailPath() {
        return thumbnailPath;
    }

    /**
     * thumbnailPath
     * @param thumbnailPath
     */
    public void setThumbnailPath(String thumbnailPath) {
        this.thumbnailPath = thumbnailPath;
    }

    /**
     * get id
     * @return id
     */
    public int getId() {
        return id;
    }

    /**
     * set id
     * @param id
     *            id
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * get path
     * @return path
     */
    public String getPath() {
        return path;
    }

    /**
     * set path
     * @param path
     */
    public void setPath(String path) {
        this.path = path;
    }

    /**
     * get title
     * @return
     */
    public String getTitle() {
        return title;
    }

    /**
     * set title
     * @param title
     */
    public void setTitle(String title) {
        this.title = title;
    }

    /**
     * get size
     * @return
     */
    public long getSize() {
        return size;
    }

    /**
     * set size
     * @param size
     */
    public void setSize(long size) {
        this.size = size;
    }

    /**
     * get Duration
     * @return
     */
    public int getDuration() {
        return duration;
    }

    /**
     * set duration
     * @param duration
     */
    public void setDuration(int duration) {
        this.duration = duration;
    }

    /**
     * get rating
     * @return
     */
    public int getRating() {
        return rating;
    }

    /**
     * set rating
     * @param rating
     */
    public void setRating(int rating) {
        this.rating = rating;
    }

    /**
     * get addedTime
     * @return
     */
    public long getAddedTime() {
        return AddedTime;
    }

    /**
     * set addedTime
     * @param addedTime
     */
    public void setAddedTime(long addedTime) {
        AddedTime = addedTime;
    }

    /**
     * get style
     * @return
     */
    public String getStyle() {
        return style;
    }

    /**
     * set style
     * @param style
     */
    public void setStyle(String style) {
        this.style = style;
    }

    /**
     * get director
     * @return
     */
    public String getDirector() {
        return director;
    }

    /**
     * set director
     * @param director
     */
    public void setDirector(String director) {
        this.director = director;
    }

    public String getMimeType() {
        return mimeType;
    }

    public void setMimeType(String mimeType) {
        this.mimeType = mimeType;
    }

    /**
     * Sort by Comparator according to size
     */
    private Comparator<MusicModel> sizeComparator = new Comparator<MusicModel>() {
        public int compare(MusicModel arg0, MusicModel arg1) {
            int res = 0;
            if (arg0.getSize() > arg1.getSize()) {
                res = 1;
            } else if (arg0.getSize() < arg1.getSize()) {
                res = -1;
            }
            return res;
        }
    };

    /**
     * get sizeComparator
     * @return sizeComparator
     */
    public Comparator<MusicModel> getSizeComparator() {
        return this.sizeComparator;
    }

    /**
     * In accordance with the added time to sort the Comparator
     */
    private Comparator<MusicModel> addedTimeComparator = new Comparator<MusicModel>() {
        public int compare(MusicModel arg0, MusicModel arg1) {
            int res = 0;
            if (arg0.getAddedTime() > arg1.getAddedTime()) {
                res = 1;
            } else if (arg0.getAddedTime() < arg1.getAddedTime()) {
                res = -1;
            }
            return res;
        }
    };

    /**
     * get addedTimeComparator
     * @return addedTimeComparator
     */
    public Comparator<MusicModel> getAddedTimeComparator() {
        return this.addedTimeComparator;
    }

    /**
     * The Comparator sorted by name
     */
    private Comparator<MusicModel> titleComparator = new Comparator<MusicModel>() {
        public int compare(MusicModel arg0, MusicModel arg1) {
            String s1 = converterToSpell(arg0.getTitle().toLowerCase());
            String s2 = converterToSpell(arg1.getTitle().toLowerCase());
            return s1.compareTo(s2);
        }
    };

    /**
     * get titleComparator
     * @return titleComparator
     */
    public Comparator<MusicModel> getTitleComparator() {
        return this.titleComparator;
    }

    /**
     * Chinese characters into pinyin, English characters remain unchanged
     * @param chinese
     * @return
     */
    private String converterToSpell(String chinese) {
        String pinyinName = "";
        char[] nameChar = chinese.toCharArray();
        HanyuPinyinOutputFormat defaultFormat = new HanyuPinyinOutputFormat();
        defaultFormat.setCaseType(HanyuPinyinCaseType.LOWERCASE);
        defaultFormat.setToneType(HanyuPinyinToneType.WITHOUT_TONE);
        for (int i = 0; i < nameChar.length; i++) {
            if (nameChar[i] > 128) {
                try {
                    pinyinName += PinyinHelper.toHanyuPinyinStringArray(
                            nameChar[i], defaultFormat)[0];
                } catch (BadHanyuPinyinOutputFormatCombination e) {
                    e.printStackTrace();
                }
            } else {
                pinyinName += nameChar[i];
            }
        }
        return pinyinName;
    }
}
