package de.masterios.heartrate2go;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class DialogMobileNotFoundActivity extends Activity implements View.OnClickListener {

    public final static String ACTIVITY_RESULT = "mobile_not_found_behavior";
    public final static int DISMISS = 1;
    public final static int RETRY = 2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_dialog_mobile_not_found);
    }

    @Override
    public void onClick(View v) {
        Boolean isActivityMeasure;

        Intent intent = getIntent();
        switch (v.getId()) {
            case R.id.button_dismiss:
                intent.putExtra(ACTIVITY_RESULT, DISMISS);
                break;
            case R.id.button_rest:
            default:
                intent.putExtra(ACTIVITY_RESULT, RETRY);
                break;
        }

        setResult(RESULT_OK, intent);
        finish();
    }
}
