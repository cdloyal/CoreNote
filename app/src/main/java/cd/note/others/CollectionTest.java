package cd.note.others;

import android.os.Build;
import android.support.annotation.RequiresApi;
import android.util.Log;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.TreeSet;
import java.util.stream.Collectors;

/**
 * 作者：chenda
 * 时间：2019/7/4:9:49
 * 邮箱：
 * 说明：
 */
public class CollectionTest {

    /**
     * Collection接口继承了java迭代接口Iterable
     * 其子类有Set、List、Queue
     *
     * 1、List接口
     *  有序、可重复
     *
     *  1)ArrayList
     *      基于数组的线性表，默认长度10；长度可动态变化，扩容方案“原始长度*3/2+1”
     *      随机访问速度快；不适合频繁插入和删除操作
     *      线程不安全
     *      遍历方法for(Object o : objects)、转换为数组list.toArray(array)、Iterator遍历
     *
     *  2)LinkedList
     *      基于链表的线性表、双向循环链表的链式线性表
     *      随机访问速度慢；适合频繁插入和删除
     *      线程不安全
     *      LinkedList继承了Queue接口，可用作堆栈
     *
     *  3)Vector
     *      基于数组的线性表，默认长度10，可设置默认长度；长度可动态变化，可设置扩容方案,默认“原始长度*2”，了解Vector.size()、Vector.capacity
     *      随机访问速度快；不适合频繁插入和删除操作
     *      线程安全
     *
     * 2、Set接口
     *  无序、唯一
     *      Set接口根据对象的hashcode和equals方法判断两个对象是否相同
     *      这里讲一下“equals和==的区别”
     *          ==：比较的是变量（栈）内存中存放的对象（堆）内存的地址
     *          equal:Object类有equal方法，其内部实现也是==，return (this==obj)
     *                  String类由于重写了equal方法，用来比较两个对象的内容是否相等
     *       所以Set接口，存放的对象如果没有重写equal方法，比较的是地址
     *
     *  1)HashSet
     *      基于哈希表（无序、唯一、位置固定） extends HashMap
     *      允许存放一个null值
     *      唯一性保证：hashcode()和equals()
     *
     *
     *  2)LinkHashSet
     *      基于链表和哈希表（FIFO插入有序先进先出、唯一）extends HashSet
     *      有序保证：链表
     *      唯一性保证：hashcode()和equals()
     *
     *  3)TreeSet
     *      基于红黑树（唯一、有序）extends TreeMap
     *      排序：自然排序（Comparable接口）、比较器排序(Comparator接口)
     *      唯一性保证：根据比较的返回值是否为0来决定
     *
     * 3、Map接口
     *  1)HashMap
     *      无序，线程不安全
     *      HashMap允许null
     *      基于hash数组实现，若key的hash值相同则使用链表方式进行保存
     *      新建一个HashMap时,默认的话会初始化一个大小为16，负载因子为0.75的空的HashMap
     *      Hash的简单算法，就是给你一个Hash因子，通过对该元素的hashCode简单的求余，来实现对其快速的定位和索引。
     *      现在我们需要看一下当数据量已经超过初始定义的负载因子时，再哈希是重新建一个指定容量的数组，然后将每个元素重新计算它要放的位置，这个工作量确实是很大的。
     *
     *
     *
     *  2)TreeMap
     *      有序，线程不安全
     *
     *  3)HashTable
     *      无序，线程安全
     *      Hashtable不允许null
     *
     *  4)LinkedHashMap
     *      顺序
     *
     *  5)ConcurrentHashMap
     *
     *
     *
     * 可以通过下面方法获取线程安全的集合
     * List list = Collections.SynchronizedList(new List<>());
     * Set set = Collections.SynchronizedSet(new Set<>());
     * Map map = Collections.SynchronizedMap(new Map<>());
     *
     *
     *
     * 栈（Stack）
     *
     * Properties 继承于 Hashtable.表示一个持久的属性集.属性列表中每个键及其对应值都是一个字符串。
     * */

    private final static String TAG = "CollectionTest";


    @RequiresApi(api = Build.VERSION_CODES.N)
    public void collectionStreamTest(){

//        int A[] = {1, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9};
        int A[] = new int[1];
        A[0] = 4;
        Log.d(TAG,"al="+A);
        ArrayList al = new ArrayList();
        al.add(A[0]);
        A[0] = 5;
        Log.d(TAG,"al="+A);
        Log.d(TAG,"al="+al);

        Student stu1 = new Student("name1",5);
        ArrayList<Student> all = new ArrayList();
        all.add(stu1);
        stu1.setName("name2");
        stu1.setArg(6);
        Log.d(TAG,"all="+all.get(0).getName()+all.get(0).getArg());

        //https://juejin.im/post/5b07f4536fb9a07ac90da4e5
        List<Integer> list = Arrays.asList(1, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9);
        Log.d(TAG,"list="+list);

        //过滤
        List<Integer> filter = list.stream().filter(integer -> integer>3).collect(Collectors.toList());
        Log.d(TAG,"list filter(>3)="+filter);

        //自己写的filter
        ArrayList arrayList = new ArrayList();
        arrayList.addAll(list);
        List<Integer> myFilter = myFilter(arrayList, (Integer a) -> a>5);
        Log.d(TAG,"list myFilter(>5) ="+myFilter);


        //去重
        List<Integer> distinct = list.stream().distinct().collect(Collectors.toList());
        Log.d(TAG,"list distinct="+distinct);

        //限制
        List<Integer> limit = list.stream().limit(3).collect(Collectors.toList());
        Log.d(TAG,"list limit(3)="+limit);

        //跳过
        List<Integer> skip = list.stream().skip(3).collect(Collectors.toList());
        Log.d(TAG,"list skip(3)="+skip);

        //映射
        List<String> map = list.stream().map(integer -> "-"+integer).collect(Collectors.toList());
        Log.d(TAG,"list map(3)="+map);

        list.iterator();
    }

    private interface MyPredicate<T>{
        public boolean test(T a);
    }
    private <T> List myFilter(ArrayList<T> list, MyPredicate<T> predicate){
        List<T> newList = new ArrayList<T>();
        for(T t : list){
            if(predicate.test(t))
                newList.add(t);
        }
        return newList;
    }

    public void TreeSetTest(){
        Student s1=new Student("zhangsan",20);
        Student s2=new Student("lis",22);
        Student s3=new Student("wangwu",24);
        Student s4=new Student("chenliu",26);
        Student s5=new Student("zhangsan",22);
        Student s6=new Student("qianqi",24);
        Student s7=new Student("zhangsan",20);

        TreeSet<Student> treeSet = new TreeSet();
        treeSet.add(s1);
        treeSet.add(s2);
        treeSet.add(s3);
        treeSet.add(s4);
        treeSet.add(s5);
        treeSet.add(s6);
        treeSet.add(s7);

        //遍历
        for(Student s:treeSet){
            Log.d(TAG,s.getName()+"-----------"+s.getArg());
        }
    }

    private class Student implements Comparable<Student>{

        private String name;
        private int arg;

        public Student(String name, int arg) {
            this.name = name;
            this.arg = arg;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

        public int getArg() {
            return arg;
        }

        public void setArg(int arg) {
            this.arg = arg;
        }

        @Override
        public int compareTo(Student o) {
            //return -1; //-1表示放在红黑树的左边,即逆序输出
            //return 1;  //1表示放在红黑树的右边，即顺序输出
            //return o;  //表示元素相同，仅存放第一个元素
            if(this.name.length()-o.name.length() < 0 ){
                return -1;
            }else if(this.name.length()-o.name.length() > 0 ){
                return 1;
            }

            if(this.name.compareTo(o.name) < 0 )
                return -1;
            else if(this.name.compareTo(o.name) > 0 )
                return 1;

            if(this.arg-o.arg < 0 )
                return -1;
            else if(this.arg-o.arg > 0 )
                return 1;

            return 0;
        }
    }

}
