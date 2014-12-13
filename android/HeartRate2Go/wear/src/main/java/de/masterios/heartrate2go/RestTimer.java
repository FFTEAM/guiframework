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
    public void setRestTimerListener(RestTimerListener restTimerListener) {
        mRestTimerListener = restTimerListener;
    }

    private void reset() {
        mTimeSpanMs = mMeasureDurationMs;
    }

    public void start() {
        mStartTimeMs = System.currentTimeMillis();
        createNewTimers();
    }

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

    public void stop() {
        pause();
        reset();
    }

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

    public void setUpdateIntervalMs(int updateIntervalMs) {
        pause();
        mUpdateIntervalMs = updateIntervalMs;
        start();
    }

    public void setMeasureDurationMs(int measureDurationMs) {
        mMeasureDurationMs = measureDurationMs;
    }
}
