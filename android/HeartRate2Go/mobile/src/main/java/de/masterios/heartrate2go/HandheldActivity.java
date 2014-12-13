package de.masterios.heartrate2go;

import android.app.Activity;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Parcelable;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.jjoe64.graphview.BarGraphView;
import com.jjoe64.graphview.CustomLabelFormatter;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GraphViewSeries;

public class HandheldActivity extends Activity {

    TextView mTextViewCaption;
    FrameLayout mFrameLayout;
    TextView mTextViewCenter;

    GraphView mGraphView;

    private AcceptThread at;

    public HandheldActivity() {
        System.out.println("HandheldActivity()");
        at = new AcceptThread();
        at.start();




    }

    private final BroadcastReceiver mReceiver = new BroadcastReceiver()
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            System.out.println(intent.getAction());
            BluetoothDevice deviceExtra = intent.getParcelableExtra("android.bluetooth.device.extra.DEVICE");

            Parcelable[] uuidExtra = intent.getParcelableArrayExtra("android.bluetooth.device.extra.UUID");
        }
    };

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

        getApplicationContext().registerReceiver(mReceiver,
                new IntentFilter(BluetoothDevice.ACTION_ACL_CONNECTED));

        getApplicationContext().registerReceiver(mReceiver,
                new IntentFilter(BluetoothDevice.ACTION_ACL_DISCONNECTED));
    }

    @Override
    protected void onResume() {
        super.onResume();
        String csvdata = DataLayerListenerService.getCurrentCsvData();
        String heartrates = getOnlyHeartRates(csvdata);
        addCsvDataToGraph(heartrates);

        refreshScreen(!heartrates.equals(""));
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    private void refreshScreen(boolean isDataAvailable) {
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


    private String getOnlyHeartRates(String data) {
        StringBuilder sb = new StringBuilder();

        if(null != data) {
            String[] lines = data.split("\n");
            for (int i = 0; i < lines.length; i++) {
                String[] content = lines[i].split(";");
                if (3 == content.length && !content[1].equals("0") && !content[1].equals("")) {
                    sb.append(content[1]);
                    if (i != lines.length - 1) {
                        sb.append(";");
                    }
                }
            }
        }

        return sb.toString();
    }

    private void addCsvDataToGraph(String data) {
        if(null != data && !data.equals("")) {
            String[] values = data.split(";");

            GraphView.GraphViewData[] graphViewDataSets = new GraphView.GraphViewData[values.length];
            for (int i = 0; i < values.length; i++) {
                try {
                    graphViewDataSets[i] = new GraphView.GraphViewData(i, Double.parseDouble(values[i]));
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
}
