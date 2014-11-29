package de.masterios.heartrate2go;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.FrameLayout;
import android.widget.Toast;

import com.jjoe64.graphview.BarGraphView;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GraphViewSeries;

public class HandheldActivity extends Activity {

    FrameLayout mFrameLayout;
    GraphView mGraphView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_handheld);

        mFrameLayout = (FrameLayout) findViewById(R.id.frame_layout);
    }

    @Override
    protected void onResume() {
        super.onResume();
        String csvdata = DataLayerListenerService.getCurrentCsvData();
        if (null != csvdata) {
            addCsvDataToGraph(csvdata);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
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
            return true;
        }
        return super.onOptionsItemSelected(item);
    }


    private String filterMeasures(String csvdata) {
        StringBuilder sb = new StringBuilder();

        String[] lines = csvdata.split("\n");
        for(int i = 0; i < lines.length; i++) {
            String[] content = lines[i].split(";");
            if (3 == content.length && !content[1].equals("0")) {
                sb.append(content[1]);

                if(i != lines.length-1) {
                    sb.append(";");
                }
            }
        }

        return sb.toString();
    }

    private void addCsvDataToGraph(String csvdata) {
        if(null != csvdata && csvdata.length() > 0) {
            String[] heartrates = filterMeasures(csvdata).split(";");

            GraphView.GraphViewData[] graphViewDataSets = new GraphView.GraphViewData[heartrates.length];
            for (int i = 0; i < heartrates.length; i++) {
                try {
                    graphViewDataSets[i] = new GraphView.GraphViewData(i, Double.parseDouble(heartrates[i]));
                } catch(NumberFormatException e) {
                    e.printStackTrace();
                }
            }

            if(null != graphViewDataSets && graphViewDataSets.length > 0) {
                mGraphView = new BarGraphView(this, "");
                mGraphView.setShowHorizontalLabels(false);
                mGraphView.addSeries(new GraphViewSeries(graphViewDataSets)); // data

                mFrameLayout.removeAllViews();
                mFrameLayout.addView(mGraphView);
            }
        }
    }

    private void showToast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_LONG).show();
    }
}
