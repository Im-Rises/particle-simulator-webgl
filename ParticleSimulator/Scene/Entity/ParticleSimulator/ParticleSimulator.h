#ifndef PARTICLE_SIMULATOR_H
#define PARTICLE_SIMULATOR_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../Entity.h"

class ParticleSimulator : public Entity {
private:
    static const char* const vertexShaderSource;
    static const char* const fragmentShaderSource;

    GLuint VAO, VBO;

    struct Particle {
        glm::vec3 position;
        glm::vec3 velocity;

        Particle() : position(glm::vec3(0.0F)), velocity(glm::vec3(1.0F, 1.0F, 1.0F)) {}
    };

    std::vector<Particle> particles;

    glm::vec3 pointOfGravity;

    float isPaused = 0.0F;
    float isTargeting = 0.0F;

    const float gravity = 1000.0F;
    const float m1 = 1000.0F;
    const float m2 = 1.0F;
    const float distanceOffset = 100.0F;

public:
    explicit ParticleSimulator(int particleCount = 100000);

    ~ParticleSimulator();

public:
    void update(const float& deltaTime) override;

    void render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) override;

public:
    void randomizeParticles();

    void reset();

public:
    void setTarget(const glm::vec3& target);

    void setIsTargeting(const bool& value);

    [[nodiscard]] auto getIsTargeting() const -> bool;

    void setIsPaused(const bool& value);

    [[nodiscard]] auto getParticleCount() const -> size_t;
};

#endif // PARTICLE_SIMULATOR_H
