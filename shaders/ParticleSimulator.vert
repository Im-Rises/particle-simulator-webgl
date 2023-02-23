#version 300 es

struct Particle {
    vec3 position;
    float offset1;
    vec3 velocity;
    float offset2;
};

layout (std430, binding = 0) buffer ParticlesSsbo {
    Particle particles[];
};

uniform mat4 u_view;
uniform mat4 u_projection;
uniform float u_deltaTime;
uniform vec3 u_pointOfGravity;
uniform bool u_isPaused;

out vec3 v_color;

const float G = 1000.0f;
const float m1 = 1000.0f;
const float m2 = 1.0f;
const float distanceOffset = 1000.0f;

void main()
{
    Particle particle = particles[gl_VertexID - 1];

    if (!u_isPaused) {
        vec3 r = u_pointOfGravity - particle.position;
        float rSquared = dot(r, r) + distanceOffset;
        vec3 force = G * m1 * m2 * normalize(r) / rSquared;
        vec3 acceleration = force / m1;
        particle.velocity += acceleration * u_deltaTime;
        particle.position += particle.velocity * u_deltaTime;
        particles[gl_VertexID - 1] = particle;
    }

    gl_Position = u_projection * u_view * vec4(particle.position, 1.0);
    v_color = vec3(0.0, 1.0, 1.0);
}
