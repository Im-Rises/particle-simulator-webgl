#version 300 es

/*
* UBO are too small to hold all the particles... and SSBO are not supported on OpenGL ES 3.0.
*/

precision highp float;

struct Particle {
    vec3 position;
    vec3 velocity;
};

layout(location = 0) in Particle particles;

uniform mat4 u_mvp;

out vec3 v_velocity;

void main()
{
    gl_Position = u_mvp * vec4(particle.position, 1.0);

    v_velocity = particle.velocity;
}
