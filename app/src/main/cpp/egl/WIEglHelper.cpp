//
// Created by asus on 2022/12/17.
//

#include "android/log.h"
#include "WIEglHelper.h"

WIEglHelper::WIEglHelper() {
    mEglDisplay = EGL_NO_DISPLAY;
    mEglSurface = EGL_NO_SURFACE;
    mEglContext = EGL_NO_CONTEXT;
    mEglConfig = NULL;
}

WIEglHelper::~WIEglHelper() {

}

int WIEglHelper::initEgl(EGLNativeWindowType win) {

    mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEglDisplay == EGL_NO_DISPLAY){
        LOGE("eglGetDisplay error");
        return -1;
    }

    //2
    EGLint *version =new EGLint [2];
    if (!eglInitialize(mEglDisplay,&version[0],&version[1])){

        LOGE("egl初始化错误")
        return  -1;
    }

    //3
    const EGLint attribs[]={
            EGL_RED_SIZE,8,
            EGL_GREEN_SIZE,8,
            EGL_BLUE_SIZE,8,
            EGL_ALPHA_SIZE,8,
            EGL_DEPTH_SIZE,8,
            EGL_STENCIL_SIZE,8,
            EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT,
            EGL_NONE
    };

    EGLint num_config;
    if (!eglChooseConfig(mEglDisplay,attribs,NULL,1,&num_config))
    return 0;
}
