#include "Cube.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

const char *vertexShaderSource = "#version 300 es\n"
                                 "\n"
                                 "layout (location = 0) in vec3 a_Pos;\n"
                                 "\n"
                                 "uniform mat4 u_mvp;\n"
                                 "uniform mat4 u_model;\n"
                                 "\n"
                                 "void main()\n"
                                 "{\n"
                                 "\tgl_Position = u_mvp * u_model * vec4(a_Pos, 1.0);\n"
                                 "}\n\0";

const char *fragmentShaderSource = "#version 300 es\n"
                                   "\n"
                                   "precision highp float;\n"
                                   "\n"
                                   "out vec4 o_fragColor;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "\to_fragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
                                   "}";

Cube::Cube() : Entity(vertexShaderSource, fragmentShaderSource) {
    create();
    position = glm::vec3(-2.0F, 0.0F, 0.0F);
    updateModelMatrix();
}

void Cube::create() {
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

Cube::~Cube() {
    destroy();
}

void Cube::destroy() {
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
    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix);
    shader.setMat4("u_model", modelMatrix);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei) vertices.size());

    glBindVertexArray(0);
}
