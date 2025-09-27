#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram() : programID(0), isCompiled(false) {}
ShaderProgram::ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) : programID(0), isCompiled(false) {
    create(vertexSource, fragmentSource);
}


ShaderProgram::~ShaderProgram() {
    cleanup();
}


bool ShaderProgram::create(const std::string& vertexFilepath, const std::string& fragmentFilepath) {
    cleanup();

    std::string vertexSource = LoadShaderSource(vertexFilepath);
    std::string fragmentSource = LoadShaderSource(fragmentFilepath);

    if (vertexSource.empty() || fragmentSource.empty()) {
        std::cerr << "Failed loading shader files!" << std::endl;
        return false;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertSource = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertSource, nullptr);
    glCompileShader(vertexShader);
    if (!checkCompileErrors(vertexShader, "VERTEX")) {
        glDeleteShader(vertexShader);
        return false;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragSource = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragSource, nullptr);
    glCompileShader(fragmentShader);
    if (!checkCompileErrors(fragmentShader, "FRAGMENT")) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);
    if (!checkCompileErrors(programID, "PROGRAM")) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(programID);
        programID = 0;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    isCompiled = true;
    return true;
}


void ShaderProgram::bind() const {
    if (isCompiled) { glUseProgram(programID); }
}


void ShaderProgram::unbind() const {
    glUseProgram(0);
}


void ShaderProgram::cleanup() {
    if (programID != 0) {
        glDeleteProgram(programID);
        programID = 0;
    }
    isCompiled = false;
}


void ShaderProgram::setUniform1i(const std::string& name, int value) const {
    if (!isCompiled) return;
    int location = glGetUniformLocation(programID, name.c_str());
    if (location != -1) {
        glUniform1i(location, value);
    }
}

void ShaderProgram::setUniform1f(const std::string& name, float value) const {
    if (!isCompiled) return;
    int location = glGetUniformLocation(programID, name.c_str());
    if (location != -1) {
        glUniform1f(location, value);
    }
}

void ShaderProgram::setUniform2f(const std::string& name, float x, float y) const {
    if (!isCompiled) return;
    int location = glGetUniformLocation(programID, name.c_str());
    if (location != -1) {
        glUniform2f(location, x, y);
    }
}

void ShaderProgram::setUniform3f(const std::string& name, float x, float y, float z) const {
    if (!isCompiled) return;
    int location = glGetUniformLocation(programID, name.c_str());
    if (location != -1) {
        glUniform3f(location, x, y, z);
    }
}

void ShaderProgram::setUniform4f(const std::string& name, float x, float y, float z, float w) const {
    if (!isCompiled) return;
    int location = glGetUniformLocation(programID, name.c_str());
    if (location != -1) {
        glUniform4f(location, x, y, z, w);
    }
}



bool ShaderProgram::checkCompileErrors(unsigned int shader, const std::string& type) {
    int success;
    char infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "SHADER_COMPILATION_ERROR: " << type << "\n" << infoLog << std::endl;
            return false;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "PROGRAM_LINKING_ERROR: " << type << "\n" << infoLog << std::endl;
            return false;
        }
    }
    return true;
}


std::string ShaderProgram::LoadShaderSource(const std::string& filename) {

    const std::string folder = "../Projekt_ZPG/";
    std::string fullPath = folder + filename;

    std::ifstream file(fullPath);
    if (!file.is_open()) {
        std::cerr << "Nepodarilo se otevrit soubor: " << fullPath << std::endl;
        return "";
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}