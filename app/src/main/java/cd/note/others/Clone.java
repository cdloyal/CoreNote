package cd.note.others;

import android.util.Log;

import java.io.Serializable;

import cd.libcorenote.CloneUtils;

/**
  * @Description:    深浅复制的问题
  * @Author:         陈达
  * @CreateDate:     2019/6/16 12:37
  * @UpdateUser:     陈达
  * @UpdateDate:     2019/6/16 12:37
  * @UpdateRemark:   更新说明：
  * @Version:        1.0
 */
public class Clone  implements Serializable,Cloneable{

    //基本数据类型，拷贝其值，比如int、float等。
    public int value;

    //若变量为String字符串，则拷贝其地址引用。但是在修改时，它会从字符串池中重新生成一个新的字符串，原有紫都城对象保持不变。
    public String str;

    //数组和对象传递的是对象的引用
    public int[] array;
    public Inner inner;

    public Clone(){}

    public Clone(int value, int[] array, String str, Inner inner){
        this.value = value;
        this.array = array;
        this.str = str;
        this.inner = inner;
    }
    public Clone(Clone constructClass){
        this.value = constructClass.value;
        this.array = constructClass.array;
        this.str = constructClass.str;
        this.inner = constructClass.inner;
        this.value = 3;
        this.array[2] = 4;
        this.str = "123";
    }

    public static class Inner implements Serializable {

        private static final long serialVersionUID = -4618336865807323074L;
    }

    @Override
    protected Clone clone() throws CloneNotSupportedException {
        return (Clone)super.clone();
    }


    public static void deepCloneTest(){
        int [] array = new int[]{1,2,3};
        Clone.Inner inner = new Clone.Inner();
        Clone copy = new Clone(5,array,"abc",inner);
        Clone newCopy = CloneUtils.clone(copy);
        Log.d("chenda","CloneDeep newCloneDeep.hashCode="+newCopy.hashCode());
        Log.d("chenda","CloneDeep cloneDeep.hashCode="+copy.hashCode());
        Log.d("chenda","CloneDeep newCloneDeep.inner.hashCode="+newCopy.inner.hashCode());
        Log.d("chenda","CloneDeep cloneDeep.inner.hashCode="+copy.inner.hashCode());
        Log.d("chenda","CloneDeep newCloneDeep.array.hashCode="+newCopy.array.hashCode());
        Log.d("chenda","CloneDeep cloneDeep.array.hashCode="+copy.array.hashCode());
    }

    public static void shallowCloneTest(){
        int [] array = new int[]{1,2,3};
        Clone.Inner inner = new Clone.Inner();
        Clone copy = new Clone(5,array,"abc",inner);
        Clone newCopy = new Clone(copy);
        Log.d("chenda","CloneShallow cloneShallow.value="+copy.value);
        Log.d("chenda","CloneShallow newCloneShallow.value="+newCopy.value);
        Log.d("chenda","CloneShallow newCloneShallow.array[2]="+newCopy.array[2]);
        Log.d("chenda","CloneShallow cloneShallow.str="+copy.str);
        Log.d("chenda","CloneShallow newCloneShallow.str="+newCopy.str);
        Log.d("chenda","CloneShallow newCloneShallow.hashCode="+newCopy.hashCode());
        Log.d("chenda","CloneShallow cloneShallow.hashCode="+copy.hashCode());


//        newCloneShallow = cloneShallow;     //newCloneShallow和cloneShallow指向同一对象
        try {
            newCopy = copy.clone(); //浅复制，数组和对象传递的是对象的引用
        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }
        Log.d("chenda","CloneShallow newCloneShallow.hashCode="+newCopy.hashCode());
        Log.d("chenda","CloneShallow cloneShallow.hashCode="+copy.hashCode());
        Log.d("chenda","CloneShallow newCloneShallow.array.hashCode="+newCopy.array.hashCode());
        Log.d("chenda","CloneShallow cloneShallow.array.hashCode="+copy.array.hashCode());
        Log.d("chenda","CloneShallow newCloneShallow.inner.hashCode="+newCopy.inner.hashCode());
        Log.d("chenda","CloneShallow cloneShallow.inner.hashCode="+copy.inner.hashCode());
    }
}
