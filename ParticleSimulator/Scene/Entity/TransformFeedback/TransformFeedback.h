#ifndef TRANSFORM_FEEDBACK_H
#define TRANSFORM_FEEDBACK_H

#include <array>

#include <glad/glad.h>

#include "../Entity.h"

class TransformFeedback : public Entity {
    static const char *vertexShaderSource;
    static const char *fragmentShaderSource;

    unsigned int VAO, VBO;

    GLuint feedbackBuffer;
    GLuint query;

    std::vector<glm::vec3> positions;

    int particlesCount = 100;

//    // Set transform feedback variables
//    const std::vector<std::string> transformFeedbackVariables = {"out_pos"};
//
//    // Set transform feedback buffers
//    const std::vector<GLuint> transformFeedbackBuffers = {0, 1};
//
//    // Set transform feedback buffer sizes
//    const std::vector<GLsizei> transformFeedbackBufferSizes = {3 * sizeof(float), 3 * sizeof(float)};
//
//    // Set transform feedback buffer modes
//    const std::vector<GLenum> transformFeedbackBufferModes = {GL_INTERLEAVED_ATTRIBS, GL_INTERLEAVED_ATTRIBS};
//

public:
    TransformFeedback();

public:
    ~TransformFeedback();

public:
    void update(const float &deltaTime) override;

    void render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) override;

};


#endif //TRANSFORM_FEEDBACK_H
