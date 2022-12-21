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
#endif //OPENGLNATIVEDEMO_MATRIXUTIL_H
