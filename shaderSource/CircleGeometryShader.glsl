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

vec3 hsvToRgb(float h, float s, float v) {
    float r = abs(h * 6.0 - 3.0) - 1.0;
    float g = 2.0 - abs(h * 6.0 - 2.0);
    float b = 2.0 - abs(h * 6.0 - 4.0);
    return clamp(vec3(r, g, b), 0.0, 1.0) * v;
}

void main() {

//   if (gs_in[0].life < 0.0f)
//        return;

    // fragColor = gs_in[0].color;

    float distance = distance(gl_in[0].gl_Position.xy, cursorPos.xy);
    float normalizedDistance = clamp(distance / sqrt(12.0), 0.0, 1.0); // Normalize distance

    float hue = normalizedDistance;
    float value = mix(1.0, 0.1, normalizedDistance);
    fragColor = vec4(hsvToRgb(hue, 1.0, value),1.0);
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
}