#version 410 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inVelocity;
layout(location = 2) in vec3 inColor;
layout(location = 3) in float inLife;
layout(location = 4) in float inSize;

// Outputs
out vec3 fragColor;
out float fragLife;
out float fragSize;

void main()
{
    const float fadeLife = 0.2f;
    
    // Processing the particle
    vec3 position = inPosition;
    vec3 color = inColor;
    float life = inLife;
    float size = inSize;
    
    // Output
    gl_Position = vec4(position, 1.0);
    fragColor = color * clamp(life / fadeLife, 0.0, 1.0);
    fragLife = life;
    fragSize = size;
}