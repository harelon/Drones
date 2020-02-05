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

    public void requestColor(View view) {
        Services.getReadWriteThread().sendMessage(new ColorRequest());
        Log.d("thread","color request sent");
    }

    public void requestHeight(View view) {
        Services.getReadWriteThread().sendMessage(new HeightRequest());
        Log.d("thread","height request sent");
    }
    public void requestTemperature(View view) {
        Services.getReadWriteThread().sendMessage(new TemperatureRequest());
        Log.d("thread","temp request sent");
    }

    public void requestLed(View view) {
        int num = 0;
        int color = 0;
        switch (view.getId())
        {
            case R.id.requestLedBlue:
                color = 0x0000FF;
                num = 3;
                break;
            case R.id.requestLedGreen:
                color = 0x00FF00;
                num = 2;
                break;
            case R.id.requestLedRed:
                color = 0xFF0000;
                num = 1;
                break;
            case R.id.requestLedWhite:
                color = 0xFFFFFF;
                num = 4;
                break;
        }
        Services.getReadWriteThread().sendMessage(new LedRequest(color,num));
        Log.d("thread","led request sent " + Integer.toHexString(color));
    }


//    @Override
//    public void onMessage(final ColorResponse msg) {
//            Log.d("thread","color response received");
//            findViewById(R.id.colorResponse).post(new Runnable() {
//                @Override
//                public void run() {
//                    Log.d("thread","thread was run");
//                    ((TextView)findViewById(R.id.colorResponse)).setText(Long.toString(msg.getColor().getHex()));
//                }
//            });
//    }
//
//    @Override
//    public void onMessage(final HeightResponse msg) {
//        Log.d("thread","height response received");
//        findViewById(R.id.heightResponse).post(new Runnable() {
//            @Override
//            public void run() {
//                Log.d("thread","thread was run");
//                ((TextView)findViewById(R.id.heightResponse)).setText(Integer.toString(msg.getHeight()));
//            }
//        });
//    }

    @Override
    public void onMessage(LedResponse msg) {
        Log.d("thread","height response received");
        findViewById(R.id.ledResponse).post(new Runnable() {
            @Override
            public void run() {
                Log.d("thread","thread was run");
                ((TextView)findViewById(R.id.ledResponse)).setText("led turned on");
            }
        });
    }

    @Override
    public void onMessage(final TemperatureResponse msg) {
        Log.d("thread","temp response received");
        findViewById(R.id.tempResponse).post(new Runnable() {
            @Override
            public void run() {
                Log.d("thread","thread was run");
                ((TextView)findViewById(R.id.tempResponse)).setText(Float.toString(msg.getTemperature()));
            }
        });
    }
}
