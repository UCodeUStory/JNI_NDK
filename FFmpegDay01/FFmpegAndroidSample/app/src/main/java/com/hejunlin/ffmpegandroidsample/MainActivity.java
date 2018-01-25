package com.hejunlin.ffmpegandroidsample;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

/**
 * 进入jni目录执行ndk-build
 * 生成多架构so
 * ndk-build APP_ABI="armeabi armeabi-v7a x86 mips"
 */
public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final TextView infoText = (TextView) findViewById(R.id.text_libinfo);
        infoText.setMovementMethod(ScrollingMovementMethod.getInstance());
        Button button = (Button) this.findViewById(R.id.button_avcodec);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                infoText.setText(avcodecinfo());
            }
        });
    }


    //JNI
    public native String avcodecinfo();

    static{
        System.loadLibrary("avutil-55");
        System.loadLibrary("swresample-2");
        System.loadLibrary("avcodec-57");
        System.loadLibrary("avformat-57");
        System.loadLibrary("swscale-4");
        System.loadLibrary("avfilter-6");
        System.loadLibrary("sffhelloworld");
    }

}
