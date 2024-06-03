#version 430

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

layout (binding = 0) uniform sampler2D leafTex;

in vec4 fragColor;
in vec2 TexCoords;

void main() {
    vec4 color = texture(leafTex, TexCoords);
    FragColor = color * fragColor;
    BrightColor = vec4(0.0f);
}