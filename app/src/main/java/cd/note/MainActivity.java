package cd.note;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import cd.note.others.Clone;
import cd.note.others.JniTest;

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
    }
}
