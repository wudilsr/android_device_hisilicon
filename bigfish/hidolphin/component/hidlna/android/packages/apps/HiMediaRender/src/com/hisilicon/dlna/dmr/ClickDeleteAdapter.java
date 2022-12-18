package com.hisilicon.dlna.dmr;

import java.util.ArrayList;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

//import com.hisilicon.dlna.settings.R;

/**
 * When Click one item in this Adapter, the item will be removed.<br>
 * �����Ὣ������ɾ����Adapter��
 * @author t00204177
 *
 */
public class ClickDeleteAdapter extends BaseAdapter
{
    private Context context;
    private ArrayList<String> text;

    public ClickDeleteAdapter(Context myContext, ArrayList<String> textDeletable)
    {
        this.context = myContext;
        this.text = textDeletable;
    }

    // @Override
    public View getView(int position, View convertView, ViewGroup parent)
    {
        // TODO Auto-generated method stub
        final int index = position;
        View view = convertView;
        if (view == null)
        {
            LayoutInflater inflater = (LayoutInflater) context
                    .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            view = inflater.inflate(R.layout.upnp_row_list_item, null);
            view.setClickable(true);// tianjia
        }
        final TextView textView = (TextView) view.findViewById(R.id.text_item_view);
        textView.setText(text.get(position));
        final ImageView imageView = (ImageView) view.findViewById(R.id.image_item_view);
        imageView.setTag(position);
        imageView.setBackgroundResource(android.R.drawable.ic_delete);

        // view.setOnClickListener(new OnClickListener() {
        imageView.setOnClickListener(new OnClickListener()
        {
            // @Override
            public void onClick(View v)
            {
                // TODO Auto-generated method stub
                text.remove(index);
                notifyDataSetChanged();
                Toast.makeText(context, textView.getText().toString(), Toast.LENGTH_SHORT).show();
            }
        });

        return view;
    }

    // @Override
    public int getCount()
    {
        // TODO Auto-generated method stub
        return text.size();
    }

    // @Override
    public Object getItem(int position)
    {
        // TODO Auto-generated method stub
        return text.get(position);
    }

    // @Override
    public long getItemId(int position)
    {
        // TODO Auto-generated method stub
        return position;
    }

}
