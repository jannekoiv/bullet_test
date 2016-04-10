//
// Created by jak on 4/7/16.
//

#include "sphere.h"

using namespace glm;


GLuint Sphere::createVertexBuffer(vec3 *vertices, int vertexCount) {
    GLuint vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertexCount, (GLfloat *) vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    return vertexBuffer;
}

GLuint Sphere::createNormalBuffer(vec3 *normals, int vertexCount) {
    GLuint normalBuffer = 0;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertexCount, (GLfloat *) normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    return normalBuffer;
}

GLuint Sphere::createColorBuffer(vec4 *colors, int vertexCount) {
    GLuint colorBuffer = 0;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * vertexCount, (GLfloat *) colors, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
    return colorBuffer;
}

GLuint Sphere::createIndexBuffer(vec3 *vertices, GLushort *indices, int indexCount) {
    GLuint indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indexCount, indices, GL_STATIC_DRAW);
    return indexBuffer;
}

int Sphere::initGeometry() {
    float sizeX = 10.0f;
    float sizeY = 10.0f;

    int segmentCount = 5;
    int vertexCount = (segmentCount + 1) * (segmentCount + 1);
    vec3 *vertices = new vec3[vertexCount];

    indexCount = segmentCount * segmentCount * 2 * 3;
    GLushort *indices = new GLushort[indexCount];

    float stepX = sizeX / (float) segmentCount;
    float stepY = sizeY / (float) segmentCount;

    int temporaryIndices[4] = {0, 0, 0, 0};
    int copyIndices[] = {0, 1, 2, 0, 2, 3};
    int indexNumber = 0;

    for (int ix = 0; ix < segmentCount; ix += 1) {
        for (int iy = 0; iy < segmentCount; iy += 1) {
            temporaryIndices[0] = iy * (segmentCount + 1) + ix;
            temporaryIndices[1] = temporaryIndices[0] + segmentCount + 1;
            temporaryIndices[2] = temporaryIndices[0] + segmentCount + 2;
            temporaryIndices[3] = temporaryIndices[0] + 1;

            vec3 offsetToCenter(sizeX / 2.0f, sizeY / 2.0f, 0.0f);
            vertices[temporaryIndices[0]] = vec3(stepX * (float) ix, stepY * (float) iy, 0.0f) - offsetToCenter;
            vertices[temporaryIndices[1]] = vertices[temporaryIndices[0]] + vec3(0.0f, stepY, 0.0f);
            vertices[temporaryIndices[2]] = vertices[temporaryIndices[0]] + vec3(stepX, stepY, 0.0f);
            vertices[temporaryIndices[3]] = vertices[temporaryIndices[0]] + vec3(stepX, 0.0f, 0.0f);
            std::cout << "lowerleft  " << vertices[temporaryIndices[0]].x << " " << vertices[temporaryIndices[0]].y << " " << vertices[temporaryIndices[0]].z << "\n";
            std::cout << "upperright " << vertices[temporaryIndices[2]].x << " " << vertices[temporaryIndices[2]].y << " " << vertices[temporaryIndices[2]].z << "\n";

            for(int i = 0; i < 6; i ++) {
                indices[indexNumber++] = temporaryIndices[copyIndices[i]];
            }
        }
    }
    for(int i = 0; i<vertexCount; i ++) {
        vertices[i] = rotate(vertices[i], 0.0f, vec3(0.0f, 1.0f, 0.0f));
    }


    vertexBuffer = createVertexBuffer(vertices, vertexCount);
    vec3 *normals = new vec3[vertexCount];
    normalBuffer = createNormalBuffer(normals, vertexCount);
    vec4 *colors = new vec4[vertexCount];
    colorBuffer = createColorBuffer(colors, vertexCount);
    indexBuffer = createIndexBuffer(vertices, indices, indexCount);
    return 0;
}

Sphere::Sphere() {
    initGeometry();
}


int Sphere::draw(glm::vec3 &lightPosition, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    glUseProgram(shaderProgram);

    glUniformMatrix4fv(glMatWorld, 1, GL_FALSE, &worldMatrix[0][0]);
    glUniformMatrix4fv(Model::glMatView, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(Model::glMatProjection, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniform3fv(Model::glLightPosition, 1, &lightPosition[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, 0);
}


