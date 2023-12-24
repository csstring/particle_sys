#version 410 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inVelocity;
layout(location = 2) in vec3 inColor;
layout(location = 3) in float inLife;
layout(location = 4) in float inSize;

uniform mat4 projection;
uniform mat4 view;

// Outputs
out VS_OUT {
    vec3 color;
    float life;
    float radius; // This was previously named 'fragSize'
} vs_out;

void main()
{
    const float fadeLife = 0.2f;
    
    // Processing the particle
    vec3 position = inPosition;
    vec3 color = inColor;
    float life = inLife;
    float size = inSize;

    vs_out.color = inColor * clamp(inLife / 0.2f, 0.0, 1.0); // Assuming you want to output the processed color
    vs_out.life = inLife;
    vs_out.radius = inSize; // Assuming 'inSize' is intended for 'radius'
    gl_Position = projection * view * vec4(inPosition, 1.0);
}