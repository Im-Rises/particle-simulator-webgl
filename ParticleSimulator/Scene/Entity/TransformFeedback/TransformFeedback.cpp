#include "TransformFeedback.h"

#include <iostream>

const char *TransformFeedback::vertexShaderSource = R"(
    #version 300 es

    in vec3 a_pos;
    in vec3 a_vel;

    out vec3 out_pos;

    uniform mat4 u_mvp;

    void main()
    {
        gl_Position = u_mvp * vec4(a_pos, 1.0);
        out_pos = a_pos + a_vel + vec3(1.09, 2.04, 3.01);
        gl_PointSize = 10.0;
    }
)";

const char *TransformFeedback::fragmentShaderSource = R"(
    #version 300 es

    precision highp float;

    out vec4 o_fragColor;

    void main()
    {
        o_fragColor = vec4(0.0, 1.0, 1.0, 1.0);
    })";

TransformFeedback::TransformFeedback() : Entity(vertexShaderSource, fragmentShaderSource, {"out_pos"}) {
//    position = glm::vec3(2.0f, 0.0f, 0.0f);
    positions.resize(particlesCount);
    velocities.resize(particlesCount);

    // Set random seed
    srand(time(NULL));
    // Set random positions in range [-1, 1]
    for (int i = 0; i < particlesCount; i++) {
        positions[i] = glm::vec3(
                (float) rand() / (float) RAND_MAX * 2.0f - 1.0f,
                (float) rand() / (float) RAND_MAX * 2.0f - 1.0f,
                (float) rand() / (float) RAND_MAX * 2.0f - 1.0f
        );
        velocities[i] = glm::vec3(10.0f, 0.0f, 0.0f);
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

//    glGenBuffers(1, &VBOpos);
//    glBindBuffer(GL_ARRAY_BUFFER, VBOpos);
//    glBufferData(GL_ARRAY_BUFFER, particlesCount * 3 * sizeof(float), positions.data(), GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
//    glEnableVertexAttribArray(0);

// Generate and bind the buffer object for positions
    GLuint posBuffer;
    glGenBuffers(1, &posBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
    glBufferData(GL_ARRAY_BUFFER, particlesCount * 3 * sizeof(float), positions.data(), GL_STATIC_DRAW);

// Generate and bind the buffer object for velocities
    GLuint velBuffer;
    glGenBuffers(1, &velBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, velBuffer);
    glBufferData(GL_ARRAY_BUFFER, particlesCount * 3 * sizeof(float), velocities.data(), GL_STATIC_DRAW);

// Bind the position buffer to attribute location 0
    glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

// Bind the velocity buffer to attribute location 1
    glBindBuffer(GL_ARRAY_BUFFER, velBuffer);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);


    glGenBuffers(1, &feedbackBuffer);
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, feedbackBuffer);
    glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, particlesCount * 3 * sizeof(float), nullptr, GL_DYNAMIC_COPY);

    glGenQueries(1, &query);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

TransformFeedback::~TransformFeedback() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBOpos);
    glDeleteBuffers(1, &feedbackBuffer);
}


void TransformFeedback::update(const float &deltaTime) {

}

void TransformFeedback::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {
    glBindVertexArray(VAO);

    // Shader
    shader.use();
    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix);

    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, feedbackBuffer);
    glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, query);
//    glEnable(GL_RASTERIZER_DISCARD);
    glBeginTransformFeedback(GL_POINTS);

    glDrawArrays(GL_POINTS, 0, particlesCount);

    glEndTransformFeedback();
//    glDisable(GL_RASTERIZER_DISCARD);
    glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
    glGetQueryObjectuiv(query, GL_QUERY_RESULT, reinterpret_cast<GLuint *>(&particlesCount));

    // Retrieve the transform feedback output
    float *feedbackData = new float[particlesCount * 3];
    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, particlesCount * 3 * sizeof(float), feedbackData);

    // Print the output
    for (int i = 0; i < particlesCount; i++) {
        std::cout << feedbackData[i * 3] << ", " << feedbackData[i * 3 + 1] << ", " << feedbackData[i * 3 + 2]
                  << std::endl;
    }
    delete[] feedbackData;

    glBindVertexArray(0);
}
