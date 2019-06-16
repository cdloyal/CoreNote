package cd.note;

/**
  * @Description:    构造函数，实例复制的问题
  * @Author:         陈达
  * @CreateDate:     2019/6/16 12:37
  * @UpdateUser:     陈达
  * @UpdateDate:     2019/6/16 12:37
  * @UpdateRemark:   更新说明：
  * @Version:        1.0
 */
public class ConstructClass {

    public int value;
    public int[] array;
    public String str;

    public ConstructClass(int value,int[] array,String str){
        this.value = value;
        this.array = array;
        this.str = str;
    }
    public ConstructClass(ConstructClass constructClass){
        this.value = constructClass.value;
        this.array = constructClass.array;
        this.str = constructClass.str;
        this.value = 3;
        this.array[2] = 4;
        this.str = "123";
    }
}
