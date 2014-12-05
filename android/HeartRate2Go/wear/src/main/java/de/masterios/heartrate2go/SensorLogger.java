package de.masterios.heartrate2go;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

public class SensorLogger implements SensorEventListener {

    public interface SensorLoggerListener {
        public void onSensorLog(int heartRate, int steps);
    }

    //private final static String SAVE_FILENAME = "measuredata.csv";
    private final static int MINIMUM_MEASURE_INTERVAL_US = 3000000;

    private SensorManager mSensorManager;
    private Sensor mHeartRateSensor;
    private Sensor mStepCountSensor;

    private int mMeasureIntervalUs;

    private int mCurrentHeartRate;
    private int mCurrentSteps;

    SensorLoggerListener mSensorLoggerListener;
    public void setSensorLoggerListener(SensorLoggerListener sensorLoggerListener) {
        mSensorLoggerListener = sensorLoggerListener;
    }

    public SensorLogger(Context context) {
        mMeasureIntervalUs = MINIMUM_MEASURE_INTERVAL_US;

        mSensorManager = ((SensorManager) context.getSystemService(Context.SENSOR_SERVICE));
        mHeartRateSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_HEART_RATE);
        mStepCountSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_STEP_COUNTER);
    }

    public void setMeasureInterval(int seconds) {
        stop();
        long us = ((long) seconds) * 1000000;
        if (us > MINIMUM_MEASURE_INTERVAL_US && us <= Integer.MAX_VALUE) {
            mMeasureIntervalUs = (int) us;
        } else {
            mMeasureIntervalUs = MINIMUM_MEASURE_INTERVAL_US;
        }
        start();
    }

    public void start() {
        if(null != mSensorManager) {
            mSensorManager.registerListener(this, mHeartRateSensor, mMeasureIntervalUs);
            mSensorManager.registerListener(this, mStepCountSensor, mMeasureIntervalUs);
        }
    }

    public void stop() {
        if(null != mSensorManager) {
            mSensorManager.unregisterListener(this, mHeartRateSensor);
            mSensorManager.unregisterListener(this, mStepCountSensor);
        }
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == Sensor.TYPE_HEART_RATE) {
            mCurrentHeartRate = (int) event.values[0];
        }
        if (event.sensor.getType() == Sensor.TYPE_STEP_COUNTER) {
            mCurrentSteps = (int) event.values[0];
        }

        //updateFile();

        if(null != mSensorLoggerListener) {
            mSensorLoggerListener.onSensorLog(mCurrentHeartRate, mCurrentSteps);
        }
    }

    /*
    private void updateFile() {
        Long timeStampSeconds = System.currentTimeMillis()/1000;

        StringBuilder sb = new StringBuilder();
        sb.append(timeStampSeconds.toString() + ";");
        sb.append(mCurrentHeartRate + ";");
        sb.append(mCurrentSteps + "\n");

        FileOutputStream outputStream;
        try {
            outputStream = mContext.openFileOutput(SAVE_FILENAME, Context.MODE_APPEND);
            outputStream.write(sb.toString().getBytes());
            outputStream.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    */

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        // Nothing to do here
    }
}
