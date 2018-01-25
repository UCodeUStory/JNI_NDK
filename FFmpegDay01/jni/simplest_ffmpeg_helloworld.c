
#include <stdio.h>
 
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavfilter/avfilter.h"

//Log
#ifdef ANDROID
#include <jni.h>
#include <android/log.h>
#define LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR, "(>_<)", format, ##__VA_ARGS__)
#else
#define LOGE(format, ...)  printf("(>_<) " format "\n", ##__VA_ARGS__)
#endif


//FIX
struct URLProtocol;


JNIEXPORT jstring Java_com_hejunlin_ffmpegandroidsample_MainActivity_avcodecinfo(JNIEnv *env, jobject obj)
{
	char info[40000] = { 0 };

	av_register_all();

	AVCodec *c_temp = av_codec_next(NULL);

	while(c_temp!=NULL){
		if (c_temp->decode!=NULL){
			sprintf(info, "%s[Dec]", info);
		}
		else{
			sprintf(info, "%s[Enc]", info);
		}
		switch (c_temp->type){
		case AVMEDIA_TYPE_VIDEO:
			sprintf(info, "%s[Video]", info);
			break;
		case AVMEDIA_TYPE_AUDIO:
			sprintf(info, "%s[Audio]", info);
			break;
		default:
			sprintf(info, "%s[Other]", info);
			break;
		}
		sprintf(info, "%s[%10s]\n", info, c_temp->name);

		
		c_temp=c_temp->next;
	}
	//LOGE("%s", info);

	return (*env)->NewStringUTF(env, info);
}
