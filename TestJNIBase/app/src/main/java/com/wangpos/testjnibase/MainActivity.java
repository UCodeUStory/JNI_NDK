package com.wangpos.testjnibase;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ListView;

/**
 * JniLibName 自动生成在
 * app/build/intermediates/ndk/debug/obj/local/armeabi

 */
public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("JniLibName"); //和生成so文件的名字对应。
    }

    private ListView listView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        listView = (ListView)findViewById(R.id.listView);
        ListAdapter adapter = new ListAdapter(this);
        listView.setAdapter(adapter);

        short a = 2;
        short b = 3;
        int array[] = {1,3,5,7,9};
        String strArray[] = {"hello","world"};

        JavaToC javaToC = new JavaToC();
        FFmpegUtil fFmpegUtil = new FFmpegUtil();
        CBase cBase = new CBase();
        adapter.getDatas().add("传递short=  "+javaToC.add(a,b)+"");
        adapter.getDatas().add("传递int=  "+javaToC.add(3,4)+"");
        adapter.getDatas().add("传递float= "+javaToC.add(3.2f,4.5f));
        adapter.getDatas().add("传递double= "+javaToC.add(3.2,4.6));
        adapter.getDatas().add("传递long= "+javaToC.add(System.currentTimeMillis(),1231311231));
        adapter.getDatas().add("传递boolean= "+javaToC.isStart(true));
        adapter.getDatas().add("传递char= "+javaToC.say('Y'));
        adapter.getDatas().add("传递string= "+javaToC.say("hello"));
        adapter.getDatas().add("传递int数组= "+javaToC.say(array)[1]);
        adapter.getDatas().add("传递String数组= "+javaToC.say(strArray)[1]);
/*        adapter.getDatas().add("C调用Java方法="+javaToC.testCtoJava());
        adapter.getDatas().add("添加多个C文件"+fFmpegUtil.test(521));
        adapter.getDatas().add("测试C语言字符串拼接方法1="+cBase.getString("age：","24"));
        adapter.getDatas().add("测试C语言int转换String方法1"+cBase.getString(23));*/

        adapter.notifyDataSetChanged();


    }
}
