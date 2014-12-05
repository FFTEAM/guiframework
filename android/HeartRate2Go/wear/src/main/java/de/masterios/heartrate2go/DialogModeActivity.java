package de.masterios.heartrate2go;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class DialogModeActivity extends Activity implements View.OnClickListener {

    public final static String ACTIVITY_RESULT = "measure_mode";
    public final static int ACTIVITY = 1;
    public final static int REST = 2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_dialog_mode);
    }

    @Override
    public void onClick(View v) {
        Intent intent = getIntent();
        switch (v.getId()) {
            case R.id.button_activity:
                intent.putExtra(ACTIVITY_RESULT, ACTIVITY);
                break;
            case R.id.button_rest:
            default:
                intent.putExtra(ACTIVITY_RESULT, REST);
                break;
        }

        setResult(RESULT_OK, intent);
        finish();
    }
}
