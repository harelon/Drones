package com.example.dronescreen;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.content.IntentFilter;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

public class BluetoothHandler {


    private BluetoothAdapter _bluetoothAdapter;
    BluetoothHandler()
    {
        _bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (!_bluetoothAdapter.isEnabled()) {
            Log.d("bluetoothModule", "requesting enable of bluetooth");
            Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            ((AppCompatActivity)Services.getMainActivity()).startActivityForResult( enableIntent, 1);
        }
    }

    public void discover()
    {
        Log.d("bluetoothModule", "registering finding");
        // Register for broadcasts when a device is discovered
        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        Services.getAppContext().registerReceiver(Services.getDiscoveryFinishReceiver(), filter);

        Log.d("bluetoothModule", "registering finish of discovering");
        // Register for broadcasts when discovery has finished
        filter = new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        Services.getAppContext().registerReceiver(Services.getDiscoveryFinishReceiver(), filter);

        if (_bluetoothAdapter.isDiscovering()) {
            _bluetoothAdapter.cancelDiscovery();
            Log.d("bluetoothModule", "canceling discovering");
        }
        Log.d("bluetoothModule", "starting discovery");
        _bluetoothAdapter.startDiscovery();
    }

}
