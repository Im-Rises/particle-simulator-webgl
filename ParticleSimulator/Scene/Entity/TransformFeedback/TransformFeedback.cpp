#include "TransformFeedback.h"

const char *TransformFeedback::vertexShaderSource = R"(
    #version 300 es

    in vec3 a_Pos;

    out vec3 out_pos;

    uniform mat4 u_mvp;
    uniform mat4 u_model;

    void main()
    {
        gl_Position = u_mvp * u_model * vec4(a_Pos, 1.0);
        out_pos = a_Pos;
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

const std::array<float, 18> TransformFeedback::vertices = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
};

TransformFeedback::TransformFeedback() : Entity(vertexShaderSource, fragmentShaderSource, {"out_pos"}) {
    position = glm::vec3(2.0f, 0.0f, 0.0f);
    updateModelMatrix();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TransformFeedback::~TransformFeedback() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


void TransformFeedback::update(const float &deltaTime) {

}

void TransformFeedback::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {
    glBindVertexArray(VAO);

    // Shader
    shader.use();
    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix);
    shader.setMat4("u_model", modelMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
