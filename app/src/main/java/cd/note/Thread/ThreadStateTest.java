package cd.note.Thread;

import android.util.Log;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * 作者：chenda
 * 时间：2019/6/27:9:40
 * 邮箱：
 * 说明：多线程状态测试类
 */
public class ThreadStateTest {

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
     * 新建--->可运行--->计时等待--->可运行--->被终止      进入等待状态，等待通知或者超时后进入可运行状态
     *
     *
     * 实际上，yield()方法对应了如下操作： 先检测当前是否有相同优先级的线程处于同可运行状态，如有，则把 CPU 的占有权交给此线程，
     * 否则继续运行原来的线程。所以yield()方法称为“退让”，它把运行机会让给了同等优先级的其他线程。
     *
     * 线程结束方法：1、使用标志位；2、使用interrupt()中断线程；3、使用stop方法（弃用）
     * if(Thread.currentThread().isInterrupted()){
     *      break;  //退出循环
     * }
     *
     * */

    private final static String TAG = "ThreadStateTest";

    //新建--->可运行--->被终止
    public static void threadNNT(){
        Log.d(TAG,"enter threadNNT");
        Thread thread = new Thread(new Task());
        Log.d(TAG,thread.getName()+":"+thread.getState());

        thread.start();
        Log.d(TAG,thread.getName()+":"+thread.getState());

        try {
            thread.join();  //等待thread执行完毕，Join方法实现原理是通过wait方法， 当main线程调用Thread.join()时，main线程会获得线程对象的锁，调用该对象的wait()，直到该对象唤醒main线程 。
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        Log.d(TAG,thread.getName()+":"+thread.getState());
    }

    //新建--->可运行--->被阻塞--->可运行--->被终止
    public static void threadNNBNT(){
        Log.d(TAG,"enter threadNNBNT");
        Thread syncThread = new Thread(new SyncTask());
        syncThread.start();
        //确保syncThread先运行,先获得锁
        try {
//            Thread.sleep(10);   //时间太短，不保证先运行
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        Thread thread = new Thread(new Task());
        Log.d(TAG,thread.getName()+":"+thread.getState());
        thread.start();
        Log.d(TAG,thread.getName()+":"+thread.getState());

        while (true){
            if(thread.getState()==Thread.State.BLOCKED){
                Log.d(TAG,"thread.getState()==Thread.State.BLOCKED?"+(thread.getState()==Thread.State.BLOCKED));
                break;
            }
        }
//        while (thread.getState()!=Thread.State.BLOCKED){}

        Log.d(TAG,thread.getName()+":"+thread.getState());

        try {
            thread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Log.d(TAG,thread.getName()+":"+thread.getState());
    }


    //wait()方法：新建--->可运行--->等待--->可运行--->被终止
    public static void threadNNWNT_wait(){
        Log.d(TAG,"enter threadNNWNT_wait");
        Thread waitThread = new Thread(new WaitTask());
        Log.d(TAG,waitThread.getName()+":"+waitThread.getState());
        waitThread.start();
        Log.d(TAG,waitThread.getName()+":"+waitThread.getState());

        while (true){
            if(waitThread.getState()==Thread.State.WAITING){
                Log.d(TAG,"thread.getState()==Thread.State.WAITING?"+(waitThread.getState()==Thread.State.WAITING));
                break;
            }
        }

        synchronized (lock){
            lock.notify();
        }

        try {
            waitThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Log.d(TAG,waitThread.getName()+":"+waitThread.getState());

    }

    //Lock.Condition.await()方法：新建--->可运行--->等待--->可运行--->被终止
    private  static Lock reentrantLock = new ReentrantLock();
    private static Condition condition = reentrantLock.newCondition();
    public static void threadNNBNT_lockwait(){
        Log.d(TAG,"enter threadNNBNT_lockwait");
        Thread waitThread = new Thread(new LockWait());
        Log.d(TAG,waitThread.getName()+":"+waitThread.getState());
        waitThread.start();
        Log.d(TAG,waitThread.getName()+":"+waitThread.getState());

        while (true){
            if(waitThread.getState()==Thread.State.WAITING){
                Log.d(TAG,"thread.getState()==Thread.State.WAITING?"+(waitThread.getState()==Thread.State.WAITING));
                break;
            }
        }

        reentrantLock.lock();
        try{
            condition.signal();
        }finally {
            reentrantLock.unlock();
        }

        try {
            waitThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Log.d(TAG,waitThread.getName()+":"+waitThread.getState());
    }
    public static class LockWait implements Runnable{
        @Override
        public void run() {
            reentrantLock.lock();
            try {
                try {
                    condition.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                Log.d(TAG, Thread.currentThread().getName() + ":" + Thread.currentThread().getState());
            }finally {
                reentrantLock.unlock();
            }
        }
    }

    //新建--->可运行--->计时等待--->可运行--->被终止


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

    private static class WaitTask implements Runnable{
        @Override
        public void run() {
            synchronized (lock) {
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                Log.d(TAG, Thread.currentThread().getName() + ":" + Thread.currentThread().getState());
            }
        }
    }
}
