//
// Created by jak on 4/9/16.
//

#ifndef BULLET_TEST_SPHERE_H
#define BULLET_TEST_SPHERE_H

#include "model.h"

class Sphere : public Model {
public:
    Sphere();
    GLuint createVertexBuffer(glm::vec3 *vertices, int vertexCount);
    GLuint createNormalBuffer(glm::vec3 *normals, int vertexCount);
    GLuint createColorBuffer(glm::vec4 *colors, int vertexCount);
    GLuint createIndexBuffer(glm::vec3 *vertices, GLushort *indices, int indexCount);
    int initGeometry();
    int draw(glm::vec3 &lightPosition, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
};

#endif //BULLET_TEST_SPHERE_H
