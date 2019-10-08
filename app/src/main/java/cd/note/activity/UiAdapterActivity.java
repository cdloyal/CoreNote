package cd.note.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;
import cd.note.R;
import cd.note.UiAdapt.UiUtils;
import me.jessyan.autosize.internal.CustomAdapt;

public class UiAdapterActivity extends AppCompatActivity  {

    @BindView(R.id.btn_ui)
    Button btn_ui;

    private static final String TAG = UiAdapterActivity.class.getSimpleName();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ui_adapter);
        Log.d(TAG,"UiAdapterActivity onCreate()");

        ButterKnife.bind(this);

//        btn_ui = findViewById(R.id.btn_ui);
//        btn_ui.setWidth(UiUtils.getInstance(UiAdapterActivity.this).getWidth(240));

    }

    @OnClick(R.id.btn_ui)
    public void widthHeight(View view) {
        UiUtils.getInstance(UiAdapterActivity.this).fun();
    }

//    @Override
//    public boolean isBaseOnWidth() {
//        return false;
//    }
//
//    @Override
//    public float getSizeInDp() {
//        return 0;
//    }
}
