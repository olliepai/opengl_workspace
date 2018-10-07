#include "SDL2/SDL.h"

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 900, 500, 0);

    SDL_Event event;
    bool isRunning = true;
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
    }

    SDL_DestroyWindow(window);
    return 0;
}