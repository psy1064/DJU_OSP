package my.homekeeper;

import android.support.annotation.NonNull;
import android.support.design.widget.BottomNavigationView;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MenuItem;

public class MainActivity extends AppCompatActivity {
    BottomNavigationView bottomNavigationView;

    private FragmentManager fragmentManager = getSupportFragmentManager();

    private Home homeFragment = new Home();
    private CCTV cctvFragment = new CCTV();

    final String TAG = "TAG+MainActivity";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d(TAG,"Create MainActivity");
        bottomNavigationView = findViewById(R.id.nav_view);
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
}
