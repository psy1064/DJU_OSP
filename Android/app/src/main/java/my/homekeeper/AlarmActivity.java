package my.homekeeper;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.WindowManager;

import java.io.IOException;

public class AlarmActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_alarm);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON
                | WindowManager.LayoutParams.FLAG_DISMISS_KEYGUARD
                | WindowManager.LayoutParams.FLAG_TURN_SCREEN_ON
                | WindowManager.LayoutParams.FLAG_SHOW_WHEN_LOCKED);
        // 잠금 화면 위로 activity 띄워줌

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    ((MainActivity)MainActivity.context).turnOn();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }
}
