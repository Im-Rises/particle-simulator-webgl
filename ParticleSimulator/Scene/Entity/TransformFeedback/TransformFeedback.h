#ifndef TRANSFORM_FEEDBACK_H
#define TRANSFORM_FEEDBACK_H

#include <array>

#include <glad/glad.h>

#include "../Entity.h"

class TransformFeedback : public Entity {
    static const char *vertexShaderSource;
    static const char *fragmentShaderSource;

    unsigned int VAO, VBO;

    static const std::array<float, 18> vertices;

public:
    TransformFeedback();

public:
    ~TransformFeedback();

public:
    void update(const float &deltaTime) override;

    void render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) override;

};


#endif //TRANSFORM_FEEDBACK_H
