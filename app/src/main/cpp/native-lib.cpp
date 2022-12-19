#include <jni.h>
#include <string>

#include "Egl/egl.h"
#include "GLES2/gl2.h"
#include "android/native_window.h"

#include "android/log.h"


extern "C" JNIEXPORT jstring JNICALL
Java_com_imooic_openglnativedemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++Opengl";
    return env->NewStringUTF(hello.c_str());
}