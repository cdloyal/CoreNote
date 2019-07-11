package cd.note.java8;

import android.util.Log;

import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/**
 * 作者：chenda
 * 时间：2019/7/11:11:40
 * 邮箱：
 * 说明：
 */
public class Java8 {

    private final static String TAG = "Java8";

    public void lambdaTest(){
        List<String> list1 = Arrays.asList("Baidu" , "Taobao" , "Runoob" , "Google", "Sina" );
        List<String> list2 = Arrays.asList("Baidu" , "Taobao" , "Runoob" , "Google", "Sina" );
        sortUsingJava7(list1);
        sortUsingJava8(list2);
        Log.d(TAG,"list1="+list1);
        Log.d(TAG,"list1="+list2);

        MathOperation mathOperation1 = (a,b)-> a+b;
        MathOperation mathOperation2 = (a,b)-> a-b;

        Log.d(TAG,"mathOperation1 a+b="+mathOperation1.operation(5,8));
        Log.d(TAG,"mathOperation2 a-b="+mathOperation2.operation(5,8));

        int a=5,b=8;
        Log.d(TAG,"mathOperation2 a-b="+mathOperation2.operation(a,b));
        a=10;
    }

    private static void sortUsingJava7(List<String> list){
        Collections.sort(list, new Comparator<String>() {
            @Override
            public int compare(String o1, String o2) {
                return o1.compareTo(o2);
            }
        });
    }

    private static void sortUsingJava8(List<String> list){
        Collections.sort(list,(s1,s2)->s1.compareTo(s2));
    }

    interface MathOperation{
        int operation(int a,int b);
    }
}
