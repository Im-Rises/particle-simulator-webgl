#ifndef SCENE_H
#define SCENE_H

#include "Camera/Camera.h"
#include "Entity/ParticleSimulator/ParticleSimulator.h"
#include "Entity/Cube/Cube.h"
#include "Entity/TransformFeedback/TransformFeedback.h"

class Scene {
private:
    bool isPaused = false;

public:
    Camera camera;
    ParticleSimulator particleSimulator;
    Cube cube;
    TransformFeedback transformFeedback;

public:
    Scene(int display_w, int display_h);

    ~Scene();

    void update(float deltaTime);

    void render();

public:
    void updateProjectionMatrix(int display_w, int display_h);

    void togglePause();

    void reset();

public:
    [[nodiscard]] bool getIsPaused() const { return isPaused; }
};

#endif // SCENE_H
