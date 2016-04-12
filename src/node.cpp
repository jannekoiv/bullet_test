//
// Created by jak on 4/12/16.
//

#include "node.h"

Node::Node() {
    worldMatrix = glm::mat4();
}

Node::~Node() {
    clearChildNodes();
}

int Node::readFromFile(std::ifstream &ifstream) {
    return 0;
}

int Node::clearChildNodes() {
    for(std::list<Node*>::iterator node = childNodes.begin(); node != childNodes.end(); node++) {
//        delete node;
    }
}
