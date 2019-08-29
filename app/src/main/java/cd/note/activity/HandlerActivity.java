package cd.note.activity;

import android.app.Activity;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import java.lang.ref.WeakReference;

import cd.note.R;

public class HandlerActivity extends AppCompatActivity {


    /**
     * 进程新建Activity a引用 -> Activity实体Acti，正常退出时，a.ondestroy()，a==null，系统回收Acti实体
     * ondestroy()，不代表被回收了。
     *
     * https://www.jianshu.com/p/804e774d9f76
     *
     * OnClickListener是匿名内部类为什么不导致android内存泄漏
     * https://blog.csdn.net/changqijihua/article/details/80951927
     *
     * 内存泄漏还是跟生命周期有关，生命周期长的A引用生命周期短的B，在B已经结束生命周期了需要释放时没有释放还被A引用着，导致B不能被GC就出现了内存泄漏。
     * 所以Handler不在子线程或者子线程生命周期已经结束，是没有问题的。
     *
     * ②为何handler要定义为static？
     * 因为静态内部类不持有外部类的引用，所以使用静态的handler不会导致activity的泄露
     * ③为何handler要定义为static的同时，还要用WeakReference 包裹外部类的对象？
     * 这是因为我们需要使用外部类的成员，可以通过"activity. "获取变量方法等，如果直接使用强引用，显然会导致activity泄露。
     *
     *
     */
    private final static String TAG = HandlerActivity.class.getSimpleName();

    private final MyHandler handler = new MyHandler(this);

    private static class MyHandler extends Handler {
        WeakReference<Activity> weakReference;

        public MyHandler(Activity activity) {
            super();
            weakReference = new WeakReference<>(activity);
        }

        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);

            Activity activity = weakReference.get();
            Log.d(TAG, "WeakReference activity=" + activity);
//            startActivity(new Intent(HandlerActivity.this, TestActivity.class));
        }
    }

    private class MyRunnable implements Runnable {
        WeakReference<Activity> weakReference;

        public MyRunnable(Activity activity) {
            super();
            weakReference = new WeakReference<>(activity);
        }

            public void run() {
                try {
                    Thread.sleep(20000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                handler.sendEmptyMessage(0);
            }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_handler);

        new Thread(new MyRunnable(this)).start();

//        handler.sendEmptyMessageDelayed(0, 3000);

//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                try {
//                    Thread.sleep(20000);
//                } catch (InterruptedException e) {
//                    e.printStackTrace();
//                }
//                handler.sendEmptyMessage(0);
//            }
//        }).start();
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d(TAG, "HandlerActivity onDestroy()");
    }
}
