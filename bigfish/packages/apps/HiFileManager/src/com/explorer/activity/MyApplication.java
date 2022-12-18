package com.explorer.activity;

import java.util.HashMap;
import java.util.List;

import android.app.Application;

public class MyApplication extends Application {

    private List<HashMap<String, Object>> sambaList;

    public List<HashMap<String, Object>> getSambaList() {
        return sambaList;
    }

    public void setSambaList(List<HashMap<String, Object>> sambaList) {
        this.sambaList = sambaList;
    }

}