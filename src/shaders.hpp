#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader {
    unsigned int id;
public:
    Shader(const char* v_path, const char* f_path);

    // Activate the shader
    void use();

    // Utility
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec4(const std::string &name, glm::vec4 value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
};