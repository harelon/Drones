package com.example.dronescreen;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

class ConnectThread extends Thread {
    private final BluetoothSocket _socket;
    private final BluetoothDevice _device;
    private  ReadWriteThread _thread;
    private static final UUID MY_UUID = UUID.fromString("8ce255c0-200a-11e0-ac64-0800200c9a66");
    public ConnectThread(BluetoothDevice device) {
        this._device = device;
        BluetoothSocket tmp = null;
        try {
            tmp = _device.createInsecureRfcommSocketToServiceRecord(MY_UUID);
        } catch (IOException e) {
            e.printStackTrace();
        }
        _socket = tmp;
    }

    public void run() {
        setName("ConnectThread");

        // Always cancel discovery because it will slow down a connection
        Services.getBH().getBA().cancelDiscovery();

        // Make a connection to the BluetoothSocket
        try {
            _socket.connect();
        } catch (IOException e) {
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
        _thread = new ReadWriteThread(_socket);
        _thread.start();
    }

    private class ReadWriteThread extends Thread {
        private final BluetoothSocket bluetoothSocket;
        private final InputStream inputStream;
        private final OutputStream outputStream;
        private MessageHandler _handler;

        public ReadWriteThread(BluetoothSocket socket) {
            this.bluetoothSocket = socket;
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            try {
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
                _handler = new MessageHandler();
            } catch (IOException e) {
            }

            inputStream = tmpIn;
            outputStream = tmpOut;
        }

        public void run() {
            byte[] buffer = new byte[1024];
            int bytes;

            // Keep listening to the InputStream
            while (true) {
                write(new byte[]{17});
                try {
                    // Read from the InputStream
                    bytes = inputStream.read(buffer);

                    // Send the obtained bytes to the UI Activity
                    _handler.obtainMessage(MessageHandler.MESSAGE_READ, bytes,
                            buffer).sendToTarget();
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

        }
        // write to OutputStream
        public void write(byte[] buffer) {
            try {
                outputStream.write(buffer);
                _handler.obtainMessage(MessageHandler.MESSAGE_WRITE, -1,
                        buffer).sendToTarget();
            } catch (IOException e) {
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
}