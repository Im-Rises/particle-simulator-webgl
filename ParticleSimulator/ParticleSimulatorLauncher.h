#ifndef PARTICLE_EMISSION_H
#define PARTICLE_EMISSION_H

#include <memory>
#include <string_view>
#include <glm/glm.hpp>

class Scene;

struct GLFWwindow;

constexpr const std::string_view PROJECT_NAME = "Particle Simulator 3D";
constexpr const std::string_view PROJECT_VERSION = "2.0.0";
constexpr const std::string_view PROJECT_GITHUB = "https://github.com/Im-Rises/ParticleSimulator";
constexpr const std::string_view PROJECT_AUTHOR = "Im-Rises (Quentin Morel)";

class ParticleSimulatorLauncher {
private:
    GLFWwindow* window;
    //    int windowWidth = 1280, windowHeight = 720;
    int displayWidth, displayHeight;
    //    bool isFullscreen = false;

    std::unique_ptr<Scene> scene;
    float fixedUpdate = 60.0F;

    struct {
        float x = 0.0F;
        float y = 0.0F;
        float z = 0.0F;
        float w = 1.0F;
    } clear_color;

    float targetDistance = 10.0F;
    glm::vec3 mousePositionWorld;

public:
    ParticleSimulatorLauncher();

    ParticleSimulatorLauncher(const ParticleSimulatorLauncher&) = delete;
    auto operator=(const ParticleSimulatorLauncher&) -> ParticleSimulatorLauncher& = delete;
    ParticleSimulatorLauncher(ParticleSimulatorLauncher&&) = delete;
    auto operator=(ParticleSimulatorLauncher&&) -> ParticleSimulatorLauncher& = delete;

    ~ParticleSimulatorLauncher();

    void start();

private:
    void handleInputs();

    void handleUi(float deltaTime);

    void updateGame(float deltaTime);

    void updateScreen();

public:
    void toggleFullscreen();

    void resetScene();

    void toggleScenePause();

private:
    void centerWindow();

private:
    static void calculateMouseMovement(const double& xMouse, const double& yMouse, double& xMovement, double& yMovement);

    auto projectMouse(const double& xMouse, const double& yMouse) -> glm::vec3;

private:
    static auto getOpenGLVendor() -> std::string_view;

    static auto getOpenGLVersion() -> std::string_view;

    static auto getGLSLVersion() -> std::string_view;

    static auto getGLFWVersion() -> std::string;

    static auto getGladVersion() -> std::string_view;

    static auto getImGuiVersion() -> std::string;

    static auto getGLMVersion() -> std::string;
};

#endif // PARTICLE_EMISSION_H
