package cd.note.UiAdapt;

import android.content.Context;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.WindowManager;

import java.lang.reflect.Field;

/**
 * @Description: java类作用描述
 * @Author: 陈达
 * @CreateDate: 2019/10/3 10:16
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/10/3 10:16
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class UiUtils {

    private static final String TAG = UiUtils.class.getSimpleName();

    private static UiUtils instance ;
    /**
     * 假设美工给我们的原型图是1080*1920，android状态栏一般占48个像素，1920-48=1872
     * 也有可能不是
     * */
    private final static int STANDARD_WIDTH = 240;
    private final static int STANDARD_HEIGHT = 352;
    private final static String DIMEN_CLASS = "com.android.internal.R$dimen";
    private final static String BAR_HEIGHT = "status_bar_height";

    //实际设备分辨率
    private float displayMetricsWidth;
    private float displayMetricsHeight;

    private Context context;
    private UiUtils(Context context){
        this.context = context.getApplicationContext();
        fun();

    };

//    private static class UiUtilsInnerClass{
//        private static UiUtils instance = new UiUtils();
//    }
//    public UiUtils getInstance(Context context){
//        return UiUtilsInnerClass.instance;
//    }

    public static UiUtils getInstance(Context context){
        if(instance==null){
            synchronized (UiUtils.class){
                if(instance==null){
                    instance = new UiUtils(context);
                }
            }
        }
        return instance;
    }

    public void fun(){
        //获取屏幕宽高
        WindowManager wm = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
        DisplayMetrics outMetrics = new DisplayMetrics();
        wm.getDefaultDisplay().getMetrics(outMetrics);
        //获取状态栏高度
        int systemBarHeight= getValue(context,DIMEN_CLASS,BAR_HEIGHT,48);

        Log.d(TAG,"outMetrics.widthPixels="+outMetrics.widthPixels
                +",outMetrics.heightPixels="+outMetrics.heightPixels
                +",systemBarHeight="+systemBarHeight
                +",orientation="+wm.getDefaultDisplay().getOrientation());
        //处理真是宽高
//        if(outMetrics.widthPixels>outMetrics.heightPixels){
//            //横屏
//            // 为什么要转换？
//            // UI的原型图是竖屏的，尺寸与像素无关，屏幕切换，android自动调整控件尺寸
//            // 我们这个代码，在绘制的时候设置像素值
//            displayMetricsWidth = outMetrics.heightPixels;
//            displayMetricsHeight = outMetrics.widthPixels-systemBarHeight;
//        }else {
//            //竖屏
//            displayMetricsWidth = outMetrics.widthPixels;
//            displayMetricsHeight = outMetrics.heightPixels-systemBarHeight;
//        }

        displayMetricsWidth = outMetrics.widthPixels;
        displayMetricsHeight = outMetrics.heightPixels-systemBarHeight;
    }

    /**
     * @method          getValue
     * @description     通过反射获取android系统某个类的成员
     * @param           #context      上下文
     * @param           #className    完整的包名和类名
     * @param           #attrName     成员名称
     * @param           #defaultValue 获取不成功，默认返回
     * @return
     */
    public static int getValue(Context context,String className, String attrName,int defaultValue){
        try {
            Class c = Class.forName(className);
            Object object = c.newInstance();
            Field field = c.getField(attrName);
            //属性id
            int attrId = Integer.parseInt(field.get(object).toString());
            return context.getResources().getDimensionPixelOffset(attrId);
        } catch (Exception e) {
            e.printStackTrace();
            return defaultValue;
        }
    }

    public int getWidth(int width){
        return (int) (width * (displayMetricsWidth/STANDARD_WIDTH));
    }
    public int getHeight(int height){
        return (int) (height * (displayMetricsHeight/STANDARD_HEIGHT));
    }

}
