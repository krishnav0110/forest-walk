#version 430

layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

out vec4 fragColor;
out vec2 TexCoords;

uniform mat4 viewMat;
uniform mat4 projectionMat;

const vec3 color = {0.86f, 0.45f, 0.24f};
const vec3 frontVector = vec3(0.0f, 0.0f, 1.0f);
const float lineWidth = 0.015f;
//const vec4 width = vec4(0.015f, 0.0f, 0.0f, 0.0f);
//const vec4 height = vec4(0.0f, 0.015f, 0.0f, 0.0f);

void main() {
    vec3 dir = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
    dir = cross(dir, frontVector);
    dir = normalize(dir);
    vec4 width = vec4(dir * lineWidth, 0.0f);

    vec4 vertexPos = gl_in[0].gl_Position - width;
    gl_Position = projectionMat * viewMat * vertexPos;
    float opacity = gl_Position.z;
    vec4 fColor = vec4(color * opacity * 0.25f, cos(opacity * 1.5f));
    fragColor = fColor;
    TexCoords = vec2(0.0f, 1.0f);
    EmitVertex();

    vertexPos = gl_in[0].gl_Position + width;
    gl_Position = projectionMat * viewMat * vertexPos;
    fragColor = fColor;
    TexCoords = vec2(1.0f, 1.0f);
    EmitVertex();

    vertexPos = gl_in[1].gl_Position - width;
    gl_Position = projectionMat * viewMat * vertexPos;
    fragColor = fColor;
    TexCoords = vec2(0.0f, 0.0f);
    EmitVertex();
    
    vertexPos = gl_in[1].gl_Position + width;
    gl_Position = projectionMat * viewMat * vertexPos;
    fragColor = fColor;
    TexCoords = vec2(1.0f, 0.0f);
    EmitVertex();

    EndPrimitive();
}