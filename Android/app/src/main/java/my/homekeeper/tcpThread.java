package my.homekeeper;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Build;
import android.os.Handler;
import android.support.v4.app.NotificationCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class tcpThread extends Thread{
    public InputStream dataInputStream;
    public OutputStream dataOutputStream;
    private Socket socket;
    private String ip = "121.153.150.157";
    private int port = 9999;
    final String TAG = "TAG+Thread";
    Handler handler;

    public tcpThread(Handler handler) {
        this.handler = handler;
    }

    @Override
    public void run() {
        try {
            socket = new Socket(ip, port);
            dataOutputStream = socket.getOutputStream();
            dataInputStream = socket.getInputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }
        byte[] buffer = new byte[1024];
        int bytes;
        Log.d(TAG, "수신 시작");
        while(true) {
            try {
                Log.d(TAG, "수신 대기");
                bytes = dataInputStream.read(buffer);
                Log.d(TAG, "byte = " + bytes);
                String tmp = new String(buffer, 0, bytes);
                Log.d(TAG,tmp);
                handler.obtainMessage(0,tmp).sendToTarget();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    public void turnOn() throws IOException {
        byte[] inst = "On".getBytes();
        dataOutputStream.write(inst);
    }
    public void turnOff() throws IOException {
        byte[] inst = "Off".getBytes();
        dataOutputStream.write(inst);
    }
}

