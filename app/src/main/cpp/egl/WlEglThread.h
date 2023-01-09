//
// Created by asus on 2022/12/20.
//

#ifndef OPENGLNATIVEDEMO_WLEGLTHREAD_H
#define OPENGLNATIVEDEMO_WLEGLTHREAD_H

#define OPENGL_RENDER_AUTO 0
#define OPENGL_RENDER_HANDLE 2

#include <android/native_window.h>
#include <EGL/eglplatform.h>
#include "pthread.h"


class WlEglThread {

public:
    pthread_t eglThread = -1;
    ANativeWindow *nativeWindow = NULL;

    bool isCreate = false;
    bool isChange = false;
    bool isExit = false;
    bool isStart = false;

    int surfaceWidth =0;
    int surfaceHeight =0;

    typedef void(*Oncreate)(void *);
    Oncreate oncreate;
    void *onCreateCtx;

    typedef void (*OnChange)(int width,int height,void *);
    OnChange onChange;
    void *onChangeCtx;

    typedef void(*OnDraw)(void *);
    OnDraw onDraw;
    void *onDrawCtx;

    int renderType = OPENGL_RENDER_AUTO;

    pthread_mutex_t pthread_mutex;
    pthread_cond_t pthread_cond;

public:
    WlEglThread();
    ~WlEglThread();

    void onSurfaceCreate(EGLNativeWindowType window);

    void onSurfaceChange(int width,int height);

    void callBackOnCreate(Oncreate onCreate,void *ctx);

    void callBackOnChange(OnChange onChange,void *ctx);

    void callBackOnDraw(OnDraw onDraw,void *ctx);

    void setRenderType(int renderType);

    void notifyRender();

    void destroy();

};



#endif //OPENGLNATIVEDEMO_WLEGLTHREAD_H
