package cd.note.Thread;

import android.util.Log;

/**
 * 作者：chenda
 * 时间：2019/6/27:16:49
 * 邮箱：
 * 说明：
 */
public class ThreadSyncTest {

    private final static String TAG = "ThreadSyncTest";

    //同步方法：控制类成员的变量的访问
    //2013-01-19 00:51:19.577 10686-10710/cd.note D/ThreadSyncTest: enter syncFun1
    //2013-01-19 00:51:19.679 10686-10711/cd.note D/ThreadSyncTest: enter notSyncfun
    //2013-01-19 00:51:19.679 10686-10712/cd.note D/ThreadSyncTest: enter syncFun1
    //2013-01-19 00:51:24.578 10686-10710/cd.note D/ThreadSyncTest: exit syncFun1
    //2013-01-19 00:51:24.680 10686-10712/cd.note D/ThreadSyncTest: exit syncFun1
    //syncFun方法被synchronized修饰，tst1和tst2同时只能有一个变量获得锁，另一个等待锁
    //但是这时候另一个变量能访问非同步方法吗？答案是可以的
    //但是这时候另一个变量能访问其它同步方法吗？答案是可以的
    //2013-01-19 00:29:44.171 9538-9562/cd.note D/ThreadSyncTest: enter syncFun1
    //2013-01-19 00:29:44.275 9538-9563/cd.note D/ThreadSyncTest: enter notSyncfun
    //2013-01-19 00:29:44.276 9538-9564/cd.note D/ThreadSyncTest: enter syncFun2
    //2013-01-19 00:29:49.172 9538-9562/cd.note D/ThreadSyncTest: exit syncFun1
    //2013-01-19 00:29:49.276 9538-9564/cd.note D/ThreadSyncTest: exit syncFun2
    //这样的话syncFun1和syncFun2内部同时修改全局变量不就是线程不安全，新建一个全局变量
    public static void test(){
        final Tst tst1 = new Tst();
        final Tst tst2 = new Tst();
        final Tst tst3 = new Tst();

        Thread thread1 = new Thread(new Runnable() {
            @Override
            public void run() {
                tst1.syncFun1();
            }
        });
        Thread thread2 = new Thread(new Runnable() {
            @Override
            public void run() {
                tst2.notSyncfun();
            }
        });
        Thread thread3 = new Thread(new Runnable() {
            @Override
            public void run() {
                tst3.syncFun1();
            }
        });

        thread1.start();
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        thread2.start();
        thread3.start();
    }

    private static class Tst{
        public synchronized void syncFun1(){
            Log.d(TAG,"enter syncFun1");
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            Log.d(TAG,"exit syncFun1");
        }
        public synchronized void syncFun2(){
            Log.d(TAG,"enter syncFun2");
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            Log.d(TAG,"exit syncFun2");
        }

        public void notSyncfun(){
            Log.d(TAG,"enter notSyncfun");
        }
    }


    public static void test1(){
        final Tst1 tst1 = new Tst1();
        final Tst1 tst2 = new Tst1();

        Thread thread1 = new Thread(new Runnable() {
            @Override
            public void run() {
                while (true){
                    tst1.add();
                }
            }
        });
        Thread thread2 = new Thread(new Runnable() {
            @Override
            public void run() {
                while (true){
                    tst2.sub();
                }
            }
        });

        thread1.start();
        thread2.start();
    }

    //2013-01-19 00:45:28.460 10085-10119/cd.note D/ThreadSyncTest: count add : 4900
    //2013-01-19 00:45:28.460 10085-10119/cd.note D/ThreadSyncTest: count add : 4905
    //2013-01-19 00:45:28.460 10085-10120/? D/ThreadSyncTest: count sub : 4900
    //2013-01-19 00:45:28.461 10085-10119/? D/ThreadSyncTest: count add : 4910
    //4900~4910,线程不安全
    public static int count = 0;
    private static int step = 5;
    private static class Tst1{
        public synchronized void add(){
            count = count +step;
            Log.d(TAG,"count add : " + count);
        }
        public synchronized void sub(){
            count = count - step;
            Log.d(TAG,"count sub : " + count);
        }
    }
}
