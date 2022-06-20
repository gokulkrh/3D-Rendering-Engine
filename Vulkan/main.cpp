#define GLFW_INCLUDE_NONE
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class Application {
    public:
        GLFWwindow* window;

        void run() {
            initWindow();
            initVulkan();
            mainLoop();
            cleanup();
        }

    private:
        void initWindow() {
            if(!glfwInit())
                std::cout << "failed to initialize" << "\n";

            window = glfwCreateWindow(1280, 720, "Coolest window ever", nullptr, nullptr);
        }

        void initVulkan() {
            std::cout << "intializing vulkan" << "\n";
        }

        void mainLoop() {
            while(!glfwWindowShouldClose(window)) {
                glfwPollEvents();
            }
        }

        void cleanup() {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
};

int main() {
    Application game;
    game.run();
    return EXIT_SUCCESS;
}