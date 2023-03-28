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

public:
    ParticleSimulatorTF();

    ParticleSimulatorTF(const ParticleSimulatorTF&) = delete;
    auto operator=(const ParticleSimulatorTF&) -> ParticleSimulatorTF& = delete;
    ParticleSimulatorTF(ParticleSimulatorTF&&) = delete;
    auto operator=(ParticleSimulatorTF&&) -> ParticleSimulatorTF& = delete;

    virtual ~ParticleSimulatorTF();

public:
    void update(const float& deltaTime) override;

    void render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) override;
};


#endif // TRANSFORM_FEEDBACK_H
