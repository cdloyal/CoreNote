package cd.note.others;

import android.util.Log;

/**
 * 作者：chenda
 * 时间：2019/6/27:9:40
 * 邮箱：
 * 说明：多线程测试类
 */
public class ThreadTest {

    /**
     * 参考：https://segmentfault.com/a/1190000016197831?utm_source=tag-newest
     *
     * 首先了解的是线程状态
     * New：new Thread()后线程的状态就是新建。
     * Runnable：线程一旦调用start()方法，无论是否运行，状态都为Runable，注意Runable状态指示表示线程可以运行，不表示线程当下一定在运行，线程是否运行由虚拟机所在操作系统调度决定。
     * 被阻塞：线程试图获取一个内部对象的Monitor（进入synchronized方法或synchronized块）但是其他线程已经抢先获取，那此线程被阻塞，知道其他线程释放Monitor并且线程调度器允许当前线程获取到Monitor，此线程就恢复到可运行状态。
     * 等待：当一个线程等待另一个线程通知调度器一个条件时，线程进入等待状态。
     * 计时等待：和等待类似，某些造成等待的方法会允许传入超时参数，这类方法会造成计时等待，收到其他线程的通知或者超时都会恢复到可运行状态。
     * 被终止：线程执行完毕正常结束或执行过程中因未捕获异常意外终止都会是线程进入被终止状态。
     *
     * 新建--->可运行--->被终止
     * 新建--->可运行--->被阻塞--->可运行--->被终止
     * 新建--->可运行--->等待--->可运行--->被终止
     * 新建--->可运行--->计时等待--->可运行--->被终止
     *
     *
     *
     * */

    private final static String TAG = "ThreadTest";

    //新建--->可运行--->被终止
    public static void threadNNT(){
        Thread thread = new Thread(new Task());
        Log.d(TAG,thread.getName()+":"+thread.getState());

        thread.start();
        Log.d(TAG,thread.getName()+":"+thread.getState());

        try {
            thread.join();  //等待thread执行完毕
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        Log.d(TAG,thread.getName()+":"+thread.getState());
    }

    //新建--->可运行--->被阻塞--->可运行--->被终止
    public static void threadNNBNT(){
        Thread syncThread = new Thread(new SyncTask());
        syncThread.start();
        //确保syncThread先运行
        try {
            Thread.sleep(10);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        Thread thread = new Thread(new Task());
        Log.d(TAG,thread.getName()+":"+thread.getState());
        thread.start();
        Log.d(TAG,thread.getName()+":"+thread.getState());

//        while (true){
//            if(thread.getState()==Thread.State.BLOCKED){
//                Log.d(TAG,"thread.getState()==Thread.State.BLOCKED?"+(thread.getState()==Thread.State.BLOCKED));
//                break;
//            }
//        }
        while (thread.getState()!=Thread.State.BLOCKED){}

        Log.d(TAG,thread.getName()+":"+thread.getState());

        try {
            thread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Log.d(TAG,thread.getName()+":"+thread.getState());
    }

    private static final Object lock = new Object();
    private static class SyncTask implements Runnable{
        @Override
        public void run() {
            synchronized (lock){
                Log.d(TAG, Thread.currentThread().getName() + ":" + Thread.currentThread().getState());
                try {
                    Thread.sleep(5000);     //锁定一定时间
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    private static class Task implements Runnable{
        @Override
        public void run() {
            synchronized (lock) {
                Log.d(TAG, Thread.currentThread().getName() + ":" + Thread.currentThread().getState());
            }
        }
    }


}
