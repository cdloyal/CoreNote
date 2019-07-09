package cd.note.Thread;

import android.util.Log;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.RejectedExecutionHandler;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * 作者：chenda
 * 时间：2019/7/9:13:53
 * 邮箱：
 * 说明：线程池使用
 */
public class ThreadPoolTest {

    /**
     * https://www.jianshu.com/p/f030aa5d7a28
     * https://www.cnblogs.com/zhujiabin/p/5404771.html
     *
     * Exc
     * FixThreadPool
     * CachedThreadPool
     * ScheduledThreadPool
     * SingleThreadPool
     * */

    private final static String TAG = "ThreadPoolTest";

    public void test(){
        int corePoolSize = 2;
        int maximumPoolSize = 4;
        long keepAliveTime = 10;
        TimeUnit unit = TimeUnit.SECONDS;
        BlockingQueue<Runnable> workQueue = new LinkedBlockingQueue<>(2);
        ThreadFactory threadFactory = new ThreadFactory() {
            //原子整形
            AtomicInteger atomicInteger = new AtomicInteger(1);
            @Override
            public Thread newThread(Runnable r) {
                Thread thread = new Thread(r,"my-thread-"+atomicInteger.getAndIncrement());
                Log.d(TAG,thread.getName()+" has been created");
                return thread;
            }
        };
        RejectedExecutionHandler handler = new RejectedExecutionHandler() {
            @Override
            public void rejectedExecution(Runnable r, ThreadPoolExecutor executor) {
                Log.d(TAG,r.toString()+" rejected!");
            }
        };

        ThreadPoolExecutor threadPoolExecutor = new ThreadPoolExecutor(corePoolSize,maximumPoolSize,keepAliveTime,unit,workQueue,threadFactory,handler);
        Log.d(TAG,"threadPoolExecutor create");
        Log.d(TAG,"threadPoolExecutor.getActiveCount()="+threadPoolExecutor.getActiveCount());

        threadPoolExecutor.prestartAllCoreThreads();    //预启动所有核心线程
        Log.d(TAG,"threadPoolExecutor.prestartAllCoreThreads()");
        Log.d(TAG,"threadPoolExecutor.getActiveCount()="+threadPoolExecutor.getActiveCount());

        for (int i=0;i<10;i++){
            MyRunnable myRunnable = new MyRunnable(String.valueOf(i));
            threadPoolExecutor.execute(myRunnable);
            Log.d(TAG,"threadPoolExecutor.getActiveCount()="+threadPoolExecutor.getActiveCount());
        }


        // shutDown 不在接受新的线程，并且等待之前提交的线程都执行完在关闭，
        // shutDownNow 直接关闭活跃状态的所有的线程 ， 并返回等待中的线程   可能会抛出异常
        threadPoolExecutor.shutdown();
        Log.d(TAG,"threadPoolExecutor.shutdown()");
        Log.d(TAG,"threadPoolExecutor.getActiveCount()="+threadPoolExecutor.getActiveCount());
    }

    private class MyRunnable implements Runnable{
        private String name;
        public MyRunnable(String name) {
            this.name = name;
        }

        @Override
        public void run() {
            Log.d(TAG,toString()+" is running!");
            try {
                Thread.sleep(3000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        @Override
        public String toString() {
            return "MyTask [name="+name+"]";
        }
    }

}
