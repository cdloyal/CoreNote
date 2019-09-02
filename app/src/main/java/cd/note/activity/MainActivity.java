package cd.note.activity;

import android.app.ActivityManager;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
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

    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d(TAG,"MainActivity onDestroy()");
    }

    public void test(View view) {
        startActivity(new Intent(this,TestActivity.class));
    }

    public void handler(View view) {
        startActivity(new Intent(this,HandlerActivity.class));
    }
    public void okhttp(View view) {

        startActivity(new Intent(this,OkHttpActivity.class));
    }


}
