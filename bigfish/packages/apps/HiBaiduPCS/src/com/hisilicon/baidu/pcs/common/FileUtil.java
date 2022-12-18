package com.hisilicon.baidu.pcs.common;

import java.text.DecimalFormat;
import java.util.Locale;

import android.app.AlertDialog;
import android.content.Context;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.hisilicon.baidu.pcs.R;

public class FileUtil {

    public static String getFileType(String fileName) {
        String end = fileName.substring(fileName.lastIndexOf(".") + 1)
                .toUpperCase(Locale.getDefault());
        if ("APK".equals(end)) {
            return "apk/*";
        }
        for (int i = 0; i < Common.AUDIO_TYPE.length; i++) {
            if (Common.AUDIO_TYPE[i].equals(end))
                return "audio/*";
        }
        for (int i = 0; i < Common.VIDEO_TYPE.length; i++) {
            if (Common.VIDEO_TYPE[i].equals(end))
                return "video/*";
        }
        for (int i = 0; i < Common.IMAGE_TYPE.length; i++) {
            if (Common.IMAGE_TYPE[i].equals(end))
                return "image/*";
        }
        return "*/*";
    }

    public static String fileSizeMsg(long length) {
        String show = "";

        DecimalFormat format = new DecimalFormat("#0.0");
        if (length / 1024.0 / 1024 / 1024 >= 1) {
            show = format.format(length / 1024.0 / 1024 / 1024) + "GB";
        } else if (length / 1024.0 / 1024 >= 1) {
            show = format.format(length / 1024.0 / 1024) + "MB";
        } else if (length / 1024.0 >= 1) {
            show = format.format(length / 1024.0) + "KB";
        } else {
            show = length + "B";
        }
        return show;
    }

    public static void showEditDialog(final Context context, String title,
            final int errorId, final EditDialogListener listener) {
        if (null == listener)
            return;
        final AlertDialog nameDialog = new AlertDialog.Builder(context)
                .create();
        LayoutInflater factory = LayoutInflater.from(context);
        View myView = factory.inflate(R.layout.view_new_file, null);
        TextView titleText = (TextView) myView.findViewById(R.id.text_title);
        titleText.setText(title);
        final EditText myEditText = (EditText) myView
                .findViewById(R.id.edit_text);
        myEditText.addTextChangedListener(new MyTextWatcher(context));
        Button newDirbutOK = (Button) myView.findViewById(R.id.button1);
        Button newDirbutCancle = (Button) myView.findViewById(R.id.button2);
        newDirbutOK.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View arg0) {
                String text = myEditText.getText().toString().trim();
                if (text.equals("")) {
                    FileMToast.getInstance(context, errorId);
                } else {
                    listener.doFinishEdit(text);

                }
                nameDialog.dismiss();
            }
        });
        newDirbutCancle.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View arg0) {
                // TODO Auto-generated method stub
                nameDialog.dismiss();
            }
        });
        nameDialog.setView(myView);
        nameDialog.show();
    }

    public static interface EditDialogListener {
        void doFinishEdit(String text);
    }

    public static class MyTextWatcher implements TextWatcher {

        private Context context;
        private int Num = 0;
        private int tempLength = 0;

        public MyTextWatcher(Context context) {
            this.context = context;
        }

        @Override
        public void afterTextChanged(Editable arg0) {
            if (arg0.length() > tempLength) {
                try {
                    int len = arg0.toString().getBytes("GBK").length;
                    // special characters to the input
                    // CNcomment: 特殊字符不给于输入
                    if (arg0.charAt(Num) == '/' || arg0.charAt(Num) == '\\'
                            || arg0.charAt(Num) == ':'
                            || arg0.charAt(Num) == '*'
                            || arg0.charAt(Num) == '?'
                            || arg0.charAt(Num) == '\"'
                            || arg0.charAt(Num) == '<'
                            || arg0.charAt(Num) == '>'
                            || arg0.charAt(Num) == '|') {
                        arg0.delete(Num, Num + 1);
                        FileMToast.getInstance(context, R.string.name_falid);
                    }
                    // the file name length is not greater than 128 bytes
                    // CNcomment:文件名长度不大于128个字节
                    else if (len > 128) {
                        arg0.delete(Num, Num + 1);
                        FileMToast.getInstance(context, R.string.name_long);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }

        @Override
        public void beforeTextChanged(CharSequence arg0, int arg1, int arg2,
                int arg3) {
            tempLength = arg0.length();
            Num = arg1;
        }

        @Override
        public void onTextChanged(CharSequence arg0, int arg1, int arg2,
                int arg3) {
        }

    }

}