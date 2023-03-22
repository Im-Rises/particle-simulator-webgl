#include "TransformFeedback.h"

#include <iostream>

const char* const TransformFeedback::vertexShaderSource =
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

const char* const TransformFeedback::fragmentShaderSource =
    R"(#version 300 es

precision highp float;

out vec4 o_fragColor;

void main()
{
    o_fragColor = vec4(0.0, 1.0, 1.0, 1.0);
}
)";

TransformFeedback::TransformFeedback() : Entity(vertexShaderSource, fragmentShaderSource, { "out_pos" }) {
    positions.resize(particlesCount);

    // Set random seed
    srand(time(nullptr));
    // Set random positions in range [-1, 1]
    for (int i = 0; i < particlesCount; i++)
    {
        positions[i] = glm::vec3(
            (float)rand() / (float)RAND_MAX * 2.0f - 1.0f,
            (float)rand() / (float)RAND_MAX * 2.0f - 1.0f,
            (float)rand() / (float)RAND_MAX * 2.0f - 1.0f);
        //        velocities[i] = glm::vec3(10.0f, 0.0f, 0.0f);
    }

    glGenVertexArrays(2, VAO);
    glGenTransformFeedbacks(2, TFBO);
    glGenBuffers(2, VBO);

    for (int i = 0; i < 2; i++)
    {
        glBindVertexArray(VAO[i]);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, particlesCount * 3 * sizeof(float), positions.data(), GL_STREAM_COPY);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, TFBO[i]);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, VBO[i]);
    }

    glBindVertexArray(0);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

TransformFeedback::~TransformFeedback() {
    glDeleteVertexArrays(2, VAO);
    glDeleteTransformFeedbacks(2, TFBO);
    glDeleteBuffers(2, VBO);
}


void TransformFeedback::update(const float& deltaTime) {
}

void TransformFeedback::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {
    static int currentSourcdIdx = 0;

    currentSourcdIdx = (currentSourcdIdx + 1) % 2;

    shader.use();

    glBindVertexArray(VAO[currentSourcdIdx]);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, TFBO[currentSourcdIdx]);

    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, VBO[currentSourcdIdx]);

    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix);

    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, particlesCount);
    glEndTransformFeedback();

    glBindVertexArray(0);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}
