#version 430

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

layout (binding = 0) uniform sampler2D sunTex;

in vec2 TexCoords;

const vec4 color = {0.93f, 0.45f, 0.28f, 1.0f};

void main() {
    FragColor = texture(sunTex, TexCoords);
    BrightColor = FragColor;
}