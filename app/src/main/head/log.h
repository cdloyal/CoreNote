#ifndef _LOG_H
#define _LOG_H


#include "android/log.h"

#define IS_DEBUG false

static const char *TAG="chenda";

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)

#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

#define LOGD(...)  __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)


// #define LOGD(fmt, args...) printf(fmt, ##args)
// #define LOGI(fmt, args...) printf(fmt, ##args)
// #define LOGE(fmt, args...) printf(fmt, ##args)

#endif