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
};



#endif //OPENGLNATIVEDEMO_WLOPENGL_H
