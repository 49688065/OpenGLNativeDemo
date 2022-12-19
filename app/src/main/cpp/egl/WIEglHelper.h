//
// Created by asus on 2022/12/17.
//

#ifndef OPENGLNATIVEDEMO_WIEGLHELPER_H
#define OPENGLNATIVEDEMO_WIEGLHELPER_H

#include "EGL/egl.h"
#include "../log//WIAndroid.h"
#include "android/log.h"

class WIEglHelper {

public:
    EGLDisplay mEglDisplay;
    EGLSurface mEglSurface;
    EGLConfig mEglConfig;
    EGLContext mEglContext;

public:
    WIEglHelper();
    ~WIEglHelper();

    int initEgl(EGLNativeWindowType win);

    int swapBuffers();

    void destoryEgl();
};



#endif //OPENGLNATIVEDEMO_WIEGLHELPER_H
