#include "ParticleSimulatorTF.h"

#include <random>

const char* const ParticleSimulatorTF::VertexShaderSource =
    R"(// Vertex Shader which use transform feedback
#version 300 es

in vec3 a_pos;
in vec3 a_vel;

out vec3 out_pos;
out vec3 out_vel;

uniform mat4 u_mvp;

out vec3 v_vel;

void main()
{
    gl_Position = u_mvp * vec4(a_pos, 1.0);
    out_pos = a_pos + vec3(0.1, 0.2, 0.3);
    gl_PointSize = 10.0;
    out_vel = a_vel;
    v_vel = vec3(0.0, 1.0, 1.0);
}
)";

const char* const ParticleSimulatorTF::FragmentShaderSource =
    R"(// Fragment Shader which use transform feedback
#version 300 es

precision highp float;

in vec3 v_vel;

out vec4 o_fragColor;

void main()
{
    o_fragColor = vec4(v_vel, 1.0);
}
)";

ParticleSimulatorTF::ParticleSimulatorTF() : Entity(VertexShaderSource, FragmentShaderSource, { "out_pos", "out_vel" }) {
    particles.resize(particlesCount);

    // Set random seed
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    // Set random positions
    for (int i = 0; i < particlesCount; i++)
    {
        particles[i].position = glm::vec3(dis(gen), dis(gen), dis(gen));
        particles[i].velocity = glm::vec3(0.0F, 0.0F, 0.0F);
    }

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenTransformFeedbacks(2, TFBO);

    for (int i = 0; i < 2; i++)
    {
        glBindVertexArray(VAO[i]);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(particles.size() * sizeof(Particle)), particles.data(), GL_DYNAMIC_COPY);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, velocity));
        glEnableVertexAttribArray(1);

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

ParticleSimulatorTF::~ParticleSimulatorTF() {
    glDeleteVertexArrays(2, VAO);
    glDeleteTransformFeedbacks(2, TFBO);
    glDeleteBuffers(2, VBO);
}


void ParticleSimulatorTF::update(const float& deltaTime) {
}

void ParticleSimulatorTF::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {
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
}
