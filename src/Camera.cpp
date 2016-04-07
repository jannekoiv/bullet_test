//
// Created by jak on 4/7/16.
//

#include <iostream>
#include "Camera.h"
#include "Box.h"

Camera::Camera() {
    position = glm::vec3(0.0f, 0.0f, 10.0f);
    viewMatrix = glm::mat4();
}


int Camera::update(float angle) {
    viewMatrix = glm::mat4();
//    viewMatrix = glm::translate(viewMatrix, position);
//    viewMatrix = glm::rotate(viewMatrix, -angle, glm::vec3(0.0f, 1.0f, 0.0f));

    viewMatrix = glm::mat4();
    viewMatrix = glm::translate(viewMatrix, position);
    viewMatrix = glm::rotate(viewMatrix, angle, glm::vec3(0.0f, -1.0f, 0.0f));




    std::cout << "angle " << angle << "\n";
    std::cout << "0: " << viewMatrix[0][0] << "  " << viewMatrix[0][1] << "  " << viewMatrix[0][2] << "  " << viewMatrix[0][3] << "\n";
    std::cout << "1: " << viewMatrix[1][0] << "  " << viewMatrix[1][1] << "  " << viewMatrix[1][2] << "  " << viewMatrix[1][3] << "\n";
    std::cout << "2: " << viewMatrix[2][0] << "  " << viewMatrix[2][1] << "  " << viewMatrix[2][2] << "  " << viewMatrix[2][3] << "\n";
    std::cout << "2: " << viewMatrix[3][0] << "  " << viewMatrix[3][1] << "  " << viewMatrix[3][2] << "  " << viewMatrix[3][3] << "\n";


    viewMatrix = glm::inverse(viewMatrix);
    glUniformMatrix4fv(Box::glMatView, 1, GL_FALSE, &viewMatrix[0][0]);

    glm::mat4 projectionMatrix = glm::perspective(45.0f, 1.25f, -1.0f, 1.0f);
    glUniformMatrix4fv(Box::glMatProjection, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniform3f(Box::glLightDirection, 0.0f, 0.0f, 1.0f);
}

int Camera::moveLeftRight(float velocity) {

//    glm::vec3 tmp = glm::cross(glm::vec3(viewMatrix[0][2], viewMatrix[1][2], -viewMatrix[2][2]),
//                               glm::vec3(0.0, 1.0f, 0.0f));

    glm::vec3 tmp = glm::vec3(1.0f, 0.0f, 0.0f);
    position += tmp * velocity;

    return 0;
}

int Camera::moveForwardBackward(float velocity) {
    position += glm::vec3(viewMatrix[0][2], viewMatrix[1][2], -viewMatrix[2][2]) * velocity;
    return 0;
}

int Camera::moveUpDown(float velocity) {
    position += glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]) * velocity;
    return 0;
}
