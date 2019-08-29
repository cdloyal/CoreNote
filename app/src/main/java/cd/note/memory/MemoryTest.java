package cd.note.memory;

import android.util.Log;

/**
 * 作者：chenda
 * 时间：2019/6/28:9:34
 * 邮箱：
 * 说明：
 */
public class MemoryTest {

    //https://blog.csdn.net/shanshan_1117/article/details/80391597
    /**
     * 面试的时候可以先讲C语言的内存管理
     * 初始化不为0的静态变量和全局变量，放在data段
     * 初始化为0或者没有初始化的静态变量和全局变量，放在bss段
     * 局部变量放在栈上
     * new、malloc、relloc初始化的变量放在堆中
     * 对于放在堆中的变量要及时free或delete
     *
     * 内存泄漏：本该被程序回收的对象不能被收回，还停留在堆内存中，导致内存泄漏
     * 内存溢出：Android系统为每个APP申请的内存有限；内存泄漏会导致内存溢出
     *
     * 1、资源对象没有关闭引起的泄漏
     *      在Activity申请的资源，这些资源持有Activity的引用，在Activity销毁时，
     *      由于这些资源任持有Activity的引用，而不能销毁Activity，导致内存溢出
     *      图片资源Bitmap、BraodcastReceive、文件流IO、数据库游标cursor、动画、线程等。
     *
     * 强引用、弱引用、软引用、虚引用的概念、及内存泄漏
     * https://www.jianshu.com/p/8614aa3fbf09
     *
     * 强引用导致的内存泄漏
     *      A a = new A();
     *      B b = new B();
     *      b.a = a;
     *      a = null;
     *
     * 匿名类导致的泄漏：匿名AsyncTsk、匿名Handler、匿名Thread、匿名TimerTask、匿名Runnable
     *
     * 单例
     *
     * 非静态内部类作为静态变量
     *
     * 解决方案1：弱引用+静态内部类
     *
     * 解决方案2：在onDestory的时候，手动清除Message
     *
     *
     * https://www.jianshu.com/p/9745a9375191
     * bitmap优化
     * 内存抖动
     *
     * */

    private final static String TAG = "MemoryTest";
    public void test(){

        A a1 = new A();
        a1.num = 10;
        A a2 = a1;
        a1.num = 11;
        Log.d(TAG,"MemoryTest a2.num="+a2.num);

        int i1 =1;
        int i2 = i1;
        i1 = 2;
        Log.d(TAG,"MemoryTest i2="+i2);

        A a = new A();
        B b = new B();
        a.num = 5;
        b.a = a;
        a = null;
        Log.d(TAG,"b.a.num="+b.a.num);
    }

    private class A{
        public int num;
        A(){};
        A(A a){
            Log.d(TAG,"A(A a)");
            this.num = a.num;
        }
    }

    private class B{
        public A a;
        private String s;
    }
}
