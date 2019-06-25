package cd.note.designmode;

import android.content.Context;

/**
 * @Description: 单例模式
 * @Author: 陈达
 * @CreateDate: 2019/6/16 14:14
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/6/16 14:14
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class SingleTon {
    private Context context;

    private SingleTon() {
    }

//    private SingleTon instance;

    //多线程下可能创建两个instance，
//    public SingleTon getInstance() {
//        if (instance == null)
//            instance = new SingleTon();
//        return instance;
//    }

    //效率不高
//    public SingleTon getInstance(){
//        synchronized (SingleTon.class){
//            if(instance==null)
//                instance = new SingleTon();
//        }
//        return instance;
//    }

    //实现复杂
//    public SingleTon getInstance() {
//        if (instance == null)
//            synchronized (SingleTon.class) {
//                if (instance == null)
//                    instance = new SingleTon();
//            }
//        return instance;
//    }



    //饿汉模式，类加载时就生成实例，当类很大的时候，占用过多资源
//    private static SingleTon instance = new SingleTon();
//    public SingleTon getInstance() {
//        return instance;
//    }

    //和饿汉模式一样，是靠JVM保证类的静态成员只能被加载一次的特点，这样就从JVM层面保证了只会有一个实例对象
    //加载一个类时，其内部类不会同时被加载。一个类被加载，当且仅当其某个静态成员（静态域、构造器、静态方法等）被调用时发生。
    private static class SingleTonInner{
        private static SingleTon singleTon = new SingleTon();
    }
    public static SingleTon getInstance(Context context){
        return SingleTonInner.singleTon;
    }

}
