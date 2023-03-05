#version 300 es

precision highp float;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_velocity;

uniform mat4 u_mvp;

out vec3 v_velocity;

void main()
{
    gl_Position = u_mvp * vec4(a_position, 1.0);
    v_velocity = a_velocity;
    gl_PointSize = 1.0f;
}
