//
// Created by jak on 4/7/16.
//

#ifndef BULLET_TEST_BOX_H
#define BULLET_TEST_BOX_H

#define GLM_FORCE_RADIANS 1;

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Box {
public:
    Box();
    int draw();
    GLuint vertexBuffer;
    GLuint normalBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLuint glMatWorld;
    static GLuint glMatView;
    static GLuint glMatProjection;
    static GLuint glLightDirection;
    glm::mat4 worldMatrix;
};

#endif //BULLET_TEST_BOX_H
