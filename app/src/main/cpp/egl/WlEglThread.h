//
// Created by asus on 2022/12/20.
//

#ifndef OPENGLNATIVEDEMO_WLEGLTHREAD_H
#define OPENGLNATIVEDEMO_WLEGLTHREAD_H

#include <android/native_window.h>
#include "pthread.h"

class WlEglThread {

public:
    pthread_t eglThread = -1;
    ANativeWindow *nativeWindow = NULL;

    bool isCreate = false;
    bool isChange = false;
    bool isExit = false;
    bool isStart = false;
};



#endif //OPENGLNATIVEDEMO_WLEGLTHREAD_H
