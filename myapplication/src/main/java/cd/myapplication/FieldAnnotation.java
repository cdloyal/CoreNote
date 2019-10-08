package cd.myapplication;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/10/4 11:50
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/10/4 11:50
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */

@Target(value = {ElementType.FIELD})
@Retention(RetentionPolicy.RUNTIME)
public @interface FieldAnnotation {
    String name(); //表字段名称
    String attr(); //表字段类型
    int length();   //表字段长度
}
