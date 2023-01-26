//
// Created by asus on 2023/1/12.
//

#ifndef OPENGLNATIVEDEMO_WLFILTERTWO_H
#define OPENGLNATIVEDEMO_WLFILTERTWO_H

#include "WlBaseOpengl.h"
#include "../matrix/MatrixUtil.h"
#include "../shaderutil/WlShaderUtil.h"

class WlFilterTwo: public WlBaseOpengl {

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
    WlFilterTwo();
    ~WlFilterTwo();

    void onCreate();

    void onChange(int width, int height);

    void draw();

    void destroy();

    void destroySource();

    void setMatrix(int width, int height);

    void setPilex(void *data, int width, int height, int length);

};



#endif //OPENGLNATIVEDEMO_WLFILTERTWO_H
