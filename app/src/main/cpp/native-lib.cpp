#include <jni.h>
#include <string>
#include <unistd.h>

#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "egl/WlEglThread.h"
#include "shaderutil/WlShaderUtil.h"
#include "log/WIAndroid.h"
#include "matrix/MatrixUtil.h"

#include "opengl/WlOpengl.h"

WlOpengl *wlOpengl = NULL;


//void callback_SurfaceCrete(void *ctx){
//    LOGD("callback_SurfaceCreate")
//    WlEglThread *wlEglThread = static_cast<WlEglThread*>(ctx);
//
//    program = createProgrm(vertex,fragment);
//    LOGD("OPENGL program is %d",program);
//    vPosition = glGetAttribLocation(program,"v_Position");
//    fPosition = glGetAttribLocation(program,"f_Position");
//    sampler = glGetUniformLocation(program,"sTexture");
//    v_matrix = glGetUniformLocation(program,"u_Matrix");
//
//    for (int i = 0; i < 16; ++i) {
//        LOGD("%f",matrix[i]);
//    }
//    LOGD("==========================")
//    initMatrix(matrix);
////    rotateMatrix(-90,matrix);
////    scaleMatrix(0.5,matrix);
////    transMatrix(-1,-0.5,matrix);
//
//    //把-3到1之间的屏幕放到-1到1的范围内
////    orthoM(-3,1,-1,1,matrix);
//    for (int i = 0; i < 16; ++i) {
//        LOGD("%f",matrix[i])
//    }
//
//
//    glGenTextures(1,&textureId);
//
//    glBindTexture(GL_TEXTURE_2D,textureId);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//
//    if (pixels != NULL){
//        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
//    }
//    glBindTexture(GL_TEXTURE_2D,0);
//}

//void callback_SurfacChange(int width ,int height,void *ctx){
//    LOGD("CALLBACK_surfaceCHANGE")
//    WlEglThread * wlEglThread = static_cast<WlEglThread *>(ctx);
//    glViewport(0,0,width,height);
//
//    //正交投影
//    float screen_r=1.0*width/height;//屏幕宽高比
//    float picture_r = 1.0 *w/h; //图片宽高比
//
//    if (screen_r>picture_r){//图片宽度缩放
//        float r = width /(1.0 * height/h *w);
//        orthoM(-r,r,-1,1,matrix);
//    } else{//图片高度缩放
//        float r = height/(1.0 * width/w * h);
//        orthoM(-1,1,-r,r,matrix);
//    }
//
//}


//void callback_SurfaceDraw(void  *ctx){
//    LOGD("callback_SurfaceDraw")
//    WlEglThread *wlEglThread = static_cast <WlEglThread*>(ctx);
//    glClearColor(0.0f,0.0f,0.0f,1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//    glUseProgram(program);
//
//    glUniformMatrix4fv(v_matrix,1,GL_FALSE,matrix);
//
//
//    glActiveTexture(GL_TEXTURE5);
//    glUniform1i(sampler,5);
//    glBindTexture(GL_TEXTURE_2D,textureId);
//
//    glEnableVertexAttribArray(vPosition);
//    glVertexAttribPointer(vPosition,2,GL_FLOAT, false,8,vertexs);
//
//    glEnableVertexAttribArray(fPosition);
//    glVertexAttribPointer(fPosition, 2, GL_FLOAT, false, 8, fragments);
//
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//
//    glBindTexture(GL_TEXTURE_2D, 0);
//}


extern "C"
JNIEXPORT void JNICALL
Java_com_imooic_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject instance, jobject surface) {

    // TODO
    if (wlOpengl == NULL)
    {
        wlOpengl = new WlOpengl();
    }
    wlOpengl->onCreateSurface(env,surface);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_imooic_opengl_NativeOpengl_surfaceChange(JNIEnv *env, jobject instance, jint width,
                                                   jint height) {

    // TODO
    if(wlOpengl != NULL)
    {
        wlOpengl->onChangeSurface(width, height);
    }

}

extern "C"
JNIEXPORT void JNICALL
Java_com_imooic_opengl_NativeOpengl_imgData(JNIEnv *env, jobject instance, jint width, jint height,
                                             jint length, jbyteArray data_) {
    jbyte *data = env->GetByteArrayElements(data_, NULL);
    if (wlOpengl != NULL)
    {
        wlOpengl ->setPixel(data,width,height,length);
    }

    env ->ReleaseByteArrayElements(data_,data,0);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_imooic_opengl_NativeOpengl_surfaceDestroy(JNIEnv *env, jobject thiz) {
    if (wlOpengl != NULL)
    {
        wlOpengl ->onDestroySurface();
        delete wlOpengl;
        wlOpengl =NULL;
    }
}