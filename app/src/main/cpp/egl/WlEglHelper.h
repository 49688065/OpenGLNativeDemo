//
// Created by asus on 2022/12/17.
//

#ifndef OPENGLNATIVEDEMO_WLEGLHELPER_H
#define OPENGLNATIVEDEMO_WLEGLHELPER_H

#include "EGL/egl.h"
#include "../log//WIAndroid.h"
#include "android/log.h"

class WlEglHelper {

public:
    EGLDisplay mEglDisplay;
    EGLSurface mEglSurface;
    EGLConfig mEglConfig;
    EGLContext mEglContext;

public:
    WlEglHelper();
    ~WlEglHelper();

    int initEgl(EGLNativeWindowType win);

    int swapBuffers();

    void destoryEgl();
};



#endif //OPENGLNATIVEDEMO_WLEGLHELPER_H
