#version 410 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in VS_OUT {
    vec4 color;
    float life;
} gs_in[];

out vec4 fragColor;


void main() {

    if (gs_in[0].life < 0.0f)
       return;
    
    fragColor = gs_in[0].color;
    float hw = 0.005;
    vec3 up = vec3(0, 1, 0);
    vec3 right = vec3(1, 0, 0);

    gl_Position = gl_in[0].gl_Position + vec4(-hw * right - hw * up, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(-hw * right + hw * up, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(hw * right - hw * up, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(hw * right + hw * up, 0.0);
    EmitVertex();

    EndPrimitive();
}