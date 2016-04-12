//
// Created by jak on 4/12/16.
//

#ifndef BULLET_TEST_SUBMESH_H
#define BULLET_TEST_SUBMESH_H

#include <fstream>

class SubMesh {
public:
    SubMesh();
    int readFromFile(std::ifstream &ifstream);
    int indexCount;
    int *indices;
};

#endif //BULLET_TEST_SUBMESH_H
