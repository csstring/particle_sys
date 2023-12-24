#version 410 core

in vec3 fragColor;  // Color from geometry shader
//in vec2 fragTexCoord; // Previously 'texCoord'
out vec4 color;  // Output color of the fragment

void main() {
    //float dist = length(vec2(0.5, 0.5) - fragTexCoord) * 2.0;
    color = vec4(fragColor, 1.0);  // Use the received color, with full opacity
}