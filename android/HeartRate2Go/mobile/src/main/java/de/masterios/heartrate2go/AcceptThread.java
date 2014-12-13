package de.masterios.heartrate2go;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

class AcceptThread extends Thread {
    // The local server socket
    private BluetoothServerSocket mmServerSocket;

    public AcceptThread() {
        System.out.println("AcceptThread()");
    }

    public void run() {
        BluetoothSocket socket = null;

        BluetoothAdapter mAdapter = BluetoothAdapter.getDefaultAdapter();

        // Listen to the server socket if we're not connected
        while (true) {

            try {
                // Create a new listening server socket
                System.out.println("Initializing RFCOMM SERVER....");

                UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
                // MY_UUID is the UUID you want to use for communication
                mmServerSocket = mAdapter.listenUsingRfcommWithServiceRecord("TEST", MY_UUID);
                //mmServerSocket = mAdapter.listenUsingInsecureRfcommWithServiceRecord(NAME, MY_UUID);  you can also try using In Secure connection...

                // This is a blocking call and will only return on a
                // successful connection or an exception
                socket = mmServerSocket.accept();

            } catch (Exception e) {
                e.printStackTrace();
            }

            try {
                System.out.println("Closing Server Socket.....");
                mmServerSocket.close();



                InputStream tmpIn = null;
                OutputStream tmpOut = null;

                // Get the BluetoothSocket input and output streams

                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();


                DataInputStream mmInStream = new DataInputStream(tmpIn);
                DataOutputStream mmOutStream = new DataOutputStream(tmpOut);

                while(mmInStream.available() > 0) {
                    System.out.print(mmInStream.readChar());
                }
                System.out.print("\n\n");

                // here you can use the Input Stream to take the string from the client whoever is connecting
                //similarly use the output stream to send the data to the client
            } catch (Exception e) {
                e.printStackTrace();
            }

        }
    }

}