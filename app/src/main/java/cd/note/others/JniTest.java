package cd.note.others;

/**
  * @Description:    jni实现的数据结构
  * @Author:         陈达
  * @CreateDate:     2019/6/16 15:00
  * @UpdateUser:     陈达
  * @UpdateDate:     2019/6/16 15:00
  * @UpdateRemark:   更新说明：
  * @Version:        1.0
  */
public class JniTest {

    static {
        System.loadLibrary("corenote");
    }

    //线性表的顺序存储结构
    public static native int sqListTest();

    //线性表的顺序链式结构
    public static native int linkListTest();

    //插入排序
    public static native void insertSortTest();

    //归并排序
    public static native void mergeSortTest();
}
