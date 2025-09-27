#pragma once
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class ShaderProgram {
private:
    unsigned int programID;
    bool isCompiled;

    bool checkCompileErrors(unsigned int shader, const std::string& type);
    static std::string LoadShaderSource(const std::string& filename);

public:
    ShaderProgram();
    ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
    ~ShaderProgram();

    bool create(const std::string& vertexSource, const std::string& fragmentSource);
    void bind() const;
    void unbind() const;
    void cleanup();

    void setUniform1i(const std::string& name, int value) const;
    void setUniform1f(const std::string& name, float value) const;
    void setUniform2f(const std::string& name, float x, float y) const;
    void setUniform3f(const std::string& name, float x, float y, float z) const;
    void setUniform4f(const std::string& name, float x, float y, float z, float w) const;
};

#endif