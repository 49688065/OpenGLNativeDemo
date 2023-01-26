//
// Created by asus on 2023/1/6.
//

#include <cstdlib>
#include "WlOpengl.h"

void callback_SurfaceCreate(void *ctx)
{
    WlOpengl *wlOpengl = static_cast<WlOpengl * >(ctx);

    if (wlOpengl != NULL)
    {
        if (wlOpengl ->baseOpengl != NULL)
        {
            wlOpengl->baseOpengl->onCreate();
        }
    }
}

void callback_SurfaceChange(int width,int height,void *ctx)
{
    WlOpengl *wlOpengl = static_cast<WlOpengl *>(ctx);
    if (wlOpengl != NULL)
    {
        if (wlOpengl->baseOpengl != NULL)
        {
            wlOpengl ->baseOpengl->onChange(width, height);
        }
    }
}
void callback_SurfaceChangeFilter(int width,int height,void *ctx)
{
    WlOpengl *wlOpengl = static_cast<WlOpengl *>(ctx);
    if (wlOpengl != NULL)
    {
        if (wlOpengl->baseOpengl !=NULL){
            wlOpengl->baseOpengl->destroy();
            wlOpengl->baseOpengl->destroySource();
            delete wlOpengl->baseOpengl;
            wlOpengl->baseOpengl = NULL;
        }
        LOGE("3.width %d height %d wlOpengl->pic_width : %d wlOpengl->pic_height: %d",width,height,wlOpengl->pic_width,wlOpengl->pic_height)

        wlOpengl ->baseOpengl = new WlFilterTwo();
        wlOpengl->baseOpengl->onCreate();
        wlOpengl->baseOpengl->onChange(width,height);
        wlOpengl->baseOpengl->setPilex(wlOpengl->pixel,wlOpengl->pic_width,wlOpengl->pic_height,0);
        wlOpengl->wlEglThread->notifyRender();
     }
}

void callback_SurfaceDestory(void *ctx)
{
    WlOpengl *wlOpengl = static_cast<WlOpengl *>(ctx);
    if (wlOpengl != NULL)
    {
        if (wlOpengl->baseOpengl != NULL)
        {
            wlOpengl->baseOpengl->destroy();
        }
    }
}
void callback_SurfaceDraw(void *ctx)
{
    WlOpengl *wlOpengl = static_cast<WlOpengl *>(ctx);
    if (wlOpengl != NULL)
    {
        if (wlOpengl ->baseOpengl !=NULL)
        {
            wlOpengl ->baseOpengl ->draw();
        }
    }

}
WlOpengl::WlOpengl() {

}

WlOpengl::~WlOpengl() {

}

void WlOpengl::onCreateSurface(JNIEnv *env, jobject surface) {
    nativeWindow = ANativeWindow_fromSurface(env,surface);
    wlEglThread = new WlEglThread();
    wlEglThread ->setRenderType(OPENGL_RENDER_HANDLE);
    wlEglThread ->callBackOnCreate(callback_SurfaceCreate,this);
    wlEglThread ->callBackOnChange(callback_SurfaceChange,this);
    wlEglThread ->callBackOnDraw(callback_SurfaceDraw,this);
    wlEglThread ->callBackOnFilterChange(callback_SurfaceChangeFilter,this);
    wlEglThread ->callBackOnDestroy(callback_SurfaceDestory,this);

    baseOpengl = new WlFilterYUV();

    wlEglThread ->onSurfaceCreate(nativeWindow);
}

void WlOpengl::onChangeSurface(int width, int height) {
    if (wlEglThread != NULL) {
        LOGE("2 、width %d height %d", width, height);
        if (baseOpengl != NULL)
        {
            baseOpengl ->surface_width = width;
            baseOpengl ->surface_height = height;
        }

        wlEglThread ->onSurfaceChange(width,height);
    }
}

void WlOpengl::onDestroySurface() {
    if (wlEglThread != NULL)
    {
        wlEglThread ->destroy();
    }
    if (baseOpengl != NULL){
        baseOpengl->destroySource();
        delete baseOpengl;
        baseOpengl = NULL;
    }

    if (nativeWindow != NULL)
    {
        ANativeWindow_release(nativeWindow);
        nativeWindow = NULL;

    }

    if (pixel != NULL)
    {
        free(pixel);
        pixel =NULL;
    }

}

void WlOpengl::setPixel(void *data, int width, int height, int length) {
    pic_width = width;
    pic_height = height;

    if (pixel != NULL)
    {
        free(pixel);
        pixel=NULL;
    }
    pixel = malloc(length);
    memcpy(pixel,data,length);
    if (baseOpengl !=  NULL){
        baseOpengl ->setPilex(pixel,width,height,length);
    }
    if (wlEglThread != NULL)
    {
        wlEglThread ->notifyRender();
    }
}

void WlOpengl::onChangeFilter() {
    if (wlEglThread != NULL)
    {
        wlEglThread->onSurfaceChangeFilter();
    }

}

void WlOpengl::setYuvData(void *y, void *u, void *v, int w, int h) {
    if (baseOpengl != NULL){
        baseOpengl->setYuvData(y,u,v,w,h);
    }

    if (wlEglThread !=NULL){
        wlEglThread->notifyRender();
    }

}


