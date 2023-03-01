#ifndef PARTICLE_SIMULATOR_H
#define PARTICLE_SIMULATOR_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../Entity.h"

class ParticleSimulator : public Entity {
private:
    const char* vertexShader = "#version 430 core\n"
                                     "\n"
                                     "// Can't use directly vec3 in SSBO (indexed by 4 bytes not 3): https://computergraphics.stackexchange.com/questions/5810/shader-storage-buffer-indexing-by-4-bytes-instead-of-3\n"
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
                                     "// Use float instead of bool as boolean condition in shader can produce unexpected results, the float is 0.0f or 1.0f\n"
                                     "// and used to multiply the force to apply or not\n"
                                     "uniform float u_isTargeting;\n"
                                     "uniform float u_isRunning;\n"
                                     "\n"
                                     "out vec3 v_color;\n"
                                     "\n"
                                     "const float G = 1000.0f;// Gravitational constant\n"
                                     "const float m1 = 1000.0f;// Mass of the particle\n"
                                     "const float m2 = 1.0f;// Mass of the point of gravity\n"
                                     "const float distanceOffset = 1000.0f;\n"
                                     "//const float friction = 0.99f;\n"
                                     "\n"
                                     "void main()\n"
                                     "{\n"
                                     "    Particle particle = particlesSsboData.particles[gl_VertexID];// Get the particle data\n"
                                     "\n"
                                     "    // Newton's law of gravity F = G * m1 * m2 / r^2 (F = force, G = gravitational constant,\n"
                                     "    // m1 = mass of the particle, m2 = mass of the point of gravity, r = distance between the\n"
                                     "    // particle and the point of gravity)\n"
                                     "    vec3 r = u_pointOfGravity - particle.position;\n"
                                     "    float rSquared = dot(r, r) + distanceOffset;// (dot(toMass, toMass)) gives the square of the magnitude (length) of the vector\n"
                                     "    vec3 force = (G * m1 * m2 * normalize(r) / rSquared) * u_isTargeting * u_isRunning;// normalize(r) gives the direction of the vector\n"
                                     "\n"
                                     "    // F = ma\n"
                                     "    vec3 acceleration = force / m1;// a = F / m\n"
                                     "\n"
                                     "    // p = p0 + v * t + 1/2 * a * t^2\n"
                                     "    particle.position += (particle.velocity * u_deltaTime + 0.5f * acceleration * u_deltaTime * u_deltaTime) * u_isRunning;\n"
                                     "\n"
                                     "    // v = v0 + at\n"
                                     "    particle.velocity += acceleration * u_deltaTime;\n"
                                     "\n"
                                     "    // Friction\n"
                                     "    //        particle.velocity *= friction;\n"
                                     "\n"
                                     "    // Set the new particle data\n"
                                     "    particlesSsboData.particles[gl_VertexID] = particle;\n"
                                     "\n"
                                     "    // Set the output\n"
                                     "    gl_Position = u_mvp * vec4(particle.position, 1.0);\n"
                                     "\n"
                                     "    // Set the color based on the velocity\n"
                                     "    v_color = vec3(max(particle.velocity.x, 0.5f), min(particle.velocity.y, 0.5f), min(particle.velocity.z, 0.5f));\n"
                                     "\n"
                                     "    //    // Old code\n"
                                     "    //    v_color = particle.velocity * 0.1f;\n"
                                     "\n"
                                     "    //    // Set fixed color\n"
                                     "    //    v_color = vec3(0.0, 1.0, 1.0);\n"
                                     "}";

    const char* fragmentShader = "#version 430 core\n"
                                       "\n"
                                       "in vec3 v_color;\n"
                                       "\n"
                                       "out vec4 o_fragColor;\n"
                                       "\n"
                                       "void main() {\n"
                                       "    o_fragColor = vec4(v_color, 1.0f);\n"
                                       "}";

private:
    GLuint VAO;
    GLuint ssbo;

    // Can't use directly vec3 in SSBO (indexed by 4 bytes not 3): https://computergraphics.stackexchange.com/questions/5810/shader-storage-buffer-indexing-by-4-bytes-instead-of-3
    struct Particle {
        glm::vec3 position;
        float offset1;
        glm::vec3 velocity;
        float offset2;
        Particle() : position(glm::vec3(0.0f)), velocity(glm::vec3(0.0f)) {}
    };

    std::vector<Particle> particles;

    float deltaTime;
    glm::vec3 pointOfGravity;

    float isPaused = 0.0f;
    float isTargeting = 0.0f;

public:
    explicit ParticleSimulator(int particleCount = 100000);
    ~ParticleSimulator();

public:
    void update(const float& deltaTime) override;
    void render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) override;

public:
    void randomizeParticles();
    void reset();
    void setTarget(const glm::vec3& target) { this->pointOfGravity = target; }

public:
    void setIsTargeting(const bool& value) { this->isTargeting = (float)value; }
    bool getIsTargeting() const { return (bool)this->isTargeting; }
    //    void setIsRunning(const bool& value) { this->isRunning = (float)value; }
    void setIsPaused(const bool& value) { this->isPaused = (float)value; }

    [[nodiscard]] size_t getParticleCount() const { return particles.size(); }
};

#endif // PARTICLE_SIMULATOR_H
