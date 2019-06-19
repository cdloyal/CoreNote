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
public class DataStructure {

    static {
        System.loadLibrary("corenote");
    }

    public static native int test();


}
