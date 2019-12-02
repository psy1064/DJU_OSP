package my.homekeeper;

import android.media.MediaPlayer;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;
import com.ebanx.swipebtn.OnStateChangeListener;
import com.ebanx.swipebtn.SwipeButton;

import java.io.IOException;
import java.util.Calendar;

public class AlarmActivity extends AppCompatActivity {
    Calendar calendar;
    RelativeLayout relativeLayout;
    SwipeButton swipeButton;
    TextView timeText;
    MediaPlayer mediaPlayer;
    Button alarmButton;
    boolean flag = true;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_alarm);
        calendar = Calendar.getInstance();
        relativeLayout = (RelativeLayout) findViewById(R.id.background);
        swipeButton = (SwipeButton) findViewById(R.id.swipe_btn);
        timeText = (TextView) findViewById(R.id.time);

        ((MainActivity)MainActivity.context).alarmButton.setBackgroundResource(R.drawable.oval);
        ((MainActivity)MainActivity.context).alarmManager.cancel(((MainActivity)MainActivity.context).alarmPendingIntent);
        ((MainActivity)MainActivity.context).alarmNotification.cancel(2);

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON
                | WindowManager.LayoutParams.FLAG_DISMISS_KEYGUARD
                | WindowManager.LayoutParams.FLAG_TURN_SCREEN_ON
                | WindowManager.LayoutParams.FLAG_SHOW_WHEN_LOCKED);
        // 잠금 화면 위로 activity 띄워줌

        mediaPlayer = MediaPlayer.create(getApplicationContext(),R.raw.beep);
        mediaPlayer.setLooping(true);
        mediaPlayer.start();
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    ((MainActivity)MainActivity.context).tcpThread.turnOn();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();

        new Thread(new Runnable() {
            @Override
            public void run() {
                while (flag == true) {
                    try {
                        calendar = Calendar.getInstance();
                        if (calendar.get(Calendar.HOUR_OF_DAY) > 0 && calendar.get(Calendar.HOUR_OF_DAY) < 12) {
                            timeText.setText("AM " + calendar.get(Calendar.HOUR_OF_DAY) + "시 " + calendar.get(Calendar.MINUTE) + "분 " + calendar.get(Calendar.SECOND) + "초");
                        } else if (calendar.get(Calendar.HOUR_OF_DAY) == 12) {
                            timeText.setText("PM " + calendar.get(Calendar.HOUR_OF_DAY) + "시 " + calendar.get(Calendar.MINUTE) + "분 " + calendar.get(Calendar.SECOND) + "초");
                        } else if (calendar.get(Calendar.HOUR_OF_DAY) > 12 && calendar.get(Calendar.HOUR_OF_DAY) < 24) {
                            timeText.setText("PM " + (calendar.get(Calendar.HOUR_OF_DAY) - 12) + "시 " + calendar.get(Calendar.MINUTE) + "분 " + calendar.get(Calendar.SECOND) + "초");
                        } else if (calendar.get(Calendar.HOUR_OF_DAY) == 0) {
                            timeText.setText("AM 0시 " + calendar.get(Calendar.MINUTE) + "분 " + calendar.get(Calendar.SECOND) + "초");
                        }
                        Thread.sleep(1000);
                    } catch (InterruptedException ex) {}
                }
            }
        }).start();

        swipeButton.setOnStateChangeListener(new OnStateChangeListener() {
            @Override
            public void onStateChange(boolean active) {
                mediaPlayer.stop();
                flag=false;
                finish();
            }
        });
    }
}
