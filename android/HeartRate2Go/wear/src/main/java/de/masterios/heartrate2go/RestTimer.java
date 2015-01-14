package de.masterios.heartrate2go;

import java.util.Timer;
import java.util.TimerTask;

public class RestTimer {
    public interface RestTimerListener {
        public void onTimerUpdate(long timeSpanMs);
        public void onTimerFinished();
    }

    private int mUpdateIntervalMs = 500;
    private int mMeasureDurationMs = 60000;

    private long mStartTimeMs;
    private long mTimeSpanMs = mMeasureDurationMs;

    Timer mTimer;
    TimerTask mTimerTask;

    RestTimerListener mRestTimerListener;

    /**
     * Set Listener for on-timer-update and on-timer-fineshed methods
     * @param restTimerListener
     */
    public void setRestTimerListener(RestTimerListener restTimerListener) {
        mRestTimerListener = restTimerListener;
    }

    /**
     * Reset Rest-Timer
     */
    private void reset() {
        mTimeSpanMs = mMeasureDurationMs;
    }

    /**
     * Start Rest-Timer
     */
    public void start() {
        mStartTimeMs = System.currentTimeMillis();
        createNewTimers();
    }

    /**
     * Pause Rest-Timer
     */
    public void pause() {
        if (null != mTimer) {
            mTimer.cancel();
            mTimer = null;
        }

        if (null != mTimerTask) {
            mTimerTask.cancel();
            mTimerTask = null;
        }
    }

    /**
     * Stop Rest-Timer
     */
    public void stop() {
        pause();
        reset();
    }

    /**
     * Creating new Timer and TimerTask objects
     */
    private void createNewTimers() {
        mTimerTask = new TimerTask() {
            @Override
            public void run() {
                long currentMs = System.currentTimeMillis();
                mTimeSpanMs -= currentMs - mStartTimeMs;
                mStartTimeMs = currentMs;

                if(null != mRestTimerListener) {
                    mRestTimerListener.onTimerUpdate(mTimeSpanMs);

                    if(mTimeSpanMs < 0) {
                        mRestTimerListener.onTimerFinished();
                    }
                }

                if(mTimeSpanMs < 0) {
                    if(null != mRestTimerListener) {
                        mRestTimerListener.onTimerFinished();
                    }
                    stop();
                }
            }
        };
        mTimer = new Timer();
        mTimer.schedule(mTimerTask, mUpdateIntervalMs, mUpdateIntervalMs);
    }

    /**
     * Set update interval for on-timer-update ticks
     * @param updateIntervalMs
     */
    public void setUpdateIntervalMs(int updateIntervalMs) {
        pause();
        mUpdateIntervalMs = updateIntervalMs;
        start();
    }

    /**
     * Set duration of measurement in milliseconds
     * @param measureDurationMs
     */
    public void setMeasureDurationMs(int measureDurationMs) {
        mMeasureDurationMs = measureDurationMs;
    }
}
