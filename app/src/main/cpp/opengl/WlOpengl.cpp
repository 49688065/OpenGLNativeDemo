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

    baseOpengl = new WlFilterOne();

    wlEglThread ->onSurfaceCreate(nativeWindow);
}

void WlOpengl::onChangeSurface(int width, int height) {
    if (wlEglThread != NULL) {
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
        baseOpengl ->destroy();
        delete baseOpengl;
        baseOpengl = NULL;
    }

    if (nativeWindow != NULL)
    {
        ANativeWindow_release(nativeWindow);
        nativeWindow = NULL;

    }

}

void WlOpengl::setPixel(void *data, int width, int height, int length) {
    pic_width = width;
    pic_height = height;
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