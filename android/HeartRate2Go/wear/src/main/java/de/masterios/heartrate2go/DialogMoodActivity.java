package de.masterios.heartrate2go;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class DialogMoodActivity extends Activity implements View.OnClickListener {

    public final static String ACTIVITY_RESULT = "measure_mood";
    public final static int GOOD = 1;
    public final static int AVERAGE = 2;
    public final static int BAD = 3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_dialog_mood);
    }

    @Override
    public void onClick(View v) {
        Intent intent = getIntent();
        switch (v.getId()) {
            case R.id.button_good:
                intent.putExtra(ACTIVITY_RESULT, GOOD);
                break;
            case R.id.button_bad:
                intent.putExtra(ACTIVITY_RESULT, BAD);
                break;
            case R.id.button_average:
            default:
                intent.putExtra(ACTIVITY_RESULT, AVERAGE);
                break;
        }

        setResult(RESULT_OK, intent);
        finish();
    }
}
