package de.masterios.heartrate2go;

import android.content.Context;
import android.os.Bundle;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.wearable.Node;
import com.google.android.gms.wearable.NodeApi;
import com.google.android.gms.wearable.Wearable;

import java.util.List;
import java.util.concurrent.TimeUnit;

public class HeartRateDataSync implements GoogleApiClient.OnConnectionFailedListener {

    private static final String SEND_MESSAGE_PATH = "/heartrate2go-message";
    private final static int CONNECTION_TIME_OUT_MS = 5000;

    private GoogleApiClient mGoogleApiClient;

    public interface SentMessageListener {
        public void onMessageSent();
    }

    private static HeartRateDataSync singleton;

    public static HeartRateDataSync getInstance(Context context) {
        if(null == singleton) {
            singleton = new HeartRateDataSync(context);
        }
        return singleton;
    }

    private HeartRateDataSync(Context context) {
        mGoogleApiClient = new GoogleApiClient.Builder(context)
                .addApi(Wearable.API)
                .addOnConnectionFailedListener(this)
                .build();
    }

    private SentMessageListener mSentMessageListener;
    public void setSentMessageListener(SentMessageListener sentMessageListener) {
        mSentMessageListener = sentMessageListener;
    }

    public void sendMessageAsync(final String text) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    ConnectionResult connectionResult =
                            mGoogleApiClient.blockingConnect(CONNECTION_TIME_OUT_MS, TimeUnit.MILLISECONDS);
                    if(connectionResult.isSuccess()) {
                        NodeApi.GetConnectedNodesResult result =
                                Wearable.NodeApi.getConnectedNodes(mGoogleApiClient).await();
                        List<Node> nodes = result.getNodes();
                        for (Node node : nodes) {
                            Wearable.MessageApi.sendMessage(mGoogleApiClient, node.getId(), SEND_MESSAGE_PATH, text.getBytes());
                        }

                        if (null != mSentMessageListener && nodes.size() > 0) {
                            mSentMessageListener.onMessageSent();
                        }

                        mGoogleApiClient.disconnect();
                    }
                }
            }).start();
    }

    @Override
    public void onConnectionFailed(ConnectionResult connectionResult) {
        if (connectionResult.getErrorCode() == ConnectionResult.API_UNAVAILABLE) {
            // The Android Wear app is not installed
        }
    }
}
