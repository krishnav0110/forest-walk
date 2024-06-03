#version 430

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

layout (binding = 0) uniform sampler2D flareTex;

uniform float alpha;

in vec2 TexCoords;

void main() {
    vec4 fragColor = texture(flareTex, TexCoords);
    FragColor = vec4(fragColor.rgb, fragColor.a * alpha);
    BrightColor = vec4(fragColor.rgb, fragColor.a * alpha * 0.1f);
}