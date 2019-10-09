package cd.note.Rxjava;


import android.os.Build;
import androidx.annotation.RequiresApi;
import android.text.TextUtils;
import android.util.Log;

import com.jakewharton.retrofit2.adapter.rxjava2.RxJava2CallAdapterFactory;

import org.reactivestreams.Subscriber;
import org.reactivestreams.Subscription;

import java.io.IOException;
import java.util.concurrent.TimeUnit;

import io.reactivex.BackpressureStrategy;
import io.reactivex.Flowable;
import io.reactivex.FlowableOnSubscribe;
import io.reactivex.Observable;
import io.reactivex.ObservableEmitter;
import io.reactivex.ObservableOnSubscribe;
import io.reactivex.ObservableSource;
import io.reactivex.Observer;
import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.annotations.NonNull;
import io.reactivex.disposables.Disposable;
import io.reactivex.functions.BiFunction;
import io.reactivex.functions.Consumer;
import io.reactivex.functions.Function;
import io.reactivex.schedulers.Schedulers;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

/**
 * 作者：chenda
 * 时间：2019/7/11:15:23
 * 邮箱：
 * 说明：
 */
public class RxjavaTest {

    private final static String TAG = "RxjavaTest";

    public void test(){

        /**
         *
		 https://blog.csdn.net/suyimin2010/article/details/92413622
         *
         * https://blog.csdn.net/carson_ho/article/details/79168723     这个博客作者666
         *
         * https://www.jianshu.com/p/6e71e31c5d3d   第五篇实例要看
         *
         * 函数响应式编程：是一种通过一些列函数的组合调用来发射、转变、监听，响应数据流的编程泛式
         * 在RxJava中，函数响应式编程具体表现为一个观察者（Observer）订阅一个可观察对象（Observable），
         * 通过创建可观察对象发射数据流，经过一系列操作符（Operators）加工处理和线程调度器（Scheduler）
         * 在不同线程间的转发，最后由观察者接受并做出响应的一个过程。
         *
         * Operator操作符
         * 创建：创建一个可观察对象Oberservable并发送数据
         * 过滤：从Oberservable发送的数据中取特定的值
         * 变换：对Oberservable发送的数据进行变换操作
         * 组合：聚合多个Oberservable,例如：{1,2,3}+{4,5,6,7}->{12,34,56,7}
         * 聚合：组合多个Oberservable,例如：{1,2,3}+{4,5,6}->{1,2,3,4,5,6}
         *
         * Schedulers.io( )：
         * Schedulers.newThread( )：
         * Schedulers.computation()：
         * Schedulers.trampoline():：在当前线程立即执行任务
         * Schedulers.single()：
         * Scheduler.from(@NonNull Executor executor)：指定一个线程调度器，
         * AndroidSchedulers.mainThread()：
         *
         * */


        /**
         * 如果在请求的过程中Activity已经退出了, 这个时候如果回到主线程去更新UI, 那么APP肯定就崩溃了
         * CompositeDisposable compositeDisposable = new CompositeDisposable();
         * compositeDisposable.add();
         * compositeDisposable.clear();
         * */

        operation();


        //无条件轮询
//        noCondRepeat();

        //有条件轮询 RepeatWhen: onComplete()触发重试
//        CondRepeat();

        //retryWhen： onError()触发重试
        retryWhen();

        //flatMap:解决嵌套
        //第二个请求依赖第一个请求，登录依赖注册的信息
        flatMap();

        //concat和firstElement结合：按顺序以不同方式做一件事，一个成功，后面不用再做
        concat();

    }

    private void concat() {
        //1.首先获取内存缓存中的数据，如果数据为空，获取硬盘缓存中的数据。
        //2.获取硬盘缓存中的数据，如果硬盘缓存中数据为空，则从网络中获取数据。
        //3.获取网络中的数据。

        String memory = null; //内存缓存的数据
        String disk = "磁盘中的数据";
        String netWorkData = "网络中的数据";


        Observable<String> observable1 = Observable.create(new ObservableOnSubscribe<String>() {
            @Override
            public void subscribe(ObservableEmitter<String> emitter) throws Exception {
                if(TextUtils.isEmpty(memory)){
                    emitter.onComplete();       //onComplete
                    return;
                }
                emitter.onNext(memory);         //onNext
            }
        });

        Observable<String> observable2 = Observable.create(new ObservableOnSubscribe<String>() {
            @Override
            public void subscribe(ObservableEmitter<String> emitter) throws Exception {
                if(TextUtils.isEmpty(disk)){
                    emitter.onComplete();       //onComplete
                    return;
                }
                emitter.onNext(disk);         //onNext
            }
        });
        Observable<String> observable3 = Observable.create(new ObservableOnSubscribe<String>() {
            @Override
            public void subscribe(ObservableEmitter<String> emitter) throws Exception {
                if(TextUtils.isEmpty(netWorkData)){
                    emitter.onComplete();       //onComplete
                    return;
                }
                emitter.onNext(netWorkData);         //onNext
            }
        });

        Observable.concat(observable1,observable2,observable3)
                // 2. 通过firstElement()，从串联队列中取出并发送第1个有效事件（Next事件），即依次判断检查memory、disk、network
                .firstElement()
                .subscribe(new Consumer<String>() {
                    @Override
                    public void accept(String s) throws Exception {
                        Log.d(TAG,s);
                    }
                });

    }

    private void flatMap(){
        int id = 123;
        Observable.just(id)
                .doOnNext(new Consumer<Integer>() {
                    @Override
                    public void accept(Integer integer) throws Exception {
                        Log.d(TAG,"register success,id="+id);
                    }
                })
                .observeOn(Schedulers.io())     //登录还要在IO线程
                .flatMap(new Function<Integer, ObservableSource<Integer>>() {
                    @Override
                    public ObservableSource<Integer> apply(Integer integer) throws Exception {
                        return Observable.just(integer);
                    }
                })
                .subscribeOn(AndroidSchedulers.mainThread())
                .subscribe(new Consumer<Integer>() {
                    @Override
                    public void accept(Integer integer) throws Exception {
                        Log.d(TAG,"login success,id="+id);
                    }
                });
    }


    private void operation(){
        //https://www.jianshu.com/p/b39afa92807e
        //Observable.interval(3, TimeUnit.SECONDS).subscribe(System.out::println);
        //Observable.range(5, 10).subscribe(i -> System.out.println("1: " + i));

        Observable.create((ObservableOnSubscribe<Integer>) emitter ->{
            emitter.onNext(1);
            emitter.onNext(2);
            emitter.onComplete();
            Log.d(TAG,"emitter.onNext(3);");    //onComplete还是会执行，但是Observer订阅已断开
            emitter.onNext(3);
        }).subscribe(new Observer<Integer>() {
            private Disposable disposable;
            @Override
            public void onSubscribe(Disposable d) {
                disposable = d;
            }

            @Override
            public void onNext(Integer integer) {
                Log.d(TAG,"onNext,"+integer);
                if(integer==1)
                    disposable.dispose();       //emitter.onNext(2); 还是会发射，但是Observer订阅已断开
            }

            //onError与onComplete互斥，两个方法只能调用一个不能同时调用
            //用来发送异常通知，只发送一次，若多次调用只发送第一条
            @Override
            public void onError(Throwable e) {
                Log.d(TAG,"onError");
            }

            //用来发送完成通知，只发送一次，若多次调用只发送第一条
            @Override
            public void onComplete() {
                Log.d(TAG,"onComplete");
            }
        });

        //defer:订阅的时候才产生Observable
        Observable<Long> observable = Observable.defer(() -> Observable.just(System.currentTimeMillis()));
        observable.subscribe((Long i) -> Log.d(TAG,String.valueOf(i)));
        System.out.println();
        observable.subscribe((Long i) -> Log.d(TAG,String.valueOf(i)));

        //empty()：创建一个不发射任何数据但是正常终止的Observable；
        //never()：创建一个不发射数据也不终止的Observable；
        //error(Throwable exception)：创建一个不发射数据以一个错误终止的Observable，它有几个重载版本，这里给出其中的一个
        Observable.empty().subscribe(i->Log.d(TAG,"empty() next"),e->Log.d(TAG,"empty() error"),()->Log.d(TAG,"empty() complete"));
        Observable.never().subscribe(i->Log.d(TAG,"never() next"),e->Log.d(TAG,"never() error"),()->Log.d(TAG,"never() complete"));
        Observable.error(new Exception("Observable.error")).subscribe(i->Log.d(TAG,"error() next"),e->Log.d(TAG,"error() error"),()->Log.d(TAG,"error() complete"));

        //from
        //单个元素发送
        Observable.fromArray(new Integer[]{1,3,2,5}).subscribe(integer -> Log.d(TAG,"fromArray() "+integer));

        //just
        //发送两个数组
        Observable.just(new Integer[]{1,3,2,5},new Integer[]{1,4,5,5}).subscribe(array -> Log.d(TAG,"just() "+array.length));

        //zip聚合，还有zipwith
        //String emit : A
        //String emit : B
        //String emit : C
        //zip : accept : A1
        //Integer emit : 1
        //zip : accept : B2
        //Integer emit : 2
        //zip : accept : C3
        //Integer emit : 3
        //Integer emit : 4
        //Integer emit : 5
        Observable.zip(getStringObservable(), getIntegerObservable(), new BiFunction<String, Integer, String>() {
            @Override
            public String apply(@NonNull String s, @NonNull Integer integer) throws Exception {
                return s + integer;
            }
        }).subscribe(new Consumer<String>() {
            @Override
            public void accept(@NonNull String s) throws Exception {
                Log.d(TAG, "zip : accept : " + s + "\n");
            }
        });

        //concat、concatWith、mergeWith
        //在操作符 concat 中，只有调用 onComplete 之后才会执行下一个 Observable
        //concat : 1
        //concat : 2
        //concat : 3
        //concat : 4
        //concat : 5
        //concat : 6
        Observable.concat(Observable.just(1,2,3), Observable.just(4,5,6))
                .subscribe(new Consumer<Integer>() {
                    @Override
                    public void accept(@NonNull Integer integer) throws Exception {
                        Log.d(TAG, "concat : "+ integer + "\n" );
                    }
                });

        //map做的事情：把二箱鸡蛋分别加工成煎蛋，还是放成原来的两箱，分给2组学生；
        //flatMap做的事情：把二箱鸡蛋分别加工成煎蛋，然后放到一起【10个煎蛋】，分给10个学生；
        //map转换
        Observable.just(new String[]{"鸡蛋_1", "鸡蛋_1", "鸡蛋_1", "鸡蛋_1", "鸡蛋_1"},new String[]{"鸡蛋_2", "鸡蛋_2", "鸡蛋_2", "鸡蛋_2", "鸡蛋_2"})
                .map(new Function<String[], String[]>() {
                    @RequiresApi(api = Build.VERSION_CODES.N)
                    @Override
                    public String[] apply(String[] strings) throws Exception {
                        for(int i=0;i<strings.length;i++)
                            strings[i]=strings[i].replace("鸡", "煎");
                        return strings;
                    }
                }).subscribe(s -> Log.d(TAG,"map() "+s[1]) );

        //FlatMap,单个Observable转换成多个Observable，再转换成单个Observable，不保证顺序
        //ConcatMap保证顺序
        Observable.just(new Integer[]{1,3,2,5},new Integer[]{1,4,5,5},new Integer[]{1,6,4})
                .flatMap( integers-> Observable.fromArray(integers)).subscribe(i -> Log.d(TAG,"map() "+i) );



        //doOnNext：订阅者在接收到数据之前干点有意思的事情，比如保存数据库


        /**
         * public  <List<Record>> readAllRecords() {
         *         return Observable.create(new ObservableOnSubscribe<List<Record>>() {
         *             @Override
         *             public void subscribe(ObservableEmitter<List<Record>> emitter) throws Exception {
         *                 Cursor cursor = null;
         *                 try {
         *                     cursor = getReadableDatabase().rawQuery("select * from " + TABLE_NAME, new String[]{});
         *                     List<Record> result = new ArrayList<>();
         *                     while (cursor.moveToNext()) {
         *                         result.add(Db.Record.read(cursor));
         *                     }
         *                     emitter.onNext(result);
         *                     emitter.onComplete();
         *                 } finally {
         *                     if (cursor != null) {
         *                         cursor.close();
         *                     }
         *                 }
         *             }
         *         }).subscribeOn(Schedulers.io()).observeOn(AndroidSchedulers.mainThread());
         *     }
         * */

        /**
         * 背压问题：
         * 当上下游在不同的线程中，通过Observable发射，处理，响应数据流时，如果上游发射数据的速度快于下游接收处理数据的速度，
         * 这样对于那些没来得及处理的数据就会造成积压，这些数据既不会丢失，也不会被垃圾回收机制回收，而是存放在一个异步缓存池中，
         * 如果缓存池中的数据一直得不到处理，越积越多，最后就会造成内存溢出，这便是响应式编程中的背压（backpressure）问题。
         *
         * Observable是ObservableSource/Observer这一组观察者模式中ObservableSource的典型实现,
         * Flowable是Publisher与Subscriber这一组观察者模式中Publisher的典型实现,
         * 由于基于Flowable发射的数据流，以及对数据加工处理的各操作符都添加了背压支持，附加了额外的逻辑，其运行效率要比Observable慢得多。
         *
         * BackpressureStrategy.MISSING     不会对通过onNext发射的数据做缓存或丢弃处理，需要下游通过背压操作符（onBackpressureBuffer()/onBackpressureDrop()/onBackpressureLatest()）指定背压策略。
         * BackpressureStrategy.ERROR       抛出MissingBackpressureException异常。
         * BackpressureStrategy.DROP        如果Flowable的异步缓存池满了，会丢掉上游发送的数据
         * BackpressureStrategy.LATEST      与Drop策略一样,LATEST都会将最后一条数据强行放入缓存池中，来保证观察者在接收到完成通知之前，能够接收到Flowable最新发射的一条数据。
         * BackpressureStrategy.BUFFER      默认策略,其内部维护了一个缓存池SpscLinkedArrayQueue，其大小不限，此策略下，如果Flowable默认的异步缓存池满了，会通过此缓存池暂存数据，它与Observable的异步缓存池一样，可以无限制向里添加数据，不会抛出MissingBackpressureException异常，但会导致OOM。
         *
         *
         * Subscription.cancel              取消Subscriber与Flowable的订阅关系
         * Subscription.request(long n);    设置Subscriber的数据请求量为n条，超出其请求范围之外的数据则不接收
         *
         *
         * */

        Flowable.create((FlowableOnSubscribe<Integer>) e -> {
            e.requested();
            System.out.println("发射----> 1");
            e.onNext(1);
            System.out.println("发射----> 2");
            e.onNext(2);
            System.out.println("发射----> 3");
            e.onNext(3);
            System.out.println("发射----> 完成");
            e.onComplete();
        },BackpressureStrategy.BUFFER)
                .subscribe(new Subscriber<Integer>() {
                    @Override
                    public void onSubscribe(Subscription s) {
                        s.request(Long.MAX_VALUE);

//                        s.request(3);//调用两次request
//                        s.request(4);//先接收3个，后接收两个
                    }

                    @Override
                    public void onNext(Integer integer) {
                        System.out.println("接收----> " + integer);
                    }

                    @Override
                    public void onError(Throwable t) {
                        System.out.println("接收----> 完成");
                    }

                    @Override
                    public void onComplete() {
                        System.out.println("接收----> 完成");
                    }
                });


//        Flowable
//                .create(new FlowableOnSubscribe<Integer>() {
//                    @Override
//                    public void subscribe(FlowableEmitter<Integer> e) throws Exception {
//                        int i = 0;
//                        while (true) {
//                            if (e.requested() == 0) continue;//此处添加代码，让flowable按需发送数据
//                            System.out.println("发射---->" + i);
//                            i++;
//                            e.onNext(i);
//                        }
//                    }
//                }, BackpressureStrategy.MISSING)
//                .subscribeOn(Schedulers.newThread())
//                .observeOn(Schedulers.newThread())
//                .subscribe(new Subscriber<Integer>() {
//                    private Subscription mSubscription;
//
//                    @Override
//                    public void onSubscribe(Subscription s) {
//                        s.request(1);            //设置初始请求数据量为1
//                        mSubscription = s;
//                    }
//
//                    @Override
//                    public void onNext(Integer integer) {
//                        try {
//                            Thread.sleep(50);
//                            System.out.println("接收------>" + integer);
//                            mSubscription.request(1);//每接收到一条数据增加一条请求量
//                        } catch (InterruptedException ignore) {
//                        }
//                    }
//
//                    @Override
//                    public void onError(Throwable t) {
//                    }
//
//                    @Override
//                    public void onComplete() {
//                    }
//                });
    }

    //无条件网络轮询
    private void noCondRepeat(){
        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl("http://fy.iciba.com/")
                .addConverterFactory(GsonConverterFactory.create())
                .addCallAdapterFactory(RxJava2CallAdapterFactory.create())
                .build();
        RetrofitInterface retrofitInterface = retrofit.create(RetrofitInterface.class);
        Observable<Translation> observable = retrofitInterface.getAjax("fy","auto","auto","hello world");
//        Observable<Translation> observable = retrofitInterface.getAjax();
        Observer observer = new Observer<Translation>() {
            @Override
            public void onSubscribe(Disposable d) {
                Log.d(TAG,"get Translation onSubscribe");
            }

            @Override
            public void onNext(Translation translation) {
                translation.show();
            }

            @Override
            public void onError(Throwable e) {
                Log.d(TAG,"get Translation onError");
                e.printStackTrace();
            }

            @Override
            public void onComplete() {
                Log.d(TAG,"get Translation onComplete");
            }
        };

        Observable.interval(2,1,TimeUnit.SECONDS)
                //每次产生一个数字前doOnNext()一次
                .doOnNext(new Consumer<Long>() {
                    @Override
                    public void accept(Long aLong) throws Exception {
                        observable.subscribeOn(Schedulers.io()) .subscribe(observer);
                    }
                })
                .subscribe(new Observer<Long>() {
                    @Override
                    public void onSubscribe(Disposable d) {

                    }

                    @Override
                    public void onNext(Long aLong) {
                        Log.d(TAG,"interval()="+aLong);
                    }

                    @Override
                    public void onError(Throwable e) {

                    }

                    @Override
                    public void onComplete() {

                    }
                });
    }

    private void CondRepeat(){
        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl("http://fy.iciba.com/")
                .addConverterFactory(GsonConverterFactory.create())
                .addCallAdapterFactory(RxJava2CallAdapterFactory.create())
                .build();
        RetrofitInterface retrofitInterface = retrofit.create(RetrofitInterface.class);
        Observable<Translation> observable = retrofitInterface.getAjax("fy","auto","auto","hello world");
//        Observable<Translation> observable = retrofitInterface.getAjax();
        Observer observer = new Observer<Translation>() {
            @Override
            public void onSubscribe(Disposable d) {
                Log.d(TAG,"get Translation onSubscribe");
            }

            @Override
            public void onNext(Translation translation) {
                translation.show();
            }

            @Override
            public void onError(Throwable e) {
                Log.d(TAG,"get Translation onError");
                e.printStackTrace();
            }

            @Override
            public void onComplete() {
                Log.d(TAG,"get Translation onComplete");
            }
        };

        observable.repeatWhen(new RepeatWithDelay(3,3000)).subscribeOn(Schedulers.io()).observeOn(AndroidSchedulers.mainThread()).subscribe(observer);

    }

    private void retryWhen(){
        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl("http://fy.iciba.com/")
                .addConverterFactory(GsonConverterFactory.create())
                .addCallAdapterFactory(RxJava2CallAdapterFactory.create())
                .build();
        RetrofitInterface retrofitInterface = retrofit.create(RetrofitInterface.class);
        Observable<Translation> observable = retrofitInterface.getAjax("fy","auto","auto","hello world");

//        Observable<Translation> observable = retrofitInterface.getAjax();
        Observer observer = new Observer<Translation>() {
            @Override
            public void onSubscribe(Disposable d) {
                Log.d(TAG,"get Translation onSubscribe");
            }

            @Override
            public void onNext(Translation translation) {
                translation.show();
            }

            @Override
            public void onError(Throwable e) {
                Log.d(TAG,"get Translation onError");
                e.printStackTrace();
            }

            @Override
            public void onComplete() {
                Log.d(TAG,"get Translation onComplete");
            }
        };

        observable.retryWhen(new RetryWithDelay(3,3000)).subscribeOn(Schedulers.io()).observeOn(AndroidSchedulers.mainThread()).subscribe(observer);

    }

    private class RepeatWithDelay implements Function<Observable<Object>, ObservableSource<?>> {

        private final int maxRetries;
        private final int retryDelayMillis;
        private int retryCount;

        public RepeatWithDelay(int maxRetries, int retryDelayMillis) {
            this.maxRetries = maxRetries;
            this.retryDelayMillis = retryDelayMillis;
        }

        @Override
        public ObservableSource<?> apply(Observable<Object> objectObservable) throws Exception {
            return objectObservable.flatMap(new Function<Object, ObservableSource<?>>() {
                @Override
                public ObservableSource<?> apply(Object o) {
                    Log.d(TAG,"retryWhen object = "+o.getClass());
                    Log.d(TAG,"retryWhen object = "+o);
                    if(++retryCount<= maxRetries)
                        return Observable.timer(retryDelayMillis,TimeUnit.MICROSECONDS);
                    return Observable.error(new Throwable("轮询失败"));
                }
            });
        }
    }

    private class RetryWithDelay implements Function<Observable<Throwable>, ObservableSource<?>> {

        private final int maxRetries;
        private final int retryDelayMillis;
        private int retryCount;

        public RetryWithDelay(int maxRetries, int retryDelayMillis) {
            this.maxRetries = maxRetries;
            this.retryDelayMillis = retryDelayMillis;
        }

        @Override
        public ObservableSource<?> apply(Observable<Throwable> throwableObservable) throws Exception {
            return throwableObservable.flatMap(new Function<Throwable, ObservableSource<?>>() {
                @Override
                public ObservableSource<?> apply(Throwable throwable) throws Exception {
                    if(throwable instanceof IOException){
                        if(++retryCount<= maxRetries)
                            return Observable.timer(retryDelayMillis,TimeUnit.MICROSECONDS);
                        return Observable.error(new Throwable("重试次数已超过设置次数"));
                    }
                    return Observable.error(new Throwable("发生了非网络异常（非I/O异常）"));
                }
            });
        }
    }

    private Observable<String> getStringObservable() {
        return Observable.create(new ObservableOnSubscribe<String>() {
            @Override
            public void subscribe(@NonNull ObservableEmitter<String> e) throws Exception {
                if (!e.isDisposed()) {
                    e.onNext("A");
                    Log.e(TAG, "String emit : A \n");
                    e.onNext("B");
                    Log.e(TAG, "String emit : B \n");
                    e.onNext("C");
                    Log.e(TAG, "String emit : C \n");
                }
            }
        });
    }

    private Observable<Integer> getIntegerObservable() {
        return Observable.create(new ObservableOnSubscribe<Integer>() {
            @Override
            public void subscribe(@NonNull ObservableEmitter<Integer> e) throws Exception {
                if (!e.isDisposed()) {
                    e.onNext(1);
                    Log.e(TAG, "Integer emit : 1 \n");
                    e.onNext(2);
                    Log.e(TAG, "Integer emit : 2 \n");
                    e.onNext(3);
                    Log.e(TAG, "Integer emit : 3 \n");
                    e.onNext(4);
                    Log.e(TAG, "Integer emit : 4 \n");
                    e.onNext(5);
                    Log.e(TAG, "Integer emit : 5 \n");
                }
            }
        });
    }


    private class MyObservable extends java.util.Observable{


    }
}
