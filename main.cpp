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
        VkInstance instance;

        void InitWindow() {
            SDL_Init(SDL_INIT_EVERYTHING);
            window = SDL_CreateWindow("Hey look! A window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_VULKAN);
        }

        void VulkInit() {
            createInstance();
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
            vkDestroyInstance(instance, nullptr);
            SDL_DestroyWindow(window);
            SDL_QUIT;
        }

        void createInstance() {
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "Test App";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "No Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;
            createInfo.enabledLayerCount = 0;

            if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
                throw std::runtime_error("failed to create instance!");
            }
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