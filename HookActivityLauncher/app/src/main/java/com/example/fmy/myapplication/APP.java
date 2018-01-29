package com.example.fmy.myapplication;

import android.app.Application;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.os.Handler.Callback;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.util.Arrays;


public class APP extends Application {
    private static final String KEY_EXTRA_TARGET_INTENT = "EXTRA_TARGET_INTENT";
    private static final String TAG = "APP";

    @Override
    protected void attachBaseContext(Context base) {
        super.attachBaseContext(base);

        try {
            Class<?> ams_class = Class.forName("android.app.ActivityManagerNative");
            Field gDefault = ams_class.getDeclaredField("gDefault");
            //因为gDefault是private所以用发射机制打破访问限制
            gDefault.setAccessible(true);
            //得到gDefault实例对象 因为是stati属性所以get传入null即可得到
            Object gDefault_instance = gDefault.get(null);
            //单例工具类class
            Class<?> singleton_class = Class.forName("android.util.Singleton");
            //单例工具类的一个属性对象保存的是IActivityManager对象实例
            Field mInstance = singleton_class.getDeclaredField("mInstance");
            //打破封装访问
            mInstance.setAccessible(true);
            //传入gDefault对象实例得到IActivityManager对象实例
            final Object mInstance_instance = mInstance.get(gDefault_instance);
            //动态代理，这个不会我真不知道讲下去。此方法会返回一个实现IActivityManager接口的实例对象
            //拿着这个对象 替换单例工具类gDefault 的mInstance即可实现
            Object proxyInstance = Proxy.newProxyInstance(Thread.currentThread().getContextClassLoader(), mInstance_instance.getClass().getInterfaces(), new InvocationHandler() {
                @Override
                public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
                    // IActivityManager接口方法太多 我们只关心它启动activity的接口方法
                    if (method.getName().equals("startActivity")) {
                        //获取调用此方法传入的参数 我们这里只要Intent替换，所以只需要Intent替换
                        for (int i = 0; i < args.length; i++) {
                            Object arg = args[i];
                            if (arg instanceof Intent) {
                                Intent intent = new Intent();
                                //PlaceholdActivity因为在清单文件注册过所以 创建一个新的Intent替换原来的SecondActivity的意图。后面用到
                                // 并将其保存到新的Intent中
                                ComponentName componentName = new ComponentName("com.example.fmy.myapplication", PlaceholdActivity.class.getName());
                                intent.setComponent(componentName);
                                intent.putExtra(KEY_EXTRA_TARGET_INTENT, ((Intent) arg));
                                args[i] = intent;
                                return method.invoke(mInstance_instance, args);
                            }
                        }

                    }

                    return method.invoke(mInstance_instance, args);
                }
            });
//         替换单例工具类gDefault 的mInstance实现动态代理
            mInstance.set(gDefault_instance, proxyInstance);

            //过检验结束
            Class<?> activityThread_class = Class.forName("android.app.ActivityThread");
            Field sCurrentActivityThread_field = activityThread_class.getDeclaredField("sCurrentActivityThread");
            sCurrentActivityThread_field.setAccessible(true);
            //获取静态属性对象实例
            Object activityThread_instance = sCurrentActivityThread_field.get(null);

            Field mH_field = activityThread_class.getDeclaredField("mH");

            mH_field.setAccessible(true);
            //获取handler对象实例
            Object mH_insance = mH_field.get(activityThread_instance);

            Field mCallback_field = Handler.class.getDeclaredField("mCallback");


            mCallback_field.setAccessible(true);
            //给handler添加mCallback
            mCallback_field.set(mH_insance, new Handler.Callback() {

                @Override
                public boolean handleMessage(Message msg) {
                    if (msg.what == 100) {
                        //得到ActivityClientRecord
                        Object obj = msg.obj;
                        try {
                            //得到Intent对象
                            Field intent_field = obj.getClass().getDeclaredField("intent");
                            intent_field.setAccessible(true);
                            Intent intent = (Intent) intent_field.get(obj);
                            //取出我们前面存在Intent里的原本没有注册在清单文件的Activity的Intent
                            Intent target_intent = intent.getParcelableExtra(KEY_EXTRA_TARGET_INTENT);

                            if (target_intent != null) {
                                intent.setComponent(target_intent.getComponent());
                            }

                        } catch (Exception e) {
                            e.printStackTrace();
                        }

                    }
                    return false;

                }
            });

        } catch (Exception e) {
            e.printStackTrace();
        }


    }

    @Override
    public void onCreate() {
        super.onCreate();
    }
}
