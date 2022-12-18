package com.hisilicon.instructions;

import android.content.Intent;
import android.os.Bundle;
import android.os.SystemProperties;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class PageActivity6 extends PageActivity implements OnClickListener {
    private Button btnCommit;
    private EditText inputText;
    private String id;

    private TextWatcher mTextWatcher = new TextWatcher() {
        private CharSequence temp;

        @Override
        public void onTextChanged(CharSequence s, int start, int before,
                int count) {
            temp = s;
        }

        @Override
        public void beforeTextChanged(CharSequence s, int start, int count,
                int after) {
        }

        @Override
        public void afterTextChanged(Editable s) {
            if (temp.length() == 8)
                btnCommit.setEnabled(true);
            else
                btnCommit.setEnabled(false);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        inputText = (EditText) findViewById(R.id.input_text);
        inputText.addTextChangedListener(mTextWatcher);

        btnCommit = (Button) findViewById(R.id.button_commit);
        btnCommit.setOnClickListener(this);
        btnCommit.setEnabled(false);
    }

    @Override
    public void onClick(View arg0) {
        id = inputText.getText().toString().trim();
        SystemProperties.set(MyApplication.SIGN_ID, id);
        System.exit(0);
    }

    @Override
    public int getLayoutId() {
        return R.layout.page_activity_6;
    }

    @Override
    public int getPosition() {
        return 5;
    }

    @Override
    public void startPrvActivity() {
        Intent intent = new Intent(PageActivity6.this, PageActivity3.class);
        startActivity(intent);
        finish();
    }

    @Override
    public void startNextActivity() {

    }
}