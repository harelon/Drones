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
        int inCurrentMessage=0;
        boolean gotLength = false;
        int length = 0;
        byte [] messageArray= new byte[0];
        // Keep listening to the InputStream
        while (true) {
            Log.d("bluetoothModule", "inside while true");

            try {
                // Read from the InputStream
                //Blocking function!!!!!!!!!!!!!!!!

                bytes= inputStream.read(buffer);
                inCurrentMessage+= bytes;
                Log.d("length",Boolean.toString(gotLength));
                if(!gotLength&&bytes>0)
                {
                    gotLength = true;
                    messageArray = new byte[buffer[0]];
                    Log.d("message2", Integer.toString(messageArray.length));
                    for(int i = 0; i<bytes;i++)
                    {
                        Log.d("messages2",Byte.toString(buffer[i]));
                    }
                    for(int i =0;i<bytes;i++)
                    {
                        messageArray[i]=buffer[i];
                    }
                }
                else
                {
                    for(int i =0;i<bytes;i++)
                    {
                        if(inCurrentMessage+i>messageArray.length-1)
                        {
                            MessageHandler.obtainMessage(messageArray.length,messageArray);
                            gotLength =true;
                            messageArray = new byte[buffer[i]];
                            inCurrentMessage=0;
                            for(int j =i;j<bytes;j++)
                            {
                                messageArray[inCurrentMessage]=buffer[i];
                            }

                            break;
                        }
                        messageArray[inCurrentMessage+i]=buffer[i];
                    }
                }
                Log.d("bluetoothModule", "bytes read");

                if(bytes > buffer[0]) {
                    // Send the obtained bytes to the UI Activity
//                     MessageHandler.obtainMessage(bytes, buffer);
//                    MessageHeader msg = MessageHandler.getMessages()[index];
//                    while(bytes>=msg.getLength())
//                    {
//                        buffer[bytes-msg.getLength()]=buffer[bytes--];
//                    }
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
