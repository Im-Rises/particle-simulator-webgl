#include "Scene.h"

Scene::Scene(int display_w, int display_h) : camera(display_w, display_h), particleSimulatorTf(1000000) // particleSimulator(500000)
{
}

void Scene::update(float deltaTime) {
    camera.update(deltaTime);
    if (isPaused)
    {
        return;
    }
    //    particleSimulator.update(deltaTime);
    particleSimulatorTf.update(deltaTime);
}

void Scene::render() {
    //    cube.render(camera.getViewMatrix(), camera.getProjectionMatrix());
    //    particleSimulator.render(camera.getViewMatrix(), camera.getProjectionMatrix());
    particleSimulatorTf.render(camera.getViewMatrix(), camera.getProjectionMatrix());
}

void Scene::updateProjectionMatrix(int display_w, int display_h) {
    camera.updateProjectionMatrix(display_w, display_h);
}

void Scene::togglePause() {
    isPaused = !isPaused;
    //    particleSimulator.setIsPaused(isPaused);
    particleSimulatorTf.setIsPaused(isPaused);
}

void Scene::reset() {
    //    particleSimulator.reset();
    particleSimulatorTf.reset();
}
