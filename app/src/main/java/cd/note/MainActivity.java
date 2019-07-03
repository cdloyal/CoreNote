package cd.note;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import cd.note.Thread.AsyncTaskTest;
import cd.note.Thread.HandlerTest;
import cd.note.Thread.ThreadSync;
import cd.note.Thread.ThreadSyncTest;
import cd.note.memory.MemoryTest;
import cd.note.designmode.Clone;
import cd.note.others.JniTest;
import cd.note.sqlite.SqliteTest;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //浅拷贝
        Clone.shallowCloneTest();

        //深拷贝
        Clone.deepCloneTest();

        //线性表的顺序存储结构
        JniTest.sqListTest();

        //插入排序算法
        JniTest.insertSortTest();
        //归并排序算法
        JniTest.mergeSortTest();

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

        //Handler测试
        HandlerTest.test();

        ThreadSyncTest.test();
//        ThreadSyncTest.test1();

        ThreadSync.test1();

        MemoryTest memoryTest = new MemoryTest();
        memoryTest.test();

        SqliteTest.test(this);
    }
}
