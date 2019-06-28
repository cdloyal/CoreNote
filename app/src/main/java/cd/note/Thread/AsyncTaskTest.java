package cd.note.Thread;

import android.os.AsyncTask;
import android.util.Log;

/**
 * 作者：chenda
 * 时间：2019/6/27:15:10
 * 邮箱：
 * 说明：
 */
public class AsyncTaskTest extends AsyncTask<Integer,String, Boolean> {

    private final static String TAG = "AsyncTaskTest";

    public AsyncTaskTest() {
        super();
    }

    @Override
    protected Boolean doInBackground(Integer... integers) {
        Log.d(TAG,"doInBackground start");
        publishProgress("publishProgress");
        Log.d(TAG,"doInBackground end");
        return false;
    }

    @Override
    protected void onPreExecute() {
        super.onPreExecute();
        Log.d(TAG,"onPreExecute");
    }

    @Override
    protected void onProgressUpdate(String... strings) {
        super.onProgressUpdate(strings);
        Log.d(TAG,"onProgressUpdate" + strings[0]);
    }

    @Override
    protected void onPostExecute(Boolean aBoolean) {
        super.onPostExecute(aBoolean);
        Log.d(TAG,"onPostExecute" + aBoolean);
    }

    @Override
    protected void onCancelled(Boolean b) {
        super.onCancelled(b);
    }

    @Override
    protected void onCancelled() {
        super.onCancelled();
    }
}
