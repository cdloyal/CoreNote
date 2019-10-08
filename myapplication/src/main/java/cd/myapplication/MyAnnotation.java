package cd.myapplication;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/10/4 11:09
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/10/4 11:09
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */

@Target(value = {ElementType.METHOD})
@Retention(RetentionPolicy.RUNTIME)
public @interface MyAnnotation {

//    int id() default -1;
//    String name();
//    String[] school() default {"taochong","huicheng"};

    String value();

}
