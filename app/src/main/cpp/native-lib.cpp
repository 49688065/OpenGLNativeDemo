#include <jni.h>
#include <string>
#include <unistd.h>

#include "Egl/egl.h"
#include "GLES2/gl2.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "android/log.h"
#include "egl/WlEglThread.h"
#include "log/WIAndroid.h"
#include "shaderutil/WlShaderUtil.h"

ANativeWindow *nativeWindow = NULL;
WlEglThread *wlEglThread = NULL;

const char *vertex = "attribute vec4 a_position;\n"
                     "\n"
                     "void main(){\n"
                     "    gl_Position = a_position;\n"
                     "}";

const char *fragment = "precision mediump float;\n"
                       "\n"
                       "void main(){\n"
                       "    gl_FragColor = vec4(1f,0f,0f,1f);\n"
                       "}";

int program;
GLint vPosition;

float vertexs [] ={
        1,-1,
        1,1,
        -1,-1,
        -1,1
};

void callback_SurfaceCrete(void *ctx){
    LOGD("callback_SurfaceCreate")
    WlEglThread *wlEglThread = static_cast<WlEglThread*>(ctx);

    program = createProgrm(vertex,fragment);
    LOGD("OPENGL program is %d",program);
    vPosition = glGetAttribLocation(program,"a_position");
}

void callback_SurfacChange(int width ,int height,void *ctx){
    LOGD("CALLBACK_surfaceCHANGE")
    WlEglThread * wlEglThread = static_cast<WlEglThread *>(ctx);
    glViewport(0,0,width,height);
}


void callback_SurfaceDraw(void  *ctx){
    LOGD("callback_SurfaceDraw")
    WlEglThread *wlEglThread = static_cast <WlEglThread*>(ctx);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition,2,GL_FLOAT, false,8,vertexs);
    glDrawArrays(GL_TRIANGLE_STRIP,0,3);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_imooic_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject thiz, jobject surface) {
    nativeWindow = ANativeWindow_fromSurface(env,surface);
    wlEglThread = new WlEglThread();
    wlEglThread->setRenderType(OPENGL_RENDER_HANDLE);
    wlEglThread ->callBackOnCreate(callback_SurfaceCrete,wlEglThread);
    wlEglThread ->callBackOnChange(callback_SurfacChange,wlEglThread);
    wlEglThread ->callBackOnDraw(callback_SurfaceDraw,wlEglThread);
    wlEglThread->onSurfaceCreate(nativeWindow);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_imooic_opengl_NativeOpengl_surfaceChange(JNIEnv *env, jobject thiz, jint width,
                                                  jint height) {
    if (wlEglThread != NULL){
        wlEglThread ->onSurfaceChange(width,height);
        usleep(1000000);
        wlEglThread ->notifyRender();
    }
}