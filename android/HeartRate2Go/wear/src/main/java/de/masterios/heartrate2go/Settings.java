package de.masterios.heartrate2go;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;

public class Settings {

    private static final int DEFAULT_MEASURE_INTERVAL = 3;
    private static final boolean DEFAULT_KEEP_SCREEN_ON = false;
    private static final boolean DEFAULT_REMEMBER_VIBRATION = true;
    private static final String DEFAULT_STYLE = "black";

    private SharedPreferences mSharedPreferences;

    public Settings (Context context) {
        mSharedPreferences = PreferenceManager.getDefaultSharedPreferences(context);
    }

    public SharedPreferences getSharedPreferences() {
        return mSharedPreferences;
    }

    /**
     * Get Setting for current measure interval
     * @return
     */
    public int getMeasureInterval() {
        String result = mSharedPreferences.getString("preference_measure_interval", Integer.toString(DEFAULT_MEASURE_INTERVAL));
        int value = 3;
        try {
            value = Integer.parseInt(result);
        } catch(NumberFormatException e) { }
        return value;
    }

    /**
     * Get Setting for remembering vibration pattern and display message
     * @return
     */
    public Boolean getRememberVibration() {
        String result = mSharedPreferences.getString("preference_remember_vibration", Boolean.toString(DEFAULT_REMEMBER_VIBRATION));
        Boolean value = DEFAULT_REMEMBER_VIBRATION;
        try {
            value = Boolean.parseBoolean(result);
        } catch(NumberFormatException e) { }
        return value;
    }

    /**
     * Get Setting for keep-screen-on feature
     * @return
     */
    public Boolean getKeepScreenOn() {
        String result = mSharedPreferences.getString("preference_keep_screen_on", Boolean.toString(DEFAULT_KEEP_SCREEN_ON));
        Boolean value = DEFAULT_KEEP_SCREEN_ON;
        try {
            value = Boolean.parseBoolean(result);
        } catch(NumberFormatException e) { }
        return value;
    }

    /*
    public String getStyle() {
        return mSharedPreferences.getString("preference_list_styles", DEFAULT_STYLE);
    }
    */
}


