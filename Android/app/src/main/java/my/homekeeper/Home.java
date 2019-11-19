package my.homekeeper;


import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.BottomNavigationView;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.io.IOException;

public class Home extends Fragment {
    final String TAG = "TAG+HomeFragment";
    Button alarmButton, turnOnButton, turnOffButton;
    TextView tempText, humText, dustText, lightBulbText, alarmText;
    CheckBox checkBox;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_home, container, false);
        Log.d(TAG, "Create Home Fragment onCreateView");

        lightBulbText = (TextView) view.findViewById(R.id.lightBulbText);
        alarmText = (TextView) view.findViewById(R.id.alarmText);
        tempText = (TextView) view.findViewById(R.id.tempText);
        humText = (TextView) view.findViewById(R.id.humText);
        dustText = (TextView) view.findViewById(R.id.dustText);

        alarmButton = (Button) view.findViewById(R.id.setAlarmTimeButton);
        turnOnButton = (Button) view.findViewById(R.id.turnOnButton);
        turnOffButton = (Button) view.findViewById(R.id.turnOffButton);

        checkBox = (CheckBox) view.findViewById(R.id.checkBox);

        tempText.setText(((MainActivity)MainActivity.context).sensorData[0] + " ℃");
        humText.setText(((MainActivity)MainActivity.context).sensorData[1] + " %");
        int dust = Integer.parseInt(((MainActivity)MainActivity.context).sensorData[2]);
        if(dust >= 0 && dust<=30) dustText.setTextColor(Color.BLUE);
        else if(dust >= 31 && dust<=80) dustText.setTextColor(Color.GREEN);
        else if(dust >= 81 && dust<=150) dustText.setTextColor(Color.parseColor("#EFC81E"));
        else if(dust >= 151) dustText.setTextColor(Color.RED);

        turnOnButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
                builder.setTitle("전등 ON");
                builder.setMessage("전등을 키시겠습니까?");
                builder.setPositiveButton("YES", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        new Thread() {
                            public void run() {
                                try {
                                    ((MainActivity)MainActivity.context).turnOn();
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        }.start();
                    }
                });
                builder.setNegativeButton("NO", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                    }
                });
                AlertDialog alertDialog = builder.create();
                alertDialog.show();
            }
        });
        turnOffButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
                builder.setTitle("전등 ON");
                builder.setMessage("전등을 끄시겠습니까?");
                builder.setPositiveButton("YES", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        try {
                            ((MainActivity)MainActivity.context).turnOff();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }

                    }
                });
                builder.setNegativeButton("NO", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                    }
                });
                AlertDialog alertDialog = builder.create();
                alertDialog.show();
            }
        });
        checkBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(checkBox.isChecked()) {
                    alarmButton.setVisibility(View.VISIBLE);
                }
                else {
                    alarmButton.setVisibility(View.INVISIBLE);
                }
            }
        });
        return view;
    }
}
