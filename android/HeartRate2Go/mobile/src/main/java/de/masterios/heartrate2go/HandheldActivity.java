package de.masterios.heartrate2go;

import android.app.ActionBar;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
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
import android.widget.ImageView;
import android.widget.LinearLayout;
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
import de.masterios.heartrate2go.common.MeasureMood;

public class HandheldActivity extends Activity implements AdapterView.OnItemSelectedListener, HeartRateMeasure.DataSentListener {

    NetworkBroadcast mNetworkBroadcast;
    HeartRateMeasure mHeartRateMeasure;

    Spinner mFilenameSpinner;
    ImageButton mButtonDismiss;
    ImageButton mButtonSend;

    LinearLayout mLinearLayoutDebug;

    LinearLayout mLinearLayoutMeasureHeader;
    ImageView mImageViewMode;
    ImageView mImageViewMood;

    LinearLayout mLinearLayoutGraphView;
    FrameLayout mFrameLayoutContainer;
    GraphView mGraphView;

    TextView mTextViewCenter;

    SharedPreferences mSharedPreferences;

    List<String> mDisplayNames = new ArrayList<>();
    ArrayAdapter<String> mSpinnerArrayAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_handheld);

        mSharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);

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

        mLinearLayoutDebug = (LinearLayout) findViewById(R.id.linear_layout_debug);

        mLinearLayoutMeasureHeader = (LinearLayout) findViewById(R.id.linear_layout_measure_header);
        mImageViewMode = (ImageView) findViewById(R.id.image_view_mode);
        mImageViewMood = (ImageView) findViewById(R.id.image_view_mood);

        mLinearLayoutGraphView = (LinearLayout) findViewById(R.id.linear_layout_graph_view);
        mFrameLayoutContainer = (FrameLayout) findViewById(R.id.frame_layout_container);
        mGraphView = new BarGraphView(this, "");
        mGraphView.setManualYAxisBounds(150, 50);
        mGraphView.setCustomLabelFormatter(new CustomLabelFormatter() {
            @Override
            public String formatLabel(double value, boolean isValueX) {
                return "" + ((int) value);
            }
        });
        mFrameLayoutContainer.addView(mGraphView);

        mTextViewCenter = (TextView) findViewById(R.id.text_view_center);

        // refresh preferences on wearable
        SettingsActivity.syncSettingsToWearable(this);

        mNetworkBroadcast = new NetworkBroadcast(this);
        mNetworkBroadcast.setBroadcastFinishedListener(new NetworkBroadcast.BroadcastFinishedListener() {
            @Override
            public void onBroadcastFinished(final InetAddress from, String answer) {
                if(null != from && null != answer) {
                    System.out.println("got answer " + answer + " from " + from.getHostAddress());
                    if(null != mHeartRateMeasure) {
                        mHeartRateMeasure.sendDataAsync(from.toString());
                    }
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
                mDisplayNames.add(HeartRateFile.getDateStringFromFilename(context, s));
            }
            Collections.sort(mDisplayNames, Collections.reverseOrder());
            mSpinnerArrayAdapter.notifyDataSetChanged();


            Boolean isDeleteAfterSend = mSharedPreferences.getBoolean("preference_delete_after_send", true);
            if (mDisplayNames.size() > 0) {
                mFilenameSpinner.setSelection(0);
                mButtonDismiss.setEnabled(true);
                mButtonDismiss.setImageResource(R.drawable.dismiss_white);
                mButtonSend.setEnabled(true);
                if(isDeleteAfterSend) {
                    mButtonSend.setImageResource(R.drawable.send_and_dismiss_white);
                } else {
                    mButtonSend.setImageResource(R.drawable.send_white);
                }
            } else {
                mButtonDismiss.setEnabled(false);
                mButtonDismiss.setImageResource(R.drawable.dismiss_grey);
                mButtonSend.setEnabled(false);
                if(isDeleteAfterSend) {
                    mButtonSend.setImageResource(R.drawable.send_and_dismiss_grey);
                } else {
                    mButtonSend.setImageResource(R.drawable.send_grey);
                }
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
            switch(mHeartRateMeasure.getMeasureMode()) {
                case ACTIVITY:
                    mImageViewMode.setImageResource(R.drawable.running_white);
                    break;
                case REST:
                    mImageViewMode.setImageResource(R.drawable.standing_white);
                    break;
            }

            switch (mHeartRateMeasure.getMeasureMood()) {
                case GOOD:
                    mImageViewMood.setImageResource(R.drawable.good);
                    break;
                case AVERAGE:
                    mImageViewMood.setImageResource(R.drawable.average);
                    break;
                case BAD:
                    mImageViewMood.setImageResource(R.drawable.bad);
                    break;
            }

            mGraphView.setVisibility(View.VISIBLE);
            mLinearLayoutGraphView.setVisibility(View.VISIBLE);
            mLinearLayoutMeasureHeader.setVisibility(View.VISIBLE);
            mTextViewCenter.setVisibility(View.INVISIBLE);
        } else {
            mGraphView.setVisibility(View.INVISIBLE);
            mLinearLayoutGraphView.setVisibility(View.INVISIBLE);
            mLinearLayoutMeasureHeader.setVisibility(View.INVISIBLE);
            mTextViewCenter.setVisibility(View.VISIBLE);
        }

        Boolean isDebugMode = mSharedPreferences.getBoolean("preference_debug_mode", false);
        if(isDebugMode) {
            mLinearLayoutDebug.setVisibility(View.VISIBLE);
        } else {
            mLinearLayoutDebug.setVisibility(View.GONE);
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
            String filename = HeartRateFile.getFilenameFromDateString(getBaseContext(), selectedDate);
            mHeartRateMeasure = HeartRateFile.openMeasureFromFile(this, filename);
            mHeartRateMeasure.setDataSentListener(this);

            int size = mHeartRateMeasure.getSize();
            if(size > 0) {
                GraphView.GraphViewData[] graphViewDataSets = new GraphView.GraphViewData[size];
                long startTime = mHeartRateMeasure.getStartTimeStampMs();
                for (int i = 0; i < size; i++) {

                    double heartrate = (double) mHeartRateMeasure.getHeartRateAt(i);
                    int minutes = (int)(((mHeartRateMeasure.getTimeStampMsAt(i) - startTime) / 1000) / 60);
                    try {
                        graphViewDataSets[i] = new GraphView.GraphViewData(minutes, heartrate);
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
                            long duration = mHeartRateMeasure.getDurationMs() / 1000; // Minutes
                            final int RESOLUTION = 6;
                            StringBuilder sb = new StringBuilder();
                            int stepSize = (int) ((double)duration / (double)RESOLUTION);
                            for(int i=1; i < RESOLUTION-1; i++) {
                                sb.append((stepSize*i) + ";");
                            }
                            mGraphView.setHorizontalLabels(sb.toString().split(";"));
                            mGraphView.setShowHorizontalLabels(true);
                            break;
                        case REST:
                            name = getString(R.string.measure_mode_rest);
                            barColor = Color.rgb(75, 200, 75);
                            mGraphView.setShowHorizontalLabels(false);
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

    public void onButtonDismissClick(View view) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(getString(R.string.delete_sure))
                .setPositiveButton(getString(R.string.delete_yes), dialogClickListener)
                .setNegativeButton(getString(R.string.delete_no), dialogClickListener)
                .show();
    }

    private void deleteCurrentMeasurement() {
        Context context = getBaseContext();
        String selectedDate = (String) mFilenameSpinner.getSelectedItem();
        if(null != selectedDate && !selectedDate.equals("")) {
            HeartRateFile.deleteFile(this, HeartRateFile.getFilenameFromDateString(context, selectedDate));
            refreshFilesList(context);
        }
    }

    public void onButtonSendClick(View view) {
        if(null != mNetworkBroadcast && null != mHeartRateMeasure) {
            String ip = mSharedPreferences.getString("preference_static_ip", "");
            if (ip.equals("")) {
                mNetworkBroadcast.sendBroadcastAsync();
            } else {
                mHeartRateMeasure.sendDataAsync(ip);
            }
        }
    }

    DialogInterface.OnClickListener dialogClickListener = new DialogInterface.OnClickListener() {
        @Override
        public void onClick(DialogInterface dialog, int which) {
            switch (which){
                case DialogInterface.BUTTON_POSITIVE:
                    deleteCurrentMeasurement();
                    break;
                case DialogInterface.BUTTON_NEGATIVE:
                    // do nothing
                    break;
            }
        }
    };

    @Override
    public void onDataSent(final boolean success) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(success) {
                    Boolean isDeleteAfterSend = mSharedPreferences.getBoolean("preference_delete_after_send", true);
                    if(isDeleteAfterSend) {
                        deleteCurrentMeasurement();
                    }
                    showToast(getString(R.string.data_sent));
                } else {
                    showToast(getString(R.string.data_not_sent));
                }
            }
        });
    }

    public void onButtonAddRandomMeasurementClick(View view) {
        HeartRateMeasure temp = HeartRateMeasure.getInstance();
        temp.createRandomTestData();
        HeartRateFile.saveMeasureToFile(this, temp);
        refreshFilesList(this);
    }

    public void onButtonSendAllMeasurementsClick(View view) {
        final String ip = mSharedPreferences.getString("preference_static_ip", "");
        if (!ip.equals("")) {
            if (null != mNetworkBroadcast) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        Context context = getBaseContext();
                        for (String s : mDisplayNames) {
                            String filename = HeartRateFile.getFilenameFromDateString(context, s);
                            HeartRateMeasure temp = HeartRateFile.openMeasureFromFile(context, filename);
                            temp.sendDataAsync(ip);
                            try { Thread.sleep(20); } catch (InterruptedException e) { }
                        }
                    }
                }).start();
            }
            showToast(mDisplayNames.size() + " " + getString(R.string.measurements_sent));
        } else {
            showToast(getString(R.string.only_with_static_ip));
        }
    }
}
