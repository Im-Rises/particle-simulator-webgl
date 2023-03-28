#ifndef TRANSFORM_FEEDBACK_H
#define TRANSFORM_FEEDBACK_H

#include <array>

#include <glad/glad.h>

#include "../Entity.h"

class ParticleSimulatorTF : public Entity {
    static const char* const VertexShaderSource;
    static const char* const FragmentShaderSource;

    GLuint VAO[2];
    GLuint TFBO[2];
    GLuint VBO[2];

    struct Particle {
        glm::vec3 position;
        glm::vec3 velocity;

        Particle() : position(glm::vec3(0.0F)), velocity(glm::vec3(0.0F, 0.0F, 0.0F)) {}
    };

    std::vector<Particle> particles;

    GLuint currentVAO;
    GLuint currentTFBO;

    int particlesCount = 100;

    float deltaTime = 0.0F;
    glm::vec3 pointOfGravity = glm::vec3(0.0F, 0.0F, 0.0F);
    float isTargeting = 0.0F;
    float isPaused = 0.0F;

public:
    ParticleSimulatorTF();

    ParticleSimulatorTF(const ParticleSimulatorTF&) = delete;
    auto operator=(const ParticleSimulatorTF&) -> ParticleSimulatorTF& = delete;
    ParticleSimulatorTF(ParticleSimulatorTF&&) = delete;
    auto operator=(ParticleSimulatorTF&&) -> ParticleSimulatorTF& = delete;

    ~ParticleSimulatorTF() override;

public:
    void update(const float& deltaTime) override;

    void render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) override;

    void reset();

public:
    void setTarget(const glm::vec3& target);

    void setIsTargeting(const bool& value);

    [[nodiscard]] auto getIsTargeting() const -> bool;

    void setIsPaused(const bool& value);

    [[nodiscard]] auto getParticleCount() const -> size_t;
};


#endif // TRANSFORM_FEEDBACK_H
