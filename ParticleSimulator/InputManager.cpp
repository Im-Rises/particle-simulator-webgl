#include "InputManager.h"

#include "ParticleSimulatorLauncher.h"
#include <GLFW/glfw3.h>

void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)scancode;
    (void)mods;
    auto* engine = static_cast<ParticleSimulatorLauncher*>(glfwGetWindowUserPointer(window));

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        break;
        //    case GLFW_KEY_F11:
        //        if (action == GLFW_PRESS)
        //        {
        //            engine->toggleFullscreen();
        //        }
        //        break;
    case GLFW_KEY_R:
        if (action == GLFW_PRESS)
        {
            engine->resetScene();
        }
        break;
    case GLFW_KEY_P:
        if (action == GLFW_PRESS)
        {
            engine->toggleScenePause();
        }
        break;
    }
}

auto InputManager::isForwardKeyPressed(GLFWwindow* window) -> bool {
    return glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
}

auto InputManager::isBackwardKeyPressed(GLFWwindow* window) -> bool {
    return glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
}

auto InputManager::isLeftKeyPressed(GLFWwindow* window) -> bool {
    return glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
}

auto InputManager::isRightKeyPressed(GLFWwindow* window) -> bool {
    return glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
}

auto InputManager::isUpKeyPressed(GLFWwindow* window) -> bool {
    return glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS;
}

auto InputManager::isDownKeyPressed(GLFWwindow* window) -> bool {
    return glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
           glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS;
}

auto InputManager::isKeyMouseMovementPressed(GLFWwindow* window) -> bool {
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

auto InputManager::isKeyMouseSetAttractorPressed(GLFWwindow* window) -> bool {
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

void InputManager::getMousePosition(GLFWwindow* window, double& xPos, double& yPos) {
    glfwGetCursorPos(window, &xPos, &yPos);
}
