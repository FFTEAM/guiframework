package de.masterios.heartrate2go.common;

public class HeartRateData {

    private long mTimeStampMs;
    private int mHeartRate;
    private int mSteps;

    /**
     * Creating new HeartRateData Object
     * @param timeStampMs
     * @param heartRate
     * @param steps
     */
    public HeartRateData(long timeStampMs, int heartRate, int steps) {
        mTimeStampMs = timeStampMs;
        mHeartRate = heartRate;
        mSteps = steps;
    }

    /**
     * Timestamp in Milliseconds
     * @return
     */
    public long getTimeStampMs() {
        return mTimeStampMs;
    }

    /**
     * HeartRate in BPM
     * @return
     */
    public int getHeartRate() {
        return mHeartRate;
    }

    /**
     * Amount of Steps
     * @return
     */
    public int getSteps() {
        return mSteps;
    }
}
