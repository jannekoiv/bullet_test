#include <iostream>
#include <SDL2/SDL.h>
#include <node.h>
#include <object.h>
#include "camera.h"
#include "mesh.h"

using namespace std;

SDL_Window *window = nullptr;
SDL_GLContext context = nullptr;
Camera camera;
Mesh *meshes = nullptr;
Object *objects = nullptr;
int objectCount = 0;

int initOpengl() {
//    window = SDL_CreateWindow("Hello world!", 0, 0, 1920, 1080, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    window = SDL_CreateWindow("Hello world!", 0, 0, 1280, 720, SDL_WINDOW_OPENGL);
    SDL_GL_SetSwapInterval(1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    context = SDL_GL_CreateContext(window);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    glewInit();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    return 0;
}


int readMesh() {
    std::ifstream ifstream("testmodel_2.3d", ios::in | ios::binary);

    int magicId = 0;
    ifstream.read((char *) &magicId, sizeof(int));

    int version = 0;
    ifstream.read((char *) &version, sizeof(int));

    int meshCount = 0;
    ifstream.read((char *) &meshCount, sizeof(int));
    meshes = new Mesh[meshCount];
    for (int i = 0; i < meshCount; i++) {
        meshes[i].readFromFile(ifstream);
    }

    ifstream.read((char *) &objectCount, sizeof(int));
    objects = new Object[objectCount];
    for (int i = 0; i < objectCount; i++) {
        int parentId = 0;
        ifstream.read((char *) &parentId, sizeof(int));
        ifstream.read((char *) &objects[i].worldMatrix, sizeof(glm::mat4));
        int meshId = 0;
        ifstream.read((char *) &meshId, sizeof(int));
        if (meshId >= 0) {
            objects[i].mesh = &meshes[meshId];
        }
    }

    ifstream.close();
    return 0;
}


int init() {
    initOpengl();
    readMesh();
    return 0;
}

int clean() {
    delete[] meshes;
    delete[] objects;
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 worldMatrix;

    for (int i = 0; i < objectCount; i++) {
        objects[i].draw(camera.position, camera.viewMatrix, camera.projectionMatrix);
    }

    SDL_GL_SwapWindow(window);
}

int run() {
    SDL_Event event;
    bool loop = true;
    int mouseX = 0;
    int mouseY = 0;
    int prevMouseX = 0;
    int prevMouseY = 0;
    float angle = 0;
    float tiltAngle = 0;
    float velocity = 1.0f;
    while (loop) {
        SDL_PollEvent(NULL);
        const Uint8 *keyState = SDL_GetKeyboardState(nullptr);
        if (keyState[SDL_SCANCODE_ESCAPE]) {
            loop = false;
        }
        if (keyState[SDL_SCANCODE_LSHIFT]) {
            velocity = 0.1f;
        } else {
            velocity = 1.0f;
        }
        if (keyState[SDL_SCANCODE_A]) {
            camera.moveLeftRight(-velocity);
        }
        if (keyState[SDL_SCANCODE_D]) {
            camera.moveLeftRight(velocity);
        }
        if (keyState[SDL_SCANCODE_W]) {
            camera.moveForwardBackward(-velocity);
        }
        if (keyState[SDL_SCANCODE_S]) {
            camera.moveForwardBackward(velocity);
        }
        if (keyState[SDL_SCANCODE_R]) {
            camera.moveUpDown(velocity);
        }
        if (keyState[SDL_SCANCODE_F]) {
            camera.moveUpDown(-velocity);
        }
        if (keyState[SDL_SCANCODE_T]) {
            tiltAngle += 0.01f;
        }
        if (keyState[SDL_SCANCODE_G]) {
            tiltAngle -= 0.01f;
        }

        SDL_GetRelativeMouseState(&mouseX, &mouseY);
        angle += mouseX / 100.f;
        camera.update(angle, tiltAngle);
        draw();
        prevMouseX = mouseX;
        prevMouseY = mouseY;
    }
    return 0;
}

int main() {
    init();
    run();
    clean();
    return 0;
}

