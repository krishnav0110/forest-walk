#version 430

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 vertColor;

void main() {
    FragColor = vec4(vertColor, 1.0f);
    BrightColor = vec4(0.0f);
}