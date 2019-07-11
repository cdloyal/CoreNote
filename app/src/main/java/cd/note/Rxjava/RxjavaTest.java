package cd.note.Rxjava;


import android.util.Log;

import io.reactivex.Observable;
import io.reactivex.ObservableEmitter;
import io.reactivex.ObservableOnSubscribe;
import io.reactivex.Observer;
import io.reactivex.annotations.NonNull;
import io.reactivex.disposables.Disposable;
import io.reactivex.functions.BiFunction;
import io.reactivex.functions.Consumer;

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
         * 如果在请求的过程中Activity已经退出了, 这个时候如果回到主线程去更新UI, 那么APP肯定就崩溃了
         * CompositeDisposable compositeDisposable = new CompositeDisposable();
         * compositeDisposable.add();
         * compositeDisposable.clear();
         * */

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

            @Override
            public void onError(Throwable e) {
                Log.d(TAG,"onError");
            }

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
        Observable.fromArray(new Integer[]{1,3,2,5}).subscribe(integer -> Log.d(TAG,"fromArray() "+integer));

        //just
        Observable.just(new Integer[]{1,3,2,5}).subscribe(integer -> Log.d(TAG,"just() "+integer.length));

        //map
        Observable.fromArray(new Integer[]{1,3,2,5}).map(integer -> String.valueOf(integer)).subscribe(s -> Log.d(TAG,"map() "+s) );

        //zip
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

        //FlatMap,转换成多个Observable



        /**
         * public Observable<List<Record>> readAllRecords() {
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
}
