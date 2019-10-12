package cd.myapplication;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import me.jessyan.autosize.internal.CustomAdapt;

public class MainActivity extends AppCompatActivity implements CustomAdapt {



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        EventBus.getDefault().register(this);

        StudentInject.injectStudent();
    }

    @Override
    public boolean isBaseOnWidth() {
        return true;
    }

    @Override
    public float getSizeInDp() {
        return 0;
    }

//    @MyAnnotation(id=0,name="cd")
    @MyAnnotation("cd") //只有一个参数可以省略参数名
    public void testMyAnnotation(){

    }
}
