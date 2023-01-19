//
// Created by HSSJ on 2022/12/20.
//

#ifndef OPENGLNATIVEDEMO_WLSHADERUTIL_H
#define OPENGLNATIVEDEMO_WLSHADERUTIL_H

static int loadShaders(int shaderType, const char *code);

#include "GLES2/gl2.h"

static int createProgrm(const char *vertex,const char *fragment,GLuint *v_shader,GLuint *f_shader){
    int vertexShader = loadShaders(GL_VERTEX_SHADER,vertex);
    int fragmentShader = loadShaders(GL_FRAGMENT_SHADER,fragment);
    int program = glCreateProgram();
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragmentShader);
    glLinkProgram(program);

    *v_shader =vertexShader;
    *f_shader =fragmentShader;
    return program;
}

static int loadShaders(int shaderType, const char *code) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader,1,&code,0);
    glCompileShader(shader);
    return shader;
}


#endif //OPENGLNATIVEDEMO_WLSHADERUTIL_H
