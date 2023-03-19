#ifndef CUBE_H
#define CUBE_H

#include <array>

#include "../Entity.h"
#include "../../../Shader/Shader.h"

class Cube : public Entity {
private:
    static const char *vertexShaderSource;
    static const char *fragmentShaderSource;

    static const std::array<float, 108> vertices;

    unsigned int VAO, VBO;

public:
    Cube();

private:
    void create();

public:
    ~Cube();

private:
    void destroy();

public:
    void update(const float &deltaTime) override;

    void render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) override;
};


#endif //CUBE_H
