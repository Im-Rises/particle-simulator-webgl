#include "TransformFeedback.h"

#include <random>

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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    // Set random positions
    for (int i = 0; i < particlesCount; i++)
    {
        positions[i] = glm::vec3(dis(gen), dis(gen), dis(gen));
    }

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenTransformFeedbacks(2, TFBO);
    //    glCreateTransformFeedbacks(2, TFBO);

    for (int i = 0; i < 2; i++)
    {
        glBindVertexArray(VAO[i]);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(static_cast<unsigned long>(particlesCount) * 3 * sizeof(float)), positions.data(), GL_STREAM_COPY);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, TFBO[i]);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, VBO[i]);
    }

    glBindVertexArray(0);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    currentVAO = VAO[0];
    currentTFBO = TFBO[1];
}

TransformFeedback::~TransformFeedback() {
    glDeleteVertexArrays(2, VAO);
    glDeleteTransformFeedbacks(2, TFBO);
    glDeleteBuffers(2, VBO);
}


void TransformFeedback::update(const float& deltaTime) {
}

void TransformFeedback::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {


    shader.use();
    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix);

    glBindVertexArray(currentVAO);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, currentTFBO);

    if (currentTFBO == TFBO[0])
    {
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, VBO[0]);
    }
    else
    {
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, VBO[1]);
    }

    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, particlesCount);
    glEndTransformFeedback();

    //    glFlush();

    if (currentVAO == VAO[0])
    {
        currentVAO = VAO[1];
        currentTFBO = TFBO[0];
    }
    else
    {
        currentVAO = VAO[0];
        currentTFBO = TFBO[1];
    }

    glBindVertexArray(0);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

    //    static int currentSourcdIdx = 0;
    //
    //    currentSourcdIdx = (currentSourcdIdx + 1) % 2;
    //
    //    shader.use();
    //
    //    glBindVertexArray(VAO[currentSourcdIdx]);
    //    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, TFBO[currentSourcdIdx]);
    //
    //    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, VBO[currentSourcdIdx]);
    //
    //    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix);
    //
    //    glBeginTransformFeedback(GL_POINTS);
    //    glDrawArrays(GL_POINTS, 0, particlesCount);
    //    glEndTransformFeedback();
    //
    //    glFlush();
    //
    //    glBindVertexArray(0);
    //    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}
