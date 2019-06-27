package cd.note.Thread;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/6/27 20:28
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/6/27 20:28
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class ThreadSync {

    //计算机中为什么会出现线程不安全的问题
    /**
     * https://www.cnblogs.com/kubidemanong/p/9505944.html
     * a = t + 1;
     * CPU执行速度很快，而cpu从内存中读取、写入数据很慢
     * CPU从内存中读取数据存在高速缓存中，待计算完毕，再重新写入内存
     * 在多线程环境先，每条线程都有自己的高速缓存，这时就会出现同一个变量在两个高速缓存中的值不一致问题了。
     *
     * Java内存模型规定所有的变量都是存在主存当中（类似于前面说的物理内存），每个线程都有自己的工作内存（类似于前面的高速缓存）。线程对变量的所有操作都必须在工作内存中进行，而不能直接对主存进行操作。并且每个线程不能访问其他线程的工作内存。
     * 由于java中的每个线程有自己的工作空间，这种工作空间相当于上面所说的高速缓存，因此多个线程在处理一个共享变量的时候，就会出现线程安全问题。
     *
     * 重点：代码重排序
     *
     * volatile关键字保证：1、可见性和2、有序性；
     *
     * volatile解决多线程内存不可见问题。对于一写多读，是可以解决变量同步问题，但是如果多写，同样无法解决线程安全问题。
     * 运算结果并不依赖变量的当前值
     * */

    //多线程的情况
    //1、同一个人同时从多个媒介（支付宝、微信）取钱，不同媒介不同线程
    //2、很多个人同时一起取钱，不同人不同线程
    //可以写一个单例，钱作为这个单例的全局变量，因为只有一个对象，对钱的操作方法同步即可
    //也可以静态变量+静态同步方法
    //假如这个钱是第三方的库，对钱的操作没有同步，那么人得到的是钱的对象引用，
    //上面1这种情况，同一个人也是只有一个对象，在人操作钱同步方法
    //上面2这种情况，需要同步类
    //注意静态变量和传进来的对象引用，修改静态变量和传进来的对象引用，同步类

    //1. 普通同步方法（实例方法），锁是当前实例对象 ，进入同步代码前要获得当前实例的锁
    //2. 静态同步方法，锁是当前类的class对象 ，进入同步代码前要获得当前类对象的锁
    //3. 同步方法块，锁是括号里面的对象，对给定对象加锁，进入同步代码库前要获得给定对象的锁。 特别主要括号里面的对象会不会被改变
    public static void test1(){
        final MoneyUtil moneyUtil = MoneyUtil.getInstance();

        Thread thread1 = new Thread(new Runnable() {
            @Override
            public void run() {
                for(int i=0;i<=10;i++)
                    moneyUtil.addMoney(100);
            }
        });
        Thread thread2 = new Thread(new Runnable() {
            @Override
            public void run() {
                for(int i=0;i<=10;i++)
                    moneyUtil.subMoney(100);
            }
        });
        thread1.start();
        thread2.start();
    }


}
