#version 120
// It was expressed that some drivers required this next line to function properly
//precision mediump float;

varying vec4 color;
void main(void) {
    gl_FragColor = color;
}
