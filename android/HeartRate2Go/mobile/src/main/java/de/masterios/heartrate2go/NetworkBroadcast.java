package de.masterios.heartrate2go;

import android.content.Context;
import android.net.DhcpInfo;
import android.net.wifi.WifiManager;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class NetworkBroadcast {

    private static final String APPLICATION_IDENTIFIER = "86417ce4-4f19-4a59-ae27-f404653e9751";
    private static final int LOCAL_PORT = 45455;
    private static final int REMOTE_PORT = 45454;
    private static final int TIMEOUT_MS = 5000;

    BroadcastFinishedListener mBroadcastFinishedListener;
    public interface BroadcastFinishedListener {
        public void onBroadcastFinished(InetAddress from, String answer);
    }
    public void setBroadcastFinishedListener(BroadcastFinishedListener broadcastFinishedListener) {
        mBroadcastFinishedListener = broadcastFinishedListener;
    }

    Context mContext;

    public NetworkBroadcast(Context context) {
        mContext = context;
    }

    public InetAddress getBroadcastAddress() throws IOException {
        WifiManager wifi = (WifiManager) mContext.getSystemService(Context.WIFI_SERVICE);
        DhcpInfo dhcp = wifi.getDhcpInfo();
        // handle null somehow

        int broadcast = (dhcp.ipAddress & dhcp.netmask) | ~dhcp.netmask;
        byte[] quads = new byte[4];
        for (int k = 0; k < 4; k++)
            quads[k] = (byte) ((broadcast >> k * 8) & 0xFF);
        return InetAddress.getByAddress(quads);
    }

    public void sendBroadcastAsync() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                DatagramSocket socket = null;
                String answer = null;
                InetAddress from = null;
                byte[] buf = new byte[1024];
                DatagramPacket packet_inc = new DatagramPacket(buf, buf.length);

                try {
                    socket = new DatagramSocket(LOCAL_PORT);
                    socket.setSoTimeout(TIMEOUT_MS);
                    socket.setReuseAddress(true);

                    InetAddress adr = getBroadcastAddress(); // TODO ?
                    System.out.println(adr.getHostAddress());
                    socket.setBroadcast(true);
                    DatagramPacket packet_out =
                            new DatagramPacket(APPLICATION_IDENTIFIER.getBytes(), APPLICATION_IDENTIFIER.getBytes().length, adr, REMOTE_PORT);
                    socket.send(packet_out);
                    socket.receive(packet_inc);

                    answer = new String(packet_inc.getData());
                    from = packet_inc.getAddress();

                } catch (SocketException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                } finally {
                    if(null != socket) {
                        socket.close();
                    }
                }

                if(null != mBroadcastFinishedListener) {
                    mBroadcastFinishedListener.onBroadcastFinished(from, answer);
                }
            }
        }).start();
    }
}