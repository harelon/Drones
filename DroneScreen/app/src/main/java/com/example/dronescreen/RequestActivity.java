package com.example.dronescreen;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class RequestActivity extends AppCompatActivity implements MessageHandler{
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.request_activity);
        Services.setMessageCracker(new MessageCracker(this));
    }

    public void requestHeight(View view) {
        Services.getReadWriteThread().sendMessage(new HeightRequest());
        Log.d("thread","height request sent");
    }

    @Override
    public void onMessage(final HeightResponse msg) {
        Log.d("thread","height response received");
        findViewById(R.id.heightResponse).post(new Runnable() {
            @Override
            public void run() {
                Log.d("thread","thread was run");
                ((TextView)findViewById(R.id.heightResponse)).setText(Integer.toString(msg.getHeight()));
            }
        });
    }
}
