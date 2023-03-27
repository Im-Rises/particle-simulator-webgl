#ifndef TRANSFORM_FEEDBACK_H
#define TRANSFORM_FEEDBACK_H

#include <array>

#include <glad/glad.h>

#include "../Entity.h"

class TransformFeedback : public Entity {
    static const char* const vertexShaderSource;
    static const char* const fragmentShaderSource;

    GLuint VAO[2];

    GLuint TFBO[2];

    GLuint VBO[2];

    struct Particle {
        glm::vec3 position;
        glm::vec3 velocity;

        Particle() : position(glm::vec3(0.0F)), velocity(glm::vec3(0.0F, 0.0F, 0.0F)) {}
    };

    std::vector<glm::vec3> positions;

    int currentVAO;
    int currentTFBO;

    int particlesCount = 100;

public:
    TransformFeedback();

public:
    ~TransformFeedback();

public:
    void update(const float& deltaTime) override;

    void render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) override;
};


#endif // TRANSFORM_FEEDBACK_H
