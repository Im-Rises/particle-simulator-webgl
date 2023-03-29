#include "ParticleSimulatorTF.h"

#include <random>

const char* const ParticleSimulatorTF::VertexShaderSource =
    R"(#version 300 es

in vec3 a_pos;
in vec3 a_vel;

out vec3 out_pos;
out vec3 out_vel;

out vec3 v_vel;

uniform mat4 u_mvp;
uniform float u_deltaTime;
uniform vec3 u_pointOfGravity;
uniform float u_isTargeting;
uniform float u_isRunning;

const float G = 1000.0f;
const float m1 = 1000.0f;
const float m2 = 1.0f;
const float distanceOffset = 1000.0f;

void main()
{
    vec3 r = u_pointOfGravity - a_pos;
    float rSquared = dot(r, r) + distanceOffset;
    vec3 force = (G * m1 * m2 * normalize(r) / rSquared) * u_isTargeting * u_isRunning;

    vec3 acceleration = force / m1;
    vec3 position = a_pos + (a_vel * u_deltaTime + 0.5f * acceleration * u_deltaTime * u_deltaTime) * u_isRunning;
    vec3 velocity = a_vel + acceleration * u_deltaTime;

    out_pos = position;
    out_vel = velocity;

    gl_Position = u_mvp * vec4(position, 1.0);

    v_vel = velocity;
}
)";

const char* const ParticleSimulatorTF::FragmentShaderSource =
    R"(#version 300 es

precision highp float;

in vec3 v_vel;

out vec4 o_fragColor;

void main()
{
    vec3 v_color = vec3(min(v_vel.y, 0.8f), max(v_vel.x, 0.5f), min(v_vel.z, 0.5f));
    o_fragColor = vec4(v_color, 1.0f);
}
)";

ParticleSimulatorTF::ParticleSimulatorTF(int particlesCount) : Entity(VertexShaderSource, FragmentShaderSource, { "out_pos", "out_vel" }) {
    // Set the particles count
    this->particlesCount = particlesCount;
    std::vector<Particle> particles(particlesCount);

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
    this->deltaTime = deltaTime;
}

void ParticleSimulatorTF::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {
    shader.use();
    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix);
    shader.setFloat("u_deltaTime", deltaTime);
    shader.setVec3("u_pointOfGravity", pointOfGravity);
    shader.setFloat("u_isTargeting", isTargeting);
    shader.setFloat("u_isRunning", !isPaused);

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

void ParticleSimulatorTF::reset() {
    // Set the particles count
    std::vector<Particle> particles(particlesCount);

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

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(particles.size() * sizeof(Particle)), particles.data(), GL_DYNAMIC_COPY);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(particles.size() * sizeof(Particle)), particles.data(), GL_DYNAMIC_COPY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleSimulatorTF::setTarget(const glm::vec3& target) {
    pointOfGravity = target;
}

void ParticleSimulatorTF::setIsTargeting(const bool& value) {
    isTargeting = static_cast<float>(value);
}

auto ParticleSimulatorTF::getIsTargeting() const -> bool {
    return isTargeting != 0.0F;
}

void ParticleSimulatorTF::setIsPaused(const bool& value) {
    isPaused = static_cast<float>(value);
}

auto ParticleSimulatorTF::getParticleCount() const -> size_t {
    return particlesCount;
}
