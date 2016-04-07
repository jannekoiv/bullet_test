//
// Created by jak on 4/7/16.
//

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Box.h"

using namespace std;

GLuint Box::glMatView = 0;
GLuint Box::glMatProjection = 0;
GLuint Box::glLightDirection = 0;

int createVertexBuffer() {
    GLfloat vertices[] = {
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,

         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
    };
    GLuint vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 24, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    return vertexBuffer;
}

int createNormalBuffer() {
    GLfloat normals[] = {
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
    };
    GLuint normalBuffer = 0;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 24, normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    return normalBuffer;
}

int createColorBuffer() {
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };
    GLuint colorBuffer = 0;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 24, colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    return colorBuffer;
}

int createIndexBuffer() {
    GLushort indices[] = {
        0, 2, 1,
        0, 3, 2,

        4, 6, 5,
        4, 7, 6,

        8, 10, 9,
        8, 11, 10,

        12, 14, 13,
        12, 15, 14,

        16, 18, 17,
        16, 19, 18,

        20, 22, 21,
        20, 23, 22
    };
    GLuint indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 36, indices, GL_STATIC_DRAW);
    return indexBuffer;
}

std::string readFile(const char *file) {
    std::ifstream t(file);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string fileContent = buffer.str();
    return fileContent;
}

int shaderFromFile(int type, string filename) {
    int shader = glCreateShader(type);
    std::string source = readFile(filename.c_str());
    const char *rawSource = source.c_str();
    int length = source.length();
    glShaderSource(shader, 1, &rawSource, &length);
    glCompileShader(shader);
    int compileStatus = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == 1) {
        cout << "Shader compiled.\n";
    } else {
        cout << "Shader compilation failed.\n";
    }
    return shader;
}

int programFromShaders(int vertexShader, int fragmentShader) {
    int program = glCreateProgram();
    glBindAttribLocation(program, 0, "inPosition");
    glBindAttribLocation(program, 1, "inColor");
//    glBindAttribLocation(program, 1, "inNormal");
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    int linkStatus = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == 1) {
        cout << "Program linked.\n";
    } else {
        cout << "Program linking failed.\n";
    }
    return program;
}

Box::Box() {
    worldMatrix = glm::mat4();
    vertexBuffer = createVertexBuffer();
//    normalBuffer = createNormalBuffer();
    colorBuffer = createColorBuffer();
    indexBuffer = createIndexBuffer();
    vertexShader = shaderFromFile(GL_VERTEX_SHADER, "shader.vert");
    fragmentShader = shaderFromFile(GL_FRAGMENT_SHADER, "shader.frag");
    shaderProgram = programFromShaders(vertexShader, fragmentShader);
    glMatWorld = glGetUniformLocation(shaderProgram, "matWorld");
    Box::glMatView = glGetUniformLocation(shaderProgram, "matView");
    Box::glMatProjection = glGetUniformLocation(shaderProgram, "matProjection");
    Box::glLightDirection = glGetUniformLocation(shaderProgram, "lightDirection");
}

float timer = 0.5;

int Box::draw() {
    glUniformMatrix4fv(glMatWorld, 1, GL_FALSE, &worldMatrix[0][0]);


    timer += 0.01f;

    glEnable(GL_CULL_FACE);

    glUseProgram(shaderProgram);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
}





