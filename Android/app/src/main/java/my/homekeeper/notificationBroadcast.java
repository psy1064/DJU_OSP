package my.homekeeper;

import android.app.ActivityManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import java.util.List;

public class notificationBroadcast extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        ActivityManager am = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        List<ActivityManager.RunningTaskInfo> tasks = am.getRunningTasks(Integer.MAX_VALUE);
        if (!tasks.isEmpty()) {
            int tasksSize = tasks.size();
            for (int i = 0; i < tasksSize; i++) {
                ActivityManager.RunningTaskInfo taskinfo = tasks.get(i);
                if (taskinfo.topActivity.getPackageName().equals(context.getApplicationContext().getPackageName())) {
                    am.moveTaskToFront(taskinfo.id, 0);
                }
            }
        }
    }
}
