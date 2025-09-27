#pragma once
#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <GL/glew.h>
#include <vector>
#include "ShaderProgram.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "IBO.h"

class DrawableObject {
private:
    
    VAO vao;
    VBO vertexVbo;
    VBO uvVbo;
    IBO ibo;
    Texture texture;
    ShaderProgram shaderProgram;
    bool isBuilt;

    std::string vertShaderPath = "Default.vert";
    std::string fragShaderPath = "Default.frag";

    std::vector<float> vertices = {       
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,  
        -0.5f, -0.5f, 0.0f,  
        -0.5f,  0.5f, 0.0f   
    };

    std::vector<float> UV = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3 
    };

public:
    DrawableObject();
    ~DrawableObject();

    void importData(const std::vector<float>& newVertices, const std::vector<unsigned int>& newIndices, const std::vector<float>& newUV);

    void changeShader(std::string newVertShaderPath, std::string newFragShaderPath);

    bool build();
    void render() const;
    void cleanup();
};

#endif