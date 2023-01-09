//
// Created by asus on 2023/1/6.
//

#ifndef OPENGLNATIVEDEMO_WLFILTERONE_H
#define OPENGLNATIVEDEMO_WLFILTERONE_H

#include "WlBaseOpengl.h"
#include "../matrix/MatrixUtil.h"
#include "../shaderutil/WlShaderUtil.h"


class WlFilterOne : public WlBaseOpengl{

public:
    GLint vPosition;
    GLint fPosition;
    GLint sampler;
    GLuint textureId;
    GLint u_matrix;

    int w;
    int h;
    void *pixels = NULL;

    float matrix[16];

public:
    WlFilterOne();
    ~WlFilterOne();

    void onCreate();

    void onChange(int w,int h);

    void draw();

    void setMatrix(int width,int height);

    void setPilex(void *data,int width,int height,int length);
};



#endif //OPENGLNATIVEDEMO_WLFILTERONE_H
