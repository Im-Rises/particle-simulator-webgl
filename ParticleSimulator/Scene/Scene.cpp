#include "Scene.h"

Scene::Scene(int display_w, int display_h) : camera(display_w, display_h), particleSimulator(500000) {
}

void Scene::update(float deltaTime) {
    camera.update(deltaTime);
    if (isPaused)
    {
        return;
    }
    particleSimulator.update(deltaTime);
}

void Scene::render() {
    particleSimulator.render(camera.getViewMatrix(), camera.getProjectionMatrix());
    cube.render(camera.getViewMatrix(), camera.getProjectionMatrix());
    particleSimulatorTf.render(camera.getViewMatrix(), camera.getProjectionMatrix());
}

void Scene::updateProjectionMatrix(int display_w, int display_h) {
    camera.updateProjectionMatrix(display_w, display_h);
}

void Scene::togglePause() {
    isPaused = !isPaused;
    particleSimulator.setIsPaused(isPaused);
}

void Scene::reset() {
    particleSimulator.reset();
}
