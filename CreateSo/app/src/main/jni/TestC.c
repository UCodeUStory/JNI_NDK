#include "com_wangpos_createso_TestSOUtil.h"
/*
 * Class:     com_android_talon_test_JniUtils.h
 * Method:    getString
 * Signature: ()Ljava/lang/String;
 */

JNIEXPORT jstring JNICALL Java_com_wangpos_createso_TestSOUtil_getMessage
  (JNIEnv *env, jobject obj){
      return (*env)->NewStringUTF(env,"Hello World!");
  }
