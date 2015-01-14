package de.masterios.heartrate2go;

import java.util.Timer;
import java.util.TimerTask;

public class RunningTimer {

    public interface RunningTimerListener {
        public void onTimerUpdate(long timeSpanMs);
    }

    private int mUpdateIntervalMs = 500;

    private long mStartTimeMs;
    private long mTimeSpanMs = 0L;

    Timer mTimer;
    TimerTask mTimerTask;

    RunningTimerListener mRunningTimerListener;

    /**
     * Set Listener for on-timer-update method
     * @param runningTimerListener
     */
    public void setRunningTimerListener(RunningTimerListener runningTimerListener) {
        mRunningTimerListener = runningTimerListener;
    }

    /**
     * Reset Running-Timer
     */
    private void reset() {
        mTimeSpanMs = 0L;
    }

    /**
     * Start Running-Timer
     */
    public void start() {
        mStartTimeMs = System.currentTimeMillis();
        createNewTimers();
    }

    /**
     * Pause Running-Timer
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
     * Stop Running-Timer
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

    /**
     * Set update interval for on-timer-update ticks
     * @param updateIntervalMs
     */
    public void setUpdateIntervalMs(int updateIntervalMs) {
        pause();
        mUpdateIntervalMs = updateIntervalMs;
        start();
    }
}
