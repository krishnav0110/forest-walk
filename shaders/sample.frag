#version 430

layout (binding = 0) uniform sampler2D scene;

out vec4 FragColor;

in vec2 TexCoords;

void main() {
    FragColor = texture(scene, TexCoords);
}