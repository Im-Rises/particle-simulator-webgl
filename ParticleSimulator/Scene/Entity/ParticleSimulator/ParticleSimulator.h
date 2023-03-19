#ifndef PARTICLE_SIMULATOR_H
#define PARTICLE_SIMULATOR_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../Entity.h"

class ParticleSimulator : public Entity {
private:
    GLuint VAO, VBO;

    struct Particle {
        glm::vec3 position;
        glm::vec3 velocity;

        Particle() : position(glm::vec3(0.0f)), velocity(glm::vec3(1.0f, 1.0f, 1.0f)) {}
    };

    std::vector<Particle> particles;

    glm::vec3 pointOfGravity;

    float isPaused = 0.0f;
    float isTargeting = 0.0f;

    const float gravity = 1000.0f;
    const float m1 = 1000.0f;
    const float m2 = 1.0f;
    const float distanceOffset = 100.0f;

public:
    explicit ParticleSimulator(int particleCount = 100000);

    ~ParticleSimulator();

public:
    void update(const float &deltaTime) override;

    void render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) override;

public:
    void randomizeParticles();

    void reset();

public:
    void setTarget(const glm::vec3 &target);

    void setIsTargeting(const bool &value);

    [[nodiscard]] bool getIsTargeting() const;

    void setIsPaused(const bool &value);

    [[nodiscard]] size_t getParticleCount() const;
};

#endif // PARTICLE_SIMULATOR_H
