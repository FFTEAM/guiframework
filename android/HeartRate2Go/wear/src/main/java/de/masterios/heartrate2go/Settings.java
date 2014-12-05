package de.masterios.heartrate2go;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;

public class Settings {

    private static final int DEFAULT_MEASURE_INTERVAL = 3;
    private static final boolean DEFAULT_KEEP_SCREEN_ON = false;
    private static final String DEFAULT_STYLE = "black";

    private SharedPreferences mSharedPreferences;

    public Settings (Context context) {
        mSharedPreferences = PreferenceManager.getDefaultSharedPreferences(context);
    }

    public SharedPreferences getSharedPreferences() {
        return mSharedPreferences;
    }

    public int getMeasureInterval() {
        String result = mSharedPreferences.getString("preference_measure_interval", Integer.toString(DEFAULT_MEASURE_INTERVAL));
        int value = 3;
        try {
            value = Integer.parseInt(result);
        } catch(NumberFormatException e) { }
        return value;
    }

    public Boolean getKeepScreenOn() {
        String result = mSharedPreferences.getString("preference_keep_screen_on", Boolean.toString(DEFAULT_KEEP_SCREEN_ON));
        Boolean value = false;
        try {
            value = Boolean.parseBoolean(result);
        } catch(NumberFormatException e) { }
        return value;
    }

    public String getStyle() {
        return mSharedPreferences.getString("preference_list_styles", DEFAULT_STYLE);
    }
}


