package de.masterios.heartrate2go;

import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.net.Uri;
import android.widget.TextView;
import android.widget.Toast;

import java.util.List;

import static android.support.v4.app.ActivityCompat.startActivityForResult;

/**
 * Created by MrBoe on 19.11.2014.
 */
public class BluetoothConnect {

    private Context mContext;
    private TextView mTextView;


    public BluetoothConnect(Context context, TextView textView) {

        mContext = context;
        mTextView = textView;

        // Check if bluetooth is supported
        BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

        if (btAdapter == null) {
            // Device does not support Bluetooth
            // Inform user that we're done.
        }

        // bring up Android chooser
        Intent intent = new Intent();
        intent.setAction(Intent.ACTION_SEND);
        intent.setType("text/plain");
        intent.putExtra(Intent.EXTRA_STREAM, Uri.fromFile(mContext.getFileStreamPath("measuredata.csv")));
        //startActivity(intent);

        //list of apps that can handle our intent
        PackageManager pm = mContext.getPackageManager();
        List<ResolveInfo> appsList = pm.queryIntentActivities( intent, 0);

        if(appsList.size() > 0 ) {
            //select bluetooth
            String packageName = null;
            String className = null;
            boolean found = false;

            for(ResolveInfo info: appsList){
                packageName = info.activityInfo.packageName;
                if( packageName.equals("com.android.bluetooth")){
                    className = info.activityInfo.name;
                    found = true;
                    break;// found
                }
            }
            if(! found){
                Toast.makeText(mContext, "Bluetooth not found", Toast.LENGTH_SHORT).show();
                // exit
            }

            intent.setClassName(packageName, className);
            mContext.startActivity(intent);
        }

    }

    // duration that the device is discoverable
    private static final int DISCOVER_DURATION = 300;

    // our request code (must be greater than zero)
    private static final int REQUEST_BLU = 1;

    public void enable(){
        // enable device discovery - this will automatically enable Bluetooth
        Intent discoveryIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);

        discoveryIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, DISCOVER_DURATION );

        //startActivityForResult(discoveryIntent, REQUEST_BLU);
    }
    /*
    // When startActivityForResult completes...
    @Override
    protected void onActivityResult (int requestCode, int resultCode, Intent data) {

        if (resultCode == DISCOVER_DURATION && requestCode == REQUEST_BLU) {

            // processing code goes here
        }
        else{ // cancelled or error
            Toast.makeText(mContext, "Bluetooth file transfer cancelled", Toast.LENGTH_SHORT).show();
        }

    }
    */
}
