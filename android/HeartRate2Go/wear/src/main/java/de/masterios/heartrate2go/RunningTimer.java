package de.masterios.heartrate2go;

import java.util.Timer;
import java.util.TimerTask;

public class RunningTimer {

    public interface RunningTimerListener {
        public void onTimerUpdate(long timeSpanMs);
    }

    private int mUpdateIntervalMs = 500;

    private long mStartTimeMs;
    private long mTimeSpanMs;

    Timer mTimer;
    TimerTask mTimerTask;

    RunningTimerListener mRunningTimerListener;
    public void setRunningTimerListener(RunningTimerListener runningTimerListener) {
        mRunningTimerListener = runningTimerListener;
    }

    private void reset() {
        mTimeSpanMs = 0L;
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
                mTimeSpanMs += currentMs - mStartTimeMs;
                mStartTimeMs = currentMs;

                if(null != mRunningTimerListener) {
                    mRunningTimerListener.onTimerUpdate(mTimeSpanMs);
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
}
