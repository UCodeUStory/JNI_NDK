package com.wangpos.plugindevelopment;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import java.lang.reflect.Array;
import java.lang.reflect.Field;

import dalvik.system.DexClassLoader;
import dalvik.system.PathClassLoader;

/**
 *  DexClassLoader可以加载jar / apk / dex，可以从SD卡中加载未安装的apk;
    PathClassLoader只能加载系统中已经安装过的apk;
 */

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        DexClassLoader dexClassLoader = createDexClassLoader(this);

        injectClassLoader(dexClassLoader,this);
        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Class activityClass = null;
                try {
                    activityClass = Class.forName("com.wangpos.pluginapkdemo.TestActivity");

                } catch (ClassNotFoundException e) {
                    e.printStackTrace();
                }
                Log.i("qiyue","activityClass="+activityClass);
                ComponentName componentName = new ComponentName("com.wangpos.pluginapkdemo","com.wangpos.pluginapkdemo.TestActivity");
                Intent intent = new Intent();
                intent.setComponent(componentName);
                startActivity(intent);
            }
        });
    }


    /**
     * 创建DexClassLoader,不能用PathClassLoader,因为PathClassLoader只能加载安装过的
     */
    public DexClassLoader createDexClassLoader(Activity pActivity) {
        String cachePath = pActivity.getCacheDir().getAbsolutePath();
        //sdcard/chajian_demo.apk
        String apkPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/pluginapkdemo.apk";
        Log.i("qiyue","path="+apkPath);
        /**
         * 创建Dex参数说明
         */
        return new DexClassLoader(apkPath, cachePath, cachePath, getClassLoader());
    }


    public  void injectClassLoader(DexClassLoader loader,Context context){
        //获取宿主的ClassLoader
        PathClassLoader pathLoader = (PathClassLoader)context.getClassLoader();
        try {
            //获取宿主pathList
            Object hostPathList = getPathList(pathLoader);
            //获取插件pathList
            Object pluginPathList = getPathList(loader);
            //获取宿主ClassLoader中的dex数组
            Object hostDexElements = getDexElements(hostPathList);
            //获取插件CassLoader中的dex数组
            Object pluginDexElements = getDexElements(pluginPathList);
            //获取合并后的pathList
            Object sumDexElements = combineArray(hostDexElements, pluginDexElements);
            //将合并的pathList设置到本应用的ClassLoader
            setFielddValue(hostPathList, hostPathList.getClass(), "dexElements", sumDexElements);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }






    private static Object getPathList(Object baseDexClassLoader)
            throws IllegalArgumentException, NoSuchFieldException, IllegalAccessException, ClassNotFoundException {
        return getField(baseDexClassLoader, Class.forName("dalvik.system.BaseDexClassLoader"), "pathList");
    }

    private static Object getDexElements(Object paramObject)
            throws IllegalArgumentException, NoSuchFieldException, IllegalAccessException {
        return getField(paramObject, paramObject.getClass(), "dexElements");
    }

    private static Object getField(Object obj, Class<?> cl, String field)
            throws NoSuchFieldException, IllegalArgumentException, IllegalAccessException {
        //反射需要获取的字段

        Field localField = cl.getDeclaredField(field);
        localField.setAccessible(true);
        return localField.get(obj);
    }

    /**
     * 两个数组合并
     *
     * @param arrayLhs
     * @param arrayRhs
     * @return
     */
    private static Object combineArray(Object arrayLhs, Object arrayRhs) {

        Class<?> localClass = arrayLhs.getClass().getComponentType();
        int i = Array.getLength(arrayLhs);
        int j = i + Array.getLength(arrayRhs);
        Log.i("qiyue","i="+i+"j="+j);
        Object result = Array.newInstance(localClass, j);
        for (int k = 0; k < j; ++k) {
            if (k < i) {
                Array.set(result, k, Array.get(arrayLhs, k));
            } else {
                Array.set(result, k, Array.get(arrayRhs, k - i));
            }
        }
        return result;
    }

    /**
     * 为指定对象中的字段重新赋值
     * @param obj
     * @param claz
     * @param filed
     * @param value
     */
    public void setFielddValue(Object obj, Class<?> claz, String filed, Object value) throws NoSuchFieldException, IllegalAccessException {
        Field field = claz.getDeclaredField(filed);
        field.setAccessible(true);
        field.set(obj, value);
//        field.setAccessible(false);
    }


}
