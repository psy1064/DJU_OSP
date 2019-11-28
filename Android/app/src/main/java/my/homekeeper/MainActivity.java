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
import android.graphics.Color;
import android.os.Build;
import android.os.Handler;
import android.os.Message;
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
import java.net.Socket;
import java.util.Calendar;

public class MainActivity extends AppCompatActivity {

    final String TAG = "TAG+MainActivity";

    /*public InputStream dataInputStream;
    public OutputStream dataOutputStream;
    private Socket socket;
    private String ip = "121.153.150.157";
    private int port = 9999;*/

    String sensorData[] = {"0","0","0","0"};

    tcpThread tcpThread;

    TextView dustText, tempText, humText;
    ImageButton lightButton, cctvButton, alarmButton, detectModeButton;
    static boolean detectModeActive = false;
    static boolean alarmActive = false;
    AlarmManager alarmManager;
    Intent alarmIntent;
    PendingIntent alarmPendingIntent, alarmCallPendingIntent, detectPendingIntent, dataPendingIntent;
    NotificationManager alarmNotification, detectNotification, dataNotification;
    int alarmHour=0, alarmMinute=0;
    Calendar alarmCalendar;

    public static Context context;
    @Override
    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
    protected void onCreate(Bundle savedInstanceState) {
        Log.d(TAG, "onCreate");
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


        final NotificationCompat.Builder builder = new NotificationCompat.Builder(getApplicationContext(), "default");
        Intent intent = new Intent(getApplicationContext(), notificationBroadcast.class);
        dataPendingIntent = PendingIntent.getBroadcast(getApplicationContext(),0,intent,PendingIntent.FLAG_UPDATE_CURRENT);

        builder.setSmallIcon(R.drawable.applogo);
        builder.setContentTitle("실내 환경 데이터");
        builder.setContentIntent(dataPendingIntent);
        builder.setContentText("온도 = 0 습도 = 0 미세먼지 = " );
        builder.setOngoing(true);
        dataNotification = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            dataNotification.createNotificationChannel(new NotificationChannel("default", "채널", NotificationManager.IMPORTANCE_LOW));
        }
        dataNotification.notify(0,builder.build());

        Handler handler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                String tmp = msg.obj.toString();
                sensorData = tmp.split(",");
                tempText.setText(sensorData[0] + " ℃");
                humText.setText(sensorData[1] + " %");
                int dust = Integer.parseInt(sensorData[2]);
                if(dust >= 0 && dust <=30) {
                    dustText.setTextColor(Color.BLUE);
                    dustText.setText("좋음 (" + sensorData[2] + "㎍/㎥)");
                    builder.setContentText("온도 = " + sensorData[0] + " ℃ 습도 = " + sensorData[1] + " % 미세먼지 농도 = 좋음 (" + sensorData[2] + "㎍/㎥)");
                } else if(dust >= 31 && dust <=80) {
                    dustText.setTextColor(Color.GREEN);
                    dustText.setText("보통 (" + sensorData[2] + "㎍/㎥)");
                    builder.setContentText("온도 = " + sensorData[0] + " ℃ 습도 = " + sensorData[1] + " % 미세먼지 농도 = 보통 (" + sensorData[2] + "㎍/㎥)");
                } else if(dust >= 81 && dust <=150) {
                    dustText.setTextColor(Color.parseColor("#FF7F00"));
                    dustText.setText("나쁨 (" + sensorData[2] + "㎍/㎥)");
                    builder.setContentText("온도 = " + sensorData[0] + " ℃ 습도 = " + sensorData[1] + " % 미세먼지 농도 = 나쁨 (" + sensorData[2] + "㎍/㎥)");
                } else if(dust >= 151) {
                    dustText.setTextColor(Color.RED);
                    dustText.setText("매우나쁨 (" + sensorData[2] + "㎍/㎥)");
                    builder.setContentText("온도 = " + sensorData[0] + " ℃ 습도 = " + sensorData[1] + " % 미세먼지 농도 = 매우나쁨 (" + sensorData[2] + "㎍/㎥)");
                }
                if(sensorData[3].equals("1") && detectModeActive == true) {
                    detectModeButton.setBackground(ContextCompat.getDrawable(MainActivity.this, R.drawable.oval));
                    detectModeActive =false;
                    showDetectNotify();
                }
                builder.setWhen(System.currentTimeMillis());
                dataNotification.notify(0,builder.build());
            }
        };

        tcpThread = new tcpThread(handler);
        tcpThread.start();
        // tcp 소켓 통신 수신 쓰레드
        lightButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                builder.setTitle("전등 제어");
                builder.setMessage("전등을 키시겠습니까? 끄시겠습니까?");
                builder.setPositiveButton("On", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                try {
                                    tcpThread.turnOn();
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
                                    tcpThread.turnOff();
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
                if(!alarmActive) {
                    TimePickerDialog timePickerDialog = new TimePickerDialog(MainActivity.this, TimePickerDialog.THEME_DEVICE_DEFAULT_LIGHT,new TimePickerDialog.OnTimeSetListener() {
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
                    alarmManager.cancel(alarmPendingIntent);
                    alarmNotification.cancel(2);
                    alarmActive = false;
                }

            }

        });
        detectModeButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                if(!detectModeActive) {
                    detectModeActive = true;
                    detectModeButton.setBackground(ContextCompat.getDrawable(MainActivity.this, R.drawable.activeoval));
                    Toast.makeText(getApplicationContext(),"감시모드가 활성화되었습니다.",Toast.LENGTH_LONG).show();
                } else {
                    detectModeActive = false;
                    detectModeButton.setBackground(ContextCompat.getDrawable(MainActivity.this, R.drawable.oval));
                }
            }
        });

    }

    @Override
    public void onBackPressed() {
        Log.d(TAG,"onBackPressed");
        Intent intent = new Intent(Intent.ACTION_MAIN);
        intent.addCategory(Intent.CATEGORY_HOME);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
    }



    public void showDetectNotify() {
        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, "1");
        detectPendingIntent = PendingIntent.getActivity(getApplicationContext(),0, new Intent(getApplicationContext(), cctvActivity.class), PendingIntent.FLAG_UPDATE_CURRENT);
        builder.setSmallIcon(R.drawable.applogo);
        builder.setContentTitle("사람이 감지되었습니다.");
        builder.setContentText("CCTV를 확인하시겠습니까?");
        builder.setContentIntent(detectPendingIntent);
        builder.setAutoCancel(true);

        detectNotification = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            detectNotification.createNotificationChannel(new NotificationChannel("1", "1", NotificationManager.IMPORTANCE_HIGH));
        }
        detectNotification.notify(1, builder.build());
    }
    public void showAlarmNotify() {
        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, "2");
        Intent intent = new Intent(getApplicationContext(), notificationBroadcast.class);
        alarmPendingIntent = PendingIntent.getBroadcast(getApplicationContext(),0,intent,PendingIntent.FLAG_UPDATE_CURRENT);
        builder.setSmallIcon(R.drawable.alarm);
        builder.setContentTitle("알람");
        builder.setOngoing(true);
        builder.setContentIntent(alarmPendingIntent);

        if(alarmHour > 0 && alarmHour < 12)
            builder.setContentText("설정된 알람 시간은 오전 " + alarmHour + "시 " + alarmMinute + "분입니다.");
        else if(alarmHour == 12)
            builder.setContentText("설정된 알람 시간은 오후 " + alarmHour + "시 " + alarmMinute + "분입니다.");
        else if(alarmHour > 12 && alarmHour <24)
            builder.setContentText("설정된 알람 시간은 오후 " + (alarmHour-12) + "시 " + alarmMinute + "분입니다.");
        else if(alarmHour == 0)
            builder.setContentText("설정된 알람 시간은 오전 " + "0시 " + alarmMinute + "분입니다.");


        alarmNotification = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            alarmNotification.createNotificationChannel(new NotificationChannel("2", "2", NotificationManager.IMPORTANCE_DEFAULT));
        }
        alarmNotification.notify(2, builder.build());
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
        alarmIntent = new Intent(getApplicationContext(), AlarmReceiver.class);
        alarmManager = (AlarmManager) getSystemService(Context.ALARM_SERVICE);
        alarmIntent.setAction(AlarmReceiver.ACTION_RESTART_SERVICE);
        alarmCallPendingIntent = PendingIntent.getBroadcast(MainActivity.this, 0, alarmIntent, PendingIntent.FLAG_UPDATE_CURRENT);
        alarmManager.setExactAndAllowWhileIdle(AlarmManager.RTC_WAKEUP, alarmCalendar.getTimeInMillis(), alarmCallPendingIntent);
    }

    @Override
    protected void onDestroy() {
        Log.d(TAG,"onDestroy");
        super.onDestroy();
    }

    @Override
    protected void onStop() {
        Log.d(TAG,"onStop");
        super.onStop();
    }
}
