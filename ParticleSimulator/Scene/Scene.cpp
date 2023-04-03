#include "Scene.h"

Scene::Scene(int display_w, int display_h) : camera(display_w, display_h), particleSimulatorTf(1000000) {
}

void Scene::update(float deltaTime) {
    camera.update(deltaTime);
    if (isPaused)
    {
        return;
    }
    particleSimulatorTf.update(deltaTime);
}

void Scene::render() {
    particleSimulatorTf.render(camera.getViewMatrix(), camera.getProjectionMatrix());
}

void Scene::updateProjectionMatrix(int display_w, int display_h) {
    camera.updateProjectionMatrix(display_w, display_h);
}

void Scene::togglePause() {
    isPaused = !isPaused;
    particleSimulatorTf.setIsPaused(isPaused);
}

void Scene::reset() {
    camera.reset();
    particleSimulatorTf.reset();
}

auto Scene::getIsPaused() const -> bool {
    return isPaused;
}
