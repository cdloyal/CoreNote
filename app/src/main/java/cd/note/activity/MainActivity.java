package cd.note.activity;

import android.app.ActivityManager;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import java.util.List;

import cd.note.R;
import cd.note.Rxjava.RxjavaTest;
import cd.note.Thread.AsyncTaskTest;
import cd.note.Thread.HandlerTest;
import cd.note.Thread.ThreadPoolTest;
import cd.note.Thread.ThreadSync;
import cd.note.Thread.ThreadSyncTest;
import cd.note.designmode.Clone;
import cd.note.java8.Java8;
import cd.note.memory.MemoryTest;
import cd.note.others.CollectionTest;
import cd.note.others.GenericTest;
import cd.note.others.JniTest;
import cd.note.sqlite.SqliteTest;

public class MainActivity extends AppCompatActivity {

    private final static String TAG = MainActivity.class.getSimpleName();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d(TAG,"isRun(this,\"cd.note.activity.MainActivity\")="+isRun(this,"cd.note.activity.MainActivity"));
        Log.d(TAG,"isRun(this,\"cd.note.activity.HandlerActivity\")="+isRun(this,"cd.note.activity.HandlerActivity"));

    }

    public void test(View view) {
        startActivity(new Intent(this,TestActivity.class));
    }

    public void handler(View view) {
        startActivity(new Intent(this,HandlerActivity.class));
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d(TAG,"MainActivity onDestroy()");
    }







    //判断应用是否在前台运行
    public boolean isRunningForeground(Context context){
        String packageName=getPackageName(context);
        String topActivityClassName=getTopActivityName(context);
        System.out.println("packageName="+packageName+",topActivityClassName="+topActivityClassName);
        if (packageName!=null&&topActivityClassName!=null&&topActivityClassName.startsWith(packageName)) {
            System.out.println("应用在前台执行");
            return true;
        } else {
            System.out.println("应用在后台执行");
            return false;
        }
    }

    // 判断应用是否在运行
    public boolean isRun(Context context,String mPackageName){
        ActivityManager am = (ActivityManager)context.getSystemService(Context.ACTIVITY_SERVICE);
        List<ActivityManager.RunningTaskInfo> list = am.getRunningTasks(100);
        boolean isAppRunning = false;
        //100表示取的最大的任务数，info.topActivity表示当前正在运行的Activity，info.baseActivity表示系统后台有此进程在运行
        for (ActivityManager.RunningTaskInfo info : list) {
            if (info.topActivity.getPackageName().equals(mPackageName) || info.baseActivity.getPackageName().equals(mPackageName)) {
                isAppRunning = true;
                Log.i("ActivityService",info.topActivity.getPackageName() + " info.baseActivity.getPackageName()="+info.baseActivity.getPackageName());
                break;
            }
        }
        if(isAppRunning){
            Log.i("ActivityService", "该程序正在运行");
        }else{
            Log.i("ActivityService", "该程序没有运行");
        }
        return isAppRunning;
    }

    //获取栈顶ActivityName
    public  String getTopActivityName(Context context){
        String topActivityClassName=null;
        ActivityManager activityManager =
                (ActivityManager)(context.getSystemService(android.content.Context.ACTIVITY_SERVICE )) ;
        List<ActivityManager.RunningTaskInfo> runningTaskInfos = activityManager.getRunningTasks(1) ;
        if(runningTaskInfos != null){
            ComponentName f=runningTaskInfos.get(0).topActivity;
            topActivityClassName=f.getClassName();
        }
        return topActivityClassName;
    }

    public String getPackageName(Context context){
        String packageName = context.getPackageName();
        return packageName;
    }
}
