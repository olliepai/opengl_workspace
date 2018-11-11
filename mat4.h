#pragma once

struct mat4 {
    //member 2D float array
    float m[4][4];

    //constructors
    mat4(){}
    mat4(float v);
    mat4(mat4& m);
    mat4(float m[4][4]);

    //methods that alter the state of this matrix
    void add(mat4 m);
    void subtract(mat4 m);
    void multiply(mat4 m);

    //static functions for generic matrix math
    static mat4 add(mat4 m1, mat4 m2);
    static mat4 subtract(mat4 m1, mat4 m2);
    static mat4 multiply(mat4 m1, mat4 m2);

    //print matrix
    void print();

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
};