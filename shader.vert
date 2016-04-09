#version 120

attribute vec3 inPosition;
attribute vec4 inColor;
attribute vec3 inNormal;

uniform mat4 matWorld;
uniform mat4 matView;
uniform mat4 matProjection;
uniform vec3 lightPosition;

varying vec4 color;

void main(void) {

    vec4 worldPosition = matWorld * vec4(inPosition.xyz, 1.0);
    vec3 normal = mat3(matWorld) * inNormal;

    vec3 directionToLight = normalize(lightPosition - worldPosition.xyz);
    float magnitude = clamp(dot(normal, directionToLight), 0.0, 1.0);

    color = inColor * magnitude;
    gl_Position = matProjection * matView * worldPosition;
}
