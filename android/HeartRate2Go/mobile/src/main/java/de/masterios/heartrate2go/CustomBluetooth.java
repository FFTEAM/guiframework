package de.masterios.heartrate2go;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

import java.io.IOException;
import java.util.UUID;

/**
 * Created by MrBoe on 19.11.2014.
 */
public class CustomBluetooth {

    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private static String address = "4C:3C:16:C9:CA:B8";

    private Context mContext;

    private static BluetoothAdapter mBluetoothAdapter = null;
    private static BluetoothSocket mBluetoothSocket = null;

    public CustomBluetooth(Context context) {
        mContext = context;
    }

    public boolean sendString(String s) {
        boolean ok = false;
        if(activateBluetooth() && connect()) {
            byte[] msgBuffer = s.getBytes();

            try {
                mBluetoothSocket.getOutputStream().write(msgBuffer);
                //mBluetoothSocket.close();
                ok = true;
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return ok;
    }

    private boolean activateBluetooth(){
        System.out.println("activateBluetooth()");

        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if(null == mBluetoothAdapter) {
            return false;
        }

        if (mBluetoothAdapter.isEnabled()) {
            return true;
        }

        Intent turnOnIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
        mContext.startActivity(turnOnIntent);
        Toast.makeText(mContext,"Bluetooth angeschaltet", Toast.LENGTH_LONG).show();

        return true;
    }

    private boolean connect() {
        System.out.println("connect()");

        mBluetoothAdapter.cancelDiscovery();

        if (null == mBluetoothSocket) {
            System.out.println("connect() 1");
            BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
            try {
                mBluetoothSocket = device.createRfcommSocketToServiceRecord(MY_UUID);
            } catch (IOException e) {
                e.printStackTrace();
                return false;
            }
        }

        if (!mBluetoothSocket.isConnected()) {
            System.out.println("connect() 2");
            try {
                mBluetoothSocket.connect();
            } catch (IOException e) {
                e.printStackTrace();
                try {
                    mBluetoothSocket.close();
                } catch (IOException e2) {
                    e2.printStackTrace();
                }
                return false;
            }
        }

        return true;
    }
}
