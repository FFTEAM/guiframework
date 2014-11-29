package de.masterios.heartrate2go;

import android.app.Activity;
import android.content.Context;
import android.graphics.drawable.AnimationDrawable;
import android.os.Bundle;
import android.support.wearable.view.WatchViewStub;
import android.view.Gravity;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TableLayout;
import android.widget.TextView;

public class WearActivity extends Activity implements WatchViewStub.OnLayoutInflatedListener {

    private static final String TAG = "DataLayerWear";
    private static final int INACTIVE = -1;

    private enum State {
        STARTED, PAUSED, STOPPED
    }

    private State mCurrentState = State.STOPPED;

    private ImageButton mImageButtonPlayPause;
    private ImageButton mImageButtonStop;
    private TextView mTextViewHeartRate;
    private ImageView mImageViewSteps;
    private TextView mTextViewSteps;
    private ImageView mImageViewTime;
    private TextView mTextViewTime;

    private SensorLogger mSensorLogger;
    private RunningTimer mRunningTimer;
    private AnimationDrawable mHeartAnimation;

    private HeartRateDataManager mHeartRateDataManager;
    private HeartRateDataSync mHeartRateDataSync;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_wear);
        final WatchViewStub stub = (WatchViewStub) findViewById(R.id.watch_view_stub);
        stub.setOnLayoutInflatedListener(this);

        mHeartRateDataManager = HeartRateDataManager.getInstance();
        mHeartRateDataSync = HeartRateDataSync.getInstance(getBaseContext());
        mHeartRateDataSync.setSentMessageListener(new HeartRateDataSync.SentMessageListener() {
            @Override
            public void onMessageSent() {
                if(null != mHeartRateDataManager) {
                    mHeartRateDataManager.clear();
                }
            }
        });
    }

    @Override
    public void onLayoutInflated(WatchViewStub watchViewStub) {
        initUiElements(watchViewStub);
        initSensorLogger(watchViewStub.getContext());
        initRunningTimer();
    }

    private void initUiElements(WatchViewStub watchViewStub) {
        ImageView animation = (ImageView) watchViewStub.findViewById(R.id.image_view_animated_heart);
        mHeartAnimation = (AnimationDrawable) animation.getBackground();

        mImageButtonPlayPause = (ImageButton) watchViewStub.findViewById(R.id.image_button_start_pause);
        mImageButtonStop = (ImageButton) watchViewStub.findViewById(R.id.image_button_stop);
        mTextViewHeartRate = (TextView) watchViewStub.findViewById(R.id.text_view_heart_rate);
        mImageViewSteps = (ImageView) watchViewStub.findViewById(R.id.image_view_steps);
        mTextViewSteps = (TextView) watchViewStub.findViewById(R.id.text_view_steps);
        mImageViewTime = (ImageView) watchViewStub.findViewById(R.id.image_view_time);
        mTextViewTime = (TextView) watchViewStub.findViewById(R.id.text_view_time);

        initButtonPlayPause();
        initButtonStop();

        refreshTextViewHeartRate(0);
        refreshTextViewSteps(0);
        refreshTextViewTime(0);
    }

    private void setButtonToPlay() {
        mImageButtonPlayPause.setImageResource(R.drawable.play_white);
    }

    private void setButtonToPause() {
        mImageButtonPlayPause.setImageResource(R.drawable.pause_white);
    }

    private void startBackgroundAnimation() {
        mHeartAnimation.start();
    }

    private void stopBackgroundAnimation() {
        mHeartAnimation.stop();
        mHeartAnimation.selectDrawable(0);
    }

    private void initButtonPlayPause() {
        mImageButtonPlayPause.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                switch(mCurrentState) {
                    case STOPPED:
                    case PAUSED:
                        mCurrentState = State.STARTED;
                        setButtonToPause();
                        startBackgroundAnimation();

                        if (null != mSensorLogger) mSensorLogger.start();
                        if (null != mRunningTimer) mRunningTimer.start();
                        break;

                    case STARTED:
                        mCurrentState = State.PAUSED;
                        setButtonToPlay();
                        stopBackgroundAnimation();

                        if (null != mSensorLogger) mSensorLogger.stop();
                        if (null != mRunningTimer) mRunningTimer.pause();
                        break;
                }
            }
        });
    }



    private void initButtonStop() {
        mImageButtonStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mCurrentState = State.STOPPED;
                setButtonToPlay();
                stopBackgroundAnimation();

                if (null != mSensorLogger) mSensorLogger.stop();
                if (null != mRunningTimer) mRunningTimer.stop();

                refreshTextViewHeartRate(0);
                refreshTextViewSteps(0);
                refreshTextViewTime(0);

                if(null != mHeartRateDataSync && null != mHeartRateDataManager) {
                    mHeartRateDataSync.sendMessageAsync(mHeartRateDataManager.getCsvMapAsString());
                }
            }
        });
    }

    private void initSensorLogger(Context context) {
        mSensorLogger = new SensorLogger(context);
        mSensorLogger.setMeasureInterval(3); // TODO CONFIG
        mSensorLogger.setSensorLoggerListener(new SensorLogger.SensorLoggerListener() {
            @Override
            public void onSensorLog(final int heartRate, final int steps) {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        refreshTextViewHeartRate(heartRate);
                        refreshTextViewSteps(steps);

                        if(mCurrentState == State.STARTED) {
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
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        refreshTextViewTime(timeSpanMs);
                    }
                });
            }
        });
    }



    private void refreshTextViewHeartRate(int heartRate) {
        if (null != mTextViewHeartRate) {
            if (mCurrentState == State.STOPPED) {
                mTextViewHeartRate.setVisibility(View.INVISIBLE);
            } else {
                mTextViewHeartRate.setVisibility(View.VISIBLE);
                if (0 == heartRate) {
                    mTextViewHeartRate.setText("calibrating");
                } else {
                    mTextViewHeartRate.setText(heartRate + " bpm");
                }
            }
        }
    }

    private void refreshTextViewSteps(int steps) {
        if (null != mTextViewSteps && null != mImageViewSteps) {
            if (mCurrentState == State.STOPPED) {
                mImageViewSteps.setVisibility(View.INVISIBLE);
                mTextViewSteps.setVisibility(View.INVISIBLE);
            } else {
                mImageViewSteps.setVisibility(View.VISIBLE);
                mTextViewSteps.setVisibility(View.VISIBLE);
                mTextViewSteps.setText(steps + " steps");
            }
        }
    }

    private void refreshTextViewTime(long timeSpanMs) {
        if(null != mTextViewTime && null != mImageViewTime) {
            if(mCurrentState == State.STOPPED) {
                mImageViewTime.setVisibility(View.INVISIBLE);
                mTextViewTime.setVisibility(View.INVISIBLE);
            } else {
                String formattedTimeSpan = getFormattedTimeSpan(timeSpanMs);
                mImageViewTime.setVisibility(View.VISIBLE);
                mTextViewTime.setVisibility(View.VISIBLE);
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
}
