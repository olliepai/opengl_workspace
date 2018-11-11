#include <stdio.h>
#include "mat4.h"
#include <math.h>

// This constructor initializes the 2d float array with v along
// the diagnal [(0, 0), (1, 1), (2, 2), (3, 3)]. The rest of
// the matrix will be zeros.
mat4::mat4(float v){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                this->m[i][j] = v;
            } else {
                this->m[i][j] = 0;
            }
        }
    }
}

// Copy Constructor. Initilaizes this matrix with the values of the
// passed in matrix.
mat4::mat4(mat4& m){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->m[i][j] = m.m[i][j];
        }
    }
}

mat4::mat4(float m[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->m[i][j] = m[i][j];
        }
    }
}

// Adds the values of m to this matrix.
void mat4::add(mat4 m){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->m[i][j] = this ->m[i][j] + m.m[i][j];
        }
    }
}

// Subtracts the values of m from this matrix
void mat4::subtract(mat4 m){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->m[i][j] = this ->m[i][j] - m.m[i][j];
        }
    }
}

// Multiplies this matrix and m together.
// If you are unfamiliar with the algorithm of multiplying matrices,
// go to this site for an introduction:
// https://www.mathsisfun.com/algebra/matrix-multiplying.html
void mat4::multiply(mat4 m){
    mat4 result(m);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int dotProduct = 0;
            for (int j2 = 0; j2 < 4; j2++) {
                for (int i2 = 0; i2 < 4; i2++) {
                    dotProduct = dotProduct + this->m[i][j2] * m.m[i2][j];
                }
            }
            result.m[i][j] = dotProduct;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j; j < 4; j++) {
            this->m[i][j] = result.m[i][j];
        }
    }
}

// Multiplies m1 and m2 and returns the result.
mat4 mat4::multiply(mat4 m1, mat4 m2){
    m1.multiply(m2);
    return m1;
}

// Adds m1 and m2 and returns the result.
mat4 mat4::add(mat4 m1, mat4 m2){
    m1.add(m2);
    return m1;
}

// subtracts m2 from m1 and returns the result.
mat4 mat4::subtract(mat4 m1, mat4 m2){
    m1.subtract(m2);
    return m1;
}

void mat4::print() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f ", this->m[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}


//rotates around x-axis (vertical rotation)
void mat4::rotateX(float angle) {
    float rx[4][4] = {
        1, 0, 0, 0,
        0, cos(angle), -1 * sin(angle), 0,
        0, sin(angle), cos(angle), 0,
        0, 0, 0, 1
    };

    mat4 mrx(rx);
    this->multiply(mrx);
}

void mat4::rotateY(float angle) {
    float ry[4][4] = {
        cos(angle), 0, sin(angle), 0,
        0, 1, 0, 0
        -1 * sin(angle), 0, cos(angle), 0,
        0, 0, 0, 1
    };

    mat4 mry(ry);
    this->multiply(mry);
}

void mat4::rotateZ(float angle) {
    float rz[4][4] = {
        cos(angle), -1 * sin(angle), 0, 0,
        sin(angle), cos(angle), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    mat4 mrz(rz);
    this->multiply(mrz);
}