#include "Cube.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

const std::array<float, 108> Cube::vertices = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
};

const char *Cube::vertexShaderSource = R"(
    #version 300 es

    layout (location = 0) in vec3 a_vertex;

    uniform mat4 u_mvp;

    void main()
    {
        gl_Position = u_mvp * vec4(a_vertex, 1.0);
    }
)";

const char *Cube::fragmentShaderSource = R"(
    #version 300 es

    precision highp float;

    out vec4 o_fragColor;

    void main()
    {
        o_fragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

Cube::Cube() : Entity(vertexShaderSource, fragmentShaderSource) {
    position = glm::vec3(-6.0F, 0.0F, 0.0F);
    updateModelMatrix();

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Cube::update(const float &deltaTime) {
    // No component to update
}

void Cube::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {
    glBindVertexArray(VAO);

    // Shader
    shader.use();
    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix * modelMatrix);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei) vertices.size());

    glBindVertexArray(0);
}