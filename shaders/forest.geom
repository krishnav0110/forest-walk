#version 430

layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

in float lineWidth[];

out vec4 fragColor;

uniform mat4 viewMat;
uniform mat4 projectionMat;

const vec3 color = vec3(0.86f, 0.45f, 0.24f);
const vec3 frontVector = vec3(0.0f, 0.0f, 1.0f);

void main() {
    vec3 dir = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
    dir = cross(dir, frontVector);
    dir = normalize(dir);
    vec4 width = vec4(dir * lineWidth[0], 0.0f);

    vec4 vertexPos = gl_in[0].gl_Position - width;
    gl_Position = projectionMat * viewMat * vertexPos;
    float opacity = gl_Position.z;
    vec4 fColor = vec4(color * opacity * 0.25f, cos(opacity * 1.5f));
    fragColor = fColor;
    EmitVertex();

    vertexPos = gl_in[0].gl_Position + width;
    gl_Position = projectionMat * viewMat * vertexPos;
    fragColor = fColor;
    EmitVertex();

    width = vec4(dir * lineWidth[1], 0.0f);
    vertexPos = gl_in[1].gl_Position - width;
    gl_Position = projectionMat * viewMat * vertexPos;
    fragColor = fColor;
    EmitVertex();
    
    vertexPos = gl_in[1].gl_Position + width;
    gl_Position = projectionMat * viewMat * vertexPos;
    fragColor = fColor;
    EmitVertex();

    EndPrimitive();
}