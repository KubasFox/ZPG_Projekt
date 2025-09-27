#include "DrawableObject.h"
#include <iostream>

DrawableObject::DrawableObject() : isBuilt(false) {}


DrawableObject::~DrawableObject() {
    cleanup();
}

void DrawableObject::importData(const std::vector<float>& newVertices, const std::vector<unsigned int>& newIndices, const std::vector<float>& newUV){
    vertices = newVertices;
    indices = newIndices;
    UV = newUV;
}

void DrawableObject::changeShader(std::string newVertShaderPath, std::string newFragShaderPath) {
    vertShaderPath = newVertShaderPath;
    fragShaderPath = newFragShaderPath;
    build();
}


bool DrawableObject::build() {
    cleanup();

    if (!shaderProgram.create(vertShaderPath, fragShaderPath)) {return false;}
    texture.create("grass.jpg");

    vao.create();
    vertexVbo.create(vertices);
    vao.linkToVBO(0, 3, vertexVbo, 0, 0);
    uvVbo.create(UV);
    vao.linkToVBO(1, 2, uvVbo, 0, 0);
    ibo.create(indices);
    isBuilt = true;
    return true;
}


void DrawableObject::render() const {
    if (!isBuilt) { std::cerr << "Error: Object not built!" << std::endl; return;}

    shaderProgram.bind();
    static float time = 0.0f;
    time += 0.01f;
    shaderProgram.setUniform1f("time", time*2);

    texture.bind(0);
    shaderProgram.setUniform1i("texture1", 0);
    
    ibo.bind();
    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.unbind();
}


void DrawableObject::cleanup() {
    texture.cleanup();
    vao.cleanup();
    vertexVbo.cleanup();
    ibo.cleanup();
    shaderProgram.cleanup();
    isBuilt = false;
}