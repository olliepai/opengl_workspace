#define STB_IMAGE_IMPLEMENTATION

#include "SDL2/SDL.h"
#include "OpenGL/gl.h"
#include "stb_image.h"
#include <math.h>

void drawRect(int x, int y, int w, int h) {
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0, 0);
    glVertex2d(x, y);
    glTexCoord2f(0, 1);
    glVertex2d(x, y + h);
    glTexCoord2f(1, 0);
    glVertex2d(x + w, y);
    glTexCoord2f(1, 1);
    glVertex2d(x + w, y + h);
    glTexCoord2f(1, 0);
    glVertex2d(x + w, y);
    glTexCoord2f(0, 1);
    glVertex2d(x, y + h);
    glEnd();
}

void drawCircle(int centerX, int centerY, int radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(centerX, centerY);
    for (int i = 0; i < 360; i++) {
        glVertex2d(centerX + cos(i), centerY - sin(i));
    }
}

int main(int argc, char** argv){

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 500, 500, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_Event event;

    glClearColor(0, 0, 1, 0);

    bool isRunning = true;

    //unsigned char texData[] = {255, 0, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 0, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255, 255, 0, 0, 255};

    int w, h, n;
    unsigned char *texData = stbi_load("img_lights.jpg", &w, &h, &n, 0);
    unsigned int textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 500, 0, -1, 1);

    while(isRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT: {
                    isRunning = false;
                }
                case SDL_KEYDOWN: {
                    if(event.key.keysym.sym == SDLK_ESCAPE){
                        isRunning = false;
                    }
                    break;
                }
            }
        }
        
        glClear(GL_COLOR_BUFFER_BIT);

        drawRect(100, 50, 400, 200);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);

    return 0;
}

