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
public class ConstructClass implements Cloneable{

    public int value;
    public int[] array; //数组传递的是对象引用，在浅引用是传递的也是数组对象的引用
    public String str;
    public Inner inner;

    public ConstructClass(int value,int[] array,String str,Inner inner){
        this.value = value;
        this.array = array;
        this.str = str;
        this.inner = inner;
    }
    public ConstructClass(ConstructClass constructClass){
        this.value = constructClass.value;
        this.array = constructClass.array;
        this.str = constructClass.str;
        this.inner = constructClass.inner;
        this.value = 3;
        this.array[2] = 4;
        this.str = "123";
    }

    @Override
    public ConstructClass clone() throws CloneNotSupportedException {
        return (ConstructClass)super.clone();
    }

    public static class Inner{

    }
}
