//
// Created by jak on 4/9/16.
//

#ifndef BULLET_TEST_MODEL_H
#define BULLET_TEST_MODEL_H
#define GLM_FORCE_RADIANS 1;

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/random.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Model {
public:
    Model();
    std::string readFile(const char *file);
    GLuint shaderFromFile(int type, std::string filename);
    GLuint programFromShaders(int vertexShader, int fragmentShader);
    GLuint createVertexBuffer(GLfloat *vertices);
    GLuint createNormalBuffer(GLfloat *normals);
    GLuint createColorBuffer(GLfloat *colors);
    GLuint createIndexBuffer(GLushort *indices);
    int draw(glm::vec3 &lightPosition, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
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
    static GLuint glLightPosition;
    glm::mat4 worldMatrix;
    int indexCount;
};

#endif //BULLET_TEST_MODEL_H
