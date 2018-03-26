//
// Created by 齐月 on 2017/7/21.
//


#include "com_wangpos_testjnibase_JavaToC.h"
#include<malloc.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<android/log.h>
#define TAG "testjni" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__) // 定义LOGD类型


/**
 * 返回值 char* 这个代表char数组的首地址
 *  Jstring2CStr 把java中的jstring的类型转化成一个c语言中的char 字符串
 */
char* Jstring2CStr(JNIEnv* env, jstring jstr) {
    char* rtn = NULL;
//    LOGD("************1***************");
    jclass clsstring = (*env)->FindClass(env, "java/lang/String"); //String
//    LOGD("**************2*************");
//    jstring strencode = (*env)->NewStringUTF(env, "GB2312"); // 得到一个java字符串 "GB2312"
    jstring strencode = (*env)->NewStringUTF(env, "UTF-8");
//    LOGD("**************3*************");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes",
                                        "(Ljava/lang/String;)[B"); //[ String.getBytes("gb2312");
//    LOGD("**********4*****************");
    jbyteArray barr = (jbyteArray)(*env)->CallObjectMethod(env, jstr, mid,
                                                           strencode); // String .getByte("GB2312");
//    LOGD("**************5*************");
    jsize alen = (*env)->GetArrayLength(env, barr); // byte数组的长度
    jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char*) malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba, 0); //
    LOGD("************jstring 转化 char成功***************");
    return rtn;
}

jstring Cstr2Jstring(JNIEnv* env, const char* pat )
{
    jstring jstr = (*env)->NewStringUTF(env,pat);
    return jstr;

}

JNIEXPORT jint JNICALL Java_com_wangpos_testjnibase_JavaToC_add__SS
        (JNIEnv *env, jobject obj, jshort x, jshort y){
    return x + y;
}

JNIEXPORT jint JNICALL Java_com_wangpos_testjnibase_JavaToC_add__II
        (JNIEnv *env, jobject obj, jint x, jint y){
    int age = x+y;

    LOGD("x=%d",x);
    LOGD("y=%d",y);
    LOGD("age=%d",age);

    return age;
}

JNIEXPORT jfloat JNICALL Java_com_wangpos_testjnibase_JavaToC_add__FF
        (JNIEnv *env, jobject obj, jfloat x, jfloat y){
    return x + y;
}

JNIEXPORT jdouble JNICALL Java_com_wangpos_testjnibase_JavaToC_add__DD
        (JNIEnv *env, jobject obj, jdouble x, jdouble y){
    return x + y;
}

JNIEXPORT jlong JNICALL Java_com_wangpos_testjnibase_JavaToC_add__JJ
        (JNIEnv *env, jobject obj, jlong x, jlong y){
    return x+y;
}

JNIEXPORT jboolean JNICALL Java_com_wangpos_testjnibase_JavaToC_isStart
        (JNIEnv *env, jobject obj, jboolean flag){
    return flag;

}

JNIEXPORT jchar JNICALL Java_com_wangpos_testjnibase_JavaToC_say__C
        (JNIEnv *env, jobject obj, jchar c){
    return c;
}

JNIEXPORT jstring JNICALL Java_com_wangpos_testjnibase_JavaToC_say__Ljava_lang_String_2
        (JNIEnv *env, jobject obj, jstring jstr){
    LOGD("***************************");

    /**
     * c语言函数的定义要在这个代码块前，否则报错
     */
//     char c[] ={'Y','e'};
//    LOGD("%s\n",jstr);

    char *c = Jstring2CStr(env,jstr);

    /**
     * log输入用法和C语言printf用法一样
     */
    LOGD("%s\n",c);

    jstring jst = Cstr2Jstring(env,c);

    return jst;
}

JNIEXPORT jintArray JNICALL Java_com_wangpos_testjnibase_JavaToC_say___3I
        (JNIEnv *env, jobject obj, jintArray jintArray1){

//    int array[] = {1,2,3,4,5};
    jint* arr;
    jint length;
    /**
     * 获取传递过来的头指针
     */
    arr = (*env)->GetIntArrayElements(env,jintArray1,NULL);
    length = (*env)->GetArrayLength(env,jintArray1);

    int i=0;
    for(i=0;i<length;i++) {
        LOGD("%d ",arr[i]);
    }

//    LOGD("*********1*");
    jintArray returnArray = (*env)->NewIntArray(env,length);

    //2.获取新数组指针
    jint *array = (*env)->GetIntArrayElements(env,returnArray, NULL);
    //3.赋值
    int j = 0;
    for(; j< length; j++){
        array[j] = arr[j];
    }
    //4.释放资源
    (*env)->ReleaseIntArrayElements(env,jintArray1, arr, 0);
    (*env)->ReleaseIntArrayElements(env,returnArray, array, 0);
//    LOGD("*********12222*");
    return returnArray;
}


JNIEXPORT jobjectArray JNICALL Java_com_wangpos_testjnibase_JavaToC_say___3Ljava_lang_String_2
        (JNIEnv *env, jobject obj, jobjectArray jobjectArray1){
        LOGD("*********1*");
    jsize size = (*env)->GetArrayLength(env,jobjectArray1);
    //遍历传递过来的字符串数组
    int i =0;
    for(i=0;i<size;i++){
        //看api 要看定义
        jstring obja= (jstring)(*env)->GetObjectArrayElement(env,jobjectArray1,i);
        const char* chars=(*env)->GetStringUTFChars(env,obja,NULL);//将jstring类型转换成char类型输出
        LOGD("%s",chars);

    }

    //复制新数组
    jclass objClass =(*env)->FindClass(env,"java/lang/String");//定义数组中元素类型
    jobjectArray texts= (*env)->NewObjectArray(env,size, objClass, 0);//创建一个数组类型为String类型
    jstring jstr;
    for(i=0;i<size;i++)
    {

        jstr=(jstring)(*env)->GetObjectArrayElement(env,jobjectArray1,i);//把array2中的元素取出来
        (*env)->SetObjectArrayElement(env,texts, i, jstr);//放入到texts数组中去，必须放入jstring
    }


        LOGD("*********5*");
    return texts;
}

JNIEXPORT jstring JNICALL Java_com_wangpos_testjnibase_JavaToC_testCtoJava
        (JNIEnv *env, jobject jobject1){

    //在C语言中调用Java的空方法
    //1.找到java代码native方法所在的字节码文件
    //jclass (*FindClass)(JNIEnv*, const char*);
    jclass clazz = (*env)->FindClass(env, "com/wangpos/testjnibase/JavaToC");
    if(clazz == 0){
        LOGD("find class error");
        return "";
    }
    LOGD("find class right");

    //2.找到class里面对应的方法
    // jmethodID (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    jmethodID method2 = (*env)->GetMethodID(env,clazz,"Add","(II)Ljava/lang/String;");
    jmethodID method3 = (*env)->GetMethodID(env,clazz,"nullMethod","()V");
    jmethodID method4 = (*env)->GetMethodID(env,clazz,"getAge","()I");
    jmethodID method6 = (*env)->GetMethodID(env,clazz,"printString","(Ljava/lang/String;)Ljava/lang/String;");
    //NOTICE 静态方法的id获取方法也不一样
    jmethodID method5 = (*env)->GetStaticMethodID(env,clazz,"sayStatic","()V");
    if(method2 == 0){
        LOGD("find method2 error");
        return "";
    }
    LOGD("find method2 right");
    //3.调用方法
    //jint (*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
//    CallIntMethod(env, jobject1, method2, 3,5);
//    LOGD("result in C = %d", result);
    jstring result = (jstring)(*env)->CallObjectMethod(env, jobject1, method2, 3,5);
//    char *str = {result};
    LOGD("*********Add方法调用成功*****");
    (*env)->CallVoidMethod(env,jobject1,method3);
    LOGD("*********nullMethod方法调用成功*****");

    int age = (*env)->CallIntMethod(env,jobject1,method4);
    LOGD("*********getAge方法调用成功*****age=%d",age);
    (*env)->CallStaticVoidMethod(env,clazz,method5);
    LOGD("*********测试调用静态方法****");

    /**
     * NOTICE 使用JAVA原生api，比如调用String工具类
     */
    jclass stringClazz = (*env)->FindClass(env, "java/lang/String");
    if(stringClazz == 0){
        LOGD("find string class error");
        return "";
    }
    LOGD("find string class right");

    /**
     * NOTICE 调用Java String 静态方法
     */
    jmethodID stringMethod1 = (*env)->GetStaticMethodID(env,stringClazz,"valueOf","(I)Ljava/lang/String;");

    if(stringMethod1 == 0){
        LOGD("find stringMethod1 error");
        return "";
    }
    int a = 10;
    LOGD("find stringMethod1 right");
    jstring stringten = (jstring)(*env)->CallStaticObjectMethod(env,stringClazz,stringMethod1,a);
    LOGD("invoke java String fuction %s",Jstring2CStr(env,stringten));



    LOGD("result in C = %s", Jstring2CStr(env,result));


    char *test1 = "哈哈哈";
    LOGD("开始调用Java方法并传递String参数 注意这里要讲C字符串转化Java字符串才可以传递成功:");
    jstring javaReturnStr = (jstring)(*env)->CallObjectMethod(env, jobject1, method6,Cstr2Jstring(env,test1));



//    char *str = "hello Java";
    return result;

}
