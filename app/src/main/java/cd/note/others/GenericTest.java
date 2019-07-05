package cd.note.others;

import java.util.List;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/7/4 18:03
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/7/4 18:03
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class GenericTest {

    private final static String TAG = "CollectionTest";

    public void test(){

        System.out.printf( "%d, %d 和 %d 中最大的数为 %d\n\n",
                3, 4, 5, maximum( 3, 4, 5 ) );

        System.out.printf( "%.1f, %.1f 和 %.1f 中最大的数为 %.1f\n\n",
                6.6, 8.8, 7.7, maximum( 6.6, 8.8, 7.7 ) );

        System.out.printf( "%s, %s 和 %s 中最大的数为 %s\n","pear",
                "apple", "orange", maximum( "pear", "apple", "orange" ) );
    }

     /**
      * @method          maximum
      * @description    泛型比较大小
      * @param
      * @return
      */
    public static <T extends Comparable<T>> T maximum(T x,T y, T z){
        T max = x;
        if(x.compareTo(y)<0)
            max = y;
        if(y.compareTo(z)<0)
            max = z;

        return max;
    }


}
