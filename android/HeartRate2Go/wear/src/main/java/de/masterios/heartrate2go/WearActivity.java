package de.masterios.heartrate2go;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.drawable.AnimationDrawable;
import android.os.Bundle;
import android.os.Vibrator;
import android.view.View;
import android.view.WindowManager;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

import de.masterios.heartrate2go.common.HeartRateData;
import de.masterios.heartrate2go.common.HeartRateDataManager;
import de.masterios.heartrate2go.common.MeasureMode;

public class WearActivity extends Activity implements SharedPreferences.OnSharedPreferenceChangeListener {

    private static final int RESULT_CODE_MEASURE_MODE = 1;
    private static final int RESULT_CODE_MOBILE_NOT_FOUND = 2;

    private static final int INACTIVE = 0;

    private static final int VIBRATION_LENGTH_MS = 100;
    private static final long[] VIBRATION_TRIPLE_PATTERN = {0
            , VIBRATION_LENGTH_MS
            , VIBRATION_LENGTH_MS
            , VIBRATION_LENGTH_MS
            , VIBRATION_LENGTH_MS
            , VIBRATION_LENGTH_MS }; // individual heartrate2go vibration pattern :)
    private static final int VIBRATION_INTERVAL_MS = 900000; // 15 minutes
    private static final int VIBRATION_INTERVAL_TOLERANCE = 1000; // 1 second


    @Override
    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
        showShortToast(getString(R.string.settings_changed));
        refreshSettings();
    }

    private enum State {
        STARTED, PAUSED, STOPPED
    }

    private Settings mSettings;
    private State mCurrentState;

    private ImageButton mImageButtonStop;
    private ImageButton mImageButtonPlayPause;
    private TextView mTextViewHeartRate;
    private TableRow mTableRowSteps;
    private TextView mTextViewSteps;
    private TableRow mTableRowTime;
    private TextView mTextViewTime;

    private SensorLogger mSensorLogger;
    private RunningTimer mRunningTimer;
    private RestTimer mRestTimer;
    private AnimationDrawable mHeartAnimation;
    private Vibrator mVibrator;

    private HeartRateDataManager mHeartRateDataManager;
    private HeartRateDataSync mHeartRateDataSync;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_wear);

        mSettings = new Settings(this);
        mSettings.getSharedPreferences().registerOnSharedPreferenceChangeListener(this);
        mVibrator = (Vibrator) getSystemService(VIBRATOR_SERVICE);

        initUiElements();

        initHeartRateDataManager();
        initSensorLogger(this);
        initRunningTimer();
        initRestTimer();

        refreshSettings();
    }

    private void setCurrentState(State state) {
        mCurrentState = state;
        refreshActionButtons();
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    private void refreshSettings() {
        if(null != mSettings) {
            if (mSettings.getKeepScreenOn()) {
                getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
            } else {
                getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
            }

            if (null != mSensorLogger) {
                mSensorLogger.setMeasureInterval(mSettings.getMeasureInterval());
            }
        }
    }

    private void initUiElements() {
        mCurrentState = State.STOPPED;

        ImageView animation = (ImageView) findViewById(R.id.image_view_animated_heart);
        animation.setBackgroundResource(R.drawable.animation_black);
        mHeartAnimation = (AnimationDrawable) animation.getBackground();

        mImageButtonPlayPause = (ImageButton) findViewById(R.id.image_button_start_pause);
        mImageButtonStop = (ImageButton) findViewById(R.id.image_button_stop);
        mTextViewHeartRate = (TextView) findViewById(R.id.text_view_heart_rate);
        mTableRowSteps = (TableRow) findViewById(R.id.table_row_steps);
        mTextViewSteps = (TextView) findViewById(R.id.text_view_steps);
        mTableRowTime = (TableRow) findViewById(R.id.table_row_time);
        mTextViewTime = (TextView) findViewById(R.id.text_view_time);

        refreshTextViewHeartRate(INACTIVE);
        refreshTextViewSteps(INACTIVE);
        refreshTextViewTime(INACTIVE);
        refreshActionButtons();
    }

    private void initSensorLogger(Context context) {
        mSensorLogger = new SensorLogger(context);
        mSensorLogger.setMeasureInterval(mSettings.getMeasureInterval());
        mSensorLogger.setSensorLoggerListener(new SensorLogger.SensorLoggerListener() {
            @Override
            public void onSensorLog(final int heartRate, final int steps) {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        refreshTextViewHeartRate(heartRate);
                        refreshTextViewSteps(steps);

                        if (State.STARTED == mCurrentState) {
                            HeartRateData heartRateData =
                                    new HeartRateData(System.currentTimeMillis(), heartRate, steps);
                            mHeartRateDataManager.add(heartRateData);
                        }
                    }
                });
            }
        });
    }

    private void initRunningTimer() {
        mRunningTimer = new RunningTimer();
        mRunningTimer.setRunningTimerListener(new RunningTimer.RunningTimerListener() {
            @Override
            public void onTimerUpdate(final long timeSpanMs) {

                boolean isVibratingActive = mSettings.getRememberVibration();
                boolean isNotFirstVibrate = timeSpanMs >= VIBRATION_INTERVAL_MS;
                boolean isVibratingTime = (timeSpanMs % VIBRATION_INTERVAL_MS < VIBRATION_INTERVAL_TOLERANCE);
                boolean isVibrating = isVibratingActive && isNotFirstVibrate && isVibratingTime;

                if (isVibrating) {
                    if (mVibrator.hasVibrator()) mVibrator.vibrate(VIBRATION_TRIPLE_PATTERN, -1);
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            showLongToast(getString(R.string.still_active));
                        }
                    });
                }

                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        refreshTextViewTime(timeSpanMs);
                    }
                });
            }
        });
    }

    private void initRestTimer() {
        mRestTimer = new RestTimer();
        mRestTimer.setRestTimerListener(new RestTimer.RestTimerListener() {
            @Override
            public void onTimerUpdate(final long timeSpanMs) {

                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        refreshTextViewTime(timeSpanMs);
                    }
                });
            }

            @Override
            public void onTimerFinished() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        stopLogging();
                        refreshTextViewHeartRate(INACTIVE);
                        refreshTextViewSteps(INACTIVE);
                        refreshTextViewTime(INACTIVE);
                        refreshActionButtons();
                    }
                });

                if(null != mHeartRateDataSync && null != mHeartRateDataManager) {
                    mHeartRateDataSync.sendMessageAsync(mHeartRateDataManager.getDataAsString());
                }
            }
        });
    }

    private void initHeartRateDataManager() {
        mHeartRateDataManager = HeartRateDataManager.getInstance();
        mHeartRateDataSync = HeartRateDataSync.getInstance(getBaseContext());
        mHeartRateDataSync.setSentMessageListener(new HeartRateDataSync.SentMessageListener() {
            @Override
            public void onMessageSent(Boolean sent) {
                if(sent) {
                    if (null != mHeartRateDataManager) {
                        mHeartRateDataManager.clear();
                    }
                } else {
                    Intent intent = new Intent(WearActivity.this, DialogMobileNotFoundActivity.class);
                    startActivityForResult(intent, RESULT_CODE_MOBILE_NOT_FOUND);
                }
            }
        });
    }

    private void refreshActionButtons() {
        switch(mCurrentState) {
            case STOPPED:
                mImageButtonPlayPause.setImageResource(R.drawable.play_white);
                mImageButtonPlayPause.setVisibility(View.VISIBLE);
                mImageButtonStop.setVisibility(View.GONE);
                break;
            case PAUSED:
                mImageButtonPlayPause.setImageResource(R.drawable.play_white);
                mImageButtonPlayPause.setVisibility(View.VISIBLE);
                mImageButtonStop.setVisibility(View.VISIBLE);
                break;
            case STARTED:
                if(MeasureMode.REST == mHeartRateDataManager.getMeasureMode()) {
                    mImageButtonPlayPause.setVisibility(View.GONE);
                    mImageButtonStop.setVisibility(View.VISIBLE);
                } else {
                    mImageButtonPlayPause.setImageResource(R.drawable.pause_white);
                    mImageButtonStop.setVisibility(View.VISIBLE);
                }
                break;
        }
    }

    private void startBackgroundAnimation() {
        if(null != mHeartAnimation) mHeartAnimation.start();
    }

    private void stopBackgroundAnimation() {
        if(null != mHeartAnimation) {
            mHeartAnimation.stop();
            mHeartAnimation.selectDrawable(0);
        }
    }

    public void onImageButtonStartPauseClick(View v) {
        switch(mCurrentState) {
            case STOPPED:
                Intent intent = new Intent(this, DialogModeActivity.class);
                startActivityForResult(intent, RESULT_CODE_MEASURE_MODE);
                break;
            case PAUSED:
                startLogging();
                break;
            case STARTED:
                pauseLogging();
                break;
        }
        refreshActionButtons();
    }

    public void onImageButtonStopClick(View v) {
        stopLogging();

        refreshTextViewHeartRate(INACTIVE);
        refreshTextViewSteps(INACTIVE);
        refreshTextViewTime(INACTIVE);
        refreshActionButtons();

        if(null != mHeartRateDataSync && null != mHeartRateDataManager) {
            mHeartRateDataSync.sendMessageAsync(mHeartRateDataManager.getDataAsString());
        }

        refreshActionButtons();
    }

    private void startLogging() {
        setCurrentState(State.STARTED);
        startBackgroundAnimation();

        if (null != mSensorLogger) mSensorLogger.start();

        switch(mHeartRateDataManager.getMeasureMode()) {
            case ACTIVITY:
                if (null != mRunningTimer) mRunningTimer.start();
                break;
            case REST:
                if (null != mRestTimer) mRestTimer.start();
                break;
        }
    }

    private void pauseLogging() {
        setCurrentState(State.PAUSED);
        stopBackgroundAnimation();

        if (null != mSensorLogger) mSensorLogger.pause();
        if (null != mRunningTimer) mRunningTimer.pause();
    }

    private void stopLogging() {
        setCurrentState(State.STOPPED);
        stopBackgroundAnimation();

        if (null != mSensorLogger) mSensorLogger.stop();

        switch(mHeartRateDataManager.getMeasureMode()) {
            case ACTIVITY:
                if (null != mRunningTimer) mRunningTimer.stop();
                break;
            case REST:
                if (null != mRestTimer) mRestTimer.stop();
                break;
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if(resultCode == RESULT_OK) {
            if(RESULT_CODE_MEASURE_MODE == requestCode) {
                int result = data.getExtras().getInt(DialogModeActivity.ACTIVITY_RESULT);
                switch(result) {
                    case DialogModeActivity.ACTIVITY:
                        mHeartRateDataManager.setMeasureMode(MeasureMode.ACTIVITY);
                        break;
                    case DialogModeActivity.REST:
                        mHeartRateDataManager.setMeasureMode(MeasureMode.REST);
                        break;
                }
                startLogging();

            } else if(RESULT_CODE_MOBILE_NOT_FOUND == requestCode) {
                int result = data.getExtras().getInt(DialogMobileNotFoundActivity.ACTIVITY_RESULT);

                switch(result) {
                    case DialogMobileNotFoundActivity.DISMISS:
                        if (null != mHeartRateDataManager) {
                            mHeartRateDataManager.clear();
                        }
                        break;
                    case DialogMobileNotFoundActivity.RETRY:
                        if (null != mHeartRateDataSync && null != mHeartRateDataManager) {
                            mHeartRateDataSync.sendMessageAsync(mHeartRateDataManager.getDataAsString());
                        }
                        break;
                }
            }
        }
    }

    private void refreshTextViewHeartRate(int heartRate) {
        if (null != mTextViewHeartRate) {
            if (State.STOPPED == mCurrentState) {
                mTextViewHeartRate.setVisibility(View.GONE);
            } else {
                mTextViewHeartRate.setVisibility(View.VISIBLE);
                if (0 == heartRate) {
                    mTextViewHeartRate.setText(getString(R.string.calibrating));
                } else {
                    mTextViewHeartRate.setText(heartRate + " " + getString(R.string.heart_rate_unit));
                }
            }
        }
    }

    private void refreshTextViewSteps(int steps) {
        if (null != mTextViewSteps && null != mTableRowSteps) {
            if (State.STOPPED == mCurrentState || MeasureMode.REST == mHeartRateDataManager.getMeasureMode()) {
                mTableRowSteps.setVisibility(View.GONE);
            } else {
                mTableRowSteps.setVisibility(View.VISIBLE);
                mTextViewSteps.setText(steps + " " + getString(R.string.steps));
            }
        }
    }

    private void refreshTextViewTime(long timeSpanMs) {
        if(null != mTextViewTime && null != mTableRowTime) {
            if(State.STOPPED == mCurrentState) {
                mTableRowTime.setVisibility(View.GONE);
            } else {
                String formattedTimeSpan = getFormattedTimeSpan(timeSpanMs);
                mTableRowTime.setVisibility(View.VISIBLE);
                mTextViewTime.setText(formattedTimeSpan);
            }
        }
    }

    private String getFormattedTimeSpan(long timeSpanMs) {
        int secondsOverall = (int) (timeSpanMs / 1000);
        int minutes = secondsOverall / 60;
        int seconds = secondsOverall % 60;

        return minutes + ":" + String.format("%02d", seconds);
    }

    private void showShortToast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    private void showLongToast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_LONG).show();
    }
}
