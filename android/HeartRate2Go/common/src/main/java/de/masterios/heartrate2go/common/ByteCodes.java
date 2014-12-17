package de.masterios.heartrate2go.common;

public class ByteCodes {
    public static final byte MEASURE_MODE = 0x00;
    public static final byte MEASURE_MODE_ACTIVITY = 0x00;
    public static final byte MEASURE_MODE_REST = 0x01;

    public static final byte MEASURE_MOOD = 0x01;
    public static final byte MEASURE_MOOD_GOOD = 0x00;
    public static final byte MEASURE_MOOD_AVERAGE = 0x01;
    public static final byte MEASURE_MOOD_BAD = 0x02;

    public static final byte DATASET = (byte) 0xff;
}
