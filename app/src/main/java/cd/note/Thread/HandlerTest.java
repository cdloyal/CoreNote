package cd.note.Thread;


import android.annotation.SuppressLint;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

/**
 * 作者：chenda
 * 时间：2019/6/27:15:32
 * 邮箱：
 * 说明：Handler的使用
 */
public class HandlerTest {

    /**
     * 子线程通过Handler发送Message或者Runnable对象，到MessageQueue中，
     * Looper线程从MessageQueue中获取Message，交给Handler，
     * handler回调handleMessage方法处理Message
     *
     * Message.what 可以知道从那条线程发来的消息
     *
     * Post：Post允许把一个Runnable对象入队到消息队列中。它的方法有：post(Runnable)、postDelayed(Runnable,long)、postAtTime(Runnable,long) Ui在收到消息后指令时间执行
     * sendMessage：sendMessage允许把一个包含消息数据的Message对象压入到消息队列中。它的方法 有：sendEmptyMessage(int)、sendMessage(Message)、 sendMessageAtTime(Message,long)、sendMessageDelayed(Message,long)。
     * */

    private final static String TAG = "HandlerTest";

    @SuppressLint("HandlerLeak")
    public static final Handler handler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            Log.d(TAG,"msg.what="+msg.what+"msg.arg1="+msg.arg1);
        }
    };

    public static void test(){
        new MyThread(1).start();
        new MyThread(2).start();
    }

    private static class MyThread extends Thread{
        int i;
        public MyThread(int i) {
            super();
            this.i = i;
        }

        @Override
        public void run() {
            super.run();
            Message message = Message.obtain();
            message.what=i;
            message.arg1=(int)Thread.currentThread().getId();
            handler.sendMessage(message);
        }
    }
}
