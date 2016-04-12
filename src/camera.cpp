//
// Created by jak on 4/7/16.
//

#include <iostream>
#include "camera.h"

Camera::Camera() {
    position = glm::vec3(0.0f, 50.0f, 200.0f);
    worldMatrix = glm::mat4();
    viewMatrix = glm::mat4();
}


int Camera::update(float angle, float tiltAngle) {
    worldMatrix = glm::mat4();
    worldMatrix = glm::translate(worldMatrix, position);
    worldMatrix = glm::rotate(worldMatrix, angle, glm::vec3(0.0f, -1.0f, 0.0f));
    worldMatrix = glm::rotate(worldMatrix, tiltAngle, glm::vec3(1.0f, 0.0f, 0.0f));

//    std::cout << "angle " << angle << "\n";
//    std::cout << "0: " << viewMatrix[0][0] << "  " << viewMatrix[0][1] << "  " << viewMatrix[0][2] << "  " << viewMatrix[0][3] << "\n";
//    std::cout << "1: " << viewMatrix[1][0] << "  " << viewMatrix[1][1] << "  " << viewMatrix[1][2] << "  " << viewMatrix[1][3] << "\n";
//    std::cout << "2: " << viewMatrix[2][0] << "  " << viewMatrix[2][1] << "  " << viewMatrix[2][2] << "  " << viewMatrix[2][3] << "\n";
//    std::cout << "2: " << viewMatrix[3][0] << "  " << viewMatrix[3][1] << "  " << viewMatrix[3][2] << "  " << viewMatrix[3][3] << "\n";



    viewMatrix = glm::inverse(worldMatrix);

    projectionMatrix = glm::perspective(45.0f, 1920.0f / 1080.0f, 0.5f, -1.0f);
}

int Camera::moveLeftRight(float velocity) {
    position += glm::vec3(worldMatrix[0][0], worldMatrix[0][1], worldMatrix[0][2]) * velocity;
    return 0;
}

int Camera::moveForwardBackward(float velocity) {
    position += glm::vec3(worldMatrix[2][0], worldMatrix[2][1], worldMatrix[2][2]) * velocity;
    return 0;
}

int Camera::moveUpDown(float velocity) {
    position += glm::vec3(worldMatrix[1][0], worldMatrix[1][1], worldMatrix[1][2]) * velocity;
    return 0;
}
