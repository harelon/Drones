package com.example.dronescreen;

import android.Manifest;
import android.os.Bundle;
import android.util.Log;

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
        Log.d("bluetoothModule", rv.getAdapter().toString());
    }

}
