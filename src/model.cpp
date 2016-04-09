//
// Created by jak on 4/9/16.
//

#include "model.h"

GLuint Model::glMatView = 0;
GLuint Model::glMatProjection = 0;
GLuint Model::glLightPosition = 0;

Model::Model() {
    worldMatrix = glm::mat4();
    vertexBuffer = 0;
    normalBuffer = 0;
    colorBuffer = 0;
    indexBuffer = 0;
    indexCount = 0;
    vertexShader = shaderFromFile(GL_VERTEX_SHADER, "shader.vert");
    fragmentShader = shaderFromFile(GL_FRAGMENT_SHADER, "shader.frag");
    shaderProgram = programFromShaders(vertexShader, fragmentShader);
    glMatWorld = glGetUniformLocation(shaderProgram, "matWorld");
    Model::glMatView = glGetUniformLocation(shaderProgram, "matView");
    Model::glMatProjection = glGetUniformLocation(shaderProgram, "matProjection");
    Model::glLightPosition = glGetUniformLocation(shaderProgram, "lightPosition");
}

std::string Model::readFile(const char *file) {
    std::ifstream t(file);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string fileContent = buffer.str();
    return fileContent;
}

GLuint Model::shaderFromFile(int type, std::string filename) {
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

GLuint Model::programFromShaders(int vertexShader, int fragmentShader) {
    int program = glCreateProgram();
    glBindAttribLocation(program, 0, "inPosition");
    glBindAttribLocation(program, 1, "inColor");
    glBindAttribLocation(program, 2, "inNormal");
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

GLuint Model::createVertexBuffer(GLfloat *vertices) {
    GLuint vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 24, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    return vertexBuffer;
}

GLuint Model::createNormalBuffer(GLfloat *normals) {
    GLuint normalBuffer = 0;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 24, normals, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);
    return normalBuffer;
}

GLuint Model::createColorBuffer(GLfloat *colors) {
    GLuint colorBuffer = 0;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 24, colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    return colorBuffer;
}

GLuint Model::createIndexBuffer(GLushort *indices) {
    GLuint indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 36, indices, GL_STATIC_DRAW);
    return indexBuffer;
}

int Model::draw(glm::vec3 &lightPosition, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    glUniformMatrix4fv(glMatWorld, 1, GL_FALSE, &worldMatrix[0][0]);
    glUniformMatrix4fv(Model::glMatView, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(Model::glMatProjection, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniform3fv(Model::glLightPosition, 1, &lightPosition[0]);
    glUseProgram(shaderProgram);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, 0);
}
