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
