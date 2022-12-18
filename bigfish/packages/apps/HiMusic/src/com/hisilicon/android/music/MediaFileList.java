package com.hisilicon.android.music;

import java.util.List;

import android.os.Parcelable;

import com.hisilicon.android.music.MusicModel;

/**
 * Play list manager interface
 * @author
 */
public abstract class MediaFileList implements Parcelable {

    /**
     * start player from where 0 - play list 1 - FileM
     */
    private int id;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    /**
     * get previous Music
     * @return
     */
    public abstract MusicModel getPreMusicInfo(List<MusicModel> list);

    /**
     * get next Music
     * @return
     */
    public abstract MusicModel getNextMusicInfo(List<MusicModel> list);

    /**
     * get next Music in mode all no cycle
     * @return
     */
    public abstract MusicModel getNextMusicInfo_NoCycle(List<MusicModel> list);

    /**
     * get random Music
     * @return
     */
    public abstract MusicModel getRandomMusicInfo(List<MusicModel> list);

    /**
     * get current Music
     * @return
     */
    public abstract MusicModel getCurrMusicInfo();

}
