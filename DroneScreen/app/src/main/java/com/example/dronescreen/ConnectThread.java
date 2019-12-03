package com.example.dronescreen;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
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
                Log.d("bluetoothModule", tmpIn!=null?tmpIn.toString():"input is null");
                tmpOut = socket.getOutputStream();
                Log.d("bluetoothModule", tmpOut!=null?tmpOut.toString():"output is null");
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
                Log.d("bluetoothModule", "inside while true");
                write(new byte[]{17,(byte)221,36});
                try {
                    // Read from the InputStream
                    bytes = inputStream.read(buffer);
                    Log.d("bluetoothModule", "bytes read");
                    // Send the obtained bytes to the UI Activity
                    _handler.obtainMessage(MessageHandler.MESSAGE_READ, bytes,
                            buffer).sendToTarget();
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
                String buff = "asd";
                for(byte b : buffer)
                {
                    if(b!=0)
                    {
                        buff +=Byte.toString(b);
                    }
                }
                Log.d("bluetoothModule", buff);
                outputStream.write(buffer);
                Log.d("bluetoothModule", "wrote buffer");
                _handler.obtainMessage(MessageHandler.MESSAGE_WRITE, -1,
                        buffer).sendToTarget();
                Log.d("bluetoothModule", "obtained message");
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
}