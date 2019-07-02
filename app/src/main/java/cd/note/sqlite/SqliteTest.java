package cd.note.sqlite;

import android.content.Context;
import android.util.Log;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/6/28 17:16
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/6/28 17:16
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class SqliteTest {

    //https://www.runoob.com/w3cnote/android-tutorial-sqlite-intro.html

    private final static String TAG = "SqliteTest";
    public static void test(Context context){
        DBManger dbManger = new DBManger(context);
        for(int i=0;i<10;i++){
            Person person = new Person();
            person.setName("name-"+i);
            person.setPhone("156666666666"+i);
            dbManger.insert(person);
        }
        Log.d(TAG,"dbManger.getCount()="+dbManger.getCount());
        dbManger.delete(1);
        Log.d(TAG,"delete 1 dbManger.getCount()="+dbManger.getCount());
        Log.d(TAG,"dbManger.select(2).getPersonid()="+dbManger.select(2).getPersonid());
        Person p = new Person(8,"ccc","111");
        dbManger.update(p);
        dbManger.transation();
        for(Person person : dbManger.getScroData(0,9))
            Log.d(TAG,person.getPersonid()+person.getName()+person.getPhone());

    }

}
