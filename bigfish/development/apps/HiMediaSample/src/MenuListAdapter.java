package com.HiMediaSample;

import android.app.Activity;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

public class MenuListAdapter extends BaseAdapter
{
    public static int CONTROL_MENU_ITEMTYPE;
    private Activity activity;
    private String[] menuItems;
    public int isAllEnable = 1;
    public int imageType = -1;
    int subType = 0;
    private static boolean TYPE_DIALOG = false;

    static class Holder
    {
        ImageView image;
        TextView text;
    }

    public MenuListAdapter(Activity a, String[] items, int isAllEnable, int subType, boolean istypedialog)
    {
        this.activity    = a;
        this.menuItems   = items;
        this.isAllEnable = isAllEnable;
        this.subType = subType;
        this.TYPE_DIALOG = istypedialog;
    }

    public MenuListAdapter(Activity a, String[] items, int isAllEnable, int subType, boolean istypedialog,int imageType)
    {
        this.activity    = a;
        this.menuItems   = items;
        this.isAllEnable = isAllEnable;
        this.subType = subType;
        this.TYPE_DIALOG = istypedialog;
        this.imageType = imageType;
    }

    public int getCount()
    {
        return menuItems.length;
    }

    public Object getItem(int position)
    {
        return menuItems[position];
    }

    public long getItemId(int position)
    {
        return position;
    }
    public void setImageType(int type)
    {
        imageType = type;
    }
    public int getImageType()
    {
        return imageType;
    }
    public View getView(int position, View convertView, ViewGroup parent)
    {
        LayoutInflater inflater = activity.getLayoutInflater();
        Holder holder = null;

        if (convertView == null)
        {
            convertView = inflater.inflate(R.layout.menu_list_item, null);
            holder = new Holder();
            holder.image = (ImageView)convertView.findViewById(R.id.menu_icon);
            holder.text = (TextView)convertView.findViewById(R.id.menu_item);

            convertView.setTag(holder);
        }
        else
        {
            holder = (Holder)convertView.getTag();
        }
        holder.text.setTextColor(Color.WHITE);

        setImage(position, holder.image);
        String item = menuItems[position];
        holder.text.setText(item);
        return convertView;
    }

    public boolean areAllItemsEnabled()
    {
        if (isAllEnable == 0)
        {
            return false;
        }

        return true;
    }
    @Override
    public boolean isEnabled(int position)
    {
        return super.isEnabled(position);
    }

    protected void setImage(int position, ImageView imageView)
    {

    }
}
