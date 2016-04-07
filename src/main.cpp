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
    window = SDL_CreateWindow("Hello world!", 0, 0, 1920, 1080, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    SDL_GL_SetSwapInterval(1);
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
        SDL_PollEvent(NULL);
        const Uint8 *keyState = SDL_GetKeyboardState(nullptr);
        if (keyState[SDL_SCANCODE_ESCAPE]) {
            loop = false;
        }
        if (keyState[SDL_SCANCODE_A]) {
            camera.moveLeftRight(-0.1f);
        }
        if (keyState[SDL_SCANCODE_D]) {
            camera.moveLeftRight(0.1f);
        }
        if (keyState[SDL_SCANCODE_W]) {
            camera.moveForwardBackward(0.1f);
        }
        if (keyState[SDL_SCANCODE_S]) {
            camera.moveForwardBackward(-0.1f);
        }
        if (keyState[SDL_SCANCODE_R]) {
            camera.moveUpDown(0.1f);
        }
        if (keyState[SDL_SCANCODE_F]) {
            camera.moveUpDown(-0.1f);
        }

        SDL_GetMouseState(&mouseX, &mouseY);
        angle = mouseX / 100.f;
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

