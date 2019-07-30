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

    //线性表的单链表结构
    public static native int linkListTest();

    //线性表的双向链表结构
    public static native int dulLinkListTest();

    //插入排序
    public static native void insertSortTest();

    //归并排序
    public static native void mergeSortTest();

    //分治法
    public static native void divideConquer();

    //快速排序
    public static native void quickSort();

    //随机排序
    public static native void randomSort();

    //堆排序
    public static native void buildMaxHeapbyMerge();

    //二叉树
    public static native void biTreeTest();

    //线索树
    public static native void thrBiTreeTest();

    //栈
    public static native void stackTest();

    //邻接多重表
    public static native void AmlGraph();
}
