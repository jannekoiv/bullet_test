//
// Created by jak on 4/12/16.
//

#include "subMesh.h"

SubMesh::SubMesh() {
    indices = nullptr;
    indexCount = 0;
}

int SubMesh::readFromFile(std::ifstream &ifstream) {
    ifstream.read((char *) &indexCount, sizeof(int));
    indices = new int[indexCount];
    ifstream.read((char *) indices, sizeof(int) * indexCount);
    return 0;
}
