//
// Created by jak on 4/12/16.
//

#ifndef BULLET_TEST_NODE_H
#define BULLET_TEST_NODE_H

#include <glm/glm.hpp>
#include <list>
#include <string>

class Node {
public:
    Node();
    ~Node();
    virtual int readFromFile(std::ifstream &ifstream);
private:
    int clearChildNodes();
    glm::mat4 worldMatrix;
    std::list<Node*> childNodes;
};


#endif //BULLET_TEST_NODE_H
