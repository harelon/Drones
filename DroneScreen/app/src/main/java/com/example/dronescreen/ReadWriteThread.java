package com.example.dronescreen;

import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class ReadWriteThread extends Thread {
    private final BluetoothSocket bluetoothSocket;
    private final InputStream inputStream;
    private final OutputStream outputStream;

    public ReadWriteThread(BluetoothSocket socket) {
        this.bluetoothSocket = socket;
        InputStream tmpIn = null;
        OutputStream tmpOut = null;

        try {
            tmpIn = socket.getInputStream();
            Log.d("bluetoothModule", tmpIn!=null?tmpIn.toString():"input is null");
            tmpOut = socket.getOutputStream();
            Log.d("bluetoothModule", tmpOut!=null?tmpOut.toString():"output is null");
        } catch (IOException e) {
        }

        inputStream = tmpIn;
        outputStream = tmpOut;
    }

    public void run() {
        byte[] buffer = new byte[1024];
        int bytes=0;

        // Keep listening to the InputStream
        while (true) {
            Log.d("bluetoothModule", "inside while true");
            try {
                // Read from the InputStream
                //Blocking function!!!!!!!!!!!!!!!!
                bytes += inputStream.read(buffer);
                Log.d("bluetoothModule", "bytes read");
                // Send the obtained bytes to the UI Activity
                if(MessageHandler.obtainMessage(bytes, buffer))
                {
                    bytes = 0;
                }
                Log.d("bluetoothModule", "obtained message");

            } catch (IOException e) {
                connectionLost();
                // Start the service over to restart listening mode
                this.start();
                break;
            }
        }
    }
    public void connectionLost()
    {
        Log.d("bluetoothModule", "connection lost");
    }
    // write to OutputStream
    public void write(byte[] buffer) {
        Log.d("bluetoothModule", "write is called");
        try {
            outputStream.write(buffer);
        } catch (IOException e) {
            Log.e("bluetoothModule", e.toString());
        }
    }

    public void cancel() {
        try {
            bluetoothSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
