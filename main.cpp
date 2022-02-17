#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char **argv){
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Hey look! A window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_VULKAN^SDL_WINDOW_RESIZABLE);

    SDL_Event e;

    while(window){
        SDL_UpdateWindowSurface(window);
        if(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                break;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_QUIT;
}