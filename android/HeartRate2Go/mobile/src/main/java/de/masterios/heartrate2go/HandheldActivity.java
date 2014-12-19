package de.masterios.heartrate2go;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.FrameLayout;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.jjoe64.graphview.BarGraphView;
import com.jjoe64.graphview.CustomLabelFormatter;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GraphViewSeries;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

import de.masterios.heartrate2go.common.HeartRateMeasure;

public class HandheldActivity extends Activity implements AdapterView.OnItemSelectedListener {

    NetworkBroadcast mNetworkBroadcast;
    HeartRateMeasure mHeartRateMeasure;

    TextView mTextViewCaption;
    FrameLayout mFrameLayout;
    TextView mTextViewCenter;

    GraphView mGraphView;

    SharedPreferences mSharedPreferences;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_handheld);
        mTextViewCaption = (TextView) findViewById(R.id.text_view_caption);
        mFrameLayout = (FrameLayout) findViewById(R.id.frame_layout);
        mTextViewCenter = (TextView) findViewById(R.id.text_view_center);

        mGraphView = new BarGraphView(this, "");
        mGraphView.setShowHorizontalLabels(false);
        mGraphView.setManualYAxisBounds(150, 50);
        mGraphView.setCustomLabelFormatter(new CustomLabelFormatter() {
            @Override
            public String formatLabel(double value, boolean isValueX) {
                // return as Integer
                return ""+((int) value);
            }
        });
        mFrameLayout.addView(mGraphView);

        // refresh preferences on wearable
        SettingsActivity.syncSettingsToWearable(this);
        mHeartRateMeasure = HeartRateMeasure.getInstance();

        mSharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);

        mNetworkBroadcast = new NetworkBroadcast(this);
        mNetworkBroadcast.setBroadcastFinishedListener(new NetworkBroadcast.BroadcastFinishedListener() {
            @Override
            public void onBroadcastFinished(final InetAddress from, String answer) {
                if(null != from && null != answer) {

                    // TODO checkAnswer

                    Socket socket = null;
                    try {
                        socket = new Socket(from.toString(), 1234);
                        OutputStream out = socket.getOutputStream();
                        mHeartRateMeasure.writeDataToOutputStream(out);
                        socket.close();
                    } catch (UnknownHostException e) {
                        e.printStackTrace();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        addDataToGraph();
        refreshScreen();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    private void refreshScreen() {
        boolean isDataAvailable = mHeartRateMeasure.getSize() > 0;

        if(isDataAvailable) {
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

    private void addDataToGraph() {
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
                mGraphView.removeAllSeries();
                mGraphView.addSeries(new GraphViewSeries(graphViewDataSets)); // data
            }
        }
    }

    private void showToast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_LONG).show();
    }

    public void onButtonTestClick(View view) {
        mHeartRateMeasure.createRandomTestData();
        addDataToGraph();
        refreshScreen();

        final String ip = mSharedPreferences.getString("preference_static_ip", "");

        if(ip.equals("")) {
            showToast("send broadcast and data");
            mNetworkBroadcast.sendBroadcastAsync();
        } else {
            showToast("send data to " + ip);
            new Thread(new Runnable() {
                @Override
                public void run() {
                    Socket socket = null;
                    try {
                        socket = new Socket(ip, 1234);
                        OutputStream out = socket.getOutputStream();
                        mHeartRateMeasure.writeDataToOutputStream(out);
                        socket.close();
                    } catch (UnknownHostException e) {
                        e.printStackTrace();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }).start();
        }
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {

    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {

    }
}
