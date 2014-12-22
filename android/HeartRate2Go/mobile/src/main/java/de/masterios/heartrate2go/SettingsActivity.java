package de.masterios.heartrate2go;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceActivity;
import android.preference.PreferenceManager;
import android.os.Bundle;
import android.widget.Toast;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.wearable.DataApi;
import com.google.android.gms.wearable.DataMap;
import com.google.android.gms.wearable.PutDataMapRequest;
import com.google.android.gms.wearable.PutDataRequest;
import com.google.android.gms.wearable.Wearable;

import java.util.Map;
import java.util.concurrent.TimeUnit;
import java.util.regex.Matcher;

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
        if(key.equals("preference_static_ip")) {
            String ipPattern = "\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}" +
                    "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b";

            String value = sharedPreferences.getString(key, "");
            if(!value.equals("") && !value.matches(ipPattern)) {
                SharedPreferences.Editor editor = sharedPreferences.edit();
                editor.putString(key, "");
                editor.apply();
                recreate();
                Toast.makeText(this, getString(R.string.ip_not_valid), Toast.LENGTH_SHORT).show();
            }
        }

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
                Wearable.DataApi.putDataItem(googleApiClient, request).await();

                googleApiClient.disconnect();
            }
        }).start();
    }
}
