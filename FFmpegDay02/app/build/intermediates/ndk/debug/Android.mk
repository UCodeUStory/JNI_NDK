LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := avcodec
LOCAL_LDFLAGS := -Wl,--build-id
LOCAL_SRC_FILES := \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/AndroidManifest.xml \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/java/com/leixiaohua1020/sffmpegandroidhelloworld/MainActivity.java \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/jni/Android.mk \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/jni/Application.mk \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/jni/libavcodec-56.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/jni/libavdevice-56.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/jni/libavfilter-5.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/jni/libavformat-56.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/jni/libavutil-54.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/jni/libpostproc-53.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/jni/libswresample-1.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/jni/libswscale-3.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/jni/simplest_ffmpeg_helloworld.c \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/libs/armeabi/libavcodec-56.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/libs/armeabi/libavdevice-56.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/libs/armeabi/libavfilter-5.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/libs/armeabi/libavformat-56.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/libs/armeabi/libavutil-54.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/libs/armeabi/libpostproc-53.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/libs/armeabi/libsffhelloworld.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/libs/armeabi/libswresample-1.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/libs/armeabi/libswscale-3.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/obj/local/armeabi/libavcodec-56.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/obj/local/armeabi/libavdevice-56.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/obj/local/armeabi/libavfilter-5.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/obj/local/armeabi/libavformat-56.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/obj/local/armeabi/libavutil-54.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/obj/local/armeabi/libpostproc-53.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/obj/local/armeabi/libsffhelloworld.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/obj/local/armeabi/libswresample-1.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/obj/local/armeabi/libswscale-3.so \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/obj/local/armeabi/objs/sffhelloworld/simplest_ffmpeg_helloworld.o \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/obj/local/armeabi/objs/sffhelloworld/simplest_ffmpeg_helloworld.o.d \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/drawable-hdpi/ic_launcher.png \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/drawable-mdpi/ic_launcher.png \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/drawable-xhdpi/ic_launcher.png \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/drawable-xxhdpi/ic_launcher.png \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/layout/activity_main.xml \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/menu/main.xml \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/values/dimens.xml \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/values/strings.xml \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/values/styles.xml \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/values-sw600dp/dimens.xml \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/values-sw720dp-land/dimens.xml \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/values-v11/styles.xml \
	/ndk/simplest_ffmpeg_android_helloworld/app/src/main/res/values-v14/styles.xml \

LOCAL_C_INCLUDES += /ndk/simplest_ffmpeg_android_helloworld/app/src/main
LOCAL_C_INCLUDES += /ndk/simplest_ffmpeg_android_helloworld/app/src/debug/jni

include $(BUILD_SHARED_LIBRARY)
