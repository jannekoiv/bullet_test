#version 120

attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inTextureCoordinate;
attribute vec4 inColor;

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

//    color = inColor * magnitude;
    color = vec4(inTextureCoordinate.x, inTextureCoordinate.y, 1.0, 1.0) * magnitude;


    gl_Position = matProjection * matView * worldPosition;
    gl_PointSize = 10.0;
}
