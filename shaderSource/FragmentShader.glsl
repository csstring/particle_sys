#version 410 core

in vec2 texCoord;
in vec3 color;
flat in uint primID; // 'flat' qualifier is often used for integer values passed to the fragment shader

layout(location = 0) out vec4 fragColor;

float smootherstep(float x) {
    x = clamp((x - 0.0) / (1.0 - 0.0), 0.0, 1.0);
    return x * x * x * (3.0 * x * (2.0 * x - 5.0) + 10.0);
}

void main() {
    float dist = length(vec2(0.5, 0.5) - texCoord) * 2.0;
    float scale = smootherstep(1.0 - dist);
    fragColor = vec4(color * scale, 1.0);
}