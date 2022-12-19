//
// Created by asus on 2022/12/18.
//

#ifndef OPENGLNATIVEDEMO_WIANDROID_H
#define OPENGLNATIVEDEMO_WIANDROID_H
#include "android/log.h"


#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG,"lam",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"lam",FORMAT,##__VA_ARGS__);



#endif //OPENGLNATIVEDEMO_WIANDROID_H
