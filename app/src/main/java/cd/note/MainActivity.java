package cd.note;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        int [] array = new int[]{1,2,3};
        ConstructClass constructClass = new ConstructClass(5,array,"abc");
        ConstructClass newConstructClass = new ConstructClass(constructClass);
        Log.d("chenda","constructClass.value="+constructClass.value);
        Log.d("chenda","newConstructClass.value="+newConstructClass.value);
        Log.d("chenda","newConstructClass.array[2]="+newConstructClass.array[2]);
        Log.d("chenda","constructClass.str="+constructClass.str);
        Log.d("chenda","newConstructClass.str="+newConstructClass.str);
    }
}
