#include "TransformFeedback.h"

const char *vertexShaderSourceTF = "";

const char *fragmentShaderSourceTF = "";

TransformFeedback::TransformFeedback() : Entity(vertexShaderSourceTF, fragmentShaderSourceTF) {
    create();
}

void TransformFeedback::create() {

}

TransformFeedback::~TransformFeedback() {
    destroy();
}

void TransformFeedback::destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void TransformFeedback::update(const float &deltaTime) {

}

void TransformFeedback::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {

}
