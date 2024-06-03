#version 430

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec4 fragColor;

void main() {
    FragColor = fragColor;
    BrightColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // float brightness = dot(FragColor.rgb, vec3(0.2126f, 0.7152f, 0.0722f));
    // if(brightness > 1.0f) {
    //     BrightColor = vec4(FragColor.rgb, 1.0f);
    // }
    // else {
    //     BrightColor = vec4(0.0, 0.0, 0.0, 1.0f);
    // }
}