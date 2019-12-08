package com.example.dronescreen;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.android.gms.tasks.TaskCompletionSource;

public class RequestActivity extends AppCompatActivity implements MessageHandler{
    private TaskCompletionSource<Integer> heightTcs = new TaskCompletionSource<>();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.request_activity);
        Services.setMessageCracker(new MessageCracker(this));
        heightTcs.getTask().addOnCompleteListener(new OnCompleteListener<Integer>() {
            @Override
            public void onComplete(@NonNull Task<Integer> task) {
                ((TextView)findViewById(R.id.heightResponse)).setText(task.getResult().toString());
                heightTcs = new TaskCompletionSource<>();
            }
        });
    }

    public void requestHeight(View view) {
        Services.getReadWriteThread().sendMessage(new HeightRequest());
    }

    @Override
    public void onMessage(HeightResponse msg) {
        heightTcs.setResult(msg.getHeight());
    }
}
