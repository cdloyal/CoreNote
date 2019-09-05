package cd.note.activity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import cd.note.R;

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


    public void Thread(View view) {
        startActivity(new Intent(this,ThreadActivity.class));
    }

    public void jvm(View view) {
        startActivity(new Intent(this,JVM.class));
    }
}
