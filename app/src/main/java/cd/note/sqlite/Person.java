package cd.note.sqlite;

import android.database.sqlite.SQLiteDatabase;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/6/28 20:57
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/6/28 20:57
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class Person {

    private int personid;
    private String name;
    private String phone;

    public Person() {}
    public Person(int personid, String name, String phone) {
        this.personid = personid;
        this.name = name;
        this.phone = phone;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public int getPersonid() {
        return personid;
    }

    public void setPersonid(int personid) {
        this.personid = personid;
    }


}
