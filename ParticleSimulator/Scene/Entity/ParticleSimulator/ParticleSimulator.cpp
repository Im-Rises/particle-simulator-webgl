#include "ParticleSimulator.h"

#include <random>
#include <iostream>

const char *vertexShader =
        R"(#version 300 es

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
)";

const char *fragmentShader =
        R"(#version 300 es

precision highp float;

in vec3 v_velocity;

out vec4 o_fragColor;

void main() {
    vec3 v_color = vec3(min(v_velocity.y, 0.8f), max(v_velocity.x, 0.5f), min(v_velocity.z, 0.5f));
    o_fragColor = vec4(v_color, 1.0f);
}
)";

ParticleSimulator::ParticleSimulator(int particleCount) : Entity(vertexShader, fragmentShader) {
    position = glm::vec3(6.0f, 0.0f, 0.0f);

    // Resize the particles vector
    particles.resize(particleCount);

    // Init the particles
    randomizeParticles();

    // Init the VAO
    glGenVertexArrays(1, &VAO);

    // Init the VBO
    glGenBuffers(1, &VBO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Set the VBO data
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), particles.data(), GL_STATIC_DRAW);

    // Set the VAO attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void *) offsetof(Particle, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void *) offsetof(Particle, velocity));
    glEnableVertexAttribArray(1);

    // Unbind the VAO
    glBindVertexArray(0);

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ParticleSimulator::~ParticleSimulator() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void ParticleSimulator::update(const float &deltaTime) {
    if (isPaused == 1.0f)
        return;
    for (auto &particle: particles) {
        // Calculate the distance between the particle and the point of gravity
        glm::vec3 r = pointOfGravity - particle.position;
        float rSquared = glm::dot(r, r) + distanceOffset;

        // Calculate the force
        glm::vec3 force = ((gravity * m1 * m2 * glm::normalize(r)) / rSquared) * isTargeting;

        // Calculate the acceleration
        glm::vec3 acceleration = force / m1;

        // Calculate the position
        particle.position += particle.velocity * deltaTime + 0.5f * acceleration * deltaTime * deltaTime;

        // Calculate the velocity
        particle.velocity += acceleration * deltaTime;
    }
}

void ParticleSimulator::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {
    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Set the VBO data
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), particles.data(), GL_STATIC_DRAW);

    // Bind the shader
    shader.use();

    // Set the uniform variables
    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix);

    // Draw the particles
    glDrawArrays(GL_POINTS, 0, particles.size());

    // Unbind the VAO
    glBindVertexArray(0);

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleSimulator::randomizeParticles() {
    // Init the random engine
    std::mt19937 randomEngine;
    std::uniform_real_distribution<float> randomFloats(-1.0f, 1.0f);

    // Init the particles as a cube
    for (auto &particle: particles) {
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
}

void ParticleSimulator::setTarget(const glm::vec3 &target) {
    pointOfGravity = target;
}

void ParticleSimulator::setIsTargeting(const bool &value) {
    isTargeting = value ? 1.0f : 0.0f;
}

bool ParticleSimulator::getIsTargeting() const {
    return isTargeting == 1.0f;
}

void ParticleSimulator::setIsPaused(const bool &value) {
    isPaused = value ? 1.0f : 0.0f;
}

size_t ParticleSimulator::getParticleCount() const {
    return particles.size();
}


