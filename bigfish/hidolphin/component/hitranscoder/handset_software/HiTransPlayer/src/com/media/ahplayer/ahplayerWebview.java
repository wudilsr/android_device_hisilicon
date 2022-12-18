/*
 * Copyright (C) 2011 xuyangpo/x54178 huawei
 */
package com.media.ahplayer;

import java.io.File;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.webkit.WebBackForwardList;
import android.webkit.WebHistoryItem;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
public class ahplayerWebview extends Activity {
    WebView webview;
    private String mEPGURL = null;
    private ahplayerConfig config = null;
    /** Called when the activity is first created. */
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.ahplayer_webview);
        config = new ahplayerConfig(this);
        mEPGURL = config.getValueByOptionName(config.ahplayerConfigPath,config.EPGURL,"http://192.168.1.18/epg.html");
        webview = (WebView) findViewById(R.id.WebView01);
        webview.setWebViewClient(new MyWebViewClient());
        webview.getSettings().setJavaScriptEnabled(true);
        webview.setInitialScale(200);
        webview.getSettings().setSupportZoom(true);
        webview.getSettings().setBuiltInZoomControls(true);
        webview.clearCache(true);
        webview.loadUrl(mEPGURL);
    }

    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if ((keyCode == KeyEvent.KEYCODE_BACK) && webview.canGoBack()) {
            webview.goBack();
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }

    private class MyWebViewClient extends WebViewClient {

        public boolean shouldOverrideUrlLoading(WebView view, String url) {
            Log.v("ahplayerWebview", "----shouldOverrideUrlLoading url="+url);
            Intent i = new Intent(ahplayerWebview.this, ahplayerActivity.class);
            i.putExtra(getResources().getString(R.string.input_file), url);
            startActivity(i);
            return true;
        }
    }
}