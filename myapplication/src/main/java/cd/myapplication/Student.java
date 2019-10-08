package cd.myapplication;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/10/4 11:45
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/10/4 11:45
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */

@TbAnnotation("tb_student")
public class Student {

    @FieldAnnotation(name = "id",attr = "int",length = 10)
    private int id;
    @FieldAnnotation(name = "sname",attr = "String",length = 10)
    private String name;
    @FieldAnnotation(name = "age",attr = "int",length = 3)
    private int age;

    //javabean必须要有无参构造方法
    public Student() {
    }

    public Student(int id, String name, int age) {
        this.id = id;
        this.name = name;
        this.age = age;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
}
