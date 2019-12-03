package com.example.dronescreen;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.util.UUID;
//Arduino bluetooth baud rate must be 38400 !!!!!!!
class ConnectThread extends Thread {
    private final BluetoothSocket _socket;
    private final BluetoothDevice _device;
    private  ReadWriteThread _thread;
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    public ConnectThread(BluetoothDevice device) {
        this._device = device;
        Log.d("bluetoothModule", device.toString());
        BluetoothSocket tmp = null;
        try {
            tmp = _device.createInsecureRfcommSocketToServiceRecord(MY_UUID);
        } catch (IOException e) {
            e.printStackTrace();
        }

        _socket = tmp;
        Log.d("bluetoothModule", _socket!=null?_socket.toString():"socket is null");
    }

    public void run() {
        setName("ConnectThread");
//        Log.d("bluetoothModule", "canceling discovery in run");
//        // Always cancel discovery because it will slow down a connection
//        Services.getBluetoothHandler().cancelDiscovery();

        // Make a connection to the BluetoothSocket
        try {
            _socket.connect();
            Log.d("bluetoothModule", "socket connected");
        } catch (IOException e) {
            Log.d("bluetoothModule", "socket couldn't connect");
            Log.e("bluetoothModule", e.toString());
            try {
                _socket.close();
            } catch (IOException e2) {
            }
//            connectionFailed();
            return;
        }

        // Reset the ConnectThread because we're done
        synchronized (this) {
            _thread = null;
        }

        // Start the connected thread
        connected();
    }

    public void cancel() {
        try {
            _socket.close();
        } catch (IOException e) {
        }
    }

    private void connected()
    {
        if(_thread==null || _device.getBondState() != BluetoothDevice.BOND_BONDED ) {
            _thread = new ReadWriteThread(_socket);
            Log.d("bluetoothModule", "read write thread initlaized");
            _thread.start();
            Log.d("bluetoothModule", "read write thread started");
        }
    }

}