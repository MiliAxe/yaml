// #version 460 core

// layout(location = 0) in vec3 a_pos;
// layout(location = 1) in vec3 a_color;
// layout(location = 2) in vec2 a_uv;

// out vec3 v_f_color;
// out vec2 v_f_uv;

// void main() {
//     v_f_color = a_color;
//     v_f_uv = a_uv;
//     gl_Position = vec4(a_pos, 1.0);
// }

#version 460 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_color;
layout(location = 2) in vec2 a_uv;

out vec3 v_f_color;
out vec2 v_f_uv;

uniform float time; // Add a time uniform

void main() {
    v_f_color = a_color;
    v_f_uv = a_uv + vec2(sin(a_pos.y + time), 0.0); // Add a sine wave to the UV coordinates
    gl_Position = vec4(a_pos, 1.0);
}