package de.masterios.heartrate2go;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.jjoe64.graphview.BarGraphView;
import com.jjoe64.graphview.CustomLabelFormatter;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GraphViewSeries;
import com.jjoe64.graphview.GraphViewStyle;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.List;

import de.masterios.heartrate2go.common.HeartRateFile;
import de.masterios.heartrate2go.common.HeartRateMeasure;
import de.masterios.heartrate2go.common.MeasureMode;

public class HandheldActivity extends Activity implements AdapterView.OnItemSelectedListener {

    NetworkBroadcast mNetworkBroadcast;
    HeartRateMeasure mHeartRateMeasure;

    TextView mTextViewCaption;
    FrameLayout mFrameLayout;
    TextView mTextViewCenter;
    Spinner mFilenameSpinner;
    ImageButton mButtonDismiss;
    ImageButton mButtonSend;

    GraphView mGraphView;

    SharedPreferences mSharedPreferences;

    List<String> mDisplayNames = new ArrayList<>();
    ArrayAdapter<String> mSpinnerArrayAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_handheld);

        mSharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);

        mTextViewCaption = (TextView) findViewById(R.id.text_view_caption);
        mFrameLayout = (FrameLayout) findViewById(R.id.frame_layout);
        mTextViewCenter = (TextView) findViewById(R.id.text_view_center);
        mFilenameSpinner = (Spinner) findViewById(R.id.filename_spinner);
        mFilenameSpinner.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_UP) {
                    refreshFilesList(getBaseContext());
                }
                return false;
            }
        });
        mButtonDismiss = (ImageButton) findViewById(R.id.button_dismiss);
        mButtonSend = (ImageButton) findViewById(R.id.button_send);

        mGraphView = new BarGraphView(this, "");
        mGraphView.setShowHorizontalLabels(false);
        mGraphView.setManualYAxisBounds(150, 50);
        mGraphView.setCustomLabelFormatter(new CustomLabelFormatter() {
            @Override
            public String formatLabel(double value, boolean isValueX) {
                return ""+((int) value);
            }
        });
        mFrameLayout.addView(mGraphView);

        // refresh preferences on wearable
        SettingsActivity.syncSettingsToWearable(this);
        mHeartRateMeasure = HeartRateMeasure.getInstance();

        mNetworkBroadcast = new NetworkBroadcast(this);
        mNetworkBroadcast.setBroadcastFinishedListener(new NetworkBroadcast.BroadcastFinishedListener() {
            @Override
            public void onBroadcastFinished(final InetAddress from, String answer) {
                if(null != from && null != answer) {
                    System.out.println("got answer " + answer + " from " + from.getHostAddress());
                    mHeartRateMeasure.sendDataAsync(from.toString());
                }
            }
        });

        mSpinnerArrayAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, mDisplayNames);
        mSpinnerArrayAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        mFilenameSpinner.setAdapter(mSpinnerArrayAdapter);
        mFilenameSpinner.setOnItemSelectedListener(this);

        refreshFilesList(this);
    }

    private void refreshFilesList(Context context) {
        if(null != mDisplayNames) {
            List<String> fileNames = HeartRateFile.getMeasureFileNames(context);
            mDisplayNames.clear();
            for (String s : fileNames) {
                mDisplayNames.add(getDateStringFromFilename(s));
            }
            Collections.sort(mDisplayNames, Collections.reverseOrder());
            mSpinnerArrayAdapter.notifyDataSetChanged();

            if (mDisplayNames.size() > 0) {
                mFilenameSpinner.setSelection(0);
                mButtonDismiss.setEnabled(true);
                mButtonDismiss.setImageResource(R.drawable.dismiss_white);
                mButtonSend.setEnabled(true);
                mButtonSend.setImageResource(R.drawable.send_white);
            } else {
                mButtonDismiss.setEnabled(false);
                mButtonDismiss.setImageResource(R.drawable.dismiss_grey);
                mButtonSend.setEnabled(false);
                mButtonSend.setImageResource(R.drawable.send_grey);
            }

            addDataToGraph();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        refreshFilesList(this);
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    private void refreshScreen() {
        boolean isDataAvailable = mDisplayNames.size() > 0;

        if(isDataAvailable) {
            String captionText = getString(R.string.caption_text);
            switch(mHeartRateMeasure.getMeasureMode()) {
                case ACTIVITY:
                    captionText += " (" + getString(R.string.measure_mode_activity) + ")";
                    break;
                case REST:
                    captionText += " (" + getString(R.string.measure_mode_rest) + ")";
                    break;
            }
            mTextViewCaption.setText(captionText);

            mGraphView.setVisibility(View.VISIBLE);
            mTextViewCaption.setVisibility(View.VISIBLE);
            mTextViewCenter.setVisibility(View.INVISIBLE);
        } else {
            mGraphView.setVisibility(View.INVISIBLE);
            mTextViewCaption.setVisibility(View.INVISIBLE);
            mTextViewCenter.setVisibility(View.VISIBLE);
        }
    }

    @Override
         public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.handheld, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            startActivity(new Intent(this, SettingsActivity.class));
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
        addDataToGraph();
    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {
        // nothing to do
    }

    private void addDataToGraph() {
        String selectedDate = (String) mFilenameSpinner.getSelectedItem();
        if(null != selectedDate && !selectedDate.equals("")) {
            mHeartRateMeasure = HeartRateFile.openMeasureFromFile(this, getFilenameFromDateString(selectedDate));

            int size = mHeartRateMeasure.getSize();
            if(size > 0) {
                GraphView.GraphViewData[] graphViewDataSets = new GraphView.GraphViewData[size];
                for (int i = 0; i < size; i++) {
                    double heartrate = (double) mHeartRateMeasure.getHeartRateAt(i);
                    try {
                        graphViewDataSets[i] = new GraphView.GraphViewData(i, heartrate);
                    } catch(NumberFormatException e) {
                        e.printStackTrace();
                    }
                }

                if(null != graphViewDataSets && graphViewDataSets.length > 0) {
                    int barColor = Color.WHITE;
                    String name = "Measurement";
                    switch(mHeartRateMeasure.getMeasureMode()) {
                        case ACTIVITY:
                            name = getString(R.string.measure_mode_activity);
                            barColor = Color.rgb(50, 120, 220);
                            break;
                        case REST:
                            name = getString(R.string.measure_mode_rest);
                            barColor = Color.rgb(75, 200, 75);
                            break;
                    }
                    mGraphView.removeAllSeries();
                    mGraphView.addSeries(new GraphViewSeries(name, new GraphViewSeries.GraphViewSeriesStyle(barColor, 3), graphViewDataSets)); // data
                }
            }
        }
        refreshScreen();
    }

    private void showToast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_LONG).show();
    }

    public void onButtonTestClick(View view) {
        HeartRateMeasure temp = HeartRateMeasure.getInstance();
        temp.createRandomTestData();
        HeartRateFile.saveMeasureToFile(this, temp);
        refreshFilesList(this);

    }

    private String getFilenameFromDateString(String date) {
        String filename = date;
        SimpleDateFormat source = new SimpleDateFormat(getString(R.string.date_format));
        SimpleDateFormat target = new SimpleDateFormat("yyyy-MM-dd_HH-mm-ss");
        try {
            filename = target.format(source.parse(date));
        } catch (ParseException e) {
            e.printStackTrace();
        }
        return filename;
    }

    private String getDateStringFromFilename(String filename) {
        String date = filename;
        SimpleDateFormat target = new SimpleDateFormat(getString(R.string.date_format));
        SimpleDateFormat source = new SimpleDateFormat("yyyy-MM-dd_HH-mm-ss");
        try {
            date = target.format(source.parse(filename));
        } catch (ParseException e) {
            e.printStackTrace();
        }
        return date;
    }

    public void onButtonDismissClick(View view) {
        String selectedDate = (String) mFilenameSpinner.getSelectedItem();
        if(null != selectedDate && !selectedDate.equals("")) {
            HeartRateFile.deleteFile(this, getFilenameFromDateString(selectedDate));
            refreshFilesList(getBaseContext());
        }
    }

    public void onButtonSendClick(View view) {
        if(null != mNetworkBroadcast && null != mHeartRateMeasure) {
            final String ip = mSharedPreferences.getString("preference_static_ip", "");

            if (ip.equals("")) {
                showToast("send broadcast and data");
                mNetworkBroadcast.sendBroadcastAsync();
            } else {
                showToast("send data to " + ip);
                mHeartRateMeasure.sendDataAsync(ip);
            }
        }
    }
}
