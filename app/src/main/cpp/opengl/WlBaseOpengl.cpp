//
// Created by asus on 2023/1/6.
//

#include "WlBaseOpengl.h"


WlBaseOpengl::WlBaseOpengl() {

    vertexs = new float [8];
    fragments = new float [8];

    float v[] ={
            1,-1,
            1,1,
            -1,-1,
            -1,1
    };
    memcpy(vertexs,v,sizeof(v));

    float f[]={
            1,1,
            1,0,
            0,1,
            0,0
    };
    memcpy(fragments,f,sizeof(f));
}

WlBaseOpengl::~WlBaseOpengl() {
    delete []vertexs;
    delete []fragments;
}

void WlBaseOpengl::onCreate() {

}

void WlBaseOpengl::onChange(int w, int h) {

}

void WlBaseOpengl::draw() {

}

void WlBaseOpengl::destroy() {

}

void WlBaseOpengl::setPilex(void *data, int width,int height, int length) {

}

void WlBaseOpengl::destorySorce() {

}
