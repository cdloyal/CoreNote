CoreNote项目是一个用来学习的项目，包含设计模式、数据结构、算法、以及java特性等等知识


=================================================多线程==================================================
线程状态
create--可运行--获得锁、获得CPU时间片段运行态--终止
create--可运行--未获得锁进入阻塞态--获得CPU时间片段运行态--终止
create--可运行--等待其它线程执行完--获得CPU时间片段运行态--终止


为什么会线程不安全
可见性
原子性
指令重排
开始举例子说明
解决方法
可见性、指令重排可以用volatile解决
原子性不可以用
原子性可以用原子变量解决
为什么
原子变量的内部实现是通过Unsafe变量jni直接写主内存中的变量，而且写操作的时候是原子性的

示例：cd.note.activity.ThreadActivity

1、Volatile  volatile是java虚拟机提供的轻量级的同步机制
​    保证可见性
​    不保证原子性
​    禁止指令重排

JVM(java虚拟机)
JMM(java内存模型)

JMM：是抽象概念并不真实存在，是一组规范或规则，通过这组规范定义了程序中各个变量
（包括示例字段，静态字段和构成数组对象的元素）的访问方式

JMM关于同步的规定
​    1、线程解锁前，必须把共享变量的值刷新回主内存
​    2、线程加锁前，必须读取主内存的最新值到自己的工作内存
​    3、加锁解锁是同一把锁
这个规定就是要求程序：可见性、原子性、有序性


硬盘<内存<CPU
​    CPU到内存间还有缓存


JVM运行程序的实体是线程，每个线程创建时JVM都会为其创建一个工作内存
每个线程的工作内存都是私有数据区域，不可以共享
而我们程序的所有变量都存在主内存当中，主内存的变量是可以共享的。
线程对变量的操作，将主内存的变量拷贝到自己的工作内存，修改这个变量后，
再将这个变量写回到主内存。
线程间的通信必须通过主内存来完成。

可见性：线程将自己修改的值写回到主内存后，其它线程马上知道该变量被修改了

原子性：不可分割，完整性，要么成功，要么失败。1000张票，20窗口售票，
​        非原子性可能3个线程同时售出1张票，理论总票数要减3，却只减了1.
​        n--;每条从主内存取值、计算、返回主内存，同时取值，同时修改，同时返回

        解决方法：1、synchronized
                 2、AtomicInteger

指令重排:
​    源代码--编译器优化重排--指令并行重排--内存系统重排--最终执行指令重排

数据依赖性
fun(){
​    int a = 1;  //语句1
​    int b = 2;  //语句2
​    a = a * a;  //语句3
​    b = a + 6;  //语句4
}
编译器优化顺序可以：1234、2134、1324


int a=b=x=y=0;
线程1                     线程2
x=a;                      y=b;
b=1;                      a=2;
同时执行输出结果，x=0;y=0
假如编译器优化后，语句顺序改变
线程1                     线程2
b=1;                      a=2;
x=a;                      y=b;
同时执行输出结果，x=2;y=1

多线程环境中线程交替执行，由于编译器优化重排的存在，
两个线程中使用的变量能否保证一致性是无法确定的，结果无法预测
public class ResortSeqDemo{
​    int a = 0
​    boolean flag = false;

    public void method1(){
        a = 1;              //指令重排的结果有可能这两句指令顺序调转
        flag = true;        //指令重排后，多线程环境下，假如一个线程先执行了flag = true;
                            //a=1;未来得及执行，另一个线程执行了method2();输出的结果就是a=5;而不是=6
                            //和存钱是不是一样
                            //volatile 写屏障，禁止将volatile变量前的普通写操作放到volatile写操作后
                            //volatile 读屏障，禁止将volatile变量后的普通读操作放到volatile读操作后
    }
    
    public void method2(){
        if(flag){
            a = a+5;
            log.d(a);
        }
    }
}


看单例cd.note.designmode.SingleTon，双端检测的情况下，加个volatile
new一个对象分3步
​    memory = allocate();    //分配内存空间
​    instance(memory);       //初始化对象
​    instance = memory;      //设置instance指向刚分配的内存地址

步骤2和步骤3不存在数据依赖关系，
重排后步骤2和步骤3调转，
执行完步骤instance!=null,但实际上未初始化，
多线程环境下，有的线程可能就得到了未初始化对象，这个未初始化对象里的成员数据就可能是乱的


原子变量
2、CAS：compare and swap   比较并交换
​    java线程操作的是工作内存的拷贝变量，
​    我们的原子类（AtomicInteger）类里有Integer变量，AtomicInteger类在实例化的时候回计算得到Integer变量在主存中的地址
​    UnSafe类通过jni直接读取和修改这个地址的值。
​    Java不能直接修改内存的值，C可以

    public final int getAndIncrement(){
        return unsafe.getAndAddInt(this,valueOffset,1);
    }
    
    getAndAddInt(this,valueOffset,1){                       //分为两步了，多线程下读和写之间可能，读和写步连续
        int var5;                                           //compareAndSwapInt()，你给我的值var5和主内存相等的时候才修改
        do{                                                 //var5是在你自己线程中获得的。
            var5 = getIntVolatile(this,valueOffset);        //get出来
        }while(!compareAndSwapInt(var1,var2,var5,var5+1));  //再修改，要确保修改的时候，我要返回的值没有被修改
                                                            //假如上面用synchronized，就不用while
                                                            //ABA问题说明compareAndSwapInt()还不是原子的？
        return var5;
    }

CAS是一条CPU并发原语，执行过程是连续的，不允许被中断。

为什么用CAS，不用synchronized


CAS缺点：
​    循环时间长、开销大，上例修改前先获得目前的值，比较不成功就要循环，比较成功才修改，修改后返回当前值
​    ABA问题

原子引用    AtomicReference<V>
 CAS --- UnSafe --- CAS底层思想 --- ABA问题 --- 原子引用问题 --- 如何规避ABA问题
​    线程one从主存取出A，线程two也从主存取出A，线程two将A改成了B，又将B改成了A,(A是对象的引用，重新改为A前，将A里的成员改变了)
​    此时线程one的进行CAS操作发现内存中仍是A，认为没修改，那么线程one取出的A就是修改过后的A


AtomicStampedReference<V>
带时间戳的原子引用


====================================================集合类=============================================================

线程非安全                       线程安全
ArrayList                       sector
​                                Collectioins.synchronizedList

set                             Collectioins.synchronizedSet

map                             Collectioins.synchronizedMap


List、Set、Map大的区别
List、Set继承Collection接口
List有ArrayList、LinkList、Vector都是基于数组和链表的，元素可以重复,有序的
Set有HashSet、LinkedHashSet、TreeSet。首先他们的元素是唯一的，跟他们的equal方法有关，元素存放的位置跟他们的hashcode值有关。
HashSet就是基于HashMap

Map未继承Collection接口，是独立的接口
Map有HashMap、LinkedHashMap、TreeMap、HashTable
HashMap存放的是键值对，内部有一个链表数组，根据元素的键值，通过hash函数计算出一个数组的下标，然后存进这个到相应的链表里。
LinkedHashMap内部有一个链表的链表
TreeMap


线程安全
ArrayList--Vector--Collections.synchronizedList()--CopyOnWriteArrayList<T>

Collections.synchronizedList()实际上是SynchronizedList<T>,内部读和写都synchronized

CopyOnWriteArrayList<T>写时复制上锁，不影响读

HashSet--Collections.synchronizedSet()--CopyOnWriteHashSet<T>

HashMap--ConcurrentHashMap<T>


==============================================================================================================

保证数据一致性，保证并发性

公平锁：先来后到，排队，先来申请锁的先获得锁，order pocify
非公平锁：需要竞争，可能造成优先级反转或者饥饿现象
ReentrantLock默认非公平锁，吞吐量大
synchronized也是一种非公平锁

偏向锁/可重入锁（递归锁）
同一线程外层函数获得锁之后，内层递归函数仍然能够获得该锁的代码
线程可以进入任何一个它已经拥有的锁所同步着的代码
ReentrantLock、synchronized都是可重入锁
避免死锁

自旋锁 使用AtomicReference<Thread>
尝试获得锁的线程不会立即阻塞，而是采用循环的方式去尝试获得锁，
好处：减少线程上下文切换的消耗
缺点：循环会销毁CPU

独占锁(写锁)/共享锁(读锁) ReentrantReadWriteLock
并发读
读写、写读、写写过程是互斥的

其实还可以向CopyOnWriteHashSet一样，写的时候复制一份，写完后再填回去。

==============================================================================================================
同步减数器     CountDownLatch    Latch门闩
​    m个线程等待n个线程完成后再干其它的事
​    同时起步

同步加数器     CyclicBarrier     循环屏障
​    等待n个线程再干其它的事

信号量         Semaphore
​    资源少（停车位少），多个线程抢资源（很多车过来停车）
信号量的使用目的：   1个或多个共享资源的互斥使用
​                    并发线程数的控制

CountDownLatch、CyclicBarrier，只能使用1次

Semaphore可多次使用

==============================================================================================================
阻塞队列方法

        抛出异常            特殊值     阻塞          超时
插入      add()           offer(e)     put(e)     offer(e,time,unit)
删除      remove()        poll()       take()     poll(time,unit)
检查      element()       peek()      不可用      不可用

队列为满，add()插入异常    poll() 返回false    put(e)阻塞    offer(e,time,unit)阻塞一定时间，超时返回false
队列为空，remove()删除异常 offer(e)返回false   take()阻塞    poll(e,time,unit)阻塞一定时间，超时返回false

生产消费模式

生产多少个，消费多少个
阻塞队列内部还是使用ReentrantLock进行同步
BlockingQueue
ArrayBlockingQueue
LinkedBlockingQueue

同一时间只能生产1个，消费1个
内部Transferer， Spin和CAS，自适应自旋，后阻塞
SynchronousQueue    不存储元素的阻塞队列,单个元素的队列

生产者和消费者模式
线程池
消息中间件


        sync                                    lock                            a
                            -->                                     -->

wait             notify                 await           singal

    object.wait()/notify                      reentrantlock
    synchronized




生产者和消费者模式
​    什么是生产者和消费者？有的线程生产资源（资源增加），有的线程消费资源（资源减少），没有着两个特性就不是生产消费模式了
​    比如要有人煮饭，其它人才可以吃饭

传统生产消费模式:
生产：
​    竞争锁                 //为什么先竞争锁，而不是先判断？如果先判断后获取锁，判断到获取锁中间可能会被修改了，那么，获取锁后要重新判断
​        获得锁：进入下一步
​        没获得锁：阻塞
​    满足条件生产？
​        满足：生产
​        不满足：等待，释放锁，阻塞的锁和等待的锁竞争锁。等待唤醒。有可能是虚假唤醒，while重新判断释放满足生产条件

消费也是同样的道理

新型生产消费模式
生产：
​    ArrayBlockingList.put()     //我要生产，内部Lock，满足条件吗？不满足就阻塞
​    ArrayBlockingList.take()



多个条件控制，控制线程执行顺序

==============================================================================================================
https://www.cnblogs.com/jinshuai86/p/9291033.html

获取锁、释放锁都是要消耗资源的
阻塞状态，挂起到恢复需要再用户态和内核态之间切换

Synchronized底层实现原理
JDK1.6之后，Synchronized锁状态有无所状态、偏向锁、轻量级锁、自适应自旋锁和重量级锁
无所状态就是不上锁
偏向锁：不存在锁竞争，只会有同一个线程进入临界区，为了减少同一线程获取锁消耗的资源，所以当进入临界区前不会先去获取重量级锁
轻量级锁：多个线程交替进入临界区，不存在锁竞争状态，为了减少阻塞状态下，挂起到恢复需要在用户态到内核态之间的切换
自适应自旋锁：也是为了减少阻塞状态下，挂起到恢复需要在用户态到内核态之间的切换。自旋锁在没有获取到锁，不会马上挂起，而是循环获取锁，消耗CPU资源
重量级锁：就是获取不到就挂起

java对象由对象头、示例数据和对其填充数据组成
Synchronized(Object),Object的有MarkWord字段和Monitor对象，记录了锁状态和当前线程获取的锁计数、等待的线程数、阻塞的线程数、获得锁当前线程



synchronized的不足
1、synchronized是非公平锁
2、synchronized加锁前无法获取锁的状态，无法做如果有其它线程获取到锁，我就不阻塞等待了，一旦获取不到锁就阻塞
3、synchronized不能做超时等待
4、synchronized不可中断
5、synchronized不可多个条件变量


造成并发问题的原因
可见性问题
代码重排序问题
原子性问题


可见性问题、代码重排序问题可以用volitale解决，不能解决原子性问题

原子性问题可以通过CAS、上锁解决

CAS：compare and swap，比较并交换。AtomicInteger内部就是通过CAS保证数据原子性。CAS是Unsafe类的方法
CAS缺点：while循环，消耗CPU资源
​        ABA问题用AtomicStampedReference/AtomicMarkableReference添加版本号解决

上锁：
​    synchronized()关键字，偏向锁--轻量级锁--自适应自旋锁--重量级锁

    synchronized缺点：
        不是公平锁
        无法获取锁状态
        不能阻塞超时
        多条件等待
        不可中断
    
    ReentrantLock可以解决上面的问题


java基于CAS、synchronized、Lock实现了很多同步类
AtomicInteger、AtomicReference等原子类型基于CAS，

CountDownLatch基于CAS、CyclicBarrier基于ReentrantLock,semaphore基于CAS

copyOnWrityArrayList,阻塞队列，都是基于CAS和锁解决的


使用这些同步类的同步方法
​    1、单纯修改数据，就不需要重新上锁了。例如AtomicInteger.decrement();
​    2、修改数据以获取资源，例如boolean AtomicInteger.compareAndSet()，获取不到就退出，或者while循环获取。也是CAS了
​                          例如CountDownLatch.countDown()，基于CAS循环等待其它线程完成
​                          例如CyclicBarrier.await(),基于ReentrantLock就线程进入等待状态
​                          所以基于CAS，数据修改不成功则循环
​                              基于synchrone,就是阻塞（Collections.synchroniedArrayList）
​                              基于Lock，数据修改不成功则进入等待或者阻塞

基于CAS的都是一个自旋锁了


CAS、上锁都可以解决线程并发、原子性问题，只是各有优缺点


==============================================================================================================
多线程的实现方式
1、继承Thread类，重新run方法
2、实现Runnable接口，重写run方法，交给Thread
3、通过Callable和FeatureTask创建线程
4、通过线程池创建线程


单个线程数的线程池
固定线程数的线程池
可缓存的线程池

ThreadPoolExcutor(corePoolSize,maximumPoolSize,keepAliveTime,unit,workQueue,threadFaceory,handler)
​    corePoolSize:核心线程数，任务过来马上执行
​    maximumPoolSize：核心线程后被占用，任务进入阻塞队列，队列满了但不大于maximumPoolSize，threadFaceory生成工作线程，
​                     从workQueue取队列。当进来的任务大于maximumPoolSize，handler拒绝进来
​                     线程池执行完了，等待keepAliveTime后，判断现在线程数是否大于corePoolSize，是就停掉
​    threadFaceory:生成工作线程的工厂
​    handler:拒绝策略

拒绝策略：等待队列已满，线程池的活动线程数达到了最大值，就要使用拒绝策略
​    AbortPolicy：直接抛出RejectedExcutionException
​    CallerRunsPolicy:不处理任务，不抛出异常，返回给调用者
​    DiscardOldestPolicy:抛弃等待最长的任务，提交当前任务
​    DiscardPolicy:直接丢弃当前任务


public static ExecutorService newFixedThreadPool(int nThreads) {
​    return new ThreadPoolExecutor(nThreads, nThreads,
​                                  0L, TimeUnit.MILLISECONDS,
​                                  new LinkedBlockingQueue<Runnable>());
}

1.核心线程数为零    2.最大线程数为无限  3.无任务时，线程存活的最大时间为60s
4.任务队列为同步移交队列，该队列没有缓冲区，即不会有任务会在该队列中排队，
每当有任务要入队时，队列都会将任务移交给一个可用的线程
public static ExecutorService newCachedThreadPool() {
​    return new ThreadPoolExecutor(0, Integer.MAX_VALUE,
​                                  60L, TimeUnit.SECONDS,
​                                  new SynchronousQueue<Runnable>());
}

public static ExecutorService newSingleThreadExecutor() {
​    return new FinalizableDelegatedExecutorService
​        (new ThreadPoolExecutor(1, 1,
​                                0L, TimeUnit.MILLISECONDS,
​                                new LinkedBlockingQueue<Runnable>()));
}

public ThreadPoolExecutor(int corePoolSize,
​                              int maximumPoolSize,
​                              long keepAliveTime,   //线程干完后休眠多长时间
​                              TimeUnit unit,
​                              BlockingQueue<Runnable> workQueue)


线程资源必须通过线程池提供，不允许应用中自行显示创建线程。线程创建开销大

线程池不允许使用Executors去创建，通过ThreadPoolExecutor的方式，明确拒绝方式
​    FixedTheadPool和SingleTheadPool;允许请求队列长度对Integer.MAX_VALUE,堆积大量请求，导致OOM
​    CacheTheadPool和ScheduledThreadPool;允许创建线程数对Integer.MAX_VALUE,导致OOM


Runtime.getRuntime().availableProcessors()  CPU核数

CPU密集型：CPU使用率很高，若开过多的线程数，只能增加上下文切换的次数，因此会带来额外的开销。
​           CPU密集型任务配置尽可能少的线程数量，CPU核数+1
​           对于计算密集型的程序，线程数应当等于核心数，但是再怎么计算密集，总有一些IO吧，所以再加一个线程来把等待IO的CPU时间利用起来
​           corePoolSize=MaximunPoolSize = N+1


IO密集型：IO密集型任务CPU使用率不高，可以让CPU在等待IO的时候去处理其它任务，充分利用CPU时间
​           可以使用稍大的线程池，
​           2*CPU核数+1
​           N/(1-阻塞因子)   阻塞因子=0.8~0.9
​           （线程等待时间/CPU等待时间+1）*CPU核数
​           线程等待时间所占比例越高，需要越多线程。线程CPU时间所占比例越高，需要越少线程。
​           corePoolSize=0,MaximunPoolSize=2*n+1

混合型：
可以将任务分成IO密集型和CPU密集型任务，然后分别用不同的线程池去处理。
只要分完之后两个任务的执行时间相差不大，那么就会比串行执行来的高效。


死锁

    线程A     持有      锁A
    线程B     持有      锁B
    线程A     尝试获取   锁B   被阻塞
    线程B     尝试获取   锁A   被阻塞
    都被阻塞  无法释放锁 死锁

查看死锁命令：https://blog.csdn.net/tankai19880619/article/details/50633778
kill -3 [pid]   //trace生成到/data/anr/trace.txt



==============================================================================================================
JVM体系结构

判断对象是否存活？
引用计数：每个对象赋值时均要维护引用计数器，有一定的消耗，较难处理循环引用。
可达性分析算法：程序把所有的引用关系看作一张图，通过一系列的名为GC Roots的对象作为起始点，从这些节点开始向下搜索，
​               搜索所走过的路径称为引用链。当一个对象到 GC Roots 没有任何引用链相连（就是从 GC Roots 到这个对象不可达）时，
​               则证明此对象是不可用的。

               哪些对象可以作为GC Root对象
                虚拟机栈（栈中的局部变量区）中的引用对象
                方法区中的类静态属性引用对象
                方法区中常量引用的对象
                本地方法栈中JNI引用的对象


什么时候回收？
CPU空闲的时候自动进行回收
堆内存满了之后
主动调用system.gc()后尝试回收


垃圾回收算法
标记清除：标记需要回收的对象，同一回收，垃圾碎片，效率低
复制算法：分成两块空间，一块空间满了之后，将存活的对象拷贝到另一块空间，同意清除，浪费空间
标记整理：标记清除后，进行排列整理
分代收集：新生区（eden、survivor0、survivor1）区--复制算法；老年代--标记清除、标记整理；
​          永久代存放静态文件，java类、方法等,在虚拟机中
​          元空间并不在虚拟机中，而是在本地内存中，大小受本地内存影响
​            虚拟机加载的类信息
​            常量池
​            静态变量
​            即时编译后的代码

当存活对象比较多，内存碎片少，使用标记清除
当存活对象比较少，内存碎片多，使用标记整理或者复制算法

垃圾回收器
​    没有完整的收集器，更加没有万能收集器，只是针对具体应用最合适的收集器，合适的分代收集器
​    Serial:串行，为单线程环境设计且只使用一个线程进行垃圾回收，会暂停所有的用户线程。
​    Parallel:并行，多个垃圾收集线程并行工作，此时用户线程是暂停的，适用于科学计算/大数据处理首台处理等弱交换场景
​    CMS:并发，用户线程和垃圾收集同时执行，不一定并行，可能交替执行，不需要停顿
​    G1:java8，将堆内存分割成不同的区域然后并发的对垃圾进行回收

    查看默认垃圾回收器
    java -xx:+PrintCommandLineFlags -version


jvm的参数类型
​    标配参数    java -version java --help
​    x参数
​    xx参数


强引用、软引用、弱引用、虚引用
SoftReference:内存足够不回收，内存不足回收
WeakReference：不管内存是否够用都会被回收

软引用的对象，如果没有被其它强引用引用，内存不足时会被回收
弱引用的对象，如果没有被其它强引用或者弱引用引用，不管内存是否够用都会被回收

    HashMap<String, SoftReference<Bitmap>>

WeakHashMap<K,V>,   K被回收，WeakHashMap相应的node也被删除

ReferenceQueue  引用队列，结合上面的软引用、弱引用、虚引用结合使用，在对象回收前，可以从ReferenceQueue获取对象，做一些事情


https://www.jianshu.com/p/825cca41d962
https://blog.csdn.net/junjunba2689/article/details/80601729

软引用：在使用缓存时有一个原则，如果缓存中有就从缓存获取，如果没有就从数据库中获取，缓存的存在是为了加快计算速度，如果因为缓存导致了内存不足进而整个程序崩溃，那就得不偿失了。
图片处理：
假设需要读取大量本地图片
​    如果每次读取图片都从硬盘读取会严重影响性能
​    如果一次性区别加载到内存又可能造成内存溢出

弱引用：当你想引用一个对象，但是这个对象有自己的生命周期，你不想介入这个对象的生命周期，这时候你就是用弱引用。
​    我们在handler、runnable已经用过了


-Xms 为jvm启动时分配的内存，比如-Xms200m，表示分配200M

-Xmx 为jvm运行过程中分配的最大内存，比如-Xms500m，表示jvm进程最多只能够占用500M内存

-Xss 为jvm启动的每个线程分配的内存大小，默认JDK1.4中是256K，JDK1.5+中是1M

=====================================================OOM=========================================================
cd.note.activity.OomActivity

Error、Exception

java.lang.StackOverflowError  栈溢出异常，中断，递归要用的栈保存现场，有可能栈异常

java.lang.OutOfMemoryError:lava heap space  堆内存溢出

java.lang.OutOfMemoryError:GC overhead limit exceeded   超过98%的时间都在GC回收，并且回收不到2%的堆内存

java.lang.OutOfMemoryError:Direct buffer memory  NIO程序经常使用ByteBuffer来读取写入本地数据。本地内存溢出异常

java.lang.OutOfMemoryError:unable to create new native thread

java.lang.OutOfMemoryError:Metaspace



=====================================================Linux=========================================================
ps -ef|grep java
pidstat -u 1 -p [pid]   每1秒查看pid的CPU使用状况
pidstat -r 1 -p [pid]   每1秒查看pid的内存使用状况
pidstat -d 1 -p [pid]   每1秒查看pid的内存使用状况

整机：top、uptime精简版
​    load average    系统负载均衡值，三个值分别系统的1分钟、5分钟、15分钟，三个值相加/3 * 100% > 60%， 负载压力大
​    Cpu(s),按键盘e，CPU(e)，查看各个CPU的评价负载
​    看各个进程的CPU，MEM
CPU：vmstat、mpstat
​    vmstat -n 2 3   //没2秒查看一次，查看3次
​    procs -----------memory---------- ---swap-- -----io---- -system-- ----cpu----
​     r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa
​     1  0      0 772804  41964 175320    0   32     5   143   22   14  0  0 99  0
​     0  0      0 772796  41964 175320    0    0     0     0   24   14  0  0 100  0
​     0  0      0 772796  41964 175320    0    0     0     0   22   15  0  0 100  0
​    r:运行等待CPU时间片的进程数，原则上整个系统运行队列不能超过总核数的2倍，否则代表系统压力过大
​    b:等待资源的进程数
​    us:用户经常消耗CPU时间百分比，us值长期大于50%，用户进程消耗CPU时间过多，优化程序
​    sy:内核进程消耗CPU时间百分比
​        us+sy>80%，可能内存不足
​    id:idle值，CPU空闲率

    mpstat -p ALL 2
    Linux 2.6.18-164.el5 (server.sys.com)    01/04/2010
    09:34:20 PM CPU   %user   %nice    %sys %iowait    %irq   %soft %steal   %idle    intr/s
    09:34:22 PM all    0.00    0.00    0.00    0.00    0.00    0.00    0.00 100.00   1001.49
    09:34:22 PM    0    0.00    0.00    0.50    0.00    0.00    0.00    0.00   99.50

内存：free
​    free -m

硬盘：df
​    df -h

磁盘IO：iostat
​    iostat  -xdk 2 3
​    %util列每秒钟百分几的时间用于I/O操作，接近100%，需要优化

网络IO：ifstat
​    ifstat 1
​    观察各个网卡的in\out
​    负载情况
​    读写是否正常


top找出CPU占比最高的
ps -ef或者jps进一步等我哪个程序
定位到具体线程或代码，strace/  ps -mp [pid] -o THREAD,tid,time
将上面的tid转换为16进制格式数
jstack [pid] | grep tid -A60


=====================================================Github=========================================================
1、查找优秀开源框架
​    watch:持续收到项目动态
​    fork：复制某个项目到自己的Github仓库
​    star：点赞
​    clone：下载到本地
​    follow：关注感兴趣的作者

    xxx关键字 in:name/in:description/in:readme 组合in:description,readme
    
    [xxx] stars:>/:<=   100..200    100到200之间
    
    [xxx] forks:>/:<=
    
    awesome [xxx]
    
    高亮文件某一行，1行--url后跟#L数字，多行--url后跟#L数字-L数字2
    
    项目内搜索，英文t，出现源代码文件列表
    
    搜索某个地区内的大佬
        location:beijing
        language:java

=====================================================OKHttp=========================================================
https://www.jianshu.com/p/a8736d2854e6
https://blog.csdn.net/TellH/article/details/71534704
支持HTTP2/SPDY黑科技
socket自动选择最好路线，并支持自动重连
拥有自动维护的socket连接池，减少握手次数
拥有队列线程池，轻松写并发
拥有Interceptors截获器轻松处理请求与相应（比如GZIP压缩，转换）
基于Headers的缓存策略

SPDY
​    是google开发的基于传输控制协议(TCP)的应用层协议，SPDY协议旨在通过压缩、多路复用和优先级来缩短网页的加载时间和提高安全性
​    SPDY和HTTP关系，SPDY协议只是在性能上对HTTP做了很大的优化，核心思想是尽量减少连接个数，而对http语义并没有做太大修改。
​    SPDY使用了HTTP的方法和页尾，但是删除了一些头并重写了HTTP中管理连接和数据转移格式的部分，兼容HTTP。
​    多路复用 请求优化
​    支持服务器推送技术
​    SPDY压缩了HTTP头        --舍弃了一些不必要的头信息，经过压缩之后可以节省多余数据传输带来的等待时间和宽带
​    强制使用ssl传输协议     ssl加密


client:应用层
​    ConnectionPool:client连接池、Dispatcher:Dispatcher分发器、Call:Client、Interceptors截获器

engine:业务逻辑层
​    sendRequest:engine，readRespone:engine,routeSelector:engine路线选择器

stream:链路层
​    connection:Connection连接、HttpSteam:Steam流、StreamAllocation:Stream流分配

应用层
构造Request请求 Request,Call
请求方式同步exceute，异步enqueue?
同步：加入Dispatch分发器中
异步：加入runningCall
创建截获器ApplicationInterceptorChain，对请求进行压缩、修改编码等处理

业务逻辑层
数据缓存：
​    缓存数据没有过期，直接使用缓存
​    缓存过期，先用过期的，然后再去网络请求数据，并更改本地数据
​    缓存数据没有，去网络直接获取
底层使用连接池
路线选择器
网络截获器可以有多个

链路层
​    底层是socket


=====================================================RecycleView====================================================
RecycleView替代listview、gridview


=====================================================Gridle=========================================================
图片加载框架
Gridle
​    使用简单
​    可配置度高，自适应程度高
​    支持常用图片格式Jpg png gif webp
​    支持多种数据源，网络、本地、资源、assets
​    高速缓存策略，支持Memory和disk图片缓存，默认Bitmap格式采样RGB_565内存使用至少减少一般
​    生命周期继承，根据Activity/Fragment生命周期自动管理请求
​    高效处理bitmap，使用Bitmap Pool使得Bitmap复用，主动recycle回收需要回收的Bitmap,减少系统压力

.with(Context); //内部使用了ApplicationContext，不受Activity/Fragment生命周期影响
.with(Activity);
.with(FragmentActivity);
.with(app.Fragment);
.with(v4.Fragment);

.load(filePath)
.load("file:///android_asset/f.jpg")    assets资源
.load("Android.resource://com.frank.glide/raw/raw_1")或者.load("Android.resource://com.frank.glide/raw/"+R.raw.)
.load("Android.resource://com.frank.glide/drawable/dr")或者.load("Android.resource://com.frank.glide/drawable/"+R.drawable.)
.load("content://media/external/images/media/138465")
.load("http://...")
.load("https://...")
不只是String类型

重要功能
​    禁止内存缓存：.skipMemoryCache(true)
​    清除内存缓存：.get(context).clearMemory() Ui线程
​    禁止磁盘缓存：.diskCacheStrategy(DiskCacheStrategy.NONE)
​    清除磁盘缓存：.get(context).cleardiskCache()   后台线程，结合清除内存缓存使用，
​    获取缓存大小：new GetDiakCacheSizeTask(textView).execute(new File(getCacheDir()),DiskCache.Factory.DEFAULT_DISK_CACHE_DIR)
​    资源加载的优先顺序：.priority(Priority.HIGH)、.priority(Priority.LOW)
​    缩略图：.thumbnail(0.1f)，先显示0.1倍，   .thumbnail(DrawableRequestBuilder)
​    对图片进行裁剪、模糊、滤镜等处理
​    请求状态监听
​    下载进度监听


=====================================================多渠道打包=========================================================
打包就是根据签名和其它标识生成安装包

签名：
​    在APK中保存一个特别字符串
​    标识不同的应用开发者
​    一个应用开发者开发的多款应用使用同一个签名

为什么要签名？
​    系统要求
​    不同开发者开发的应用包名可能会相同，导致一个应用覆盖另一个应用,加入签名后会安装不成功提示签名不一样
​        签名文件不能不见了啊，不见了只能重新签名，应用市场排行变成0


默认签名：debug.keystore，不同电脑的debug.keystore不同，这是为什么换了电脑重新卸载安装
Eclipse生成：xxx.keystore，
android生成：xxx.jks

签名文件：
​    签名密码、Alias别名、Alias密码、有效期、
​    签名文件信息（name、组织、部门、国家、城市）


多渠道打包
   在安装包中添加渠道信息channel，对应不同的渠道

为什么要多渠道打包
   在安装包中添加渠道信息channel，应用在请求网络的时候携带渠道信息，方便后台做运营统计

多渠道打包原理
​    一般来说，这个渠道标识放在AndroidManifest.xml的Application的一个Metadata。通过api获取这个变量

如何实现
友盟
​        gradle--productFlavors--AndroidManifest.xml引用--java获取--返回给服务器、

        productFlavors{
            wandoujia{
            //manifestplaceholders = [UMENG_CHANNEL_VALUE: "wandoujia"]
            }
            xiaomi{}
    
            productFlavors.all{ flavor ->
                flavor.manifestplaceholders = [UMENG_CHANNEL_VALUE: name]
            }
    
            applicationVariants.all{ variant ->
                variant.outputs.each { output ->
                    def outputFile = output.outputFile
                    if(outputFile !=null && outputFile.name.endsWith('.apk')){
                        def fileName = outputFile.name.replace(".apk","-${defaultConfig.versionName}.apk")
                        output.outputFile = new File(outputFile.parent,fileName);
                    }
                }
            }
        }
    
        <meta-data
            android:name="UMENG_CHANNEL"
            android:value="${UMENG_CHANNEL_VALUE}"
        />
    
        java -- getChannnel(){}

 美团
​    把Android应用当作zip解压，在签名生成的目录下META-INF添加一个空文件，文件名就是渠道名
​    缺点：google修改规则
​         不法渠道商通过网络劫持和篡改的组合方式来获取暴利
​    工具：MultiChannelBuildTool.py

360
​    zip文件可以添加comment(摘要)的数据结构特点，在文件末尾写入任意数据，而不用重新解压zip文件
​    邀请码，分享信息

    MCPTool.bat



=================================================算法=============================================
查找算法
​    顺序查找
​    二分查找        min = low+(high-low)/2
​    插值查找        min = low+(key-a[low])/(a[high]-a[low])*(high-low)
​    斐波那契查找
​    树表查找
​        二叉顺序树：左子树上所有节点小于它的根结点，右子树上所有节点大于它的根结点。
​                   最坏的情况树不平衡
​        平衡查找树2-3查找树：
​    分块查找
​    哈希查找
​        关键字和存储地址的关系
​        计算简单+分布均匀 = 好的散列函数
​        直接定址法：f(key)=a*key+b  ==> 年龄50岁的人数存放在A[50]中
​        数字分析法：去除关键字中一些同性质的东西
​        平方取中法：关键字平方，取中间几位数作为关键字
​        折叠法：关键字分割相等的几部分，叠加求和
​        除留余数法：f(key)=key mod p(p<=m)
​        随机数法：f(key)=random(key) 关键字长度不等时

        散列冲突解决：
            线性探测法：  fi(key)=(f(key)+di) MOD m (di=1^2,-1^2,2^2,-2^2......,q^2,-q^2,q<=m/2)
            二次探测法：  fi(key)=(f(key)+di) MOD m (di=1^2,-1^2,2^2,-2^2......,q^2,-q^2,q<=m/2)
            随机探测法：  fi(key)=(f(key)+di) MOD m (di随机函数获得的数列)
            再散列函数法：fi(key)=RHi(key) (i=i,2,3...k)
            链地址法：数组加链表
            公共溢出法

插入排序时间复杂度：
​            T(n)=theta(n^2)
​            常数个元素空间存储临时数据
​            稳定

归并排序时间复杂度：
​                    1
​            T(n)=                       ==>     theta(nlgn)
​                    2T(n/2)+OHM(n)
​            随着n越大，临时数据越多
​            稳定

堆排序时间复杂度：
​            T(n)=theta(nlgn)
​            常数个元素空间存储临时数据
​            不稳定

快速排序：
​            最坏情况：当划分不平衡时，T(N)=O(n^2)
​            在输入元素互异的情况下，快速排序算法的期望运行时间O(nlgn)
​            不稳定


上面集中都是比较排序，任何比较排序在最快情况下都要经过OHM(nlgn)次比较
因此，归并排序和堆排序是渐进最优的

线性时间复杂度的排序：计数排序、基数排序、桶排序

计数排序：
​            假设n个输入元素中的每个元素都是在0~k区间的一个整数。当k=O(n)时，排序时间theta(n)

COUNTING_SORT(A,B,k)
​    let C[0..k] be a new array
​    for i = 0 to k
​        C[i]=0
​    for i = 0 to A.length
​        C[A[i]]++;
​    for i = 0 to A.length
​        B[C[A[i]]] = A[i]
​        C[A[i]]--

基数排序：
​            不适用与负数，要用链表，还要在链表中做插入操作
RADIX-SORT(A)
​    //TODO 找到最大值，计算出最大位数d
​    //TODO 新建一个数组，数组的每个元素都是链表
​    for i = 0 to d
​        //TODO 插入
​        //TODO 排序


对于数据结构，动态集合的操作，基本功能：增删改查
​    SEARCH(S,k)     k关键字或下标
​    INSERT(S,x)     插入到集合当中
​    DELETE(S,x)
​    MINIMUM(S)
​    MAXIMUM(S)
​    SUCCESSOR(S,x)  找到x，返回x的前一个指针
​    PREDECRSSOR(S,x)


=================================================bufferknife=============================================

1、省略findViewById
Activity:
@BindView(R.id.xxx)
TextView mTextView;     //不能用static，private修饰
布局设置好之后调用
ButterKnife.inject(this)

Fragment
@BindView(R.id.xxx)
TextView mTextView;     //不能用static，private修饰
View view = View.inflate(R.layout.simple,container,false);
BufferKnife.inject(this,view);

ViewHolder中使用
static class ViewHolder{
​    @InjectView(R.id.xxx)
​    TextView mTextView;     //不能用static，private修饰

    public ViewHolder(view){
        BufferKnife.inject(this,view);
    }
}

2、省略setOnclickListener()
@OnClick(R.id.xxx)
void xxx(View v){}

3、@OnItemClick、@OnCheckedChanged

4、@OnClick{R.id.xxx、R.id.yyy}
void xxx(View v){}  //同一个处理函数


=================================================屏幕适配方案=============================================
一个是 代码是否规定了横竖屏
一个是 我们现在手机是否横竖屏


https://blog.csdn.net/u010349644/article/details/83619912

dpi:像素密度，单位尺寸的像素数
dpi=总px/尺寸

dp:与像素密度无关的尺寸
px=dp*(dpi/160)=dp*(总px/(尺寸*160))

dp=px*尺寸*160/总px

总dp=总px*160/dpi=尺寸*160

我们设置控件的dp值
    dpi相同，计算出px越大，屏幕尺寸越大，控件占的位置越大
    屏幕尺寸相同，dpi越大，计算出的px越大，但是控件占的位置一样，但是

设备 A ， 屏幕宽度为 720px， dpi为160，则屏幕总dp为 720/(160/160) = 720 dp
设备 B ， 屏幕宽度为 720px， dpi为320，则屏幕总dp为 720/(320/160) = 360 dp


============================================  反射&字节码操作  =======================================
B站

动态语言
    程序运行时，可以改变程序结构或者变量类型
    Python、ruby、javascript等
        function test(){
            var s = "var a=3;var b=5;alert(a+b);"
            eval(s);
        }

    java不是动态语言，但有一定动态型，反射机制、字节码操作获得类似动态语言的特性

反射机制 reflection
    通过字符串加载一个类，动态获取处理类信息（类名、属性、方法、构造器），构造对象、调用类的任意方法、构造器
    获取泛型信息、处理注解
    我们自定义的类，怎么加载到内存？
    一个类被加载后，JVM通过Class.forName(String)将一个类的类信息封装成一个Class对象，通过这个class对象
    可以获取类的所有类结构信息
    一个类只会被加载一个，多次加载的class对象hashcode一样

    Class.forName(String ClassName)
    object.getClass()
    Object.class

    class.getName()/class.getSimpleName()
    class.getField(fieldName)/class.getFields()                   获得public属性
    class.getDeclaredField(fieldName)/class.getDeclaredFields()   获得所有属性
    class.getMethod(MethodName,String.class...)/class.getMethods()   实例参数类型String.class
    class.getDeclaredMethod(MethodName,String.class...)/class.getDeclaredMethods()
    class.getConstructor(String.class...)/class.getConstructors()   实例参数类型String.class
    class.getDeclaredConstructor(String.class...)/class.getDeclaredConstructors()

    Class<User> clazz = (Class<User>)Class.forName(String ClassName);
    User user = clazz.newInstance();    //无参构造方法

    Constructor<Student> constructor = clazz.getDeclaredConstructor(int.class,String.class,int.class);
    Student student = constructor.newInstance(1,"chenda",26);

    Method method = clazz.getDeclaredMethod("setName",String.class);
    method.invoke(student,"chendada");

    Field field = clazz.getDeclaredField("age");
    field.setAccessible(true);
    field.set(student,18);      //报错，不能这样修改私有属性,加上上面一句才可以
    Log.d(TAG,"student.getAge()="+field.get(student));

    setAccessible(boolean); //启用/禁用访问安全检查的开关，禁用后效率更高

    //通过反射获得泛型实际类型，获得方法，获得方法的所有参数类型，获得参数化类型中的实际参数类型
    https://blog.csdn.net/fxl5202301/article/details/85291493
    泛型
        ParameterizedType   参数化类型 Collection<String>
        GenericArrayType    表示一种元素类型的是参数化类型或者类型变量的数组类型
        TypeVariable        各种类型变量的公共父接口
        WildcardType        一种通配符类型表达式 ?、? extends Number、? super Integer


动态编译
    1、Runtime启动新的进程操作
        Runtime run = Runtime.getRuntime();
        Process p = run.exec("javac -cp d:/myjava/ helloworld.java");

    2、通过JavaCompiler动态编译
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        int ret = compiler.run(null,null,null,"d:/myjava/helloworld.java");
        运行方式一
        Runtime run = Runtime.getRuntime();
        Process p = run.exec("java -cp d:/myjava/ helloworld");
        InputStream in = p.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(in));
        String info = "";
        while((info=reader.readLine())!=null){
            log.d();
        }
        运行方式二 URLClassLoader

========================================  脚本引擎执行javascri代码  ==================================
B站 尚学堂 脚本引擎执行javascript脚本

百度
android Rhino
android JSBridge

为什么？因为有一些javascri代码效率高很多，比如计算字符串"3+1+4-1-7+1"

//java和android有些不一样

java
    ScriptEngineMananger

android
https://www.jianshu.com/p/b649c3c241a6

=============================================  字节码操作  ===========================================
运行java程序运行时新建java类或者修改java类
BCEL
ASM
CGLIB
javassist




=================================================  注解  =============================================
@Override   重写超类的方法
@Deprecated 过时方法，不建议继续使用
@SuppressWarnings(value={"deprecated","unchecked"})    压制警告
    @Target({TYPE, FIELD, METHOD, PARAMETER, CONSTRUCTOR, LOCAL_VARIABLE})
    @Retention(RetentionPolicy.SOURCE)
    public @interface SuppressWarnings {
        String[] value() default {""};   //参数名value，类型String[]
        int id() default -1;             //-1代表不存在的意思
    }

元注解:给自定义注解使用的注解
@Target
    描述注解的使用范围   ElementType.
    PACKAGE         包
    TYPE            类、接口、枚举、Annotation类型
    CONSTRUCTOR     描述构造器
    FIELD           描述域
    METHOD          描述方法
    LOCAL_VARIABLE  描述局部方法
    PARAMETER       描述参数
@Retention
    需要在什么级别保存该注解信息，描述注解的生命周期
    SOURCE      在源文件中有效
    CLASS       在class文件中有效
    RUNTIME     在运行时有效，为Runtime可以被反射机制读取
@Documented
@Inherited

反射读取注解
ORM object relationship mapping 对象关系映射

bean类--加注解--解析类--解析成创建数据表语句

=================================================eventbus=============================================



==============================================热修复&插件和==========================================
class文件能够被jvm识别、加载并执行的文件格式，记录一个类文件的所有信息
    class文件可以由java、python等语言生成

生成：1、IDE帮我们build，2、javac生成
执行：java命令

class文件结构
一种8位字节的二进制流文件
各个数据按顺序紧密的排列，无间隙
每个类或接口都单独占据一个class文件

类型                                    数量
u4              magic                     1                         //加密校验数据
u2              minor_version             1                         //最小支持的jdk版本
u2              major_version             1                         //主要支持的jdk版本
u2              constant_pool_conunt      1                         //常量池数量
cp_info         constant_pool             constant_pool_conunt-1    //常量池
u2              access_flags              1                         //作用域
u2              this_class                1                         //当前class
u2              super_clas                1                         //父class
u2              interfaces_count          1                         //继承的接口数量
u2              interfaces                interfaces_count          //继承的接口数量
u2              fields_count              1                         //成员变量
field_info      fields                    fields_count
u2              method_count              1                         //方法
method_info     method                    method_count
u2              attributes_count          1                         //类属性，注解
attributes_info attributes                attributes_count


access_flags
标志名             标志值     标志含义                    针对对象
ACC_PUBLIC         0x0001   public类型                    所有类型
ACC_FINAL          0x0010   final类型                     类
ACC_SUPPER         0x0020   使用心得invokespecial语义     类和接口
ACC_INTERFACE
ACC_ABSTRACT
ACC_SYNTHRTIC               不由用户代码生成
ACC_ANNOTATION
ACC_ENUM

constant_pool
CONSTANT_Integer_info       //常量整型类型
CONSTANT_Long_info
CONSTANT_String_info
CONSTANT_Class_info         //类相关信息，类相关引用的相关信息
CONSTANT_Fieldref_info      //存储的是索引，指向field_info、method_info、attributes_info
CONSTANT_Methodredref_info

010 editor 二进制文件查看器

class文件弊端
内存占用大，不适合移动端
堆栈的加载模式，加载速度慢
文件IO操作多，类查找慢


dex文件能够被DVM识别，加载并执行的文件格式
    class文件可以由java、C\C++等语言生成

生成：1、IDE帮我们build，2、dex生成        dex --dex --output Hello.dex Hello.class
执行：dex命令
SDK\build-tools\24.0.0\dx.bat
dalvikvm -cp /sdcard/Hello.dex Hello

dex文件记录整个工程中所有类文件信息，记住的是整个工程，class文件记录的是一个类文件信息
class文件存在许多冗余信息，dex会取出冗余，并整合

dex文件结构
一种8位字节的二进制流文件
各个数据按顺序紧密的排列，无间隙
整个应用中所有java源文件都放在一个dex文件中

https://blog.csdn.net/tabactivity/article/details/78950379

header                  文件头
索引区
string_ids              字符串的索引
type_ids                类型的索引
proto_ids               方法原型的索引
field_ids               域的索引
methos_ids              方法的索引
数据区
class_defs              类的定义区
data                    数据区
link_data               链接数据区


============================================java虚拟机========================================
B站 Android学习 热修复与插件化

java虚拟机结构解析

    class文件 --> 类加载器子系统ClassLoader <-->  内存空间(方法区、java堆、java栈、本地方法栈)
    内存空间(方法区、java堆、java栈、本地方法栈) <--> 垃圾收集器
    内存空间(方法区、java堆、java栈、本地方法栈) <-- 指令计数器以及其它隐含寄存器 <--> 执行引擎
    内存空间(方法区、java堆、java栈、本地方法栈) <--> 执行引擎 <--> 本地方法接口
    内存空间(方法区、java堆、java栈、本地方法栈) <--> 本地方法接口 <-- 本地方法库

javac编译流程
源代码-词法分析器-Token流-语法分析器-语法树/抽象语法树-语义分析其-注解抽象语法树-字节码生成器-JVM字节码

jvm类加载器结构
    BootstrapClassLoader    load JRE\lib\rt.jar或者-Xbootclasspath选项指定的jar包           jdk的jar
    ExtensionClassLoader    load JRE\lib\ext\*.jar或者-Djava.ext.path选项指定目录的jar包    jdk的jar
    AppClassLoader          load CLASSPATH或者-Djava.class.path选项指定目录的类和jar包      app的jar
    CustomClassLoader       通过java.lang.lassLoader的子类自定义加载class
    自底向上检查类是否已经加载
    自顶向下尝试加载类

android的类加载器
    BootClassLoader         加载android的framework层的字节码文件
    PathClassLoader         加载apk中的字节码文件
    DexClassLoader          加载自定义的字节码文件
    BaseDexClassLoader      子类


双亲代理模型    当要加载一个类时，会判断当前的classloader是否加载过了，加载过了直接返回；没有加载过则寻找其父类是否加载过
类共享功能
类加载的隔离功能    不同的classloader加载的类都认为是不同的类


类加载流程
loading -- > linking(Verifying-preparing-Resolving) --> Initializing
loading：类信息从文件中获取并且载入到jvm的内存中
Verifying：检查读入的结构是否符合jvm规范的描述
preparing：分配一个结构用来存储类信息
Resolving：把这个类的常量池中的所有的符合引用改变成直接引用
Initializing：执行静态初始化程序，把静态变量初始化成指定的值

jvm内存管理
内存空间（方法区、堆区、栈区、本地方法区）
堆区：存放的是java方法执行时的所有数据，堆区描述java方法执行的完整模型
组成：有栈帧组成，一个栈帧代表一个方法的执行
栈帧：每个方法从调用到执行完成就对应一个栈帧在虚拟机中从入栈到出栈
组成：局部变量表、栈操作数、动态链接、方法出口
本地方法栈：专为native方法服务的
方法区：存储被虚拟机加载的类信息、常量、静态变量、即时编译器编译后等数据
堆区：new创建的对象在堆中分配内存
特点：是虚拟机中最大一块内存，是GC要回收的部分

Dalvik与jvm的不同
执行文件不同，一个是class，一个是dex
类加载系统不同
可以同时存在多个dvm
dvm基于寄存器的，jvm基于栈的

ART比Dalvik有哪些优势
程序每次启动，DVM使用JIT来将字节码转换成机器码，再执行，效率低
程序在安装的时候，art采用AOT预编译技术，将字节码转换成机器码保存，程序启动直接执行机器码
ART会占用更多的安装时间和存储空间


java的classloader

Android的classloader

android的动态加载比一般java程序复杂
    有许多组件需要注册才能使用，
    资源的动态加载很复杂
    android不同版本对类和资源的注册加载也不同
    原因都是android程序运行需要一个上下文环境


热修复详解
    动态更新apk
    正式发布和热修复同时使用

流行的热修复技术
    QQ空间的超级补丁方案
    微信的Tinker
    阿里的AndFix，dexposed
    美团的Robust，ele的migo，百度hotfix


                Tinker  QZone   AndFix  Robust
类替换             y       y       n       n
So替换             y       n       n       n
资源替换           y       y       n       n
全平台支持         y       y       y       y
即时生效           n       n       y       y
性能损耗           小      大     小       小
补丁包大小         小      大     一般     一般
开发透明           y       y       n       n
复杂度             低      低      高      高
gradle支持         y       n       n       n
Rom体积            大      小      小      小
成功率             较高    较高    一般    最高

能满足需求的条件下，找学习成本最低的。
学习成本一样的情况下，优先选择大公司的方案。


收集线上应用bug
分析bug
创建分支
Modify code
Test pass check in code
Build,diff,make patch,add annotation base on diff
Release patch, pull or push
verify, merge code to trunk
finish

AndFix









