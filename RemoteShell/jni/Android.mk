LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := rs-jni.c
LOCAL_MODULE    := rs-jni

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)

