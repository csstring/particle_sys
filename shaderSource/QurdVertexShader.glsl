#version 410 core

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inVelocity;  // Not used in this example
layout(location = 2) in vec4 inColor;
//layout(location = 3) in float inLife;     // Not used in this example
//layout(location = 4) in float inSize;     // Not used in this example

//out vec3 passColor; 

uniform mat4 projection;
uniform mat4 view;

out VS_OUT {
    vec4 color;
//    float life;
//    float radius; // This was previously named 'fragSize'
} vs_out;

void main() {
    const float fadeLife = 0.2f;

    gl_Position = projection * view * inPosition;
    vs_out.color = inColor; // * clamp(inLife / 0.2f, 0.0, 1.0);;  // Pass the color directly to the next stage
//    vs_out.life = inLife;
//    vs_out.radius = inSize;
}