package cd.note.activity;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import java.lang.ref.ReferenceQueue;
import java.lang.ref.SoftReference;
import java.lang.ref.WeakReference;

import cd.libcorenote.LogUtil;
import cd.note.R;

public class JvmActivity extends AppCompatActivity {

    private static MyJvm myJvm = new MyJvm();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jvm);

        weakRef_enough();

        sofeRef_enough();
//        sofeRef_not_enough();

        referenceQueue();

    }



    static class MyJvm{
        public int test;
    }
    private void jvm(){                     //java方法是在栈区，是GC Root
        MyJvm myJvm1 = new MyJvm();         //对象Integer.valueOf(1)被这个方法引用
        MyJvm myJvm2 = myJvm1;

    }

    private static void weakRef_enough(){
        MyJvm myJvm = new MyJvm();
        WeakReference<MyJvm> softReference = new WeakReference<>(myJvm);
        LogUtil.d("myJvm.test="+myJvm.test);
        LogUtil.d("WeakReference.get().test="+softReference.get().test);

        myJvm=null;     //不再引用，
         Runtime.getRuntime().gc();

        LogUtil.d("myJvm"+myJvm);
        LogUtil.d("WeakReference.get()="+softReference.get());

    }

    private static void sofeRef_enough(){
        MyJvm myJvm = new MyJvm();
        SoftReference<MyJvm> softReference = new SoftReference<>(myJvm);
        LogUtil.d("myJvm.test="+myJvm.test);
        LogUtil.d("softReference.get().test="+softReference.get().test);

        myJvm=null;     //不再引用，但是内存够，不回收
         Runtime.getRuntime().gc();

        LogUtil.d("myJvm"+myJvm);
        LogUtil.d("softReference.get().test="+softReference.get().test);

    }

    private void referenceQueue(){
        Object o = new Object();
        ReferenceQueue<Object> referenceQueue = new ReferenceQueue<>();
        WeakReference<Object> weakReference = new WeakReference<Object>(o,referenceQueue);
        LogUtil.d("o="+o);
        LogUtil.d("weakReference.get()="+weakReference.get());
        LogUtil.d("referenceQueue.poll()="+referenceQueue.poll());

        o=null;

        Runtime.getRuntime().gc();
        try {
            Thread.sleep(1000);      //等待回收
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        LogUtil.d("o="+o);
        LogUtil.d("weakReference.get()="+weakReference.get());
        LogUtil.d("referenceQueue.poll()="+referenceQueue.poll());

    }

    private static void sofeRef_not_enough(){
        MyJvm myJvm = new MyJvm();
        SoftReference<MyJvm> softReference = new SoftReference<>(myJvm);
        LogUtil.d("myJvm.test="+myJvm.test);
        LogUtil.d("softReference.get().test="+softReference.get().test);

        myJvm=null;
//         Runtime.getRuntime().gc();  //

        try {
            byte[] bytes = new byte[1024*1024*500];    //申请大内存照成内存不够用，看GC会不会收MyJvm
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            LogUtil.d("myJvm="+myJvm);
            LogUtil.d("softReference.get()="+softReference.get());  //崩溃前打印是不是被回收了
        }
    }




}
