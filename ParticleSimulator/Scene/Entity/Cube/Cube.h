#ifndef CUBE_H
#define CUBE_H

#include <array>

#include "../Entity.h"
#include "../../../Shader/Shader.h"

class Cube : public Entity {
private:
    static const std::array<float, 108> vertices;

    static const char* const vertexShaderSource;
    static const char* const fragmentShaderSource;

    unsigned int VAO, VBO;

public:
    Cube();

public:
    ~Cube();

public:
    void update(const float& deltaTime) override;

    void render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) override;
};


#endif // CUBE_H
