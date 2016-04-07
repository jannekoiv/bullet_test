#version 120

attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec4 inColor;

uniform mat4 matWorld;
uniform mat4 matView;
uniform mat4 matProjection;
uniform vec3 lightDirection;

varying vec4 color;

void main(void) {
    vec3 normal = mat3(matWorld) * inNormal;


    float magnitude = clamp(dot(normal, lightDirection), 0.3, 1.0);
//    color = vec4(1.0, 1.0, 1.0, 1.0) * magnitude;
    color = inColor;
    gl_Position = matProjection * matView * matWorld * vec4(inPosition.x, inPosition.y, inPosition.z, 1.0);
}
