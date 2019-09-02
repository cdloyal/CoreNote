package cd.note.activity;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import java.io.IOException;

import cd.note.R;
import io.reactivex.Observable;
import io.reactivex.ObservableOnSubscribe;
import io.reactivex.Observer;
import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.disposables.Disposable;
import io.reactivex.schedulers.Schedulers;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/9/1 12:37
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/9/1 12:37
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class OkHttpActivity extends Activity implements View.OnClickListener {
    private final static MediaType MEDIA_TYPE_JSON = MediaType.parse("application/json; charset=utf-8");
    private TextView tv_response;
    private OkHttpClient client;

    @Override
    protected void onCreate( Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_okhttp);
        /**
         * OKHttp是一款高效的HTTP客户端，支持链接同一地址的链接共享同一个socket，
         * 通过连接池来减少响应延时，还有透明gzip压缩，请求缓存等优势
         * 核心主要有路由、连接协议、拦截器、代理、安全性认证、连接池以及网络适配
         * 拦截器主要指添加，移除或者转换请求或者回应的头部信息
         *
         * 主要功能：
         *  联网请求文本数据
         *  大文件下载
         *  大文件上传
         *  请求图片
         *
         * 使用OkHttpClient发起Request请求，返回Response回应
         * Http的请求HEAD\DATA封装到Request对象当中
         * Http的响应HEAD\DATA封装到Response对象当中
         *
         * 都可以添加HEAD,head由key-value键值对组成
         * GET方法,一般没有DATA域
         * POST方法，一定有DATA域，Requestbody封装(Media-type + data)，Media-type指定数据类型: "application/json; charset=utf-8"
         *
         * 大文件下载
         *  一般用一个tag作为唯一的一个下载标志，有准备完成、进度、下载完成回调
         *
         * 大文件上传
         *   MultipartBody.FORM
         *
         * 请求图片
         * 
         * */

        client = new OkHttpClient();
        findViewById(R.id.btn_get).setOnClickListener(this);
        findViewById(R.id.btn_post).setOnClickListener(this);
        tv_response = findViewById(R.id.tv_response);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn_get:
                request(emitter -> emitter.onNext(get("http://api.m.mtime.cn/PageSubArea/TrailerList.api")));
                break;
            case R.id.btn_post:
                request(emitter -> emitter.onNext(post("http://api.m.mtime.cn/PageSubArea/TrailerList.api","")));
                break;
            default:
                break;
        }
    }


    private void request(ObservableOnSubscribe<String> observableOnSubscribe){
        tv_response.setText("");
        Observable.create(observableOnSubscribe)
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(new Observer<String>() {
                    @Override
                    public void onSubscribe(Disposable d) {

                    }

                    @Override
                    public void onNext(String s) {
                        tv_response.setText(s);
                    }

                    @Override
                    public void onError(Throwable e) {
                        e.printStackTrace();
                    }

                    @Override
                    public void onComplete() {

                    }
                });
    }

    /**
     * GET请求
     * */
    private String get(String url) throws IOException {

        Request request = new Request.Builder()
                .url(url)
                .build();
        Response response = client.newCall(request).execute();
        return response.body().string();
    }

    /**
     * POST请求
     * */
    private String post(String url,String json) throws IOException {
        RequestBody body = RequestBody.create(MEDIA_TYPE_JSON,json);
        Request request = new Request.Builder()
                .url(url)
                .post(body)
                .build();
        Response response = client.newCall(request).execute();
        return response.body().string();
    }



}
