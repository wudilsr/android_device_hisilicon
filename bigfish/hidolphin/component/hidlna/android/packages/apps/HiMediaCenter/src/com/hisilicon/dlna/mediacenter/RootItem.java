package com.hisilicon.dlna.mediacenter;

public enum RootItem
{
    NETWORK, UPNP, NFS, LOCAL;
    public int getNameId()
    {
        switch (this)
        {
            case NETWORK:
                return R.string.network;
            case UPNP:
                return R.string.upnp;
            case NFS:
                return R.string.nfs;
            case LOCAL:
                return R.string.local;
        }
        return 0;
    }

    public int getDrawableId()
    {
        switch (this)
        {
            case NETWORK:
                return R.drawable.icon_network;
            case UPNP:
                return R.drawable.icon_upnp;
            case NFS:
                return R.drawable.icon_nfs;
            case LOCAL:
                return R.drawable.icon_local;
        }
        return 0;
    }
}
