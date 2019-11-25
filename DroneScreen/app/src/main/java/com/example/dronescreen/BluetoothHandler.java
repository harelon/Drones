package com.example.dronescreen;

import android.app.Application;
import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothHeadset;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

import androidx.appcompat.app.AppCompatActivity;

public class BluetoothHandler {


    private BluetoothAdapter _bluetoothAdapter;
    BluetoothHandler()
    {
        _bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (!_bluetoothAdapter.isEnabled()) {
            Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            ((AppCompatActivity)Services.getMainActiviy()).startActivityForResult( enableIntent, 1);
        }
    }

    public boolean connected()
    {
        return _bluetoothAdapter != null && _bluetoothAdapter.isEnabled() && _bluetoothAdapter.getProfileConnectionState(BluetoothHeadset.HEADSET) == BluetoothHeadset.STATE_CONNECTED;
    }
    public void discover()
    {
        if (_bluetoothAdapter.isDiscovering()) {
            _bluetoothAdapter.cancelDiscovery();
        }
        _bluetoothAdapter.startDiscovery();

        // Register for broadcasts when a device is discovered
        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        Services.getAppContext().registerReceiver(Services.getDiscoveryFinishReceiver(), filter);

        // Register for broadcasts when discovery has finished
        filter = new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        Services.getAppContext().registerReceiver(Services.getDiscoveryFinishReceiver(), filter);
    }

}
