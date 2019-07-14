package cd.note.Rxjava;


import io.reactivex.Observable;
import retrofit2.Response;
import retrofit2.http.GET;
import retrofit2.http.Query;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/7/14 22:09
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/7/14 22:09
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public interface RetrofitInterface {
    // http://fy.iciba.com/ajax.php?a=fy&f=auto&t=auto&w=hello%20world
    @GET("/ajax.php")
    Observable<Translation> getAjax(@Query("a") String a,@Query("f") String f,@Query("t") String t,@Query("w") String w);
//    @GET("ajax.php?a=fy&f=auto&t=auto&w=hi%20world")
//    Observable<Translation> getAjax();
}
