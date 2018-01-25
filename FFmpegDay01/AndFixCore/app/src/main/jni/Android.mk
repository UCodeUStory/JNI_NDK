LOCAL_PATH := $(call my-dir)

# FFmpeg library
include $(CLEAR_VARS)
LOCAL_MODULE := fixlib
LOCAL_SRC_FILES := replace_method.cpp


include $(BUILD_SHARED_LIBRARY)