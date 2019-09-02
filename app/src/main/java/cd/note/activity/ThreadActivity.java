package cd.note.activity;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

import cd.libcorenote.LogUtil;
import cd.note.R;

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
                LogUtil.d("Thread "+Thread.currentThread().getName()+" come in");
                try {
                    Thread.sleep(3000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                myData.addTO60();
                LogUtil.d("Thread "+Thread.currentThread().getName()+" update myData.number="+myData.number);
            }
        },"AAA").start();


        new Thread(new Runnable() {
            @Override
            public void run() {
                LogUtil.d(Thread.currentThread().getName()+" come in");
                while (myData.number==0){   //MyData.number不加volatile关键字,主线程不知道MyData.number被修改，可能一直死循环

                }

                LogUtil.d("Thread "+Thread.currentThread().getName()+" myData.number="+myData.number);
            }
        },"BBB").start();
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

        for(int i=0;i<20;i++){
            new Thread(new Runnable() {
                @Override
                public void run() {
                    LogUtil.d("Thread "+Thread.currentThread().getName()+" come in");
                    int i=0;
                    while (i<1000){
                        myData.add();
                        myData.atomicAdd();
                        i++;
                    }
//                    LogUtil.d("Thread "+Thread.currentThread().getName()+" update myData.number="+myData.number);
                }
            },String.valueOf(i)).start();
        }

        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        while (Thread.activeCount()>2){ //不严谨，有的线程已经结束,有的线程还没起来呢，刚好==1，上面加上一个延时
            Thread.yield();
        }

        LogUtil.d("Thread "+Thread.currentThread().getName()+" update myData.number="+myData.number);
        LogUtil.d("Thread "+Thread.currentThread().getName()+" update myData.atonumber="+myData.atonumber);
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
                atomicReference.compareAndSet(A,B); //这里线程one中间挂起了
            }
        },"one").start();

        new Thread(new Runnable() {
            @Override
            public void run() {
                atomicReference.compareAndSet(A,B);
                A.number = 3;
                atomicReference.compareAndSet(B,A); //线程one重新获得CPU时间片段，此时的A其实已经被修改过
            }
        },"two").start();

    }


    class MyData{
        volatile int number = 0;

        public void addTO60(){
            this.number=60;
        }
        public  void add(){
            this.number++;
        }

        volatile int atonumber = 0;
        AtomicInteger atomicInteger = new AtomicInteger(atonumber);
        public void atomicAdd(){
            atonumber = atomicInteger.incrementAndGet();


//            while (!atomicInteger.compareAndSet(0,1)){ //==0代表没有被锁住
//            }
//            this.atonumber++;
//            atomicInteger.set(0);
        }

    }
}
