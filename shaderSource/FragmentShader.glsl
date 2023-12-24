#version 410 core

in vec3 fragColor; // Previously 'color'
in vec2 fragTexCoord; // Previously 'texCoord'

out vec4 outColor;

float smootherstep(float x) {
    x = clamp((x - 0.0) / (1.0 - 0.0), 0.0, 1.0);
    return x * x * x * (3.0 * x * (2.0 * x - 5.0) + 10.0);
}

void main() {
    float dist = length(vec2(0.5, 0.5) - fragTexCoord) * 2.0;
    float scale = smootherstep(1.0 - dist);
    outColor = vec4(fragColor * scale, 1.0);
}