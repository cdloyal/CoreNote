package cd.note.Rxjava;


import io.reactivex.BackpressureStrategy;
import io.reactivex.Flowable;
import io.reactivex.Observable;
import io.reactivex.subjects.PublishSubject;
import io.reactivex.subjects.Subject;

/**
 * 作者：chenda
 * 时间：2019/10/11:10:12
 * 邮箱：
 * 说明：
 */
public class RxBus {

    private static volatile RxBus rxBus;

    private final Subject<Object> subject = PublishSubject.create().toSerialized();

    public static RxBus getInstance(){
        if(rxBus==null){
            synchronized (RxBus.class){
                if(rxBus==null){
                    rxBus = new RxBus();
                }
            }
        }

        return rxBus;
    }

    public <T> Observable<T> getObservable(Class<T> type, BackpressureStrategy strategy){
        return subject.ofType(type);
    }

    public <T> Flowable<T> getFlowable(Class<T> type, BackpressureStrategy strategy){
        return subject.toFlowable(strategy).ofType(type);
    }

    public void post(Object o){
        subject.onNext(o);
    }


}
