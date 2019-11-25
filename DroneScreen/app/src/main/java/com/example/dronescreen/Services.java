package com.example.dronescreen;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import java.util.List;

public class Services {
    private static Context _appContext;
    @SuppressLint("StaticFieldLeak")
    private static Context _mainActivity;
    private static BluetoothHandler _bh;
    private static List<String> _discoveredDevices;
    private static final BroadcastReceiver _discoveryFinishReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();

            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                if (device.getBondState() != BluetoothDevice.BOND_BONDED) {
                    _discoveredDevices.add(device.getName());
                }
            } else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action)) {
            }
        }
    };
    public static void init() {
        _appContext = MyApplication.getAppContext();
        _bh = new BluetoothHandler();
    }

    static Context getAppContext() {
        return _appContext;
    }

    static void setMainActivity(Context mainActivity)
    {
        _mainActivity = mainActivity;
    }
    static Context getMainActiviy()
    {
        return  _mainActivity;
    }
    static  BroadcastReceiver getDiscoveryFinishReceiver()
    {
        return  _discoveryFinishReceiver;
    }
//    public static Task<Boolean> mainActivitySet()
//    {
//
//    }


}
