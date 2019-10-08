package cd.myapplication;

import android.renderscript.RenderScript;
import android.util.Log;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.net.URLClassLoader;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/10/4 11:56
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/10/4 11:56
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class StudentInject {

    private static final String TAG = StudentInject.class.getSimpleName();

    public static void injectStudent(){
        try {
            Log.d(TAG,"Student.class.getName()="+Student.class.getName());
            Class clazz = Class.forName(Student.class.getName());
            Annotation[] annotations = clazz.getAnnotations();
            for (Annotation annotation:annotations){
                Log.d(TAG,"annotation="+annotation);
            }
            TbAnnotation tbAnnotation = (TbAnnotation) clazz.getAnnotation(TbAnnotation.class);
            Log.d(TAG,"tbAnnotation.value()="+tbAnnotation.value());

            Field[] fields = clazz.getDeclaredFields();
            for (Field field:fields){
                Log.d(TAG,"field="+field);
                FieldAnnotation fieldAnnotation = field.getAnnotation(FieldAnnotation.class);
                if(fieldAnnotation==null)
                    continue;
                Log.d(TAG,"fieldAnnotation.name()="+fieldAnnotation.name());
            }


            Constructor<Student> constructor = clazz.getDeclaredConstructor(int.class,String.class,int.class);
            Student student = constructor.newInstance(1,"chenda",26);

            Method method = clazz.getDeclaredMethod("setName",String.class);
            method.invoke(student,"chendada");
            Log.d(TAG,"student.getName()="+student.getName());

            Field field = clazz.getDeclaredField("age");
            field.setAccessible(true);
            field.set(student,18);      //报错，不能这样修改私有属性,加上上面一句才可以
            Log.d(TAG,"student.getAge()="+field.get(student));



        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
