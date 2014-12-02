package de.masterios.heartrate2go;

import android.content.Intent;

import com.google.android.gms.wearable.MessageEvent;
import com.google.android.gms.wearable.Node;
import com.google.android.gms.wearable.WearableListenerService;

public class DataLayerListenerService extends WearableListenerService {

    private static final String MESSAGE_RECEIVED_PATH = "/heartrate2go-message";

    private static String csvData = "";
    public static String getCurrentCsvData() {
        return csvData;
    }

    @Override
    public void onPeerConnected(Node peer) {
        super.onPeerConnected(peer);
    }

    @Override
    public void onMessageReceived(MessageEvent messageEvent) {
        super.onMessageReceived(messageEvent);
        if(messageEvent.getPath().equalsIgnoreCase(MESSAGE_RECEIVED_PATH)) {

            csvData = new String(messageEvent.getData());
            if(!csvData.equals("")) {
                Intent intent = new Intent(getBaseContext(), HandheldActivity.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                getApplication().startActivity(intent);
            }
        }
    }

    @Override
    public void onPeerDisconnected(Node peer) {
        super.onPeerDisconnected(peer);
    }
}