//
// Created by jak on 4/11/16.
//

#ifndef BULLET_TEST_MESH_H
#define BULLET_TEST_MESH_H

#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "subMesh.h"

class Mesh {
public:
    Mesh();
    ~Mesh();

    int initGeometry();
    std::string readFile(const char *file);
    GLuint shaderFromFile(int type, std::string filename);
    GLuint programFromShaders(int vertexShader, int fragmentShader);
    GLuint createVertexBuffer(glm::vec3 *vertices, int vertexCount);
    GLuint createNormalBuffer(glm::vec3 *normals, int vertexCount);
    GLuint createTextureCoordinateBuffer(glm::vec2 *textureCoordinates, int count);
    GLuint createIndexBuffer(GLint *indices, int indexCount);
    int readFromFile(std::ifstream &ifstream);
    int heh();
    int draw(glm::vec3 &lightPosition, glm::mat4 &worldMatrix, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);

    GLuint vertexBuffer;
    GLuint normalBuffer;
    GLuint textureCoordinateBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLuint glMatWorld;
    int vertexCount;
    int indexCount;
    SubMesh *subMeshes;
    int subMeshCount;
    static GLuint glMatView;
    static GLuint glMatProjection;
    static GLuint glLightPosition;
};


#endif //BULLET_TEST_MESH_H
