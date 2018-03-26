package com.wangpos.testjnibase;

import android.util.Log;

import static android.icu.lang.UCharacter.GraphemeClusterBreak.L;

/**
 * Created by qiyue on 2017/7/20.
 */

public class JavaToC {

    public native int add(short x, short y);
//
    public native int add(int x, int y);

    public native float add(float x,float y);

    public native double add(double x,double y);

    public native long add(long x,long y);

    public native boolean isStart(boolean flag);

    public native char say(char c);

    public native String say(String str);


    public native int[] say(int arr[]);

    public native String[] say(String str[]);


    public native String testCtoJava();


    /**
     * C 调用Java
     */

    public String sayHello(){
        return "hello Java";
    }

    public void sayName(String name){
        Log.i("testjni","name="+name);
    }

    public void sayAge(int age){
        Log.i("testjni","age="+age);
    }

    public static void sayStatic(){
        Log.i("testjni","age=24");
    }

    public int  getAge(){
        return 23;
    }


    /**
     * C调用java空方法
     */
    public void nullMethod() {
        Log.i("testjni","hello from javan");
    }
    /**
     * C调用java中的带两个int参数的方法
     *
     * @param x
     * @param y
     * @return
     */
    public String Add(int x, int y) {
        int result = x + y;
//        System.out.println("result in java " + result);
//        String.valueOf();
        Log.i("testjni","Add调用成功="+result);
        return result+"";
    }


    /**
     * C调用java中参数为String的方法
     *
     * @param s
     */
    public String printString(String s) {

        Log.i("testjni","printString="+s);
        System.out.println("java " + s);
        return s;
    }






}
