#version 410 core

in vec4 fragColor;  // Color from geometry shader
out vec4 color;  // Output color of the fragment

void main() {
    color = fragColor;  // Use the received color, with full opacity
}