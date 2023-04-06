#ifndef SCENE_H
#define SCENE_H

#include "Camera/Camera.h"
// #include "Entity/ParticleSimulator/ParticleSimulator.h"
//  #include "Entity/Cube/Cube.h"
#include "Entity/ParticleSimulatorTF/ParticleSimulatorTF.h"

class Scene {
private:
    bool isPaused = false;

public:
    Camera camera;
    //    ParticleSimulator particleSimulator;
    //    Cube cube;
    ParticleSimulatorTF particleSimulatorTf;

    //    std::vector<Entity*> entities;

public:
    Scene(int display_w, int display_h);

    void update(float deltaTime);

    void render();

public:
    void updateProjectionMatrix(int display_w, int display_h);

    void togglePause();

    void reset();

public:
    [[nodiscard]] auto getIsPaused() const -> bool;
};

#endif // SCENE_H
