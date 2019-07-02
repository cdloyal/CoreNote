package cd.note.designmode;

/**
 * @Description:    抽象工厂模式
 * @Author: 陈达
 * @CreateDate: 2019/7/2 14:46
 * @UpdateUser: 陈达
 * @UpdateDate: 2019/7/2 14:46
 * @UpdateRemark: 更新说明：
 * @Version: 1.0
 */
public class AbstractFactory {

    /**
     * http://c.biancheng.net/view/1351.html
     * 怎么使用抽象工厂？适用与初始化复杂的情况
     * 1、我有一个工厂，这个工厂要生产鞋、衣服，我就要实现这个工厂，让它生产鞋和衣服    ==>简单工厂模式
     *
     * 2、我有一个串口，这个串口可以连读卡器、身份证阅读器，如果我要读身份证，就要实现这个工厂，让其生产身份证阅读器  ==>这个举例不对
     * */


    //抽象工厂
    interface Factory{
        public Product getProduct(String path,int baudrate);
    }

    class IDReaderFactory implements Factory{
        @Override
        public Product getProduct(String path,int baudrate) {
            IDReader idReader = new IDReader();
            if(idReader.open(path,baudrate)<0)
                return null;

            return idReader;
        }
    }

    class ICReaderFactory implements Factory{

        @Override
        public Product getProduct(String path,int baudrate) {
            ICReader icReader = new ICReader();
            if(icReader.open(path,baudrate)<0)
                return null;

            return icReader;
        }
    }

    //抽象产品
    abstract class Product{
        int fd;
        int open(String path,int baudrate){
            //TODO fd = openSerial();
            return 0;
        }
        void close(){
            //TOdO close(fd);
        }
        abstract String getversion();
    }

    class IDReader extends Product {

        @Override
        String getversion() {
            return null;
        }
    }

    class ICReader extends Product{

        @Override
        String getversion() {
            return null;
        }
    }

}
