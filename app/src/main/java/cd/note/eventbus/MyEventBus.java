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
public class MyEventBus {

    private final static String TAG = MyEventBus.class.getSimpleName();

    public static void main(String[] arg){
        MyEventBus1 myEventBus1 = new MyEventBus1();
        MyEventBus myEventBus = new MyEventBus();
    }

    public MyEventBus(){
        EventBus.getDefault().register(this);



        EventBus.getDefault().post(new EventBusMsg<String>(EventBusMsg.Message.test,"EventBusMsg"));
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMessageEvent(String event) {
//        Log.d(TAG,"onMessageEvent()"+event);
        System.out.println("onMessageEvent()"+event);
    };

//    @Subscribe(threadMode = ThreadMode.MAIN)
//    public void onMessageEvent1(String event) {
////        Log.d(TAG,"onMessageEvent1()");
//        System.out.println("onMessageEvent1()"+event);
//    };

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMessageEvent2(EventBusMsg event) {
        if(event.getMessage()!=EventBusMsg.Message.test)
            return;

        System.out.println("onMessageEvent2()"+event.getData());

        byte b = 0x01;
        String s = "567ui";
        EventBus.getDefault().post(s);

        EventBus.getDefault().post("32534");
    };
}
