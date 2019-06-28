package cd.note.memory;

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
     *
     *
     * */
}
