#include <vulkan/vulkan.h>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

class Application{
    public:
        void run() {
            InitWindow();
            VulkInit();
            Loop();
            CleanUp();
        }
    private:
        SDL_Window *window;
        SDL_Event e;

        void InitWindow() {
            SDL_Init(SDL_INIT_EVERYTHING);
            window = SDL_CreateWindow("Hey look! A window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_VULKAN);
        }

        void VulkInit() {
            std::cout << "Hey it works!!!" << std::endl;
        }

        void Loop() {
            while(window){
                SDL_UpdateWindowSurface(window);
                if(SDL_PollEvent(&e)){
                    if(e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                        break;
                    }
                }
            }
        }

        void CleanUp() {
            SDL_DestroyWindow(window);
            SDL_QUIT;
        }
};


int main(int argc, char **argv){
    Application app;

    try{
        app.run();
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}