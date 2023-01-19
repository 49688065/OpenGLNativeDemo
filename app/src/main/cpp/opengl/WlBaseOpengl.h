//
// Created by asus on 2023/1/6.
//

#ifndef OPENGLNATIVEDEMO_WLBASEOPENGL_H
#define OPENGLNATIVEDEMO_WLBASEOPENGL_H

#include <GLES2/gl2.h>
#include <cstring>
#include "../log/WIAndroid.h"

class WlBaseOpengl {

public:
    int surface_width;
    int surface_height;

    char * vertex;
    char * fragment;

    float * vertexs;
    float * fragments;

    GLuint program;
    GLuint vShader;
    GLuint fShader;


public:
    WlBaseOpengl();
    ~WlBaseOpengl();

    virtual void onCreate();

    virtual void onChange(int w,int h);

    virtual void draw();

    virtual void destroy();

    virtual void destorySorce();

    virtual void setPilex(void * data,int width,int height,int length);
};



#endif //OPENGLNATIVEDEMO_WLBASEOPENGL_H
