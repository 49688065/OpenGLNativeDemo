//
// Created by asus on 2022/12/17.
//

#include "android/log.h"
#include "WlEglHelper.h"

WlEglHelper::WlEglHelper() {
    mEglDisplay = EGL_NO_DISPLAY;
    mEglSurface = EGL_NO_SURFACE;
    mEglContext = EGL_NO_CONTEXT;
    mEglConfig = NULL;
}

WlEglHelper::~WlEglHelper() {

}

int WlEglHelper::initEgl(EGLNativeWindowType window) {

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
    if (!eglChooseConfig(mEglDisplay,attribs,NULL,1,&num_config)){
        LOGE("EglChooseConfig error 1")
        return -1;
    }

    //4
    if (!eglChooseConfig(mEglDisplay,attribs,&mEglConfig,num_config,&num_config)){
        LOGE("eglChooseConfig error2")
        return -1;
    }

    //5
    int attrib_list[] = {
            EGL_CONTEXT_CLIENT_VERSION,2,
            EGL_NONE
    };

    mEglContext = eglCreateContext(mEglDisplay,mEglConfig,EGL_NO_CONTEXT,attrib_list);
    if (mEglContext ==EGL_NO_CONTEXT){
        LOGE("eglCreateContext error")
        return -1;
    }

    //6
    mEglSurface = eglCreateWindowSurface(mEglDisplay,mEglConfig,window,NULL);
    if (mEglSurface == EGL_NO_SURFACE){
        LOGE("eglCreateWindowSurface error")
        return  -1;
    }

    //7
    if (!eglMakeCurrent(mEglDisplay,mEglSurface,mEglSurface,mEglContext)){
        LOGE("eglMakeCurrent error")
        return -1;
    }

    LOGD( "egl init success! ")
    return 0;
}

int WlEglHelper::swapBuffers() {
    if (mEglDisplay != EGL_NO_DISPLAY && mEglSurface !=EGL_NO_SURFACE){
        if (eglSwapBuffers(mEglDisplay,mEglSurface)){
            return  0;
        }
    }
    return -1;
}

void WlEglHelper::destoryEgl() {
    if (mEglDisplay != EGL_NO_DISPLAY){
        eglMakeCurrent(mEglDisplay,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
    }

    if (mEglDisplay !=EGL_NO_DISPLAY && mEglSurface !=EGL_NO_SURFACE){
        eglDestroySurface(mEglDisplay,mEglSurface);
        mEglSurface = EGL_NO_SURFACE;
    }

    if (mEglDisplay != EGL_NO_DISPLAY &&mEglContext!=EGL_NO_CONTEXT){
        eglDestroyContext(mEglDisplay,mEglContext);
        mEglContext = EGL_NO_CONTEXT;
    }

    if (mEglDisplay != EGL_NO_DISPLAY){
        mEglDisplay = EGL_NO_DISPLAY;
    }
}
