package cd.note.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import butterknife.ButterKnife;
import butterknife.OnClick;
import cd.note.R;

public class OomActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_oom);

        ButterKnife.bind(this);
    }

    @OnClick(R.id.btn_stackoverflow)
    void stackoverflow(View v){
        stackoverflow(v);       //递归用到栈保存临时变量，没有退出条件最终栈溢出
    }

}
