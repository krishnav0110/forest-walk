#version 430

layout (binding = 0) uniform sampler2D scene;
layout (binding = 1) uniform sampler2D godRays;

out vec4 FragColor;

in vec2 TexCoords;

const float gamma = 0.8f;

void main() {
    vec3 sceneColor = texture(scene, TexCoords).rgb;
    vec3 godRaysColor = texture(godRays, TexCoords).rgb;
    
    vec3 result = sceneColor + godRaysColor;
    result = pow(result, vec3(1.0f / gamma));

    FragColor = vec4(result, 1.0f);
}