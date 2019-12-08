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
    private final byte[] buffer = new byte[1024];
    private int bytes=0;

    public ReadWriteThread(BluetoothSocket socket) {
        this.bluetoothSocket = socket;
        InputStream tmpIn = null;
        OutputStream tmpOut = null;
        Services.setReadWriteThread(this);
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
        // Keep listening to the InputStream
        while (true) {
            Log.d("bluetoothModule", "inside while true");

            try {
                // Read from the InputStream
                //Blocking function!!!!!!!!!!!!!!!!
                bytes += inputStream.read(buffer,bytes,1);
                if(bytes==buffer[0])
                {
                    Services.getMessageCracker().crack(buffer);
                    resetBuffer();
                }
                Log.d("bluetoothModule", "bytes read");

            } catch (IOException e) {
                connectionLost();
                // Start the service over to restart listening mode
                this.start();
                break;
            }
        }
    }

    public void resetBuffer()
    {
        byte length = buffer[0];
        System.arraycopy(buffer, length, buffer, 0,buffer.length-length);
    }
    public void sendMessage(MessageHeader msg)
    {
        write(msg.serialize());
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
