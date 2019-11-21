package my.homekeeper;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class AlarmReceiver extends BroadcastReceiver {
    Context context;
    String TAG = "TAG+AlarmReceiver";
    @Override
    public void onReceive(Context context, Intent intent) {
        this.context = context;
        Log.d(TAG, "AlarmReceiver");
        Intent in = new Intent(context, AlarmService.class);
        context.startService(in);
    }
}
