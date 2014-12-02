package de.masterios.heartrate2go;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceActivity;
import android.preference.PreferenceManager;
import android.os.Bundle;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.wearable.DataApi;
import com.google.android.gms.wearable.DataMap;
import com.google.android.gms.wearable.PutDataMapRequest;
import com.google.android.gms.wearable.PutDataRequest;
import com.google.android.gms.wearable.Wearable;

import java.util.Map;
import java.util.concurrent.TimeUnit;

public class SettingsActivity extends PreferenceActivity implements SharedPreferences.OnSharedPreferenceChangeListener {

    private final static String PREFERENCES_PATH = "/heartrate2go-preferences";
    private final static int CONNECTION_TIME_OUT_MS = 5000;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        addPreferencesFromResource(R.xml.preferences);
    }

    @Override
    protected void onResume(){
        super.onResume();
        PreferenceManager.getDefaultSharedPreferences(this).registerOnSharedPreferenceChangeListener(this);
    }

    @Override
    protected void onPause() {
        super.onPause();
        PreferenceManager.getDefaultSharedPreferences(this).unregisterOnSharedPreferenceChangeListener(this);
    }

    @Override
    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
        syncSettingsToWearable(getBaseContext());
    }

    public static void syncSettingsToWearable(final Context context) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                GoogleApiClient googleApiClient;
                ConnectionResult connectionResult;
                do {
                    googleApiClient = new GoogleApiClient.Builder(context).addApi(Wearable.API).build();
                    connectionResult = googleApiClient.blockingConnect(CONNECTION_TIME_OUT_MS, TimeUnit.MILLISECONDS);
                } while(!connectionResult.isSuccess());

                SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(context);

                Map<String,?> settings = sp.getAll();

                PutDataMapRequest dataMapRequest = PutDataMapRequest.create(PREFERENCES_PATH);
                DataMap dataMap = dataMapRequest.getDataMap();
                for(Map.Entry<String,?> entry : settings.entrySet()){
                    dataMap.putString(entry.getKey(), entry.getValue().toString());
                }
                PutDataRequest request = dataMapRequest.asPutDataRequest();
                DataApi.DataItemResult result =
                        Wearable.DataApi.putDataItem(googleApiClient, request).await();

                if(result.getStatus().isSuccess()) {
                    System.out.println("Settings synced.");
                } else {
                    System.out.println("Settings not synced.");
                }

                googleApiClient.disconnect();
            }
        }).start();
    }
}
