//
// Created by jak on 4/12/16.
//

#ifndef BULLET_TEST_OBJECT_H
#define BULLET_TEST_OBJECT_H


#include "node.h"
#include "mesh.h"

class Object : public Node {
public:
    Object();
    ~Object();

    int readFromFile(std::ifstream &ifstream);
    int draw(glm::vec3 &lightPosition, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
//private:
    glm::mat4 worldMatrix;
    Mesh *mesh;
};

#endif //BULLET_TEST_OBJECT_H
