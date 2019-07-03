package cd.note.sqlite;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/6/28 21:01
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/6/28 21:01
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class DBManger {
    private final static String TAG = "DBManger";
    private SQLiteHelper myDbHelper;

    DBManger(Context context){
        myDbHelper = new SQLiteHelper(context);
    }

    public void insert(Person person){
        SQLiteDatabase db = myDbHelper.getWritableDatabase();
        db.execSQL("INSERT INTO person(name,phone) values(?,?)",new String[]{person.getName(),person.getPhone()});
    }

    public void delete(int id){
        SQLiteDatabase db = myDbHelper.getWritableDatabase();
        db.execSQL("DELETE FROM person where personid = ?",new String[]{String.valueOf(id)});
    }

    public void update(Person person){
        SQLiteDatabase db = myDbHelper.getWritableDatabase();
        db.execSQL("UPDATE person SET name = ?, phone = ? where personid = ?",new String[]{person.getName(),person.getPhone(), String.valueOf(person.getPersonid())});
    }

    public Person select(int id){
        SQLiteDatabase db = myDbHelper.getReadableDatabase();
        Cursor cursor = db.rawQuery("SELECT * FROM person where personid = ?",new String[]{String.valueOf(id)});
        Person person = null;
        if(cursor.moveToFirst()){
            person = new Person();
            person.setPersonid(cursor.getInt(cursor.getColumnIndex("personid")));
            person.setName(cursor.getString(cursor.getColumnIndex("name")));
            person.setPhone(cursor.getString(cursor.getColumnIndex("phone")));
        }
        cursor.close();
        return person;
    }

    public List<Person> getScroData(int offset,int maxResult){
        List<Person> personList = new ArrayList<>();
        SQLiteDatabase db = myDbHelper.getReadableDatabase();
        Cursor cursor = db.rawQuery("SELECT * FROM person ORDER BY personid ASC LIMIT ?,?",new String[]{String.valueOf(offset), String.valueOf(maxResult)});
        while (cursor.moveToNext()){
            Person person = new Person();
            person.setPersonid(cursor.getInt(cursor.getColumnIndex("personid")));
            person.setName(cursor.getString(cursor.getColumnIndex("name")));
            person.setPhone(cursor.getString(cursor.getColumnIndex("phone")));
            personList.add(person);
        }
        cursor.close();
        return personList;
    }

    public long getCount(){

        SQLiteDatabase db = myDbHelper.getReadableDatabase();
        Cursor cursor = db.rawQuery("SELECT COUNT (*) FROM person ",null);

        cursor.moveToFirst();
        long ret1 = cursor.getLong(0);
        Log.d(TAG,"cursor.getLong(0)="+ret1);

        cursor.close();
        return ret1;
    }

    public void transation(){
        //事务提交
        //persionid=3和persionid=4交换号码，交换成功则事务成功，否则回滚，拿回自己的号码
        SQLiteDatabase dbW = myDbHelper.getWritableDatabase();
        SQLiteDatabase dbR = myDbHelper.getReadableDatabase();
        try {
            dbW.beginTransaction();
            Cursor cursor = dbR.rawQuery("SELECT * FROM person WHERE personid = ?" ,new String[]{String.valueOf(3)});
            cursor.moveToFirst();
            String phone3 = cursor.getString(cursor.getColumnIndex("phone"));
            cursor.close();
            cursor = dbR.rawQuery("SELECT * FROM person WHERE personid = ?" ,new String[]{String.valueOf(4)});
            cursor.moveToFirst();
            String phone4 = cursor.getString(cursor.getColumnIndex("phone"));
            cursor.close();
            Person person3 = select(3);
            person3.setPhone(phone4);
            Person person4 = select(4);
            person4.setPhone(phone3);
            update(person3);
            update(person4);
            dbW.setTransactionSuccessful();
        }finally {
            dbW.endTransaction();
        }
    }

    public void setBlob(byte[] blob){
        SQLiteDatabase db = myDbHelper.getWritableDatabase();
        db.execSQL("INSERT INTO person(img) values (?)", new byte[][]{blob});

    }
}
