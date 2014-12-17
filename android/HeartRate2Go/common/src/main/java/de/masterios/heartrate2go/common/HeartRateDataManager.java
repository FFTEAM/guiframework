package de.masterios.heartrate2go.common;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class HeartRateDataManager {

    private static HeartRateDataManager singleton;

    private MeasureMode mMeasureMode;
    private MeasureMood mMeasureMood;
    private List<HeartRateData> mHeartRateDataList;

    private HeartRateDataManager() {
        if(null == mHeartRateDataList) {
            mHeartRateDataList = new ArrayList<>();
        } else {
            mHeartRateDataList.clear();
        }

        mMeasureMode = MeasureMode.ACTIVITY;
        mMeasureMood = MeasureMood.AVERAGE;
    }

    public synchronized MeasureMode getMeasureMode() {
        return mMeasureMode;
    }

    public synchronized void setMeasureMode(MeasureMode measureMode) {
        mMeasureMode = measureMode;
    }

    public synchronized static HeartRateDataManager getInstance() {
        if(null == singleton) {
            singleton = new HeartRateDataManager();
        }
        return singleton;
    }

    public synchronized void add(HeartRateData heartRateData) {
        if(!mHeartRateDataList.contains(heartRateData)) {
            mHeartRateDataList.add(heartRateData);
        }
    }

    public synchronized void remove(HeartRateData heartRateData) {
        if(mHeartRateDataList.contains(heartRateData)) {
            mHeartRateDataList.remove(heartRateData);
        }
    }

    public synchronized void clear() {
        if(mHeartRateDataList.size() > 0) {
            mHeartRateDataList.clear();
        }
    }

    public synchronized int getSize() {
        return mHeartRateDataList.size();
    }

    public synchronized int getHeartRateAt(int index) {
        int heartrate = 0;
        if(index >= 0 && index < mHeartRateDataList.size()) {
            heartrate =  mHeartRateDataList.get(index).getHeartRate();
        }
        return heartrate;
    }

    public synchronized String getDataAsString() {
        StringBuilder sb = new StringBuilder();
        if(mHeartRateDataList.size() > 0) {
            // begin settings
            sb.append("measure_mode=" + mMeasureMode.toString() + ";");
            sb.append("measure_mood=" + mMeasureMood.toString());
            sb.append("\n");
            // end settings
            HeartRateData lastDataSet = mHeartRateDataList.get(mHeartRateDataList.size() - 1);
            for (HeartRateData heartRateData : mHeartRateDataList) {
                sb.append(heartRateData.getTimeStampMs() + ";");
                sb.append(heartRateData.getHeartRate() + ";");
                sb.append(heartRateData.getSteps());

                if (heartRateData != lastDataSet) {
                    sb.append("\n");
                }
            }
        }
        return sb.toString();
    }

    public synchronized void setDataFromString(String data) {
        if(null != data && !data.equals("")) {
            String[] lines = data.split("\n");
            // begin settings
            String[] settings = lines[0].split(";");
            for(String setting : settings) {
                if(setting.contains("=")) {
                    String[] pair = setting.split("=");
                    if(2 == pair.length) {
                        String key = pair[0];
                        String value = pair[1];

                        if(key.equals("measure_mode")) {
                            try { mMeasureMode = MeasureMode.valueOf(value); } catch (IllegalArgumentException e) {}
                        } else if(key.equals("measure_mood")) {
                            try { mMeasureMood = MeasureMood.valueOf(value); } catch (IllegalArgumentException e) {}
                        }
                    }
                }
            }
            // end settings

            clear();
            for(int i=1; i < lines.length; i++) {
                String[] dataset = lines[i].split(";");
                if(3 == dataset.length) {
                    try {
                        int timestamp = Integer.parseInt(dataset[0]);
                        int heartrate = Integer.parseInt(dataset[1]);
                        int steps = Integer.parseInt(dataset[2]);
                        add(new HeartRateData(timestamp, heartrate, steps));
                    } catch (NumberFormatException e) { }
                }
            }
        }
    }

    public synchronized void writeDataToOutputStream(OutputStream out) {
        try {
            DataOutputStream outputStream = new DataOutputStream(out);
            if (mHeartRateDataList.size() > 0) {
                outputStream.write(ByteCodes.MEASURE_MODE);
                switch (mMeasureMode) {
                    case ACTIVITY:
                        outputStream.write(ByteCodes.MEASURE_MODE_ACTIVITY);
                        break;
                    case REST:
                        outputStream.write(ByteCodes.MEASURE_MODE_REST);
                        break;
                }

                outputStream.write(ByteCodes.MEASURE_MOOD);
                switch (mMeasureMood) {
                    case GOOD:
                        outputStream.write(ByteCodes.MEASURE_MOOD_GOOD);
                        break;
                    case AVERAGE:
                        outputStream.write(ByteCodes.MEASURE_MOOD_AVERAGE);
                        break;
                    case BAD:
                        outputStream.write(ByteCodes.MEASURE_MOOD_BAD);
                        break;
                }

                outputStream.write(ByteCodes.DATASET);
                for (HeartRateData heartRateData : mHeartRateDataList) {
                    outputStream.write(ByteBuffer.allocate(8).putLong(heartRateData.getTimeStampMs()).array());
                    outputStream.write(ByteBuffer.allocate(2).putShort((short) heartRateData.getHeartRate()).array());
                    outputStream.write(ByteBuffer.allocate(2).putShort((short) heartRateData.getSteps()).array());
                    outputStream.write(ByteCodes.DATASET);
                }
            }
            outputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void createRandomTestData() {
        mMeasureMode = MeasureMode.ACTIVITY;
        mMeasureMood = MeasureMood.BAD;
        mHeartRateDataList.clear();
        long currentTime = System.currentTimeMillis();
        Random rdm = new Random(currentTime);
        int amountOfDatasets = rdm.nextInt(100);
        int steps = 0;
        for(int i=0; i < amountOfDatasets; i++) {
            long time = currentTime+i*3000;
            int heartrate = rdm.nextInt(150);
            steps += rdm.nextInt(10);
            mHeartRateDataList.add(new HeartRateData(time, heartrate, steps));
        }
    }
}
