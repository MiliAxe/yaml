#version 460 core

out vec4 FragColor;

in vec3 v_f_color;

void main() {
    // FragColor = vec4(1.0, 0.4, 0.0, 1.0);
    FragColor = vec4(v_f_color, 1.0);
}
