package cd.libcorenote;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

/**
 * 作者：chenda
 * 时间：2019/6/18:11:07
 * 邮箱：
 * 说明：
 */
public class CloneUtils {

    public static <T extends Serializable> T clone(T obj){
        T cloneObj = null;

        try {
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            ObjectOutputStream obs = new ObjectOutputStream(out);
            obs.writeObject(obj);
            obs.close();

            ByteArrayInputStream in = new ByteArrayInputStream(out.toByteArray());
            ObjectInputStream ois = new ObjectInputStream(in);
            cloneObj = (T)ois.readObject();
            ois.close();
            in.close();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return cloneObj;
    }
}
