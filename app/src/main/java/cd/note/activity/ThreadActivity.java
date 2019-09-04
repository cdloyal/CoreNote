package cd.note.activity;

import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import java.util.HashMap;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.Callable;
import java.util.concurrent.CompletionService;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorCompletionService;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.FutureTask;
import java.util.concurrent.LinkedBlockingDeque;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

import cd.libcorenote.LogUtil;
import cd.note.R;
import cd.note.bean.CountryEnum;

public class ThreadActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_thread);

    }


    public void visibility(View view) {
        /**
         * 验证volatile的保证可见性
         *  1、MyData.number不加volatile关键字
         *  2、MyData.number加上volatile关键字
         * */

        MyData myData = new MyData();
        new Thread(new Runnable() {
            @Override
            public void run() {
                LogUtil.d("Thread " + Thread.currentThread().getName() + " come in");
                try {
                    Thread.sleep(3000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                myData.addTO60();
                LogUtil.d("Thread " + Thread.currentThread().getName() + " update myData.number=" + myData.number);
            }
        }, "AAA").start();


        new Thread(new Runnable() {
            @Override
            public void run() {
                LogUtil.d(Thread.currentThread().getName() + " come in");
                while (myData.number == 0) {   //MyData.number不加volatile关键字,主线程不知道MyData.number被修改，可能一直死循环

                }

                LogUtil.d("Thread " + Thread.currentThread().getName() + " myData.number=" + myData.number);
            }
        }, "BBB").start();
    }

    public void automic(View view) {
        /**
         * 验证volatile的保证原子性
         *  不可分割，完整性，要么成功，要么失败
         *
         *  n个线程调用MyData.add()方法自加1000次，
         *  如果是原子性，两个线程同一时刻修改后的值不应该相同，最终结果应该是0+n*1000
         *
         * 2019-09-02 11:28:23.540 29872-29872/cd.note D/ThreadActivity.automic(Line:92): Thread main update myData.number=19941
         *
         * */

        MyData myData = new MyData();

        for (int i = 0; i < 20; i++) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    LogUtil.d("Thread " + Thread.currentThread().getName() + " come in");
                    int i = 0;
                    while (i < 1000) {
                        myData.add();
                        myData.atomicAdd();
                        i++;
                    }
//                    LogUtil.d("Thread "+Thread.currentThread().getName()+" update myData.number="+myData.number);
                }
            }, String.valueOf(i)).start();
        }

        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        while (Thread.activeCount() > 2) { //不严谨，有的线程已经结束,有的线程还没起来呢，刚好==1，上面加上一个延时
            Thread.yield();
        }

        LogUtil.d("Thread " + Thread.currentThread().getName() + " update myData.number=" + myData.number);
        LogUtil.d("Thread " + Thread.currentThread().getName() + " update myData.atonumber=" + myData.atonumber);
    }


    public void ABA(View view) {
        /**
         * ABA问题
         *
         * 线程one从主存取出A，线程two也从主存取出A，线程two将A改成了B，又将B改成了A,(A是对象的引用，重新改为A前，将A里的成员改变了)
         * 此时线程one的进行CAS操作发现内存中仍是A，认为没修改，那么线程one取出的A就是修改过后的A
         * */
        MyData A = new MyData();
        A.number = 1;
        MyData B = new MyData();
        B.number = 2;

        AtomicReference<MyData> atomicReference = new AtomicReference<>();
        atomicReference.set(A);

        new Thread(new Runnable() {
            @Override
            public void run() {
                atomicReference.compareAndSet(A, B); //这里线程one中间挂起了
            }
        }, "one").start();

        new Thread(new Runnable() {
            @Override
            public void run() {
                atomicReference.compareAndSet(A, B);
                A.number = 3;
                atomicReference.compareAndSet(B, A); //线程one重新获得CPU时间片段，此时的A其实已经被修改过
            }
        }, "two").start();


    }

    public void NonfairSync(View view) {
        /**
         * 公平锁：先来后到，排队，先来申请锁的先获得锁，order pocify
         * 非公平锁：需要竞争，可能造成优先级反转或者饥饿现象
         *
         * ReentrantLock默认非公平锁，吞吐量大
         *
         * synchronized也是一种非公平锁
         *
         * */

        ReentrantLock reentrantLock = new ReentrantLock();
        reentrantLock.lock();
        reentrantLock.unlock();
    }


    //原子线程引用
    AtomicReference<Thread> spinLock = new AtomicReference<>();

    private void spinLock() {
        Thread thread = Thread.currentThread();
        while (!spinLock.compareAndSet(null, thread)) {

        }
        LogUtil.d(Thread.currentThread().getName() + "获得锁");
    }

    private void spinUnlock() {
        Thread thread = Thread.currentThread();
        spinLock.compareAndSet(thread, null);
    }

    public void spinlock(View view) {

        new Thread(new Runnable() {
            @Override
            public void run() {
                spinLock();
                try {
                    Thread.sleep(5000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                spinUnlock();
            }
        }, "spinlock Thread 1").start();

        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                spinLock();

                spinUnlock();
            }
        }, "spinlock Thread 2").start();

    }

    ReentrantReadWriteLock readWriteLock = new ReentrantReadWriteLock();
    private HashMap<String, String> hashMap = new HashMap<>();

    public void writeLock(String key, String value) {
        readWriteLock.writeLock().lock();
        LogUtil.d("线程："+Thread.currentThread().getName() + "开始写入 key="+key);
        try {
            hashMap.put(key, value);
            Thread.sleep(30); //示例去掉读写锁，会不会被中断
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            LogUtil.d("线程："+Thread.currentThread().getName() + "写入完成 key="+key);
            readWriteLock.writeLock().unlock();
        }
    }

    public String readLock(String key) {
        String v = "";
        readWriteLock.readLock().lock();
        LogUtil.d("线程："+Thread.currentThread().getName() + "开始读取");
        try {
            v = hashMap.get(key);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            LogUtil.d("线程："+Thread.currentThread().getName() + "读取完成，key="+key);
            readWriteLock.readLock().unlock();
        }
        return v;
    }

    public void readwritelock(View view) {
        for (int i = 0; i < 20; i++) {
            int finalI = i;
            new Thread(new Runnable() {
                @Override
                public void run() {
                    writeLock("key"+ finalI,"value"+ finalI);
                }
            }, String.valueOf(i)).start();
        }
        for (int i = 0; i < 20; i++) {
            int finalI = i;
            new Thread(new Runnable() {
                @Override
                public void run() {
                    readLock("key"+ finalI);
                }
            }, String.valueOf(i)).start();
        }

    }

    public void countdownlatch(View view) {
        /**
         * 倒计时计数器
         * */

        CountDownLatch countDownLatch = new CountDownLatch(CountryEnum.values().length);

        for(int i=0;i<CountryEnum.values().length;i++){
            new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    LogUtil.d(Thread.currentThread().getName() + "国被秦国所灭");
                    countDownLatch.countDown();
                }
            },CountryEnum.forEach_CountryEnum(i+1).getCountry()).start();   //code从1开始
        }

        try {
            countDownLatch.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        LogUtil.d("-------秦灭六国，一统华夏-------");
    }

    public void cyclicbarrier(View view) {
        CyclicBarrier cyclicBarrier = new CyclicBarrier(5, new Runnable() {
            @Override
            public void run() {
                LogUtil.d(Thread.currentThread().getName() + "都跑完了");
            }
        });
        for(int i=0;i<5;i++){
            new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    LogUtil.d(Thread.currentThread().getName() + "跑完了");
                    try {
                        cyclicBarrier.await();
                    } catch (BrokenBarrierException e) {
                        e.printStackTrace();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            },"学生"+i).start();   //code从1开始
        }

    }

    public void semaphone(View view) {
        /**
         * 3个车位，n台车进来停车
         * */
        Semaphore semaphore = new Semaphore(3);
        for(int i=0;i<6;i++){
            new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        semaphore.acquire();
                        LogUtil.d(Thread.currentThread().getName() + "找到停车位");
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }finally {
                        semaphore.release();
                        LogUtil.d(Thread.currentThread().getName() + "离开停车位");
                    }
                }
            },"车"+i).start();   //code从1开始
        }
    }

    public void callable_feature(View view) {
        //Callable and FeatureTask
        AtomicInteger aaa= new AtomicInteger(444);
        Callable callable = (Callable<Integer>) () -> {LogUtil.d("Enter callable");return aaa.incrementAndGet();};
        FutureTask futureTask = new FutureTask<Integer>(callable);
        FutureTask futureTask1 = new FutureTask<Integer>(callable);
        new Thread(futureTask).start();
//        new Thread(futureTask).start(); //不会执行两次相同的task
        new Thread(futureTask1).start();

//        while (!futureTask.isDone()){
//
//        }
        try {
            LogUtil.d("futureTask.get()="+futureTask.get());
            LogUtil.d("futureTask1.get()="+futureTask1.get());
        } catch (ExecutionException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }


        AtomicInteger bbb= new AtomicInteger(555);
        ExecutorService executorService = Executors.newSingleThreadExecutor();
        Future feature = executorService.submit(() -> bbb.incrementAndGet());
        feature = executorService.submit(() -> bbb.incrementAndGet());
        executorService.
        try {
            LogUtil.d("feature.get()="+feature.get());
        } catch (ExecutionException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        executorService = Executors.newCachedThreadPool();
        CompletionService completionService = new ExecutorCompletionService(executorService);
        for(int i=0;i<5;i++){
            int finalI = i;
            completionService.submit(()->finalI);
        }
        for(int i=0;i<5;i++){
            try {
                LogUtil.d("completionService.take().get()="+completionService.take().get());        //按完成顺序排序
            } catch (ExecutionException e) {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        Executors.newFixedThreadPool()
        Executors.newCachedThreadPool()
        Executors.newSingleThreadExecutor()
    }

    private class MuchCond{
        /**
         * 线程1执行完，才能执行线程2;线程2执行完，才能执行线程3；线程3执行完，才能执行线程1；
         * */
        private int next = 1;   //下一个要执行的线程
        private ReentrantLock lock = new ReentrantLock();
        private Condition c1 = lock.newCondition();
        private Condition c2 = lock.newCondition();
        private Condition c3 = lock.newCondition();

        private void excute1(){     //线程1要干的事
            lock.lock();
            try {
                while (next!=1){
                    c1.await();
                }

                LogUtil.d(Thread.currentThread().getName() + "执行完");
                next = 2;       //下面两句关键
                c2.signal();
            }catch (Exception e){
                e.printStackTrace();
            }finally {
                lock.unlock();
            }
        }

        private void excute2(){     //线程2要干的事
            lock.lock();
            try {
                while (next!=2){
                    c2.await();
                }

                LogUtil.d(Thread.currentThread().getName() + "执行完");
                next = 3;
                c3.signal();
            }catch (Exception e){
                e.printStackTrace();
            }finally {
                lock.unlock();
            }
        }

        private void excute3(){     //线程3要干的事
            lock.lock();
            try {
                while (next!=3){
                    c3.await();
                }

                LogUtil.d(Thread.currentThread().getName() + "执行完");
                next = 1;
                c1.signal();
            }catch (Exception e){
                e.printStackTrace();
            }finally {
                lock.unlock();
            }
        }
    }

    public void muchcond(View view) {
        MuchCond muchCond = new MuchCond();

        new Thread(new Runnable() {
            @Override
            public void run() {
                muchCond.excute2();
            }
        },"线程2").start();

        new Thread(new Runnable() {
            @Override
            public void run() {
                muchCond.excute3();
            }
        },"线程3").start();
            new Thread(new Runnable() {
                @Override
                public void run() {
                        muchCond.excute1();
                }
            },"线程1").start();

    }


    private class ProdCons{
        LinkedBlockingDeque e;

        private volatile int rice = 0;   //煮了多少饭
        //原子性问题
        private AtomicInteger atomicRice = new AtomicInteger(0);   //煮了多少饭

        private ReentrantLock lock = new ReentrantLock();
        private Condition condition = lock.newCondition();

        public void cook(int add){      //要再煮多少饭
            rice += add;

            LogUtil.d(Thread.currentThread().getName() + ",煮了饭，rice="+rice);
        }
        public boolean eat(int cut){       //要吃多少饭
            if(rice-cut<0)
                return false;   //不够吃

            rice -=cut;
            LogUtil.d(Thread.currentThread().getName() + ",吃了饭，rice="+rice);
            return true;
        }

        public void cookLock(int add){      //要再煮多少饭
            lock.lock();
            try {
                rice += add;
                LogUtil.d(Thread.currentThread().getName() + ",煮了饭，rice="+rice);
                condition.signal();
            }catch (Exception e){
                e.printStackTrace();
            }finally {
                lock.unlock();
            }
        }
        public boolean eatLock(int cut){       //要吃多少饭
            lock.lock();
            try {
//                if(rice-cut<0)
//                    return false;   //不够吃,要加condition
                while (rice-cut<0){
                    condition.await();
                }

                rice -=cut;
                LogUtil.d(Thread.currentThread().getName() + ",吃了饭，rice="+rice);

            }catch (Exception e){
                e.printStackTrace();
            }finally {
                lock.unlock();
            }
            return true;
        }

        public void atomicCook(int add){      //要再煮多少饭
//            LogUtil.d(Thread.currentThread().getName() + ",煮了饭，atomicRice="+atomicRice.addAndGet(add)); //打印会延后
            atomicRice.addAndGet(add);
        }
        public void atomicEat(int cut){
//            LogUtil.d(Thread.currentThread().getName() + ",吃了饭，atomicRice="+atomicRice.addAndGet(-cut));    //<0,没有condition
            int temp;
            while (!((temp=atomicRice.get())>cut) && !atomicRice.compareAndSet(temp,temp-cut)){     //这个就是自旋

            }
//            LogUtil.d(Thread.currentThread().getName() + ",吃了饭，atomicRice="+(temp-cut));
        }



    }

    public void prodConsumer(View view) {
        ProdCons prodCons = new ProdCons();
        for(int i=0;i<6;i++){
            new Thread(new Runnable() {
                @Override
                public void run() {
//                    while (!prodCons.eat(5));
//                    prodCons.atomicEat(5);
                    prodCons.eatLock(5);
                }
            },"人"+i).start();   //code从1开始
        }

        for(int i=0;i<6;i++){
            new Thread(new Runnable() {
                @Override
                public void run() {
//                    prodCons.cook(5);
//                    prodCons.atomicCook(5);
                    prodCons.cookLock(5);
                }
            },"人"+i).start();   //code从1开始
        }

        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

//        LogUtil.d("剩下多少饭?"+prodCons.atomicRice.get());

    }


    class MyData {


        volatile int number = 0;

        public void addTO60() {
            this.number = 60;
        }

        public void add() {
            this.number++;
        }

        volatile int atonumber = 0;
        AtomicInteger atomicInteger = new AtomicInteger(atonumber);

        public void atomicAdd() {
            atonumber = atomicInteger.incrementAndGet();

//            while (!atomicInteger.compareAndSet(0,1)){ //==0代表没有被锁住
//            }
//            this.atonumber++;
//            atomicInteger.set(0);
        }

    }
}
