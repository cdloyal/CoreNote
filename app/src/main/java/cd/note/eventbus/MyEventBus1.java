package cd.note.eventbus;

import org.greenrobot.eventbus.EventBus;
import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

/**
 * 作者：chenda
 * 时间：2019/10/11:11:48
 * 邮箱：
 * 说明：
 */
public class MyEventBus1 {

    private final static String TAG = MyEventBus1.class.getSimpleName();

    public static void main(String[] arg){
        MyEventBus1 myEventBus = new MyEventBus1();
    }

    public MyEventBus1(){
        EventBus.getDefault().register(this);

    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMessageEvent(String event) {
//        Log.d(TAG,"onMessageEvent()");
        System.out.println("onMessageEvent()"+event);
    };

}
