package cd.note;

import android.os.Build;
import android.os.Bundle;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;

import cd.note.Rxjava.RxjavaTest;
import cd.note.Thread.AsyncTaskTest;
import cd.note.Thread.HandlerTest;
import cd.note.Thread.ThreadPoolTest;
import cd.note.Thread.ThreadSync;
import cd.note.Thread.ThreadSyncTest;
import cd.note.designmode.Clone;
import cd.note.java8.Java8;
import cd.note.memory.MemoryTest;
import cd.note.others.CollectionTest;
import cd.note.others.GenericTest;
import cd.note.others.JniTest;
import cd.note.sqlite.SqliteTest;

public class MainActivity extends AppCompatActivity {

    @RequiresApi(api = Build.VERSION_CODES.N)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //浅拷贝
        Clone.shallowCloneTest();

        //深拷贝
        Clone.deepCloneTest();

        //Rxjava
        new RxjavaTest().test();

        //线性表的顺序存储结构
        JniTest.sqListTest();
        //线性表的单链表结构
        JniTest.linkListTest();
        //线性表的双向链表结构
        JniTest.dulLinkListTest();

        //插入排序算法
        JniTest.insertSortTest();
        //归并排序算法
        JniTest.mergeSortTest();
        //分治法
        JniTest.divideConquer();
        //快速排序
        JniTest.quickSort();
        //随机排序
        JniTest.randomSort();
        //堆排序
        JniTest.buildMaxHeapbyMerge();

//        //多线程状态测试
//        //新建--->可运行--->被终止
//        ThreadStateTest.threadNNT();
//        //新建--->可运行--->被阻塞--->可运行--->被终止
//        ThreadStateTest.threadNNBNT();
//        //wait()方法：新建--->可运行--->等待--->可运行--->被终止
//        ThreadStateTest.threadNNWNT_wait();
//        //Lock.Condition.await()方法：新建--->可运行--->等待--->可运行--->被终止
//        ThreadStateTest.threadNNBNT_lockwait();

        //AsyncTask的使用
        AsyncTaskTest asyncTaskTest = new AsyncTaskTest();
        asyncTaskTest.execute();

        //ThreadPool的使用
        new ThreadPoolTest().test();

        //Handler测试
        HandlerTest.test();

        ThreadSyncTest.test();
//        ThreadSyncTest.test1();

        ThreadSync.test1();

        MemoryTest memoryTest = new MemoryTest();
        memoryTest.test();

        SqliteTest.test(this);



        new Java8().lambdaTest();
        //java 集合测试
        new CollectionTest().TreeSetTest();
        new CollectionTest().collectionStreamTest();

        //java泛型
        new GenericTest().test();

        //二叉树
        JniTest.biTreeTest();

        //二叉搜索树
        JniTest.thrBiTreeTest();

        //栈
        JniTest.stackTest();

        //邻接多重表
        JniTest.AmlGraph();
    }

}
