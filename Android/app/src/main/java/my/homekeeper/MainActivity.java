package my.homekeeper;

import android.content.Context;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.support.design.widget.BottomNavigationView;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInput;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    BottomNavigationView bottomNavigationView;
    private FragmentManager fragmentManager = getSupportFragmentManager();

    private Home homeFragment = new Home();
    private CCTV cctvFragment = new CCTV();

    final String TAG = "TAG+MainActivity";

    public DataInputStream dataInputStream;
    public DataOutputStream dataOutputStream;
    private Socket socket;
    private String readData;

    public static Context context;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        context = this;

        Log.d(TAG,"Create MainActivity");

        ConnectThread connectThread = new ConnectThread();
        connectThread.start();

        bottomNavigationView = (BottomNavigationView) findViewById(R.id.nav_view);
        bottomNavigationView.setSelectedItemId(R.id.navigation_home);

        FragmentTransaction transaction = fragmentManager.beginTransaction();           // 첫 화면 지정
        transaction.replace(R.id.frameLayout, homeFragment).commitAllowingStateLoss();

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
        Toast.makeText(getApplicationContext(), "lampOn", Toast.LENGTH_LONG).show();
        try {
            dataOutputStream.writeUTF("On");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public void turnOff() throws IOException {
        Toast.makeText(getApplicationContext(), "lampOff", Toast.LENGTH_LONG).show();
        try {
            dataOutputStream.writeUTF("Off");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    class ConnectThread extends Thread {
        String hostname;
        int port;
        public ConnectThread() {
            hostname = "121.153.150.157";
            port = 9999;
        }
        public void run() {
            try{
                socket = new Socket(hostname, port);
                dataInputStream = new DataInputStream(socket.getInputStream());
                dataOutputStream = new DataOutputStream(socket.getOutputStream());
                while(true) {
                    Log.d(TAG, "Listening");
                    try{
                        readData = dataInputStream.readUTF();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                }
                // socket.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
