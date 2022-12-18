package com.hisilicon.dlna.dmr;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.view.Display;
import android.view.KeyEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.view.WindowManager.LayoutParams;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.AdapterView.OnItemClickListener;

//import com.hisilicon.dlna.settings.R;

/**
 * A Dialog for directory browsing and selection.<br>
 * CN:用于目录浏览和选择的对话框<br>
 *
 * @author t00204177
 */
public class DirExplorDialog extends Activity
{
    private ListView list;
    ArrayAdapter<String> Adapter;
    ArrayList<String> arr = new ArrayList<String>();

    Context context;
    private String path;

    private Button ok;
    private Button cancel;
    private TextView currentDir = null;

    private int type = 1;
    private String[] fileType = null;
    //private DialogListener dListener = null;// tianjia

    public final static int TypeOpen = 1;
    public final static int TypeSave = 2;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        // TODO Auto-generated method stub
        super.onCreate(savedInstanceState);
        // requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);// set title bar
        setContentView(R.layout.upnp_chooserdialog);

        WindowManager m = getWindowManager();
        Display d = m.getDefaultDisplay();
        Window window = getWindow();
        if ((null != window) && (null != d))
        {
            LayoutParams p = window.getAttributes(); // 获取对话框当前的参数
            p.height = (int) (d.getHeight() * 0.7); // 高度设置为屏幕的1.0
            p.width = (int) (d.getWidth() * 0.7); // 宽度设置为屏幕的0.8
            // p.x = 110;
            // p.y = -30;
            // p.alpha = 1.0f; //设置本身透明
            // p.dimAmount = 0.0f; //设置黑暗
            window.setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.upnp_titlebar);
            window.setAttributes(p); // 设置生效
        }

        /**
         * Obtain a list of the root directory, and displayed in alphabetical order <br>
         * CN: 获取根目录列表，并以字母顺序显示.<br>
         */
        path = getRootDir();
        arr = (ArrayList<String>) getDirSubFileList(path);
        Collections.sort(arr, new Comparator<String>()
        {

            // @Override
            public int compare(String object1, String object2)
            {
                // TODO Auto-generated method stub
                return object1.compareTo(object2);
            }

        });
        Adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, arr);

        currentDir = (TextView) findViewById(R.id.Cur_dir);
        list = (ListView) findViewById(R.id.list_dir);
        list.setAdapter(Adapter);

        list.setOnItemClickListener(lvLis);
        /**
         * Return the selected directory to DirManager.class  <br>
         * CN: 返回选中的目录给DirManager.class <br>
         */
        ok = (Button) findViewById(R.id.ok_button);
        ok.setOnClickListener(new OnClickListener()
        {

            public void onClick(View arg0)
            {
                // TODO Auto-generated method stub
                Intent intent = getIntent();
                Bundle data = new Bundle();
                data.putString("dirPath", path);
                intent.putExtras(data);
                DirExplorDialog.this.setResult(1, intent);
                DirExplorDialog.this.finish();
            }
        });
        cancel = (Button) findViewById(R.id.cancel_button);
        cancel.setOnClickListener(new OnClickListener()
        {

            public void onClick(View arg0)
            {
                // TODO Auto-generated method stub
                DirExplorDialog.this.finish();
            }
        });

        if (type == TypeOpen)
        {
            currentDir.setText(path);
        }
        else if (type == TypeSave)
        {
            currentDir.setText(path);//
        }
    }

    /**
     * Through the remote control left and right keys to focus on the buttons. Through the remote
     * back key to return to the parent directory. If already on the top directory, then exit this
     * dialog. <br>
     * CN:  通过遥控器的左右键聚焦到button上，通过遥控器的返回键返回到上一层目录，已经是根目录就退出此对话框<br>
     */
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        // TODO Auto-generated method stub
        if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT)
        {
            // Toast.makeText(this.context,"aaaaa", Toast.LENGTH_SHORT).show();
            System.out.println("left pressed");
            ok.requestFocus();
        }
        else if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT)
        {
            // Toast.makeText(this.context,"bbbb", Toast.LENGTH_SHORT).show();
            cancel.requestFocus();
        }
        else if (keyCode == KeyEvent.KEYCODE_BACK)
        {
            // Toast.makeText(this.context,"bbbb", Toast.LENGTH_SHORT).show();
            if (path.equals("/"))
            {
                DirExplorDialog.this.finish();
            }
            path = getParentDir(path);
            Handler handler = new Handler();
            handler.post(RefreshFilelist);
            currentDir.setText(path);

            return true;
        }
        return super.onKeyDown(keyCode, event);
    }

    Runnable RefreshFilelist = new Runnable()
    {

        // @Override
        public void run()
        {
            // TODO Auto-generated method stub
            // System.out.println("Runnable path:"+path);
            // String root_name = getRootDir();
            // System.out.println("Runnable path:"+root_name);
            arr.clear();

            //
            List<String> temp = getDirSubFileList(path);
            // String t = path+" rootdir "+getRootDir()+" "+path.length();
            // Toast.makeText(getContext(),t, Toast.LENGTH_SHORT).show();
            // if (! ((path.equals("/") && (1 == path.length()) )))
            // arr.add("..");
            for (int i = 0; i < temp.size(); i++)
                arr.add(temp.get(i));
            Collections.sort(arr, new Comparator<String>()
            {

                // @Override
                public int compare(String object1, String object2)
                {
                    // TODO Auto-generated method stub
                    return object1.compareTo(object2);
                }

            });
            Adapter.notifyDataSetChanged();
        }
    };

    /**
     * click the ‘..’ in directory list will back to parent directory，otherwise， enter into the
     * clicked directory.  <br>
     * CN: 点击目录列表中的“..”回到上层目录，否则进入点击的目录<br>
     */
    private OnItemClickListener lvLis = new OnItemClickListener()
    {
        // @Override
        public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3)
        {
            String temp = String.format("%s", arg0.getItemAtPosition(arg2));
            // System.out.println("OnItemClick path1:"+path);
            if (temp.equals(".."))
                path = getParentDir(path);
            else if (path.equals("/"))
                path = path + temp;
            else
                path = path + "/" + temp;

            // System.out.println("OnItemClick path2"+path);
            if (type == TypeOpen)
                currentDir.setText(path);

            Handler handler = new Handler();
            handler.post(RefreshFilelist);
        }
    };

    /**
     * Supply the contents for Listview to display. Filter non-directory entries, and add '..' <br>
     * CN: 提供Listview显示的内容，过滤非目录项，并添加“..” <br>
     *
     * @param ipath
     * @return
     */
    private List<String> getDirSubFileList(String ipath)
    {
        List<String> file = new ArrayList<String>();
        System.out.println("getDirSubFileList path:" + ipath);
        File[] fileDescriptors = new File(ipath).listFiles();
        if (!(ipath.equals("/")))
        {
            file.add("..");
        }
        if (fileDescriptors == null)
        {
            // file.add("..");
            System.out.println("getDirSubFileList null path:" + ipath);
        }
        else
        {
            for (File f : fileDescriptors)
            {
                // System.out.println("getDirSubFileList parent path:"+f.getParent());
                if (f.isDirectory())
                {
                    String tempf = f.toString();
                    int pos = tempf.lastIndexOf("/");
                    String subTemp = tempf.substring(pos + 1, tempf.length());
                    // String subTemp =
                    // tempf.substring(path.length(),tempf.length());
                    file.add(subTemp);
                    // System.out.println("files in dir:"+subTemp);
                }
                //
                if (f.isFile() && fileType != null)
                {
                    for (int i = 0; i < fileType.length; i++)
                    {
                        int typeStrLen = fileType[i].length();

                        String fileName = f.getPath().substring(f.getPath().length() - typeStrLen);
                        if (fileName.toLowerCase().equals(fileType[i]))
                        {
                            file.add(f.toString().substring(path.length() + 1,
                                    f.toString().length()));
                        }
                    }
                }
            }
        }

        if (file.size() == 0)
            file.add("..");
        // System.out.println("file[0]:"+file.get(0)+" File size:"+file.size());
        return file;
    }

    // public void onClick(View v) {
    // // TODO Auto-generated method stub
    // if(v.getId() == ok.getId()){
    // Intent intent = getIntent();
    // Bundle data = new Bundle();
    // data.putString("dirPath", path);
    // intent.putExtras(data);
    // DirExplorDialog.this.setResult(1, intent);
    // DirExplorDialog.this.finish();
    // // Toast.makeText(context, path, Toast.LENGTH_SHORT).show();
    // }else if(v.getId() == cancel.getId()){
    // DirExplorDialog.this.finish();
    // }
    // }

    private String getSDPath()
    {
        File sdDir = null;
        boolean ChecksdCard = Environment.getExternalStorageState().equals(
                android.os.Environment.MEDIA_MOUNTED);
        if (ChecksdCard)
        {
            sdDir = Environment.getExternalStorageDirectory();
        }
        if (null == sdDir)
        {
            // Toast.makeText(context,
            // "No SDCard inside!",Toast.LENGTH_SHORT).show();
            return null;
        }

        return sdDir.toString();
    }

    /**
     * use '/' as root directory. <br>
     * CN:  使用“/”作为根目录<br>
     *
     * @return
     */
    private String getRootDir()
    {
        String root = "/";

        path = getSDPath();
        if (null == path)
            path = "/";

        return root;
    }

    /**
     * Return the parent directory name  <br>
     *  CN: 返回上一级的目录名<br>
     *
     * @param path
     * @return
     */
    private String getParentDir(String path)
    {
        int pos = path.lastIndexOf("/");
        System.out.println("pos=" + pos + ";path=" + path);

        if (pos == path.length())
        {
            path = path.substring(0, path.length() - 1);
            pos = path.lastIndexOf("/");
        }

        String parentPath = path.substring(0, pos);
        if (pos == 0)
        {
            parentPath = getRootDir();
        }

        return parentPath;
    }
}
