#version 430

layout (location = 0) in vec3 pos;
layout (location = 1) in float width;

out float lineWidth;

void main() {
    gl_Position = vec4(pos, 1.0f);
    lineWidth = width;
}