//
// Created by jak on 4/11/16.
//

#include <sstream>
#include <iostream>
#include "mesh.h"

using namespace std;

GLuint Mesh::glMatView = 0;
GLuint Mesh::glMatProjection = 0;
GLuint Mesh::glLightPosition = 0;

Mesh::Mesh() {
    vertexBuffer = 0;
    normalBuffer = 0;
    textureCoordinateBuffer = 0;
    colorBuffer = 0;
    indexBuffer = 0;

    vertexShader = shaderFromFile(GL_VERTEX_SHADER, "shader.vert");
    fragmentShader = shaderFromFile(GL_FRAGMENT_SHADER, "shader.frag");
    shaderProgram = programFromShaders(vertexShader, fragmentShader);

    vertexCount = 0;
    indexCount = 0;
    subMeshes = nullptr;
    subMeshCount = 0;
    subMeshes = nullptr;

    glMatWorld = glGetUniformLocation(shaderProgram, "matWorld");
    Mesh::glMatView = glGetUniformLocation(shaderProgram, "matView");
    Mesh::glMatProjection = glGetUniformLocation(shaderProgram, "matProjection");
    Mesh::glLightPosition = glGetUniformLocation(shaderProgram, "lightPosition");
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &normalBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

std::string Mesh::readFile(const char *file) {
    std::ifstream t(file);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string fileContent = buffer.str();
    return fileContent;
}

GLuint Mesh::shaderFromFile(int type, std::string filename) {
    int shader = glCreateShader(type);
    std::string source = readFile(filename.c_str());
    const char *rawSource = source.c_str();
    int length = source.length();
    glShaderSource(shader, 1, &rawSource, &length);
    glCompileShader(shader);
    int compileStatus = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == 1) {
        std::cout << "Shader compiled.\n";
    } else {
        std::cout << "Shader compilation failed.\n";
    }
    return shader;
}

GLuint Mesh::programFromShaders(int vertexShader, int fragmentShader) {
    int program = glCreateProgram();
    glBindAttribLocation(program, 0, "inPosition");
    glBindAttribLocation(program, 1, "inNormal");
    glBindAttribLocation(program, 2, "inTextureCoordinate");
    glBindAttribLocation(program, 3, "inColor");
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    int linkStatus = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == 1) {
        std::cout << "Program linked.\n";
    } else {
        std::cout << "Program linking failed.\n";
    }
    return program;
}

GLuint Mesh::createVertexBuffer(glm::vec3 *vertices, int vertexCount) {
    GLuint vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexCount, (GLfloat *) vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    return vertexBuffer;
}

GLuint Mesh::createNormalBuffer(glm::vec3 *normals, int vertexCount) {
    GLuint normalBuffer = 0;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexCount, (GLfloat *) normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    return normalBuffer;
}

GLuint Mesh::createTextureCoordinateBuffer(glm::vec2 *textureCoordinates, int count) {
    GLuint buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * count, (GLfloat *) textureCoordinates, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    return buffer;
}

GLuint Mesh::createIndexBuffer(GLint *indices, int indexCount) {
    GLuint indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indexCount, indices, GL_STATIC_DRAW);
    return indexBuffer;
}

int Mesh::readFromFile(std::ifstream &ifstream) {
    ifstream.read((char *) &subMeshCount, sizeof(int));
    subMeshes = new SubMesh[subMeshCount];
    for (int i = 0; i < subMeshCount; i++) {
        subMeshes[i].readFromFile(ifstream);
    }

    ifstream.read((char *) &vertexCount, sizeof(int));
    glm::vec3 *vertices = new glm::vec3[vertexCount];
    glm::vec3 *normals = new glm::vec3[vertexCount];
    glm::vec2 *textureCoordinates = new glm::vec2[vertexCount];

    for (int i = 0; i < vertexCount; i++) {
        ifstream.read((char *) &vertices[i], sizeof(glm::vec3));
        ifstream.read((char *) &normals[i], sizeof(glm::vec3));
        ifstream.read((char *) &textureCoordinates[i], sizeof(glm::vec2));
    }


    vertexBuffer = createVertexBuffer(vertices, vertexCount);
    normalBuffer = createNormalBuffer(normals, vertexCount);
    textureCoordinateBuffer = createTextureCoordinateBuffer(textureCoordinates, vertexCount);


    indexBuffer = createIndexBuffer(subMeshes[0].indices, subMeshes[0].indexCount);

    return 0;
}

int Mesh::draw(glm::vec3 &lightPosition, glm::mat4 &worldMatrix, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    glUseProgram(shaderProgram);

    glUniformMatrix4fv(glMatWorld, 1, GL_FALSE, &worldMatrix[0][0]);
    glUniformMatrix4fv(Mesh::glMatView, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(Mesh::glMatProjection, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniform3fv(Mesh::glLightPosition, 1, &lightPosition[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, textureCoordinateBuffer);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, subMeshes[0].indexCount, GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_POINTS, 0, vertexCount);
}

int Mesh::heh() {

}

