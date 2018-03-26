//
// Created by 齐月 on 2017/7/28.
//

#include "com_wangpos_testjnibase_FFmpegUtil.h"
#include<malloc.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<android/log.h>

#define TAG "testjni" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__) // 定义LOGD类型





JNIEXPORT jint JNICALL Java_com_wangpos_testjnibase_FFmpegUtil_test
        (JNIEnv * jniEnv, jobject object, jint x){
    return x;
}