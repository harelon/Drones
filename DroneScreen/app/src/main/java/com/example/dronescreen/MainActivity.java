package com.example.dronescreen;

import android.Manifest;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Services.setMainActivity(this);
        String[] permissions = new String[]{Manifest.permission.BLUETOOTH, Manifest.permission.ACCESS_COARSE_LOCATION};
        ActivityCompat.requestPermissions(MainActivity.this, permissions,1);
        RecyclerView rv = findViewById(R.id.rv);


        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(Services.getAppContext(), LinearLayoutManager.VERTICAL, false);
        rv.setLayoutManager(layoutManager);
        rv.setAdapter(Services.getDeviceListAdapter());
        rv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ConnectThread thread = new ConnectThread(Services.getDeviceDictionary().get(((TextView)v).getText().toString()));
                thread.start();
            }
        });
        Log.d("bluetoothModule", rv.getAdapter().toString());
    }

}
