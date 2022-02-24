#include <SDL2/SDL.h>
#include <iostream>
#include "include/glad/glad.h"

#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_EVERYTHING);

    GLfloat vertices[] = {
        -0.5, -0.5 * float(sqrt(3)) / 3, 0.0f,
        0.5, -0.5 * float(sqrt(3)) / 3, 0.0f,
        0.0, 0.5 * float(sqrt(3)) * 2 / 3, 0.0f,
        -0.5/2, 0.5 * float(sqrt(3)) / 6, 0.0f,
        0.5/2, 0.5 * float(sqrt(3)) / 6, 0.0f,
        0.0, -0.5 * float(sqrt(3)) / 3, 0.0f,
    };

    GLuint indices[] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };

    SDL_Window *window = SDL_CreateWindow("Windowww!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_Event e;

    gladLoadGL();

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    while(window) {
        SDL_UpdateWindowSurface(window);
        if(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                break;
            }
        }
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        
        SDL_GL_SwapWindow(window);
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}