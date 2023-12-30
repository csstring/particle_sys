#version 410 core

layout(points) in;
//layout(points, max_vertices = 1) out;
layout(triangle_strip, max_vertices = 4) out;

in VS_OUT {
    vec3 color;
//    float life;
//    float radius;
} gs_in[];

out vec3 fragColor;  // Pass color to fragment shader

void main() {

//   if (gs_in[0].life < 0.0f)
//        return;
    float hw = 0.001;
    vec3 up = vec3(0, 1, 0);
    vec3 right = vec3(1, 0, 0);

    fragColor = gs_in[0].color;

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