package de.masterios.heartrate2go;

import android.content.Intent;

import com.google.android.gms.wearable.MessageEvent;
import com.google.android.gms.wearable.Node;
import com.google.android.gms.wearable.WearableListenerService;

import java.net.InetAddress;

import de.masterios.heartrate2go.common.HeartRateFile;
import de.masterios.heartrate2go.common.HeartRateMeasure;

public class DataLayerListenerService extends WearableListenerService {

    private static final String MESSAGE_RECEIVED_PATH = "/heartrate2go-message";

    NetworkBroadcast mNetworkBroadcast;
    HeartRateMeasure mHeartRateMeasure;

    public DataLayerListenerService() {
        mNetworkBroadcast = new NetworkBroadcast(this);
        mNetworkBroadcast.setBroadcastFinishedListener(new NetworkBroadcast.BroadcastFinishedListener() {
            @Override
            public void onBroadcastFinished(InetAddress from, String answer) {
                if(null != from && null != answer) {
                    mHeartRateMeasure.sendDataAsync(from.toString());
                }
            }
        });
        mHeartRateMeasure = HeartRateMeasure.getInstance();
    }

    @Override
    public void onPeerConnected(Node peer) {
        super.onPeerConnected(peer);
    }

    @Override
    public void onMessageReceived(MessageEvent messageEvent) {
        super.onMessageReceived(messageEvent);
        if(messageEvent.getPath().equalsIgnoreCase(MESSAGE_RECEIVED_PATH)) {

            String data = new String(messageEvent.getData());
            if(!data.equals("")) {
                mHeartRateMeasure.setDataFromString(data);
                HeartRateFile.saveMeasureToFile(this, mHeartRateMeasure);
                mNetworkBroadcast.sendBroadcastAsync();

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