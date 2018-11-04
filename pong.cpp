#include "SDL2/SDL.h"
#include "OpenGL/gl3.h"

#include <time.h>
#include <stdlib.h>

#include "shader_compiler.h"

#define GRAVITY -1
#define MAX_TRIANGLES 4096

#define WIDTH 900
#define HEIGHT 500

void setIdentityMatrix(float matrix[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(i == j){
                matrix[i][j] = 1;
            }else{
                matrix[i][j] = 0;
            }
        }
    }
}

void setOrthoganalProjectionMatrix(float matrix[4][4], float left, float right, float bottom, float top){
    matrix[0][0] = 2 / (right - left);
    matrix[1][1] = 2 / (top - bottom);
    matrix[3][0] = -((right + left) / (right - left));
    matrix[3][1] = -((top + bottom) / (top - bottom));
}

void translateMatrix2D(float matrix[4][4], float newPos[2]){
    matrix[3][0] += newPos[0];
    matrix[3][1] += newPos[1];
}

void scaleMatrix2D(float matrix[4][4], float newScale[2]){
    matrix[0][0] = newScale[0];
    matrix[1][1] = newScale[1];
}

struct Paddle {
    float position[2];
    float yspeed;
    float scale[2];
    int dir = 0;

    Paddle(float position[2], float yspeed, float scale[2]) {
        this->position[0] = position[0];
        this->position[1] = position[1];
        this->yspeed = yspeed;
        this->scale[0] = scale[0];
        this->scale[1] = scale[1];
    }

    void update() {
        switch (dir) {
            case 1:
                position[1] += yspeed;
                break;
            case -1:
                position[1] -= yspeed;
                break;
        }
    }

    void render(int modelMatrixId) {
        float model[4][4];
        setIdentityMatrix(model);

        translateMatrix2D(model, position);
        scaleMatrix2D(model, scale);
        glUniformMatrix4fv(modelMatrixId, 1, false, model[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
};

struct Ball {
    float position[2];
    float speed[2];
    float scale[2];

    Ball(float position[2], float speed[2], float scale[2]) {
        this->position[0] = position[0];
        this->position[1] = position[1];
        this->speed[0]=speed[0];
        this->speed[1]=speed[1];
        this->scale[0] = scale[0];
        this->scale[1] = scale[1];
    }

    void update() {
        position[0] += speed[0];
        position[1] += speed[1];
    }

    void render(int modelMatrixId) {
        float model[4][4];
        setIdentityMatrix(model);

        translateMatrix2D(model, position);
        scaleMatrix2D(model, scale);
        glUniformMatrix4fv(modelMatrixId, 1, false, model[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};

// void updateTriangles(Triangle* tris, unsigned int totalTriangles){
//     for(int i = 0; i < totalTriangles; i++){
//         float nextPos[2]; 
//         nextPos[0] = tris[i].position[0];
//         nextPos[1] = tris[i].position[1] + tris[i].velocity[1];
//         tris[i].velocity[1] += GRAVITY;
//         nextPos[0] += tris[i].velocity[0];
//         tris[i].position[0] = nextPos[0];
//         tris[i].position[1] = nextPos[1];
//     }
// }

// void addTriangle(int x, int y, Triangle* tris, unsigned int& totalTriangles){
//     if(totalTriangles + 1 >= MAX_TRIANGLES){ totalTriangles = 0; }
//     tris[totalTriangles].position[0] = x;
//     tris[totalTriangles].position[1] = HEIGHT - y;
//     tris[totalTriangles].velocity[0] = (rand() % 10) - 5;;
//     tris[totalTriangles].velocity[1] = 20;
//     totalTriangles++;
// }

// void renderTriangles(Triangle* tris, unsigned int totalTriangles, int modelMatId){
//     for(int i = 0; i < totalTriangles; i++){
//         float modelMatrix[4][4];
//         setIdentityMatrix(modelMatrix);  
//         float newPos[2];
//         newPos[0] = tris[i].position[0];
//         newPos[1] = tris[i].position[1];
//         float newScale[2] = {10, 10};
//         translateMatrix2D(modelMatrix, newPos);
//         scaleMatrix2D(modelMatrix, newScale);
//         glUniformMatrix4fv(modelMatId, 1, false, modelMatrix[0]);
//         glDrawArrays(GL_TRIANGLES, 0, 3);
//     }
// }

int main(int argc, char** argv){
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    char* vertexData = readFileToCharArray("vertex_shader.glsl");
    char* fragData = readFileToCharArray("fragment_shader.glsl");

    unsigned int shader = compileShaderVF(vertexData, fragData);
    glUseProgram(shader);
    int postionId = glGetAttribLocation(shader, "position");
    int texCoordId = glGetAttribLocation(shader, "texCoord");

    int modelMatId = glGetUniformLocation(shader, "modelMatrix");
    int projectionMatId = glGetUniformLocation(shader, "projectionMatrix");

    float projectionMatrix[4][4];
    setIdentityMatrix(projectionMatrix);
    setOrthoganalProjectionMatrix(projectionMatrix, 0, WIDTH, 0, HEIGHT); 
    glUniformMatrix4fv(projectionMatId, 1, false, projectionMatrix[0]);

    float verts[] = {
        -1, -1, 0, 1, 
        -1, 1, 0.5, 0,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, -1, 0, 0,
        -1, -1, 0, 1, 
    };

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glVertexAttribPointer(postionId, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(postionId);
    glVertexAttribPointer(texCoordId, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(texCoordId);

    unsigned char texture[] = {
        255,255,255,255,0,0,0,255,
        0,0,0,255,255,255,255,255
    };

    unsigned int tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture); 

    glClearColor(1, 1, 0, 1);

    // Triangle triangles[MAX_TRIANGLES];
    // unsigned int totalTriangles = 0;

    float paddle1Pos[2] = {0, 400};
    float ballPos[2] = {400, 400};
    float ballSpeed[2] = {5, 5};
    float scale[2] = {4, 4};

    Paddle paddle1(paddle1Pos, 10, scale);
    Ball ball(ballPos, ballSpeed, scale);

    SDL_Event event;
    bool isRunning = true;
    while(isRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:{
                    isRunning = false;
                    break;
                }
                case SDL_KEYDOWN :{
                    if(event.key.keysym.sym == SDLK_ESCAPE){
                        isRunning = false;
                    }
                    if(event.key.keysym.sym == SDLK_w){
                        paddle1.dir = 1;
                    }
                    if(event.key.keysym.sym == SDLK_s){
                        paddle1.dir = -1;
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN :{
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    // addTriangle(x, y, triangles, totalTriangles);
                    break;
                }
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);
        
        paddle1.update();
        paddle1.render(modelMatId);
        ball.render(modelMatId);

        // updateTriangles(triangles, totalTriangles);      
        // renderTriangles(triangles, totalTriangles, modelMatId);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    return 0;
}