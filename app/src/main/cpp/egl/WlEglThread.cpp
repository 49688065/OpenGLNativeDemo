//
// Created by asus on 2022/12/20.
//

#include <unistd.h>
#include "WlEglThread.h"
#include "WlEglHelper.h"

WlEglThread::WlEglThread() {
    pthread_mutex_init(&pthread_mutex,NULL);
    pthread_cond_init(&pthread_cond,NULL);
}

WlEglThread::~WlEglThread() {
    pthread_mutex_destroy(&pthread_mutex);
    pthread_cond_destroy(&pthread_cond);

}

void * eglThreadImpl(void *context){
    WlEglThread *wlEglThread = static_cast<WlEglThread*>(context);

    if (wlEglThread !=  NULL){
        WlEglHelper *wlEglHelper = new WlEglHelper();
        wlEglHelper ->initEgl(wlEglThread->nativeWindow);
        wlEglThread->isExit = false;

        while(true){
            if (wlEglThread ->isCreate){
                LOGD("eglThread call surfaceCreate");
                wlEglThread ->isCreate = false;
                wlEglThread ->oncreate(wlEglThread->onCreateCtx);
            }

            if (wlEglThread ->isChange){
                LOGD("eglThread call surfaceChange")
                wlEglThread ->isChange = false;
                wlEglThread ->onChange(wlEglThread->surfaceWidth,wlEglThread->surfaceHeight,wlEglThread ->onChangeCtx);
                wlEglThread ->isStart = true;
            }

            LOGD("DRAW")
            if (wlEglThread->isStart){
                LOGD("isStart")
                wlEglThread->onDraw(wlEglThread->onDrawCtx);
                wlEglHelper ->swapBuffers();
            }
            if (wlEglThread ->renderType ==OPENGL_RENDER_AUTO){
                usleep(1000000 / 60);
            } else{
                pthread_mutex_lock(&wlEglThread ->pthread_mutex);
                pthread_cond_wait(&wlEglThread->pthread_cond,&wlEglThread->pthread_mutex);
                pthread_mutex_unlock(&wlEglThread->pthread_mutex);
            }

            if (wlEglThread->isExit){
                break;
            }

        }

    }
    return 0;
}

void WlEglThread::onSurfaceCreate(EGLNativeWindowType window) {

    if (eglThread ==-1){
        isCreate = true;
        nativeWindow = window;

        pthread_create(&eglThread,NULL,eglThreadImpl,this);
    }
}

void WlEglThread::onSurfaceChange(int width, int height) {
    isChange = true;
    surfaceWidth = width;
    surfaceHeight = height;
    notifyRender();
}

void WlEglThread::callBackOnCreate(WlEglThread::Oncreate onCreate, void *ctx) {
    this ->oncreate=onCreate;
    this ->onCreateCtx = ctx;
}

void WlEglThread::callBackOnChange(WlEglThread::OnChange onChange, void *ctx) {
    this ->onChange = onChange;
    this ->onChangeCtx = ctx;
}

void WlEglThread::callBackOnDraw(WlEglThread::OnDraw onDraw, void *ctx) {
    this ->onDraw = onDraw;
    this ->onDrawCtx = ctx;
}

void WlEglThread::setRenderType(int renderType) {
    this ->renderType = renderType;
}

void WlEglThread::notifyRender() {
    pthread_mutex_lock(&pthread_mutex);
    pthread_cond_signal(&pthread_cond);
    pthread_mutex_unlock(&pthread_mutex);
}

