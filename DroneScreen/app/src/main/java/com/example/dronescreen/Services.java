package com.example.dronescreen;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import androidx.annotation.NonNull;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.android.gms.tasks.TaskCompletionSource;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Services {
    private static Context _appContext;
    @SuppressLint("StaticFieldLeak")
    private static Context _mainActivity;
    private static BluetoothHandler _bh;
    private static List<String> _discoveredDevices = new ArrayList<>();
    private static RecyclerViewAdapter _rva;
    private static HashMap<String, BluetoothDevice> idToDeviceDictionary = new HashMap<>();
    private static TaskCompletionSource<Boolean> tcs = new TaskCompletionSource<Boolean>();
    private static final BroadcastReceiver _discoveryFinishReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();

            Log.d("bluetoothModule", "action is " + action);
            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                Log.d("bluetoothModule", device.getName()!=null?device.getName():"null" + "\n" + device.getAddress());
//                if (device.getBondState() != BluetoothDevice.BOND_BONDED) {
//                    _discoveredDevices.add(device.getName() + "\n" + device.getAddress());
                    _rva.add(device.getName() + "\n" + device.getAddress());
                    idToDeviceDictionary.put(device.getName() + "\n" + device.getAddress(),device);
//                }
            } else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action) && _discoveredDevices.size()==0) {
                Log.d("bluetoothModule", "no devices were found");
            }
        }
    };
    public static RecyclerViewAdapter getDeviceListAdapter()
    {
        Log.d("bluetoothModule", "rva set");
        return _rva;
    }
    public static void init() {
        Log.d("bluetoothModule", "services initialized");
         _rva = new RecyclerViewAdapter(_discoveredDevices);
        _appContext = MyApplication.getAppContext();
        if(tcs.getTask().isComplete())
        {
            _bh = new BluetoothHandler();
            _bh.discover();
        }
        else {
            tcs.getTask().addOnCompleteListener(new OnCompleteListener<Boolean>() {
                @Override
                public void onComplete(@NonNull Task<Boolean> task) {
                    _bh = new BluetoothHandler();
                    _bh.discover();
                }
            });
        }
    }

    static Context getAppContext() {
        return _appContext;
    }

    static void setMainActivity(Context mainActivity)
    {
        _mainActivity = mainActivity;
        if(!tcs.getTask().isComplete()) {
            tcs.setResult(true);
        }
    }
    static Context getMainActivity()
    {
        return  _mainActivity;
    }
    static  BroadcastReceiver getDiscoveryFinishReceiver()
    {
        Log.d("bluetoothModule", "return registeration reciver");
        return  _discoveryFinishReceiver;
    }
    static BluetoothHandler getBluetoothHandler()
    {
        return _bh;
    }
    public static HashMap<String, BluetoothDevice> getDeviceDictionary()
    {
        return idToDeviceDictionary;
    }
//    public static Task<Boolean> mainActivitySet()
//    {
//
//    }


}
