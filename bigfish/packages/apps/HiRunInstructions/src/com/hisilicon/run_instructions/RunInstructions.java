package com.hisilicon.run_instructions;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;

public class RunInstructions extends Activity {
    private static final String PACKAGE_NAME = "com.hisilicon.instructions";
    private static final String ACTIVITY_NAME = "com.hisilicon.instructions.MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ComponentName mComponentName = new ComponentName(PACKAGE_NAME,
                ACTIVITY_NAME);
        Intent intent = new Intent();
        intent.setComponent(mComponentName);
        intent.setAction(Intent.ACTION_VIEW);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);

        PackageManager pm = getPackageManager();
        ComponentName name = new ComponentName(this, RunInstructions.class);
        pm.setComponentEnabledSetting(name,
                PackageManager.COMPONENT_ENABLED_STATE_DISABLED, 0);

        System.exit(0);
    }
}