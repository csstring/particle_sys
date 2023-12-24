#version 410 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in VS_OUT {
    vec3 color;
    float life;
    float radius;
} gs_in[];

out vec3 fragColor; // Changed from 'color' to 'fragColor'
out vec2 fragTexCoord;

void main() {
    if (gs_in[0].life < 0.0f)
        return;

    float hw = gs_in[0].radius; // halfWidth
    vec3 up = vec3(0, 1, 0);
    vec3 right = vec3(1, 0, 0);

    fragColor = gs_in[0].color;

    fragTexCoord = vec2(0.0, 1.0);
    gl_Position = gl_in[0].gl_Position + vec4(-hw * right - hw * up, 0.0);
    EmitVertex();

    fragTexCoord = vec2(0.0, 0.0);
    gl_Position = gl_in[0].gl_Position + vec4(-hw * right + hw * up, 0.0);
    EmitVertex();

    fragTexCoord = vec2(1.0, 1.0);
    gl_Position = gl_in[0].gl_Position + vec4(hw * right - hw * up, 0.0);
    EmitVertex();

    fragTexCoord = vec2(1.0, 0.0);
    gl_Position = gl_in[0].gl_Position + vec4(hw * right + hw * up, 0.0);
    EmitVertex();

    EndPrimitive();
}