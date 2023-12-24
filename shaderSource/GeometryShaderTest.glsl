#version 410 core

layout(points) in;
layout(points, max_vertices = 1) out;

in VS_OUT {
    vec3 color;
    float life;
    float radius;
} gs_in[];

out vec3 fragColor;  // Pass color to fragment shader
out vec2 fragTexCoord;

void main() {

    if (gs_in[0].life < 0.0f)
        return;
    fragColor = gs_in[0].color;
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
}