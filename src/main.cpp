#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>
#include <bullet/btBulletDynamicsCommon.h>
#include "Box.h"
#include "Camera.h"

using namespace std;

SDL_Window *window = nullptr;
SDL_GLContext context = nullptr;
Box *box = nullptr;
Camera camera;

int initOpengl() {
    window = SDL_CreateWindow("Hello world!", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    context = SDL_GL_CreateContext(window);
    glewInit();
    return 0;
}

int init() {
    initOpengl();
    box = new Box();
    return 0;
}

float angle = 0;
int draw() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    box->worldMatrix = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
    box->draw();

//    box->worldMatrix = glm::translate(glm::vec3(-10.0f, 0.0f, 0.0f));
//    box->worldMatrix = glm::scale(box->worldMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
//    box->draw();

    SDL_GL_SwapWindow(window);
    angle += 0.01f;
}

int run() {
    SDL_Event event;
    bool loop = true;
    int mouseX = 0;
    int mouseY = 0;
    int prevMouseX = 0;
    int prevMouseY = 0;
    float angle = 0;
    while (loop) {
        while (SDL_PollEvent(&event)) {
            SDL_GetMouseState(&mouseX, &mouseY);
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        loop = false;
                        break;
                    case SDLK_a:
                        camera.moveLeftRight(-0.1f);
                        break;
                    case SDLK_d:
                        camera.moveLeftRight(0.1f);
                        break;
                    case SDLK_w:
                        camera.moveForwardBackward(0.1f);
                        break;
                    case SDLK_s:
                        camera.moveForwardBackward(-0.1f);
                        break;
                    case SDLK_r:
                        camera.moveUpDown(0.1f);
                        break;
                    case SDLK_f:
                        camera.moveUpDown(-0.1f);
                        break;
                    case SDLK_j:
                        angle -= 0.05f;
                        break;
                    case SDLK_k:
                        angle += 0.05f;
                        break;
                    default:
                        break;
                }
            }
        }
//        angle = mouseX / 100.f;
        camera.update(angle);
        draw();
        prevMouseX = mouseX;
        prevMouseY = mouseY;
    }
    return 0;
}

int main() {
    init();
    run();
    SDL_Quit();
    return 0;
}

