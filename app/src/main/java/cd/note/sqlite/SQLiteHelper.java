package cd.note.sqlite;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/6/28 20:31
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/6/28 20:31
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class SQLiteHelper extends SQLiteOpenHelper {

    private final static String DBNEME = "my.db";
    private final static int VERSION = 3;
    public SQLiteHelper(Context context) {
        super(context, DBNEME, null,VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        sqLiteDatabase.execSQL("CREATE TABLE person(personid INTEGER PRIMARY KEY AUTOINCREMENT,name VARCHAR(20))");
    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i1) {
        sqLiteDatabase.execSQL("ALTER TABLE person ADD phone VARCHAR(12)");
    }
    /**
     * public void onUpgrade(SQLiteDatabase db, ConnectionSource connectionSource,
     *             int arg2, int arg3) {
     *     switch(arg2){
     *         case 1:
     *             db.execSQL(第一个版本的建表语句);
     *         case 2:
     *             db.execSQL(第二个版本的建表语句);
     *         case 3:
     *             db.execSQL(第三个版本的建表语句);
     *     }
     * }
     * */

    /**
     * 答：呵呵，给你跪了，当然，也有解决办法，下面说下思路：
     *
     * 1.将旧表改名成临时表: ALTER TABLE User RENAME TO _temp_User;
     *
     * 2.创建新表: CREATE TABLE User (u_id INTEGER PRIMARY KEY,u_name VARCHAR(20),u_age VARCHAR(4));
     *
     * 3.导入数据； INSERT INTO User SELECT u_id,u_name,"18" FROM _temp_User; //原表中没有的要自己设个默认值
     *
     * 4.删除临时表； DROP TABLE_temp_User;
     * */


}
