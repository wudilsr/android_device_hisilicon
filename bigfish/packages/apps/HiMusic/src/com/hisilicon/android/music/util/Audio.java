package com.hisilicon.android.music.util;

import java.io.File;
import java.io.Serializable;
import java.util.Vector;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.logging.Level;
import java.util.logging.Logger;

import android.util.Log;

/**
 * @author
 */
/**
 * This class implements item for playlist.
 */
public class Audio implements Serializable {

    private static final long serialVersionUID = 20071213L;
    private static Logger log = Logger.getLogger(Audio.class.getName());
    protected String name = "";
    protected String displayName = "";
    protected String location = "";
    protected boolean isFile = true;
    protected long seconds = -1;
    protected boolean isSelected = false;
    protected TagInfo taginfo = null;
    private String bitRate;
    private String sampled;
    private String channels;
    private String artist;
    private String title;
    private String path;
    private String comment;
    private String album;
    private String year;
    private String track;
    private String genre;
    private boolean isRead;
    private File lyricFile;
    protected static ExecutorService es = Executors.newSingleThreadExecutor();
    private int offset;

    protected Audio() {
    }

    public boolean isInited() {
        return isRead;
    }

    /**
     * Contructor for playlist item.
     * @param name
     *            Song name to be displayed
     * @param location
     *            File or URL
     * @param seconds
     *            Time length
     * @param isFile
     *            true for File instance
     */
    public Audio(String name, String location, long seconds, boolean isFile) {
        Log.v("PlayListItem", "PlayListItem");
        this.name = name;
        this.seconds = seconds;
        this.isFile = isFile;
        this.location = location;
    }

    public int getOffset() {
        return offset;
    }

    public void setOffset(int offset) {
        this.offset = offset;
    }

    public String getGenre() {
        return genre;
    }

    public void setGenre(String genre) {
        this.genre = genre;
    }

    public String getTrack() {
        return track;
    }

    public void setTrack(String track) {
        this.track = track;
    }

    public File getLyricFile() {
        return lyricFile;
    }

    public void setLyricFile(File lyricFile) {
        this.lyricFile = lyricFile;
    }

    public boolean isValid() {
        TagInfo tag = getTagInfo();
        return tag != null;
    }

    public void setDuration(long sec) {
        seconds = sec;
    }

    public void setBitRate(String s) {
        bitRate = s;
    }

    public void setSampled(String s) {
        sampled = s;
    }

    public void setPath(String s) {
        path = s;
    }

    public String getPath() {
        return path;
    }

    public String getBitRate() {
        if (bitRate == null) {
            int bit = getBitrate();
            if (bit <= 0) {
            } else {
                bit = Math.round((bit / 1000));
                if (bit > 999) {
                    bit = (bit / 100);
                    bitRate = bit + "Hkbps";
                } else {
                    bitRate = String.valueOf(bit) + "kbps";
                }
            }

        }
        return bitRate;
    }

    public String getSampled() {
        if (sampled == null) {
            int sam = getSamplerate();
            if (sam <= 0) {
            } else {
                sampled = String.valueOf(Math.round((sam / 1000))) + "kHz";
            }
        }
        return sampled;
    }

    /**
     * Returns item name such as (hh:mm:ss) Title - Artist if available.
     * @return
     */
    public String getFormattedName() {

        return name;

    }

    public String getName() {
        return name;
        // return Util.getSongName(location);
    }

    public String getLocation() {
        return location;
    }

    /**
     * Returns true if item to play is coming for a file.
     * @return
     */
    public boolean isFile() {
        return isFile;
    }

    /**
     * Set File flag for playslit item.
     * @param b
     */
    public void setFile(boolean b) {
        isFile = b;
    }

    /**
     * Returns playtime in seconds. If tag info is available then its playtime
     * will be returned.
     * @return playtime
     */
    public long getLength() {
        if ((taginfo != null) && (taginfo.getPlayTime() > 0)) {
            return taginfo.getPlayTime();
        } else {
            return seconds;
        }
    }

    public int getBitrate() {
        if (taginfo != null) {
            return taginfo.getBitRate();
        } else {
            return -1;
        }
    }

    public void setAlbum(String album) {
        this.album = album;
    }

    public String getAlbum() {
        if (album != null) {
            return album;
        } else if ((taginfo = getTagInfo()) != null) {
            album = taginfo.getAlbum();
            return album;
        } else {
            return null;
        }
    }

    public String getChannelInfo() {
        if (channels == null) {
        }
        return channels;
    }

    public void setChannels(String s) {
        this.channels = s;
    }

    public int getSamplerate() {
        if (taginfo != null) {
            return taginfo.getSamplingRate();
        } else {
            return -1;
        }
    }

    public int getChannels() {
        if (taginfo != null) {
            return taginfo.getChannels();
        } else {
            return -1;
        }
    }

    public String getComment() {
        if (comment != null) {
            return comment;
        } else if ((taginfo = getTagInfo()) != null) {
            Vector v = taginfo.getComment();
            if (v != null) {
                comment = String.valueOf(v.get(0));
                return comment;
            }
            return "";
        } else {
            return "";
        }
    }

    public void setComment(String comment) {
        this.comment = comment;
    }

    public void reRead() {
        if (!isFile) {
            return;
        }
        bitRate = null;
        sampled = null;
        channels = null;
        artist = null;
        title = null;
        comment = null;
        album = null;
        year = null;
        isRead = true;
        displayName = getFormattedDisplayName();
        log.log(Level.INFO, "setDisPlay=" + displayName);
    }

    public String getYear() {
        if (year != null) {
            return year;
        } else if ((taginfo = getTagInfo()) != null) {
            year = String.valueOf(taginfo.getYear());
            return year;
        } else {
            return "";
        }
    }

    public void setYear(String year) {
        this.year = year;
    }

    public void setSelected(boolean mode) {
        isSelected = mode;
    }

    public boolean isSelected() {
        return isSelected;
    }

    /**
     * Reads file comments/tags.
     * @param l
     */
    public void setLocation(String l) {
        this.location = l;
    }

    /**
     * Reads (or not) file comments/tags.
     * @param l
     *            input location
     * @param readInfo
     */
    private void setLocation(final String l, final boolean readInfo) {
        if (isRead) {
            return;
        }
        if (isFile) {
            es.execute(new Runnable() {
                public void run() {
                    setLocation0(l, readInfo);
                }
            });
        } else {
            new Thread() {
                public void run() {
                    setLocation0(l, readInfo);
                }
            }.start();
        }
    }

    private void setLocation0(String l, boolean readInfo) {
        if (isRead) {
            return;
        }
        isRead = readInfo;
        location = l;
        displayName = getFormattedDisplayName();
        log.log(Level.INFO, "setDisPlay=" + displayName);
    }

    /**
     * Returns item lenght such as hh:mm:ss
     * @return formatted String.
     */
    public String getFormattedLength() {
        long time = getLength();
        String length = "";
        if (time > -1) {
            int minutes = (int) Math.floor(time / 60);
            int hours = (int) Math.floor(minutes / 60);
            minutes = minutes - hours * 60;
            int ss = (int) (time - minutes * 60 - hours * 3600);
            if (hours > 0) {
                length = length + FileUtil.rightPadString(hours + "", '0', 2)
                        + ":";
            }
            length = length + FileUtil.rightPadString(minutes + "", '0', 2)
                    + ":" + FileUtil.rightPadString(ss + "", '0', 2);
        } else {
            length = "" + time;
        }
        return length;
    }

    /**
     * Returns item name such as (hh:mm:ss) Title - Artist
     * @return formatted String.
     */
    public String getFormattedDisplayName() {
        if (artist != null && title != null) {
            String temp = "";
            if (!artist.trim().equals("")) {
                temp = artist.trim() + " - ";
            }
            if (!title.trim().equals("")) {
                temp += title.trim();
            }
            return temp;
        } else if (taginfo == null) {
            return null;
        } else {
            if ((taginfo.getTitle() != null)
                    && (!taginfo.getTitle().trim().equals(""))
                    && (taginfo.getArtist() != null)
                    && (!taginfo.getArtist().trim().equals(""))) {
                return (taginfo.getArtist() + " - " + taginfo.getTitle());

            } else if ((taginfo.getTitle() != null)
                    && (!taginfo.getTitle().trim().equals(""))) {
                return (taginfo.getTitle());
            } else {
                return (name);
            }
        }
    }

    public void setFormattedDisplayName(String fname) {
        displayName = fname;
    }

    /**
     * Return item name such as hh:mm:ss,Title,Artist
     * @return formatted String.
     */
    public String getM3UExtInf() {
        if (taginfo == null) {
            return (seconds + "," + name);
        } else {
            if ((taginfo.getTitle() != null) && (taginfo.getArtist() != null)) {
                return (getLength() + "," + taginfo.getTitle() + " - " + taginfo
                        .getArtist());
            } else if (taginfo.getTitle() != null) {
                return (getLength() + "," + taginfo.getTitle());
            } else {
                return (seconds + "," + name);
            }
        }
    }

    /**
     * Return TagInfo.
     * @return
     */
    public TagInfo getTagInfo() {
        return taginfo;
    }

    public String getFormat() {
        String f = location.substring(location.lastIndexOf(".") + 1);
        f = f + " " + getSampled() + " " + getBitRate();
        return f;
    }

    public String getType() {
        TagInfo tag = getTagInfo();
        if (tag == null) {
        } else {
            return tag.getType();
        }
        return null;

    }

    public String getTitle() {
        TagInfo tag = getTagInfo();
        if (tag != null) {
            title = tag.getTitle() == null ? name : tag.getTitle().trim();
        } else if (title != null) {
            return title;
        } else {
            title = name;
        }
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getArtist() {
        if ((taginfo = getTagInfo()) != null) {
            artist = taginfo.getArtist() == null ? "" : taginfo.getArtist()
                    .trim();
        } else if (artist != null) {
            return artist;
        }
        return artist;
    }

    public void setArtist(String artist) {
        this.artist = artist;
    }

    public String toString() {
        TagInfo tag = getTagInfo();
        return displayName;
    }
}
