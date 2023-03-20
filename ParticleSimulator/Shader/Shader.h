#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>

#include <glm/glm.hpp>

class Shader {
private:
    unsigned int ID;

public:
    Shader(const char *vertexSource, const char *fragmentSource);

    Shader(const char *vertexSource, const char *fragmentSource,
           const std::vector<std::string> &varyings);

    ~Shader();

    void checkCompileErrors(unsigned int shader, const std::string &type);

public:
    void use();

    [[nodiscard]] unsigned int getID() const;

public:
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setVec2(const std::string &name, float x, float y) const;

    void setVec3(const std::string &name, float x, float y, float z) const;

    void setVec4(const std::string &name, float x, float y, float z, float w) const;

    void setVec2(const std::string &name, const glm::vec2 &value) const;

    void setVec3(const std::string &name, const glm::vec3 &value) const;

    void setVec4(const std::string &name, const glm::vec4 &value) const;

    void setMat2(const std::string &name, const glm::mat2 &mat) const;

    void setMat3(const std::string &name, const glm::mat3 &mat) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;
};

#endif //SHADER_H
