package my.homekeeper;

import android.app.AlarmManager;
import android.app.AlertDialog;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.TimePickerDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.support.v4.app.NotificationCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.TimePicker;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.net.Socket;
import java.util.Calendar;

public class MainActivity extends AppCompatActivity {

    final String TAG = "TAG+MainActivity";

    public InputStream dataInputStream;
    public OutputStream dataOutputStream;
    private Socket socket;
    private String ip = "121.153.150.157";
    private int port = 9999;

    String sensorData[] = {"0","0","0","0"};

    Thread thread;

    TextView dustText, tempText, humText;
    ImageButton lightButton, cctvButton, alarmButton, detectModeButton;
    static boolean detectModeActive = false;
    static boolean alarmActive = false;
    AlarmManager alarmManager;
    Intent alarmIntent;
    PendingIntent alarmPendingIntent;
    int alarmHour=0, alarmMinute=0;
    Calendar alarmCalendar;

    public static Context context;
    @Override
    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        context = this;
        dustText = (TextView) findViewById(R.id.dustText);
        tempText = (TextView) findViewById(R.id.tempText);
        humText = (TextView) findViewById(R.id.humText);
        lightButton = (ImageButton) findViewById(R.id.lightButton);
        cctvButton = (ImageButton) findViewById(R.id.cctvButton);
        alarmButton = (ImageButton) findViewById(R.id.alarmButton);
        detectModeButton = (ImageButton) findViewById(R.id.detectModeButton);

        if(detectModeActive == true) detectModeButton.setBackground(ContextCompat.getDrawable(MainActivity.this, R.drawable.activeoval));
        if(alarmActive == true) alarmButton.setBackground(ContextCompat.getDrawable(MainActivity.this, R.drawable.activeoval));

        lightButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                builder.setTitle("전등");
                builder.setMessage("");
                builder.setPositiveButton("On", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                try {
                                    turnOn();
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        }).start();
                    }
                });
                builder.setNegativeButton("Off", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                try {
                                    turnOff();
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        }).start();
                    }
                });
                AlertDialog alertDialog = builder.create();
                alertDialog.show();
            }
        });
        cctvButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), cctvActivity.class);
                startActivity(intent);
            }
        });
        alarmButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(alarmActive == false) {
                    TimePickerDialog timePickerDialog = new TimePickerDialog(MainActivity.this, TimePickerDialog.THEME_HOLO_LIGHT,new TimePickerDialog.OnTimeSetListener() {
                        @RequiresApi(api = Build.VERSION_CODES.M)
                        @Override
                        public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
                            alarmHour = hourOfDay;
                            alarmMinute = minute;
                            showAlarmNotify();
                            setAlarm();
                            alarmButton.setBackground(ContextCompat.getDrawable(MainActivity.this,R.drawable.activeoval));
                            alarmActive = true;
                        }
                    },alarmHour, alarmMinute, false);
                    timePickerDialog.show();


                } else {
                    alarmButton.setBackground(ContextCompat.getDrawable(MainActivity.this,R.drawable.oval));
                    alarmActive = false;
                }

            }

        });
        detectModeButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                if(detectModeActive == false) {
                    detectModeActive = true;
                    detectModeButton.setBackground(ContextCompat.getDrawable(MainActivity.this, R.drawable.activeoval));
                    Toast.makeText(getApplicationContext(),"감시모드가 활성화되었습니다.",Toast.LENGTH_LONG).show();
                } else {
                    detectModeActive = false;
                    detectModeButton.setBackground(ContextCompat.getDrawable(MainActivity.this, R.drawable.oval));
                }
            }
        });
        thread = new Thread(new Runnable() {
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
                        Log.d(TAG, "수신 대기");
                        bytes = dataInputStream.read(buffer);
                        Log.d(TAG, "byte = " + bytes);
                        String tmp = new String(buffer, 0, bytes);
                        Log.d(TAG,tmp);
                        sensorData = tmp.split(",");
                        tempText.setText(sensorData[0] + "℃");
                        humText.setText(sensorData[1] + "%");
                        dustText.setText(sensorData[2] + "㎍/㎥");
                        if(sensorData[3].equals("1") && detectModeActive == true) {
                            detectModeButton.setBackground(ContextCompat.getDrawable(MainActivity.this, R.drawable.oval));
                            detectModeActive =false;
                            showNotify();
                        }
                    } catch (IOException e) {
                        StringWriter stringWriter = new StringWriter();
                        e.printStackTrace(new PrintWriter(stringWriter));
                        Log.d(TAG,stringWriter.toString());
                    }
                }
            }
        });
        thread.start();
        // tcp 소켓 통신 수신 쓰레드
    }

    public void turnOn() throws IOException {
        byte[] inst = "On".getBytes();
        dataOutputStream.write(inst);
    }
    public void turnOff() throws IOException {
        byte[] inst = "Off".getBytes();
        dataOutputStream.write(inst);
    }
    public void showNotify() {
        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, "default");
        PendingIntent pendingIntent = PendingIntent.getActivity(getApplicationContext(),0, new Intent(getApplicationContext(), cctvActivity.class), PendingIntent.FLAG_UPDATE_CURRENT);
        builder.setSmallIcon(R.drawable.applogo);
        builder.setContentTitle("사람이 감지되었습니다.");
        builder.setContentText("CCTV를 확인하시겠습니까?");
        builder.setContentIntent(pendingIntent);
        builder.setAutoCancel(true);

        NotificationManager notificationManager = (NotificationManager) this.getSystemService(Context.NOTIFICATION_SERVICE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            notificationManager.createNotificationChannel(new NotificationChannel("default", "기본 채널", NotificationManager.IMPORTANCE_DEFAULT));
        }
        notificationManager.notify(1, builder.build());
    }
    public void showAlarmNotify() {
        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, "default");
        PendingIntent pendingIntent = PendingIntent.getActivity(getApplicationContext(),0, new Intent(getApplicationContext(), cctvActivity.class), PendingIntent.FLAG_UPDATE_CURRENT);
        builder.setSmallIcon(R.drawable.alarm);
        builder.setContentTitle("알람");
        builder.setOngoing(true);
        builder.setContentIntent(pendingIntent);

        if(alarmHour > 0 && alarmHour < 12)
            builder.setContentText("설정된 알람 시간은 오전 " + alarmHour + "시 " + alarmMinute + "분입니다.");
        else if(alarmHour == 12)
            builder.setContentText("설정된 알람 시간은 오후 " + alarmHour + "시 " + alarmMinute + "분입니다.");
        else if(alarmHour > 12 && alarmHour <24)
            builder.setContentText("설정된 알람 시간은 오후 " + (alarmHour-12) + "시 " + alarmMinute + "분입니다.");
        else if(alarmHour == 0)
            builder.setContentText("설정된 알람 시간은 오전 " + "0시 " + alarmMinute + "분입니다.");


        NotificationManager notificationManager = (NotificationManager) this.getSystemService(Context.NOTIFICATION_SERVICE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            notificationManager.createNotificationChannel(new NotificationChannel("default", "채널", NotificationManager.IMPORTANCE_DEFAULT));
        }
        notificationManager.notify(0, builder.build());
        Log.d(TAG,"show Alarm notify");
    }
    @RequiresApi(api = Build.VERSION_CODES.M)
    public void setAlarm() {
        alarmCalendar = Calendar.getInstance();
        alarmCalendar.setTimeInMillis(System.currentTimeMillis());
        alarmCalendar.set(Calendar.HOUR_OF_DAY,alarmHour);
        alarmCalendar.set(Calendar.MINUTE, alarmMinute);
        alarmCalendar.set(Calendar.SECOND, 0);

        if(alarmCalendar.before(Calendar.getInstance()))     alarmCalendar.add(Calendar.DATE, 1);

        alarmManager = (AlarmManager) getSystemService(Context.ALARM_SERVICE);
        alarmIntent = new Intent(getApplicationContext(), AlarmReceiver.class);
        alarmPendingIntent = PendingIntent.getBroadcast(MainActivity.this, 0, alarmIntent, PendingIntent.FLAG_UPDATE_CURRENT);
        alarmManager.setExactAndAllowWhileIdle(AlarmManager.RTC_WAKEUP, alarmCalendar.getTimeInMillis(), alarmPendingIntent);
    }
}
