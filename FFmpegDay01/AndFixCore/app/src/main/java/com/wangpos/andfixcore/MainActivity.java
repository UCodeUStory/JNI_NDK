package com.wangpos.andfixcore;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import java.lang.reflect.Method;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    private TextView tvTextView;

    static {
        System.loadLibrary("fixlib");
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tvTextView = (TextView) findViewById(R.id.tvTextView);

        findViewById(R.id.btn_calculate).setOnClickListener(this);
        findViewById(R.id.btn_xiufu).setOnClickListener(this);


    }



    public native void replaceNative(Method wrong, Method right);

    @Override
    public void onClick(View view) {

        switch (view.getId()){
            case R.id.btn_calculate:
                Wrong wrong = new Wrong();
                tvTextView.setText( wrong.run(10,8));
                break;
            case R.id.btn_xiufu:
                update();
                break;
        }
    }

    private void update() {

        try {
            Class wrong = Class.forName("com.wangpos.andfixcore.Wrong");

            Class right = Class.forName("com.wangpos.andfixcore.Right");

            try {
                Method wrongMethod = wrong.getDeclaredMethod("run",int.class,int.class);

                Method rightMethod = right.getDeclaredMethod("run",int.class,int.class);

                replaceNative(wrongMethod,rightMethod);

            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
