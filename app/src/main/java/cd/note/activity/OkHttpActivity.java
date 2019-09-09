package cd.note.activity;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.util.Iterator;
import java.util.Set;
import java.util.concurrent.TimeUnit;

import cd.note.R;
import io.reactivex.Observable;
import io.reactivex.ObservableOnSubscribe;
import io.reactivex.Observer;
import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.disposables.Disposable;
import io.reactivex.schedulers.Schedulers;
import okhttp3.Cache;
import okhttp3.Headers;
import okhttp3.HttpUrl;
import okhttp3.Interceptor;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;
import okhttp3.ResponseBody;
import okio.Buffer;

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

    public void cacheTimeoutInterceptor(){
        Cache cache = new Cache(this.getCacheDir(),10*1024*1024);
        OkHttpClient okHttpClient = new OkHttpClient.Builder()
                .addInterceptor(new myInterceptor(3))
//                .retryOnConnectionFailure(true)//默认重试一次，若需要重试N次，则要实现拦截器。
                .addNetworkInterceptor(new myNetworkInterceptor(20))
                .cache(cache)
                .connectTimeout(10, TimeUnit.SECONDS)
                .readTimeout(20, TimeUnit.SECONDS)
                .writeTimeout(20, TimeUnit.SECONDS)
                .build();
    }

    class myNetworkInterceptor implements Interceptor{

        private int maxCacheTimeSecond = 0;

        public myNetworkInterceptor(int maxCacheTimeSecond) {
            this.maxCacheTimeSecond = maxCacheTimeSecond;
        }

        @NotNull
        @Override
        public Response intercept(@NotNull Chain chain) throws IOException {
            /**
             * 设置在有网络的情况下的缓存时间
             *  在有网络的时候，会优先获取缓存
             * 通过：addNetworkInterceptor 设置
             */
            Request request = chain.request();
            Response originalResponse = chain.proceed(request);
            return originalResponse.newBuilder()
                    .removeHeader("Pragma")// 清除头信息，因为服务器如果不支持，会返回一些干扰信息，不清除下面无法生效
                    .removeHeader("Cache-Control")
                    .header("Cache-Control", "public, max-age=" + maxCacheTimeSecond)
                    .build();

        }
    }

    class myInterceptor implements Interceptor{
        public int maxRetry;//最大重试次数
        private int retryNum = 0;//假如设置为3次重试的话，则最大可能请求4次（默认1次+3次重试）

        public myInterceptor(int maxRetry) {
            this.maxRetry = maxRetry;
        }

        @NotNull
        @Override
        public Response intercept(@NotNull Chain chain) throws IOException {
            Request request = chain.request();

            //设置没有网络的情况下，缓存时间
//            if (!NetworkUtils.isConnected(applicationContext)) {
//                CacheControl tempCacheControl = new CacheControl.Builder()
//                        .onlyIfCached()
//                        .maxStale(maxCacheTimeSecond, TimeUnit.SECONDS)
//                        .build();
//                request = request.newBuilder()
//                        .cacheControl(tempCacheControl)
//                        .build();
//            }

            //http://127.0.0.1/test/upload/img?userName=xiaoming&userPassword=12345
            StringBuffer sb = new StringBuffer();
            String newUrl;

            //URL重定向
            HttpUrl httpUrl = request.url();
            String scheme = httpUrl.scheme();
            String host = httpUrl.host();            //127.0.0.1
            String path = httpUrl.encodedPath();    //  /test/upload/img
            String query = httpUrl.encodedQuery();  //  userName=xiaoming&userPassword=12345
            sb.setLength(0);
            newUrl = sb.append(scheme).append(host).append(path).append("?").append(query).toString();

            //加密数据
            Set<String> queqyList = httpUrl.queryParameterNames();
            Iterator iterator = queqyList.iterator();
            sb.setLength(0);
            sb.append(scheme).append(host).append(path).append("?");
            for(int i=0;i<queqyList.size();i++){
                String name = (String) iterator.next();
                String value = httpUrl.queryParameter(name);
                String newValue = value + 1;    //加密新数据
                sb.append(name).append("=").append(newValue);
                if(iterator.hasNext()){
                    sb.append("&");
                }
            }
            RequestBody body = request.body();
            Buffer buffer = new Buffer();
            body.writeTo(buffer);
            String s = buffer.readUtf8();
            //Gson to Java bean
            //Java bean 字段加密
            //Java bean to Gson
            RequestBody requestBody = RequestBody.create(MediaType.parse("application/json"),s);

            Request.Builder build = request.newBuilder()
                    .post(requestBody)
                    .url(newUrl);

            //Head动态添加
            switch (path){
                case "/test/upload/img":
                    build.addHeader("token","token");
                break;
            }


            //增加日志
            Response response = chain.proceed(build.build());
            if (response != null) {
                ResponseBody responseBody = response.body();
                long contentLength = responseBody.contentLength();
                String bodySize = contentLength != -1 ? contentLength + "-byte" : "unknown-length";

                Log.e("chenda",response.code() + ' '
                        + response.message() + ' '
                        + response.request().url()+' '
                        + bodySize
                );

                Headers headers = response.headers();
                for (int i = 0, count = headers.size(); i < count; i++) {
                    Log.e("chenda",headers.name(i) + ": " + headers.value(i));
                }
            }

            //重试
//            while (!response.isSuccessful() && retryNum < maxRetry) {
//                retryNum++;
//                Log.i("Retry","num:"+retryNum);
//                response = chain.proceed(request);
//            }

            return response;
        }
    }



}
