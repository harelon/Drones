package com.example.dronescreen;

import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

public class MainActivity extends AppCompatActivity {
    private Context _context;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        _context = this;
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Services.setMainActivity(this);
        String[] permissions = new String[]{Manifest.permission.BLUETOOTH, Manifest.permission.ACCESS_COARSE_LOCATION};
        ActivityCompat.requestPermissions(MainActivity.this, permissions,1);
        RecyclerView rv = findViewById(R.id.rv);
        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(Services.getAppContext(), LinearLayoutManager.VERTICAL, false);
        rv.setLayoutManager(layoutManager);
        Services.getDeviceListAdapter().setClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                TextView tv  = v.findViewById(R.id.textName);
                ConnectThread thread = new ConnectThread(Services.getDeviceDictionary().get(tv.getText().toString()));
                thread.start();
                startActivity(new Intent(_context ,RequestActivity.class));
            }
        });
        rv.setAdapter(Services.getDeviceListAdapter());
        Log.d("bluetoothModule", rv.getAdapter().toString());
    }

}
