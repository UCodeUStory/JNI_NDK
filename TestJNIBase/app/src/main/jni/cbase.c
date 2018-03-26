//
// Created by 齐月 on 2017/7/31.
//

#include "com_wangpos_testjnibase_CBase.h"
#include<malloc.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<android/log.h>

#define TAG "testjni" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__) // 定义LOGD类型


//这里声明一下，因为在其他文件有现实过了
char* Jstring2CStr(JNIEnv* env, jstring jstr);
jstring Cstr2Jstring(JNIEnv* env, const char* pat );


/*方法三，调用C库函数,*/
char* join3(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    if (result == NULL) exit (1);

    strcpy(result, s1);
    strcat(result, s2);

//    free(result);
    return result;
}

JNIEXPORT jstring JNICALL Java_com_wangpos_testjnibase_CBase_getString__Ljava_lang_String_2Ljava_lang_String_2
        (JNIEnv *env, jobject obj, jstring str1, jstring str2){

    char* a = Jstring2CStr(env,str1);
    char* b =  Jstring2CStr(env,str2);

    char* c = join3(a,b);


    jstring  returnStr = (*env)->NewStringUTF(env,c);

    //当程序退出时，操作系统会自动释放所有分配给程序的内存，但是，建议您在不需要内存时，都应该调用函数 free() 来释放内存。
//    free(c); 这里还没使用完就会不能

//    jstring returnStr = Cstr2Jstring(env,c);
    return returnStr;


}

JNIEXPORT jstring JNICALL Java_com_wangpos_testjnibase_CBase_getString__I
        (JNIEnv *env, jobject obj, jint x){
    int num = 100;
    char str[25];

//     str[0] = 2+'0';

    return Cstr2Jstring(env,str);

}


