package cd.note.Rxjava;

import android.util.Log;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/7/14 22:05
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/7/14 22:05
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class Translation {

    //金山词霸翻译API
    // URL实例
    // http://fy.iciba.com/ajax.php?a=fy&f=auto&t=auto&w=hello%20world
    // 参数说明：
    // a：固定值 fy
    // f：原文内容类型，日语取 ja，中文取 zh，英语取 en，韩语取 ko，德语取 de，西班牙语取 es，法语取 fr，自动则取 auto
    // t：译文内容类型，日语取 ja，中文取 zh，英语取 en，韩语取 ko，德语取 de，西班牙语取 es，法语取 fr，自动则取 auto
    // w：查询内容

    private final static String TAG = "RxjavaTest";

    private int status;

    private content content;
    private static class content {
        private String from;
        private String to;
        private String vendor;
        private String out;
        private int errNo;
    }

    //定义 输出返回数据 的方法
    public void show() {
        Log.d(TAG, "Translation out="+content.out );
    }

}
