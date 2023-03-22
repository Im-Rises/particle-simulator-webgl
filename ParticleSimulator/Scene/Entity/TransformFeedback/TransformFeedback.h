#ifndef TRANSFORM_FEEDBACK_H
#define TRANSFORM_FEEDBACK_H

#include <array>

#include <glad/glad.h>

#include "../Entity.h"

class TransformFeedback : public Entity {
    static const char* const vertexShaderSource;
    static const char* const fragmentShaderSource;

    GLuint VAO;

    GLuint TFBO[2];

    GLuint VBO[2];

    std::vector<glm::vec3> positions;
    //    std::vector<glm::vec3> velocities;

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
