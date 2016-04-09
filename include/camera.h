//
// Created by jak on 4/7/16.
//

#ifndef BULLET_TEST_CAMERA_H
#define BULLET_TEST_CAMERA_H

#define GLM_FORCE_RADIANS 1;

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera {
public:
    Camera();
    int update(float angle);
    int moveLeftRight(float velocity);
    int moveForwardBackward(float velocity);
    int moveUpDown(float velocity);

    glm::vec3 position;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};


#endif //BULLET_TEST_CAMERA_H
