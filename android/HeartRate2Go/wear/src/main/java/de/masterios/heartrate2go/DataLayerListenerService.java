package de.masterios.heartrate2go;

import android.content.SharedPreferences;
import android.preference.PreferenceManager;

import com.google.android.gms.wearable.DataEvent;
import com.google.android.gms.wearable.DataEventBuffer;
import com.google.android.gms.wearable.DataMap;
import com.google.android.gms.wearable.DataMapItem;
import com.google.android.gms.wearable.MessageEvent;
import com.google.android.gms.wearable.Node;
import com.google.android.gms.wearable.WearableListenerService;

public class DataLayerListenerService extends WearableListenerService {

    private static final String PREFERENCES_PATH = "/heartrate2go-preferences";

    @Override
    public void onDataChanged(DataEventBuffer dataEvents) {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        SharedPreferences.Editor editor = sharedPreferences.edit();

        for (DataEvent event : dataEvents) {
            if (event.getType() == DataEvent.TYPE_CHANGED) {
                String path = event.getDataItem().getUri().getPath();
                if (path.equals(PREFERENCES_PATH)) {
                    DataMap dataMap = DataMapItem.fromDataItem(event.getDataItem()).getDataMap();
                    for(String key : dataMap.keySet()) {
                        editor.putString(key, dataMap.get(key).toString());
                    }
                }
            }
        }

        editor.commit();
    }

    @Override
    public void onPeerConnected(Node peer) {
        super.onPeerConnected(peer);
    }

    @Override
    public void onMessageReceived(MessageEvent messageEvent) {
        super.onMessageReceived(messageEvent);
    }

    @Override
    public void onPeerDisconnected(Node peer) {
        super.onPeerDisconnected(peer);
    }
}

