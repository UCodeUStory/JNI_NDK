package com.wangpos.plugindevelopment;

import android.app.Activity;
import android.content.Context;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

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
    }


    /**
     * 创建DexClassLoader,不能用PathClassLoader,因为PathClassLoader只能加载安装过的
     */
    public DexClassLoader createDexClassLoader(Activity pActivity) {
        String cachePath = pActivity.getCacheDir().getAbsolutePath();
        //sdcard/chajian_demo.apk
        String apkPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/chajian_demo.apk";
        /**
         * 创建Dex参数说明
         */
        return new DexClassLoader(apkPath, cachePath, cachePath, getClassLoader());
    }


    public static void injectClassLoader(DexClassLoader loader,Context context){
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
//            Object sumDexElements = combineArray(hostDexElements, pluginDexElements);
            //将合并的pathList设置到本应用的ClassLoader
//            setField(hostPathList, suZhuPathList.getClass(), "dexElements", sumDexElements);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }



    public static void setField(String classname, String filedName, Object obj, Object filedVaule) {
        try {
            Class obj_class = Class.forName(classname);
            Field field = obj_class.getDeclaredField(filedName);
            field.setAccessible(true);
            field.set(obj, filedVaule);
        } catch (SecurityException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (NoSuchFieldException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            // TODO Auto-generated catch block
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
}
