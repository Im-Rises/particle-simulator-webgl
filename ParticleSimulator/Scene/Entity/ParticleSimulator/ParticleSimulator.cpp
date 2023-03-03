#include "ParticleSimulator.h"

#include <random>
#include <iostream>

const char* vertexShaderParticle = "#version 300 es\n"
                                   "\n"
                                   "precision highp float;\n"
                                   "\n"
                                   "struct Particle {\n"
                                   "    vec3 position;\n"
                                   "    float offset1;\n"
                                   "    vec3 velocity;\n"
                                   "    float offset2;\n"
                                   "};\n"
                                   "\n"
                                   "layout (std430, binding = 0) buffer ParticlesSsbo {\n"
                                   "    Particle particles[];\n"
                                   "} particlesSsboData;\n"
                                   "\n"
                                   "uniform mat4 u_mvp;\n"
                                   "uniform float u_deltaTime;\n"
                                   "uniform vec3 u_pointOfGravity;\n"
                                   "\n"
                                   "uniform float u_isTargeting;\n"
                                   "uniform float u_isRunning;\n"
                                   "\n"
                                   "out vec3 v_velocity;\n"
                                   "\n"
                                   "const float G = 1000.0;\n"
                                   "const float m1 = 1000.0;\n"
                                   "const float m2 = 1.0;\n"
                                   "const float distanceOffset = 1000.0;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    Particle particle = particlesSsboData.particles[gl_VertexID];\n"
                                   "\n"
                                   "    vec3 r = u_pointOfGravity - particle.position;\n"
                                   "    float rSquared = dot(r, r) + distanceOffset;\n"
                                   "    vec3 force = (G * m1 * m2 * normalize(r) / rSquared) * u_isTargeting * u_isRunning;\n"
                                   "\n"
                                   "    vec3 acceleration = force / m1;\n"
                                   "\n"
                                   "    particle.position += (particle.velocity * u_deltaTime + 0.5 * acceleration * u_deltaTime * u_deltaTime) * u_isRunning;\n"
                                   "\n"
                                   "    particle.velocity += acceleration * u_deltaTime;\n"
                                   "\n"
                                   "    particlesSsboData.particles[gl_VertexID] = particle;\n"
                                   "\n"
                                   "    gl_Position = u_mvp * vec4(particle.position, 1.0);\n"
                                   "\n"
                                   "    v_velocity = particle.velocity;\n"
                                   "}\n\0";

const char* fragmentShaderParticle = "#version 300 es\n"
                                     "\n"
                                     "precision highp float;\n"
                                     "\n"
                                     "in vec3 v_velocity;\n"
                                     "\n"
                                     "out vec4 o_fragColor;\n"
                                     "\n"
                                     "void main() {\n"
                                     "    vec3 v_color = vec3(min(v_velocity.y, 0.8f), max(v_velocity.x, 0.5f), min(v_velocity.z, 0.5f));\n"
                                     "    o_fragColor = vec4(v_color, 1.0f);\n"
                                     "}\n\0";

ParticleSimulator::ParticleSimulator(int particleCount) : Entity(vertexShaderParticle, fragmentShaderParticle) {
    position = glm::vec3(0.0f, 0.0f, 0.0f);

    // Resize the particles vector
    particles.resize(particleCount);

    // Init the particles
    randomizeParticles();

    // Init the VAO and VBO
    glGenVertexArrays(1, &VAO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Generate the SSBO
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, particles.size() * sizeof(Particle), particles.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);

    // Unbind the VAO
    glBindVertexArray(0);

    // Unbind the SSBO
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

ParticleSimulator::~ParticleSimulator() {
    glDeleteBuffers(1, &ssbo);
}

void ParticleSimulator::update(const float& deltaTime) {
    this->deltaTime = deltaTime;
}

void ParticleSimulator::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {
    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind the SSBO
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);

    // Bind the shader
    shader.use();

    // Set the uniform variables
    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix);
    shader.setFloat("u_deltaTime", deltaTime);
    shader.setVec3("u_pointOfGravity", pointOfGravity);
    shader.setFloat("u_isTargeting", isTargeting);
    shader.setFloat("u_isRunning", !isPaused);

    // Draw the particles
    glDrawArrays(GL_POINTS, 0, particles.size());

    // Barrier
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    // Unbind the VAO
    glBindVertexArray(0);

    // Unbind the SSBO
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticleSimulator::randomizeParticles() {
    // Init the random engine
    std::mt19937 randomEngine;
    std::uniform_real_distribution<float> randomFloats(-1.0f, 1.0f);

    // Init the particles as a cube
    for (auto& particle : particles)
    {
        particle.position = glm::vec3(randomFloats(randomEngine),
                                randomFloats(randomEngine),
                                randomFloats(randomEngine)) +
                            position;
        particle.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    //    // Init the particles as a sphere
    //    for (auto & particle : particles)
    //    {
    //        particle.position = glm::vec3(randomFloats(randomEngine),
    //                                      randomFloats(randomEngine),
    //                                      randomFloats(randomEngine));
    //        particle.position = glm::normalize(particle.position) * 0.5f;
    //    }
}

void ParticleSimulator::reset() {
    // Reset the particles positions and velocities
    randomizeParticles();

    // Resend to the GPU
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, particles.size() * sizeof(Particle), particles.data()); // We use glBufferSubData because the buffer is already allocated, and we want to update it
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
