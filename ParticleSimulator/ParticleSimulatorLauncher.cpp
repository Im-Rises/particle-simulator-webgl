#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-vararg"

#include "ParticleSimulatorLauncher.h"

#include "InputManager.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <cstdlib>

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <cmath>
#include "Scene/Scene.h"
#include <iostream>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#ifdef __EMSCRIPTEN__
#include "imgui/libs/emscripten/emscripten_mainloop_stub.h"
#include <emscripten/html5.h>

// EM_BOOL touchStart(int eventType, const EmscriptenTouchEvent* touchEvent, void* userData) {
//     // Handle touch start event here
//     return EM_TRUE; // Return true to allow the event to propagate
// }
//
// EM_BOOL touchMove(int eventType, const EmscriptenTouchEvent* touchEvent, void* userData) {
//     // Handle touch move event here
//     //    for (int i = 0; i < touchEvent->numTouches; i++)
//     //    {
//     //        std::cout << "Touch " << i << " x: " << touchEvent->touches[i].canvasX << " y: " << touchEvent->touches[i].canvasY << std::endl;
//     //    }
//     return EM_TRUE; // Return true to allow the event to propagate
// }
//
// EM_BOOL touchEnd(int eventType, const EmscriptenTouchEvent* touchEvent, void* userData) {
//     // Handle touch end event here
//     return EM_TRUE; // Return true to allow the event to propagate
// }
#endif

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

ParticleSimulatorLauncher::ParticleSimulatorLauncher() {
    glfwSetErrorCallback(glfw_error_callback);
    if (glfwInit() == 0)
        exit(1);

// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    const char* glsl_version = "#version 300 es";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // 3.0+ only
#endif

    // Set display size
#ifdef __EMSCRIPTEN__
    // According to canvas
    emscripten_get_canvas_element_size("#canvas", &displayWidth, &displayHeight);
#else
    // According to init windowSize
    //    displayWidth = windowWidth;
    //    displayHeight = windowHeight;
    displayWidth = 1080;
    displayHeight = 720;
#endif

    // Create window with graphics context
    window = glfwCreateWindow(displayWidth, displayHeight, PROJECT_NAME.data(), nullptr, nullptr);
    if (window == nullptr)
        exit(1);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Callbacks
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, InputManager::key_callback);
#ifdef __EMSCRIPTEN__
    //    if (emscripten_set_touchstart_callback("#canvas", NULL, EM_FALSE, touchStart))
    //        std::cout << "touchStart callback set" << std::endl;
    //    else
    //        std::cout << "touchStart callback not set" << std::endl;
    //
    //    if (emscripten_set_touchmove_callback("#canvas", NULL, EM_FALSE, touchMove))
    //        std::cout << "touchMove callback set" << std::endl;
    //    else
    //        std::cout << "touchMove callback not set" << std::endl;
    //
    //    if (emscripten_set_touchend_callback("#canvas", NULL, EM_FALSE, touchEnd))
    //        std::cout << "touchEnd callback set" << std::endl;
    //    else
    //        std::cout << "touchEnd callback not set" << std::endl;
#endif

    // Center window
    centerWindow();

#ifdef __EMSCRIPTEN__
    // Initialize OpenGL loader
    if (gladLoadGLES2Loader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0)
        exit(1);
#else
    // Initialize OpenGL loader
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0)
        exit(1);
#endif

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0)
    {
        style.WindowRounding = 0.0F;
        style.Colors[ImGuiCol_WindowBg].w = 1.0F;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Same line as above but with C++ string
    std::cout << "OpenGL vendor: " << getOpenGLVendor() << std::endl
              << "OpenGL version: " << getOpenGLVersion() << std::endl
              << "GLSL version: " << getGLSLVersion() << std::endl
              << "GLFW version: " << getGLFWVersion() << std::endl
              << "Glad version: " << getGladVersion() << std::endl
              << "ImGui version: " << getImGuiVersion() << std::endl
              << "GLM version: " << getGLMVersion() << std::endl;

    // Setup OpenGL state
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //    glEnable(GL_POINT_SMOOTH); // Deprecated
    //    glPointSize(1.0f); // Not working in OpenGL ES 3.0
}

ParticleSimulatorLauncher::~ParticleSimulatorLauncher() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void ParticleSimulatorLauncher::start() {
    // Create the scene
    scene = std::make_unique<Scene>(displayWidth, displayHeight);

    // Variables for the main loop
    float deltaTime = NAN;

#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (glfwWindowShouldClose(window) == 0)
#endif
    {
        deltaTime = ImGui::GetIO().DeltaTime;

        handleInputs();

        handleUi(deltaTime);

        updateGame(deltaTime);

        updateScreen();
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif
}

void ParticleSimulatorLauncher::handleInputs() {
    glfwPollEvents();

    /* Read keyboard inputs and update states (buffers) */
    if (InputManager::isLeftKeyPressed(window))
        scene->camera.moveLeft();

    if (InputManager::isRightKeyPressed(window))
        scene->camera.moveRight();

    if (InputManager::isForwardKeyPressed(window))
        scene->camera.moveForward();

    if (InputManager::isBackwardKeyPressed(window))
        scene->camera.moveBackward();

    if (InputManager::isUpKeyPressed(window))
        scene->camera.moveUp();

    if (InputManager::isDownKeyPressed(window))
        scene->camera.moveDown();

    /* Read and update mouse controls */
    // Get mouse position
    double mouseX = 0, mouseY = 0;
    InputManager::getMousePosition(window, mouseX, mouseY);

    // Get mouse delta
    double mouseDeltaX = 0, mouseDeltaY = 0;
    calculateMouseMovement(mouseX, mouseY, mouseDeltaX, mouseDeltaY);

    // Read mouse inputs and update camera
    if (InputManager::isKeyMouseMovementPressed(window))
    {
        scene->camera.processMouseMovement(static_cast<float>(mouseDeltaX), static_cast<float>(mouseDeltaY));
    }

    // Read mouse inputs and update particle simulator target
    bool const isTargeting = InputManager::isKeyMouseSetTargetPressed(window);
    scene->particleSimulatorTf.setIsTargeting(isTargeting);
    mousePositionWorld = projectMouse(mouseX, mouseY);
    scene->particleSimulatorTf.setTarget(mousePositionWorld);
}

void ParticleSimulatorLauncher::handleUi(float deltaTime) {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
#ifdef __EMSCRIPTEN__
        static bool isCollapsed = true;
        ImGui::SetNextWindowPos(ImVec2(-static_cast<float>(displayWidth) / 2, (-static_cast<float>(displayHeight) / 2)), ImGuiCond_Once);
        ImGui::SetNextWindowCollapsed(isCollapsed, ImGuiCond_Once);
#endif
        ImGui::Begin("Window info");
        ImGui::Text("%.3f ms/frame (%.1f FPS)", deltaTime, 1.0F / deltaTime);
        ImGui::Text("Window width: %d", displayWidth);
        ImGui::Text("Window height: %d", displayHeight);
        ImGui::Text("GPU: %s", getOpenGLVendor().data());
        ImGui::Text("OpenGL version: %s", getOpenGLVersion().data());
        ImGui::Text("GLSL version: %s", getGLSLVersion().data());
        ImGui::End();
    }

    {
#ifdef __EMSCRIPTEN__
        static bool isCollapsed = true;
        ImGui::SetNextWindowPos(ImVec2(-static_cast<float>(displayWidth) / 2, (-static_cast<float>(displayHeight) / 2) + 20), ImGuiCond_Once);
        ImGui::SetNextWindowCollapsed(isCollapsed, ImGuiCond_Once);
#endif
        ImGui::Begin("Camera settings");
        ImGui::TextColored(ImVec4(1.0F, 0.0F, 1.0F, 1.0F), "View settings");
        //        static bool wireframe = false;
        //        ImGui::Checkbox("Wireframe", &wireframe);
        //        if (wireframe)
        //        {
        //            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //        }
        //        else
        //        {
        //            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //        }
        //        ImGui::NewLine();

        ImGui::TextColored(ImVec4(1.0F, 0.0F, 1.0F, 1.0F), "Camera settings");

        ImGui::Text("Position:");
        ImGui::DragFloat3("##position", reinterpret_cast<float*>(&scene->camera.position));

        ImGui::NewLine();
        ImGui::Text("Pitch:");
        ImGui::Checkbox("Pitch constrained", &scene->camera.constrainPitch);
        ImGui::DragFloat("##pitch", &scene->camera.pitch);

        ImGui::Text("Yaw:");
        ImGui::DragFloat("##yaw", &scene->camera.yaw);

        ImGui::NewLine();
        ImGui::Text("FOV:");
        ImGui::DragFloat("##fov", &scene->camera.fov);

        ImGui::NewLine();
        ImGui::Text("Near plane:");
        ImGui::DragFloat("##near", &scene->camera.nearPlane);

        ImGui::Text("Far plane:");
        ImGui::DragFloat("##far", &scene->camera.farPlane);

        ImGui::NewLine();
        ImGui::Text("Speed:");
        ImGui::DragFloat("##speed", &scene->camera.movementSpeed);

        ImGui::Text("Sensitivity: ");
        ImGui::DragFloat("##sensitivity", &scene->camera.rotationSpeed, 0.1F);

        ImGui::End();
    }

    {
#ifdef __EMSCRIPTEN__
        static bool isCollapsed = true;
        ImGui::SetNextWindowPos(ImVec2(-static_cast<float>(displayWidth) / 2, (-static_cast<float>(displayHeight) / 2) + 40), ImGuiCond_Once);
        ImGui::SetNextWindowCollapsed(isCollapsed, ImGuiCond_Once);
#endif
        ImGui::Begin("Particle simulator settings");

        ImGui::TextColored(ImVec4(1.0F, 0.0F, 1.0F, 1.0F), "Particles settings");

        ImGui::Text("Particle count: %s", std::to_string(scene->particleSimulatorTf.getParticlesCount()).c_str());
        static int particlesCount = static_cast<int>(scene->particleSimulatorTf.getParticlesCount());
        ImGui::Text("Select particles count:");
        ImGui::DragInt("##particlesCount", &particlesCount, 1, 1, MAX_PARTICLES_COUNT);
        ImGui::Button("Validate##ParticlesCountSetterButton");
        if (ImGui::IsItemClicked())
        {
            scene->particleSimulatorTf.setParticlesCount(particlesCount);
        }
        ImGui::NewLine();

        ImGui::Text("Reset simulation:");
        ImGui::SameLine();
        ImGui::Button("Reset##ResetBtn");
        if (ImGui::IsItemClicked())
        {
            resetScene();
        }

        ImGui::Text("Spawn position:");
        ImGui::DragFloat3("##spawnPosition", reinterpret_cast<float*>(&scene->particleSimulatorTf.position));

        ImGui::Text("Spawn radius:");
        ImGui::DragFloat("##spawnRadius", &scene->particleSimulatorTf.spawnRadius, 0.1F, 0.1F, 100.0F);

        ImGui::Text("Toggle pause:");
        ImGui::SameLine();
        ImGui::Button(scene->getIsPaused() ? "Resume##TogglePAuseBtn" : "Pause##TogglePAuseBtn");
        if (ImGui::IsItemClicked())
        {
            scene->togglePause();
        }

        ImGui::End();
    }

    {
#ifdef __EMSCRIPTEN__
        static bool isCollapsed = true;
        ImGui::SetNextWindowPos(ImVec2(-static_cast<float>(displayWidth) / 2, (-static_cast<float>(displayHeight) / 2) + 60), ImGuiCond_Once);
        ImGui::SetNextWindowCollapsed(isCollapsed, ImGuiCond_Once);
#endif
        ImGui::Begin("Mouse controls");

        //        ImGui::Text("Is targeting: %s", scene->particleSimulator.getIsTargeting() ? "true" : "false");
        ImGui::Text("Is targeting: %s", scene->particleSimulatorTf.getIsTargeting() ? "true" : "false");

        ImGui::Text("Mouse position world:");
        ImGui::Text("X: %f", mousePositionWorld.x);
        ImGui::SameLine();
        ImGui::Text("Y: %f", mousePositionWorld.y);
        ImGui::SameLine();
        ImGui::Text("Z: %f", mousePositionWorld.z);

        ImGui::Text("Target distance:");
        ImGui::DragFloat("##targetDistance", &targetDistance, 0.1F, 0.0F, 100.0F);

        ImGui::End();
    }

    ImGui::Render();
}

void ParticleSimulatorLauncher::updateGame(float deltaTime) {
    // Update
    scene->update(deltaTime);
}

void ParticleSimulatorLauncher::updateScreen() {
#ifdef __EMSCRIPTEN__
    emscripten_get_canvas_element_size("#canvas", &displayWidth, &displayHeight);
#else
    glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
#endif
    scene->updateProjectionMatrix(displayWidth, displayHeight);
    glViewport(0, 0, displayWidth, displayHeight);

    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
        clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO const& io = ImGui::GetIO();
    if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window);
}

void ParticleSimulatorLauncher::centerWindow() {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    auto xPos = (mode->width - displayWidth) / 2;
    auto yPos = (mode->height - displayHeight) / 2;
    glfwSetWindowPos(window, xPos, yPos);
}

void ParticleSimulatorLauncher::resetScene() {
    scene->reset();
}

void ParticleSimulatorLauncher::toggleScenePause() {
    scene->togglePause();
}

void ParticleSimulatorLauncher::calculateMouseMovement(const double& xMouse, const double& yMouse, double& xMovement,
    double& yMovement) {
    static double lastMouseX = 0.0;
    static double lastMouseY = 0.0;

    xMovement = xMouse - lastMouseX;
    yMovement = lastMouseY - yMouse;

    lastMouseX = xMouse;
    lastMouseY = yMouse;
}

auto ParticleSimulatorLauncher::projectMouse(const double& xMouse, const double& yMouse) -> glm::vec3 {
    // Convert the mouse coordinates from screen space to NDC space
    float const normalized_x = (2.0F * static_cast<float>(xMouse)) / static_cast<float>(displayWidth) - 1.0F;
    float const normalized_y = 1.0F - (2.0F * static_cast<float>(yMouse)) / static_cast<float>(displayHeight);

    // Create a vector representing the mouse coordinates in NDC space
    glm::vec4 const mouse_ndc(normalized_x, normalized_y, -1.0F, 1.0F);

    // Convert the mouse coordinates from NDC space to world space
    glm::mat4 const inverse_projection = glm::inverse(scene->camera.getProjectionMatrix());
    glm::mat4 const inverse_view = glm::inverse(scene->camera.getViewMatrix());
    glm::vec4 mouse_world = inverse_projection * mouse_ndc;
    mouse_world = mouse_world / mouse_world.w;
    mouse_world = inverse_view * mouse_world;

    // Calculate the direction from the camera position to the mouse position
    glm::vec3 const camera_to_mouse = glm::normalize(glm::vec3(mouse_world) - scene->camera.position);

    // Use the direction to update the position of an object in the 3D environment
    return scene->camera.position + camera_to_mouse * targetDistance;
}

auto ParticleSimulatorLauncher::getOpenGLVendor() -> std::string_view {
    return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}

auto ParticleSimulatorLauncher::getOpenGLVersion() -> std::string_view {
    return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

auto ParticleSimulatorLauncher::getGLSLVersion() -> std::string_view {
    return reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
}

auto ParticleSimulatorLauncher::getGLFWVersion() -> std::string {
    return std::to_string(GLFW_VERSION_MAJOR) + "." + std::to_string(GLFW_VERSION_MINOR) + "." +
           std::to_string(GLFW_VERSION_REVISION);
}

auto ParticleSimulatorLauncher::getGladVersion() -> std::string_view {
    return "0.1.36";
}

auto ParticleSimulatorLauncher::getImGuiVersion() -> std::string {
    return IMGUI_VERSION;
}

auto ParticleSimulatorLauncher::getGLMVersion() -> std::string {
    return std::to_string(GLM_VERSION_MAJOR) + "." + std::to_string(GLM_VERSION_MINOR) + "." +
           std::to_string(GLM_VERSION_PATCH);
}

#pragma clang diagnostic pop
