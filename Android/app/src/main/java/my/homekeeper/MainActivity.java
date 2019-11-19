package my.homekeeper;

import android.content.Context;
import android.graphics.Color;
import android.support.annotation.NonNull;
import android.support.design.widget.BottomNavigationView;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MenuItem;
import android.widget.Toast;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    BottomNavigationView bottomNavigationView;
    private FragmentManager fragmentManager = getSupportFragmentManager();

    private Home homeFragment = new Home();
    private CCTV cctvFragment = new CCTV();

    final String TAG = "TAG+MainActivity";

    public InputStream dataInputStream;
    public OutputStream dataOutputStream;
    private Socket socket;
    private String ip = "121.153.150.157";
    private int port = 9999;
    String sensorData[] = {"0","0","0","0"};
    public static Context context;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        context = this;

        Log.d(TAG,"Create MainActivity");

        bottomNavigationView = (BottomNavigationView) findViewById(R.id.nav_view);
        bottomNavigationView.setSelectedItemId(R.id.navigation_home);

        FragmentTransaction transaction = fragmentManager.beginTransaction();           // 첫 화면 지정
        transaction.replace(R.id.frameLayout, homeFragment).commitAllowingStateLoss();

        new Thread(new Runnable() {
            @Override
            public void run() {
                try{
                    socket = new Socket(ip,port);
                    dataInputStream = socket.getInputStream();
                    dataOutputStream = socket.getOutputStream();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                byte[] buffer = new byte[1024];
                int bytes;
                Log.d(TAG, "수신 시작");
                while(true) {
                    try {
                        Log.d(TAG, "수신 시작");
                        bytes = dataInputStream.read(buffer);
                        Log.d(TAG, "byte = " + bytes);
                        String tmp = new String(buffer, 0, bytes);
                        Log.d(TAG,tmp);
                        sensorData = tmp.split(",");

                        homeFragment.tempText.setText(sensorData[0] + " ℃");
                        homeFragment.humText.setText(sensorData[1] + " %");
                        homeFragment.dustText.setText(sensorData[2] + " μg/m³");
                        int dust = Integer.parseInt(sensorData[2]);
                        if(dust >= 0 && dust<=30) homeFragment.dustText.setTextColor(Color.BLUE);
                        else if(dust >= 31 && dust<=80) homeFragment.dustText.setTextColor(Color.GREEN);
                        else if(dust >= 81 && dust<=150) homeFragment.dustText.setTextColor(Color.parseColor("#EFC81E"));
                        else if(dust >= 151) homeFragment.dustText.setTextColor(Color.RED);
                        if(sensorData[3] == "1") {

                        }
                    } catch (IOException e) {
                        StringWriter stringWriter = new StringWriter();
                        e.printStackTrace(new PrintWriter(stringWriter));
                        Log.d(TAG,stringWriter.toString());
                    }
                }
            }
        }).start();

        bottomNavigationView.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                FragmentTransaction transaction = fragmentManager.beginTransaction();
                switch (item.getItemId()) {
                    case R.id.navigation_home: {
                        transaction.replace(R.id.frameLayout, homeFragment).commitAllowingStateLoss();
                        break;
                    }
                    case R.id.navigation_cctv: {
                        transaction.replace(R.id.frameLayout, cctvFragment).commitAllowingStateLoss();
                        break;
                    }
                }
                return true;
            }
        }); // Navigation Bar 리스너
    }

    @Override
    protected void onRestart() {
        bottomNavigationView.setSelectedItemId(R.id.navigation_home);
        super.onRestart();
        Log.d(TAG, "onRestart");
    } // 어플 다시 로딩 시 처음 fragment로 전환


    public void turnOn() throws IOException {
        byte[] inst = "On".getBytes();
        dataOutputStream.write(inst);
    }
    public void turnOff() throws IOException {
        byte[] inst = "Off".getBytes();
        dataOutputStream.write(inst);
    }
}


