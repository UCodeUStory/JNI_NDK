package com.wangpos.hookactivitylauncher;

import android.app.Application;

/**
 * Created by qiyue on 2018/1/25.
 */

public class App extends Application {

    @Override
    public void onCreate() {
        super.onCreate();
        HookUtil hookUtil = new HookUtil(ProxyActivity.class,getApplicationContext());
        hookUtil.hookAms();
        hookUtil.hookSystemHandler();
    }
}
