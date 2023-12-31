#version 410 core

layout(points) in;
layout(points, max_vertices = 1) out;

uniform vec4 cursorPos;

in VS_OUT {
    vec4 color;
//    float life;
//    float radius;
} gs_in[];

out vec4 fragColor;  // Pass color to fragment shader

void main() {

//   if (gs_in[0].life < 0.0f)
//        return;

    // fragColor = gs_in[0].color;

    float maxDistance = 1.0;
    float distance = distance(gl_in[0].gl_Position, cursorPos);
    float normalizedDistance = clamp((distance / maxDistance) * 255.0, 0.0, 255.0);
    fragColor = vec4(normalizedDistance / 255.0 *2, normalizedDistance / 255.0, normalizedDistance / 255.0 * 3, 1.0);

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
}