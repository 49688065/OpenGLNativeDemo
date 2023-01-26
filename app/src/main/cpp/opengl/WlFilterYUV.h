//
// Created by asus on 2023/1/19.
//

#ifndef OPENGLNATIVEDEMO_WLFILTERYUV_H
#define OPENGLNATIVEDEMO_WLFILTERYUV_H


#include "WlBaseOpengl.h"
#include "../matrix/MatrixUtil.h"
#include "../shaderutil/WlShaderUtil.h"

class WlFilterYUV : public WlBaseOpengl{

public:
    GLint vPosition;
    GLint fPosition;
    GLint u_matrix;

    GLint sampler_y;
    GLint sampler_u;
    GLint sampler_v;

    GLuint samplers[3];

    float matrix[16];
    void *y = NULL;
    void *u = NULL;
    void *v = NULL;
    int yuv_width =0;
    int yuv_height =0;

public:
    WlFilterYUV();
    ~WlFilterYUV();
    void onCreate();

    void onChange(int width,int height);
    void draw();
    void destroy();
    void destroySource();
    void setMatrix(int width,int height);
    void setYuvData(void *y,void *u ,void *v,int width,int height);
};



#endif //OPENGLNATIVEDEMO_WLFILTERYUV_H
