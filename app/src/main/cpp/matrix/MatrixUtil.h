//
// Created by HSSJ on 2022/12/21.
//

#ifndef OPENGLNATIVEDEMO_MATRIXUTIL_H
#define OPENGLNATIVEDEMO_MATRIXUTIL_H


static void initMatrix(float *matrix){
    for (int i = 0; i < 16; ++i) {
        if(i%5 ==0){
            matrix[i] = 1;
        } else{
            matrix[i]=0;
        }
    }
}

static void rotateMatrix(double angle,float *matrix){
    angle = angle* (M_PI/180.0);

    matrix[0] = cos(angle);
    matrix[1] = -sin(angle);
    matrix[4] = sin(angle);
    matrix[5] = cos(angle);
}


static void scaleMatrix(double scale, float matrix[16]) {
   matrix[0]= scale;
   matrix[5] = scale;
}

static void transMatrix(double x,double y,float *matrix){
    matrix [3] = x;
    matrix[7] =y;
}

static void orthoM(float left,float right,float bottom,float  top,float *matrix){
    matrix[0] = 2 / (right - left);
    matrix[3] = (right + left)/(right - left) * -1;
    matrix[5] = 2 / (top - bottom);
    matrix[7] = (top + bottom) / (top - bottom) * -1;
    matrix[10] = 1;
    matrix[11] = 1;
}
#endif //OPENGLNATIVEDEMO_MATRIXUTIL_H
