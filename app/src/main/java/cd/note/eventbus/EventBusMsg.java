package cd.note.eventbus;

/**
 * 作者：chenda
 * 时间：2019/10/12:9:35
 * 邮箱：
 * 说明：
 */
public class EventBusMsg<T> {

    public T data;
    public Message msg;
    public static enum Message{
        test;
    }

    public EventBusMsg(){

    }

    public EventBusMsg(Message msg, T data){
        this.msg = msg;
        this.data = data;
    }

    public Message getMessage() {
        return msg;
    }

    public T getData(){
        return data;
    }
}
