package cd.myapplication;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/10/4 11:46
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/10/4 11:46
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */

@Target(value = {ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
public @interface TbAnnotation {
    String value(); //类和一个表对应，value是表名称
}
