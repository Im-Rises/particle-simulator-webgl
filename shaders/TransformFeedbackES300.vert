#version 300 es

precision mediump float;

// Input from vertex shader
in vec3 a_position;

// Transform feedback output
out vec3 out_position;

// Output to fragment shader
out vec4 v_color;

void main() {
    gl_Position = vec4(a_position, 1.0);
    out_position = a_position + vec3(0.0, 0.0, 0.1);
    v_color = vec4(0.0, 1.0, 1.0, 1.0);
}
