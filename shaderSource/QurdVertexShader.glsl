#version 410 core

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inVelocity;
layout(location = 2) in vec3 inColor;
layout(location = 3) in float life;

uniform mat4 projection;
uniform mat4 view;
out VS_OUT {
    vec4 color;
    float life;
} vs_out;


void main() {

    gl_Position = projection * view * inPosition;
    vs_out.color = vec4(inColor,1.0);
    vs_out.life = life;
}