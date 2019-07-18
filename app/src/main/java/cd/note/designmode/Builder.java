package cd.note.designmode;

import java.util.ArrayList;
import java.util.List;

/**
 * 作者：chenda
 * 时间：2019/7/18:13:57
 * 邮箱：
 * 说明：
 */
public class Builder {

    /**
     * 建造者模式：
     *  我要买一台组装电脑
     *  我告诉老板（Director），我这台电脑需要什么东西，形成清单
     *  老板（Director）根据这个清单生成出电脑
     * */

    private final static String TAG = "Builder";
    public void test(){

        Director director = new Director();
        AbsBuilder absBuilder = new BBBuilder();
        director.construct(absBuilder);

        Computor computor = absBuilder.getComputer();
    }

    private class Director{
        public void construct(AbsBuilder absBuilder){
            absBuilder.buildCPU();
            absBuilder.buildHD();
            absBuilder.buildMainboard();
        }
    }

    private class Computor{
        private List<String> parts = new ArrayList<>();
        public void add(String part){
            parts.add(part);
        }
    }

    private abstract class AbsBuilder{
        public abstract void buildCPU();
        public abstract void buildMainboard();
        public abstract void buildHD();
        public abstract Computor getComputer();
    }

    private class BBBuilder extends AbsBuilder{

        Computor computor = new Computor();

        @Override
        public void buildCPU() {
            computor.add("CPU");
        }

        @Override
        public void buildMainboard() {
            computor.add("Mainboard");
        }

        @Override
        public void buildHD() {
            computor.add("HD");
        }

        @Override
        public Computor getComputer() {
            return computor;
        }
    }

}
