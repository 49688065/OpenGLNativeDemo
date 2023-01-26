//
// Created by asus on 2023/1/6.
//

#ifndef OPENGLNATIVEDEMO_WLOPENGL_H
#define OPENGLNATIVEDEMO_WLOPENGL_H

#include "../egl/WlEglThread.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "WlBaseOpengl.h"
#include "WlFilterOne.h"
#include "WlFilterTwo.h"
#include "WlFilterYUV.h"

class WlOpengl {

public:
    WlEglThread *wlEglThread =NULL;
    ANativeWindow *nativeWindow = NULL;
    WlBaseOpengl *baseOpengl = NULL;

    int pic_width;
    int pic_height;
    void *pixel = NULL;

public:
    WlOpengl();
    ~WlOpengl();

    void onCreateSurface(JNIEnv *env,jobject surface);

    void onChangeSurface(int width,int height);

    void onDestroySurface();

    void setPixel(void *data,int width, int height,int length);

    void onChangeFilter();

    void setYuvData(void *y, void *u, void *v, int w, int h);
};



#endif //OPENGLNATIVEDEMO_WLOPENGL_H
