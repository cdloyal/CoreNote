package cd.note;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //浅拷贝
        Clone.shallowCloneTest();

        //深拷贝
        Clone.deepCloneTest();


        DataStructure.test();
    }
}
