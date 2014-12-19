package de.masterios.heartrate2go.common;

import android.content.Context;
import android.text.format.DateFormat;

import java.util.ArrayList;
import java.util.List;

public class HeartRateFile {

    public static void saveMeasureToFile(Context context, HeartRateMeasure heartRateMeasure) {
        String filename = (String)getFileName(heartRateMeasure);

        // TODO
    }

    public static List<HeartRateMeasure> readMeasuresFromFiles(Context context) {
        List<HeartRateMeasure> heartRateMeasures = new ArrayList<HeartRateMeasure>();

        // TODO

        return heartRateMeasures;
    }

    public static void deleteFile(Context context, HeartRateMeasure heartRateMeasure) {
        // TODO
    }

    public static CharSequence getFileName(HeartRateMeasure heartRateMeasure) {
        long timeStampMs = heartRateMeasure.getStartTimeStampMs();
        return DateFormat.format("yyyy-MM-dd_HH-mm", timeStampMs);
    }
}
