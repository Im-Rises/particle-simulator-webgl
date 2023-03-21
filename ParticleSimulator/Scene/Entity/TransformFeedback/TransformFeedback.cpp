#include "TransformFeedback.h"

#include <iostream>

const char *TransformFeedback::vertexShaderSource =
        R"(#version 300 es
in vec3 a_pos;
//    in vec3 a_vel;

out vec3 out_pos;

uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * vec4(a_pos, 1.0);
//        out_pos = a_pos + a_vel + vec3(1.09, 2.04, 3.01);
    out_pos = a_pos + vec3(0.1, 0.2, 0.3);
    gl_PointSize = 10.0;
}
)";

const char *TransformFeedback::fragmentShaderSource =
        R"(#version 300 es

precision highp float;

out vec4 o_fragColor;

void main()
{
    o_fragColor = vec4(0.0, 1.0, 1.0, 1.0);
}
)";

TransformFeedback::TransformFeedback() : Entity(vertexShaderSource, fragmentShaderSource, {"out_pos"}) {
//    position = glm::vec3(2.0f, 0.0f, 0.0f);
    positions.resize(particlesCount);
//    velocities.resize(particlesCount);

    // Set random seed
    srand(time(NULL));
    // Set random positions in range [-1, 1]
    for (int i = 0; i < particlesCount; i++) {
        positions[i] = glm::vec3(
                (float) rand() / (float) RAND_MAX * 2.0f - 1.0f,
                (float) rand() / (float) RAND_MAX * 2.0f - 1.0f,
                (float) rand() / (float) RAND_MAX * 2.0f - 1.0f
        );
//        velocities[i] = glm::vec3(10.0f, 0.0f, 0.0f);
    }

    // Generate and bind the vertex array object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind the buffer object for position input and set the data for the first pass
    glGenBuffers(1, &posInputVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posInputVBO);
    glBufferData(GL_ARRAY_BUFFER, particlesCount * 3 * sizeof(float), positions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Create the output buffer empty for the first pass
    glGenBuffers(1, &posOutputVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posOutputVBO);
    glBufferData(GL_ARRAY_BUFFER, particlesCount * 3 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    // Create the transform feedback object and set the output buffer
    glGenTransformFeedbacks(1, &transformFeedback);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedback);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, posOutputVBO);

    // Unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}

TransformFeedback::~TransformFeedback() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &posInputVBO);
    glDeleteBuffers(1, &posOutputVBO);
    glDeleteTransformFeedbacks(1, &transformFeedback);
}


void TransformFeedback::update(const float &deltaTime) {

}

void TransformFeedback::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {
    // Bind the VAO
    glBindVertexArray(VAO);

    // Shader
    shader.use();
    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix);

    // Set output buffer
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedback);
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, posOutputVBO);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, posOutputVBO);

    // Begin transform feedback with input buffer
    glBeginTransformFeedback(GL_POINTS);
    glBindBuffer(GL_ARRAY_BUFFER, posInputVBO);
    glDrawArrays(GL_POINTS, 0, particlesCount);
    glEndTransformFeedback();

    // Swap input and output buffers
    std::swap(posInputVBO, posOutputVBO);

    // Unbind
    glBindVertexArray(0);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
//    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
