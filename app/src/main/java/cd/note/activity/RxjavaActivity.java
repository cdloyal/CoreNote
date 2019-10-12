package cd.note.activity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;
import cd.note.R;
import cd.note.Rxjava.RxBus;
import io.reactivex.BackpressureStrategy;
import io.reactivex.Observable;
import io.reactivex.ObservableEmitter;
import io.reactivex.ObservableOnSubscribe;
import io.reactivex.ObservableSource;
import io.reactivex.Observer;
import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.disposables.Disposable;
import io.reactivex.functions.Consumer;
import io.reactivex.functions.Function;
import io.reactivex.schedulers.Schedulers;

public class RxjavaActivity extends AppCompatActivity {

    private final static String TAG = RxjavaActivity.class.getSimpleName();

    @BindView(R.id.btn_subject)
    Button btn_subject;

    ObservableEmitter<Integer> emitter;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rxjava);

        ButterKnife.bind(this);

        RxBus.getInstance().getObservable(String.class, BackpressureStrategy.BUFFER)
                .map(new Function<String, char[]>() {
                    @Override
                    public char[] apply(String s) throws Exception {
                        Log.d(TAG,"Thread = "+Thread.currentThread().getName()+",map()="+s);
                        char[] chars = new char[s.length()-1] ;
                        s.getChars(0,s.length()-2,chars,0);
                        return chars;
                    }
                })
                .flatMap(new Function<char[], ObservableSource<?>>() {
                    @Override
                    public ObservableSource<?> apply(char[] chars) throws Exception {
                        Log.d(TAG,"Thread = "+Thread.currentThread().getName()+",flatMap()");
                        return Observable.fromArray(chars);
                    }
                })
                .subscribeOn(Schedulers.newThread())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(new Observer<Object>() {
                    @Override
                    public void onSubscribe(Disposable d) {

                    }

                    @Override
                    public void onNext(Object o) {

                        Log.d(TAG,"Thread = "+Thread.currentThread().getName()+",onNext = " +o +",o.getClass()="+o.getClass().getName());
                    }

                    @Override
                    public void onError(Throwable e) {

                    }

                    @Override
                    public void onComplete() {

                    }
                });


        Observable.create(new ObservableOnSubscribe<Integer>() {
            @Override
            public void subscribe(ObservableEmitter<Integer> emitter) throws Exception {
                RxjavaActivity.this.emitter = emitter;
                Log.d(TAG,"Thread = "+Thread.currentThread().getName()+",create() ");
            }
        })
                .map(new Function<Integer, String>() {
                    @Override
                    public String apply(Integer integer) throws Exception {
                        Log.d(TAG,"Thread = "+Thread.currentThread().getName()+",map() ");
                        return integer+"..";
                    }
                })
            .subscribeOn(Schedulers.io())
            .observeOn(AndroidSchedulers.mainThread())
                .subscribe(new Consumer<String>() {
                    @Override
                    public void accept(String integer) throws Exception {
                        Log.d(TAG,"Thread = "+Thread.currentThread().getName()+",onNext = " +integer );
                    }
                });
    }

    @OnClick(R.id.btn_subject)
    public void subject(View view){
        RxBus.getInstance().post("hello rxbus");
    }

    @OnClick(R.id.btn_emitor)
    public void emitor(View view){

        emitter.onNext(11);
    }
}
