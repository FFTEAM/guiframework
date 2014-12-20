package de.masterios.heartrate2go.common;

import android.content.Context;
import android.text.format.DateFormat;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class HeartRateFile {

    private static final String LINE_SEPARATOR = "\n";

    public static void saveMeasureToFile(Context context, HeartRateMeasure heartRateMeasure) {
        String filename = getFileName(heartRateMeasure);

        try {
            FileOutputStream outputStream = context.openFileOutput(filename, Context.MODE_PRIVATE);
            PrintWriter printWriter = new PrintWriter(outputStream);
            printWriter.append(heartRateMeasure.getDataAsString());
            printWriter.close();
            outputStream.close();
            System.out.println("saved file " + filename);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static HeartRateMeasure openMeasureFromFile(Context context, String filename) {
        HeartRateMeasure heartRateMeasure = null;
        try {
            FileInputStream inputStream = context.openFileInput(filename);
            InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
            BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
            StringBuilder sb = new StringBuilder();
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                sb.append(line + LINE_SEPARATOR);
            }
            heartRateMeasure = HeartRateMeasure.getInstance();
            heartRateMeasure.setDataFromString(sb.toString());
        } catch (Exception e) {
            e.printStackTrace();
        }
        return heartRateMeasure;
    }

    public static List<String> getMeasureFileNames(Context context) {
        List<String> measureFileNames = new ArrayList<String>();

        String filePattern = "\\d{4}-\\d{2}-\\d{2}_\\d{2}-\\d{2}-\\d{2}";

        File dir = context.getFilesDir();
        if(dir.isDirectory()) {
            File[] files = dir.listFiles();
            for(File file : files) {
                String filename = file.getName();
                if(filename.matches(filePattern)) {
                    measureFileNames.add(filename);
                }
            }
        }

        return measureFileNames;
    }

    public static boolean deleteFile(Context context, String filename) {
        return context.deleteFile(filename);
    }

    public static String getFileName(HeartRateMeasure heartRateMeasure) {
        long timeStampMs = heartRateMeasure.getStartTimeStampMs();
        return (String) DateFormat.format("yyyy-MM-dd_HH-mm-ss", timeStampMs);
    }
}
