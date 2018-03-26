package com.wangpos.testjnibase;

/**
 * Created by qiyue on 2017/7/31.
 */

public class CBase {


    /**
     * 字符串拼接
     * @param str1
     * @param str2
     * @return
     */
    public native String getString(String str1,String str2);

    /**
     * 将int转化String
     * @param age
     * @return
     */
    public native String getString(int age);
}
