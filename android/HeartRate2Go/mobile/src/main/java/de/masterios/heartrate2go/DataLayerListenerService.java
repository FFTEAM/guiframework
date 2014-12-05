package de.masterios.heartrate2go;

import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

import com.google.android.gms.wearable.MessageEvent;
import com.google.android.gms.wearable.Node;
import com.google.android.gms.wearable.WearableListenerService;

/**
 * Created by MrBoe on 24.11.2014.
 */
public class DataLayerListenerService extends WearableListenerService {

    public final static String BROADCAST_ACTION = "de.masterios.heartrate2go-csvdata";

    private static final String TAG = "DataLayerMobile";
    private static final String MESSAGE_RECEIVED_PATH = "/heartrate2go-message";
    //private static final String DATA_ITEM_RECEIVED_PATH = "/heartrate2go-data";

    private static String csvdata = "";
    public static String getCurrentCsvData() {
        return csvdata;
    }

    @Override
    public void onPeerConnected(Node peer) {
        super.onPeerConnected(peer);
    }

    @Override
    public void onMessageReceived(MessageEvent messageEvent) {
        super.onMessageReceived(messageEvent);
        if(messageEvent.getPath().equalsIgnoreCase(MESSAGE_RECEIVED_PATH)) {

            csvdata = new String(messageEvent.getData());

            Intent intent = new Intent(getBaseContext(), HandheldActivity.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            getApplication().startActivity(intent);
        }
    }

    @Override
    public void onPeerDisconnected(Node peer) {
        super.onPeerDisconnected(peer);
    }
}