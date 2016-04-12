//
// Created by jak on 4/12/16.
//

#include "object.h"


Object::Object() {
    mesh = nullptr;
}

Object::~Object() {
}

int Object::readFromFile(std::ifstream &ifstream) {
    return 0;
}

int Object::draw(glm::vec3 &lightPosition, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    if (mesh) {
        mesh->draw(lightPosition, worldMatrix, viewMatrix, projectionMatrix);
    }
}
