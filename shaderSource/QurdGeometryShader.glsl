#version 410 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;
uniform vec4 cursorPos;

in VS_OUT {
    float life;
} gs_in[];

out vec4 fragColor;

vec3 hsvToRgb(float h, float s, float v) {
    float r = abs(h * 6.0 - 3.0) - 1.0;
    float g = 2.0 - abs(h * 6.0 - 2.0);
    float b = 2.0 - abs(h * 6.0 - 4.0);
    return clamp(vec3(r, g, b), 0.0, 1.0) * v;
}

void main() {

    if (gs_in[0].life < 0.0f)
       return;
    float distance = distance(gl_in[0].gl_Position.xy, cursorPos.xy);
    float normalizedDistance = clamp(distance / sqrt(12.0), 0.0, 1.0); // Normalize distance

    float hue = normalizedDistance;
    float value = mix(1.0, 0.1, normalizedDistance);
    fragColor = vec4(hsvToRgb(hue, 1.0, value),1.0);

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