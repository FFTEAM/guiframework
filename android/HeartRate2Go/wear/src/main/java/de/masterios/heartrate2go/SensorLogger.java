package de.masterios.heartrate2go;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

import java.io.FileOutputStream;

/**
 * Created by MrBoe on 19.11.2014.
 */
public class SensorLogger implements SensorEventListener {

    private final static String SAVE_FILENAME = "measuredata.csv";
    private final static int MINIMUM_MEASURE_INTERVAL_US = 3000000;

    SensorManager mSensorManager;
    Sensor mHeartRateSensor;
    Sensor mStepCountSensor;

    Context mContext;
    int mMeasureIntervalUs;

    SensorLoggerListener mSensorLoggerListener;

    public SensorLogger(Context context) {
        mContext = context;
        mMeasureIntervalUs = MINIMUM_MEASURE_INTERVAL_US;

        mSensorManager = ((SensorManager)mContext.getSystemService(Context.SENSOR_SERVICE));
        mHeartRateSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_HEART_RATE);
        mStepCountSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_STEP_COUNTER);

        resume();
    }

    public void setSensorLoggerListener(SensorLoggerListener sensorLoggerListener) {
        mSensorLoggerListener = sensorLoggerListener;
    }

    public void setMeasureInterval(int seconds) {
        pause();
        long us = ((long) seconds) * 1000000;
        if(us > MINIMUM_MEASURE_INTERVAL_US && us <= Integer.MAX_VALUE) {
            mMeasureIntervalUs = (int) us;
        } else {
            mMeasureIntervalUs = MINIMUM_MEASURE_INTERVAL_US;
        }
        resume();
    }

    public void start() {
        resume();
    }

    public void resume() {
        if(null != mSensorManager) {
            mSensorManager.registerListener(this, mHeartRateSensor, mMeasureIntervalUs);
            mSensorManager.registerListener(this, mStepCountSensor, mMeasureIntervalUs);
        }
    }

    public void stop() {
        pause();
    }

    public void pause() {
        if(null != mSensorManager) {
            mSensorManager.unregisterListener(this, mHeartRateSensor);
            mSensorManager.unregisterListener(this, mStepCountSensor);
        }
    }

    String heartRateString = "";
    String stepCounterString = "";

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == Sensor.TYPE_HEART_RATE) {
            heartRateString = Integer.toString((int) event.values[0]);
        }
        if (event.sensor.getType() == Sensor.TYPE_STEP_COUNTER) {
            stepCounterString = Integer.toString((int) event.values[0]);
        }

        updateFile();

        if(null != mSensorLoggerListener) {
            mSensorLoggerListener.onSensorLog();
        }
    }

    private void updateFile() {
        Long timeStampSeconds = System.currentTimeMillis()/1000;

        StringBuilder sb = new StringBuilder();
        sb.append(timeStampSeconds.toString() + ";");
        sb.append(heartRateString + ";");
        sb.append(stepCounterString + "\n");

        FileOutputStream outputStream;
        try {
            outputStream = mContext.openFileOutput(SAVE_FILENAME, Context.MODE_APPEND);
            outputStream.write(sb.toString().getBytes());
            outputStream.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        // Nothing to do here
    }
}
