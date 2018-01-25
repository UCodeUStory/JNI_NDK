package com.wangpos.hookclickview;

import android.content.Intent;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

/**
 *  Java层通过反射 HookView的点击事件
 */
public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
         final Handler handler = new Handler();
        Button oneBtn = (Button) findViewById(R.id.btn_one);
        oneBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                Log.i("qiyue","onClick");
                /**
                 * 模拟复杂业务
                 */
                handler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        startActivity(new Intent(getApplicationContext(),SecondActvity.class));
                    }
                },500);
            }

        });

        Button twoBtn = (Button)findViewById(R.id.btn_two);
        twoBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
//                startActivity(new Intent(getApplicationContext(),SecondActvity.class));
                /**
                 * 模拟复杂业务
                 */
                handler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        startActivity(new Intent(getApplicationContext(),SecondActvity.class));
                    }
                },500);
            }
        });

        HookViewClickUtil.hookView(twoBtn);
    }



}
