package de.masterios.heartrate2go.common;

public class HeartRateData {

    private long mTimeStampMs;
    private int mHeartRate;
    private int mSteps;

    public HeartRateData(long timeStampMs, int heartRate, int steps) {
        mTimeStampMs = timeStampMs;
        mHeartRate = heartRate;
        mSteps = steps;
    }

    public long getTimeStampMs() {
        return mTimeStampMs;
    }

    public int getHeartRate() {
        return mHeartRate;
    }

    public int getSteps() {
        return mSteps;
    }
}
