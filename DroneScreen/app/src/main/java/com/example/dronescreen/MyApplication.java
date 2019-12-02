package com.example.dronescreen;

import android.annotation.SuppressLint;
import android.app.Application;
import android.content.Context;
import android.util.Log;

public class MyApplication extends Application {
    @SuppressLint("StaticFieldLeak")
    private static Context context;

    public void onCreate() {
        super.onCreate();
        MyApplication.context = getApplicationContext();
        Log.d("bluetoothModule", "app created");
        Services.init();
    }

    public static Context getAppContext() {
        return MyApplication.context;
    }
}
