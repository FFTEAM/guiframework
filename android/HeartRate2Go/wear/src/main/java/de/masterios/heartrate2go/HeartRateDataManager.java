package de.masterios.heartrate2go;

import java.util.ArrayList;
import java.util.List;

public class HeartRateDataManager {

    private static HeartRateDataManager singleton;

    private List<HeartRateData> mHeartRateDataList;

    private HeartRateDataManager() {
        if(null == mHeartRateDataList) {
            mHeartRateDataList = new ArrayList<>();
        } else {
            mHeartRateDataList.clear();
        }
    }

    public static HeartRateDataManager getInstance() {
        if(null == singleton) {
            singleton = new HeartRateDataManager();
        }
        return singleton;
    }

    public void add(HeartRateData heartRateData) {
        if(!mHeartRateDataList.contains(heartRateData)) {
            mHeartRateDataList.add(heartRateData);
        }
    }

    public void remove(HeartRateData heartRateData) {
        if(mHeartRateDataList.contains(heartRateData)) {
            mHeartRateDataList.remove(heartRateData);
        }
    }

    public void clear() {
        if(mHeartRateDataList.size() > 0) {
            mHeartRateDataList.clear();
        }
    }

    public String getCsvMapAsString() {
        StringBuilder sb = new StringBuilder();
        if(mHeartRateDataList.size() > 0) {
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
}
