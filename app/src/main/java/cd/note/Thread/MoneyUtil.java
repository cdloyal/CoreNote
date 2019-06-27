package cd.note.Thread;

import android.util.Log;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/6/27 20:32
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/6/27 20:32
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class MoneyUtil {
    private final static String TAG = "MoneyUtil";

//    private Object object = new Object();   //同步
    private static Object object = new Object();    //同步
    private int money;
    private static MoneyUtil moneyUtil;

    private MoneyUtil(){}

    public static MoneyUtil getInstance(){
        if(moneyUtil ==null){
            synchronized (MoneyUtil.class){
                if(moneyUtil ==null){
                    moneyUtil = new MoneyUtil();
                    moneyUtil.money=0;
                    Log.d(TAG,"初始化余额="+moneyUtil.money);
                }
            }
        }
        return moneyUtil;
    }

    //取钱
//    public synchronized void subMoney(int sub) {    //同步
    public void subMoney(int sub) {    //同步
        synchronized (this) {   //同步
//        synchronized (moneyUtil) {  //同步
//        synchronized (object) {
            if(money<=0){       //在判断前加入sync，不然下面取money的时候有可能已经被改了
                Log.d(TAG,"余额不足"+",余额="+money);
                return;
            }
            money-=sub;
            Log.d(TAG,"取出"+sub+",余额="+money);
        }
    }

    public synchronized void addMoney(int add){ //同步
        synchronized (this) {   //同步
//        synchronized (moneyUtil) {  //同步
//        synchronized (object) {
            money += add;
            Log.d(TAG,"存入"+add+",余额="+money);
        }
    }


}
