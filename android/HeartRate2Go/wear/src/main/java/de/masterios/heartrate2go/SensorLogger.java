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

    private final static int MINIMUM_MEASURE_INTERVAL_US = 3000000;
    private final static int STEP_INIT_VALUE = -1;

    private SensorManager mSensorManager;
    private Sensor mHeartRateSensor;
    private Sensor mStepCountSensor;

    private int mMeasureIntervalUs;
    private boolean mIsLogging;

    private int mCurrentHeartRate;
    private int mStartStepsOverall;
    private int mCurrentSteps;

    SensorLoggerListener mSensorLoggerListener;
    public void setSensorLoggerListener(SensorLoggerListener sensorLoggerListener) {
        mSensorLoggerListener = sensorLoggerListener;
    }

    public SensorLogger(Context context) {
        mIsLogging = false;

        mSensorManager = ((SensorManager) context.getSystemService(Context.SENSOR_SERVICE));
        mHeartRateSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_HEART_RATE);
        mStepCountSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_STEP_COUNTER);

        mCurrentHeartRate = 0;
        mCurrentSteps = 0;
        mStartStepsOverall = STEP_INIT_VALUE;
    }

    /**
     * Set interval of sensor logging
     * @param seconds
     */
    public void setMeasureInterval(int seconds) {
        boolean currentIsLogging = mIsLogging;
        if(currentIsLogging) {
            pause();
        }

        long us = ((long) seconds) * 1000000;
        if (us > MINIMUM_MEASURE_INTERVAL_US && us <= Integer.MAX_VALUE) {
            mMeasureIntervalUs = (int) us;
        } else {
            mMeasureIntervalUs = MINIMUM_MEASURE_INTERVAL_US;
        }

        if(currentIsLogging) {
            start();
        }
    }

    /**
     * Start Sensor-Logging
     */
    public void start() {
        if(null != mSensorManager) {
            mSensorManager.registerListener(this, mHeartRateSensor, mMeasureIntervalUs);
            mSensorManager.registerListener(this, mStepCountSensor, mMeasureIntervalUs);
            mIsLogging = true;
            System.out.println("startLogging");
        }
    }

    /**
     * Pause sensor-Logging
     */
    public void pause() {
        if(null != mSensorManager) {
            mSensorManager.unregisterListener(this, mHeartRateSensor);
            mSensorManager.unregisterListener(this, mStepCountSensor);
            mIsLogging = false;
            System.out.println("pauseLogging");
        }
    }

    /**
     * Stop Sensor-Logging
     */
    public void stop() {
        pause();
        mCurrentHeartRate = 0;
        mCurrentSteps = 0;
        mStartStepsOverall = STEP_INIT_VALUE;
        System.out.println("StopLogging");
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == Sensor.TYPE_HEART_RATE) {
            mCurrentHeartRate = (int) event.values[0];
        }
        if (event.sensor.getType() == Sensor.TYPE_STEP_COUNTER) {
            int stepsOverall = (int) event.values[0];
            if(STEP_INIT_VALUE == mStartStepsOverall) {
                mStartStepsOverall = stepsOverall;
            } else {
                mCurrentSteps += stepsOverall - mStartStepsOverall;
                mStartStepsOverall = stepsOverall;
            }
        }

        if(null != mSensorLoggerListener) {
            mSensorLoggerListener.onSensorLog(mCurrentHeartRate, mCurrentSteps);
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        // Nothing to do here
    }
}
