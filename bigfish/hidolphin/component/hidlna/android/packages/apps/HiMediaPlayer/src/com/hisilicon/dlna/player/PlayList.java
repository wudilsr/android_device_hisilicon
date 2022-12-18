package com.hisilicon.dlna.player;

import java.util.ArrayList;
import java.util.List;


/**
 * @author j00209609 <br>
 *         CN:播放列表
 */
public class PlayList
{
    private List<String> hfilelist = null;
    private int pos = 0;
    private int length = 0;
    private static PlayList hlist = null;
    protected String rootPath = null;

    public static PlayList getinstance()
    {
        if (hlist == null)
            hlist = new PlayList();
        return hlist;
    }

    public void setlist(List<String> filelist, int startpos)
    {
        hfilelist = new ArrayList<String>();
        for (String list : filelist)
        {
            hfilelist.add(list);
        }
        length = filelist.size();
        pos = startpos;
    }

    public int getLength()
    {
        return this.length;
    }

    public String movenext()
    {
        if (hfilelist == null || hfilelist.size() == 0)
        {
            //  should return null, but worry about NullPointerException
            return "";
        }
        if (pos < length - 1)
            pos++;
        else
            pos = 0;
        return hfilelist.get(pos);
    }

    public String moveprev()
    {
        if (hfilelist == null || hfilelist.size() == 0)
        {
            //  should return null, but worry about NullPointerException
            return "";
        }
        if (pos > 0)
            pos--;
        else
            pos = length - 1;
        return hfilelist.get(pos);
    }

    public String getcur()
    {
        if (hfilelist == null || hfilelist.size() == 0)
        {
            //  should return null, but worry about NullPointerException
            return "";
        }
        return hfilelist.get(pos);
    }

    public String movehead()
    {
        if (hfilelist == null || hfilelist.size() == 0)
        {
            //  should return null, but worry about NullPointerException
            return "";
        }
        pos = 0;
        return hfilelist.get(pos);
    }

    public String movelast()
    {
        if (hfilelist == null || hfilelist.size() == 0)
        {
            //  should return null, but worry about NullPointerException
            return "";
        }
        pos = length - 1;
        return hfilelist.get(pos);
    }

    public int getPosition()
    {
        return this.pos;
    }

    public void setPosition(int position)
    {
        if (0 <= position)
        {
            this.pos = position;
        }
    }

    public void removeItem(int position)
    {
        if (position < length && position >= 0)
        {
            hfilelist.remove(position);
            length -= 1;
        }
    }
}
