package de.masterios.heartrate2go;

import android.app.Activity;
import android.os.Bundle;
import android.support.wearable.view.WatchViewStub;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;

public class WearActivity extends Activity {

    private TextView mTextView;
    private SensorLogger mSensorLogger;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_wear);
        final WatchViewStub stub = (WatchViewStub) findViewById(R.id.watch_view_stub);
        stub.setOnLayoutInflatedListener(new WatchViewStub.OnLayoutInflatedListener() {
            @Override
            public void onLayoutInflated(WatchViewStub stub) {
                final WatchViewStub stub2 = stub;
                mTextView = (TextView) stub.findViewById(R.id.text);
                mSensorLogger = new SensorLogger(stub.getContext());
                mSensorLogger.setMeasureInterval(3);
                mSensorLogger.setSensorLoggerListener(new SensorLoggerListener() {
                    @Override
                    public void onSensorLog() {
                        FileInputStream inputStream;
                        try {
                            inputStream = stub2.getContext().openFileInput("measuredata.csv");
                            InputStreamReader inputreader = new InputStreamReader(inputStream);
                            BufferedReader buffreader = new BufferedReader(inputreader);
                            String line = "", prelastline = "";
                            try {
                                while ((line = buffreader.readLine()) != null) {
                                    prelastline = line;
                                }
                            } catch (Exception e) {
                                e.printStackTrace();
                            }
                            inputStream.close();

                            mTextView.setText(prelastline);
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }
                });
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        if(null != mSensorLogger) {
            mSensorLogger.resume();
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        if(null != mSensorLogger) {
            mSensorLogger.pause();
        }
    }
}
