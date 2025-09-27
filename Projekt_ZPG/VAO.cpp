#include "VAO.h"
#include <iostream>

VAO::VAO() : ID(0), isCreated(false) {}

VAO::~VAO() {
    cleanup();
}

void VAO::create() {
    cleanup();
    glGenVertexArrays(1, &ID);
    isCreated = true;
}


void VAO::bind() const {
    if (isCreated) {
        glBindVertexArray(ID);
    }
}


void VAO::unbind() const {
    glBindVertexArray(0);
}


void VAO::cleanup() {
    if (isCreated) {
        glDeleteVertexArrays(1, &ID);
        ID = 0;
        isCreated = false;
    }
}


void VAO::linkToVBO(int location, int size, const VBO& vbo, int stride, void* offset) {

    if (!isCreated) {std::cerr << "VAO not created!" << std::endl; return;}
    bind();
    vbo.bind();
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(location);
    vbo.unbind();
}

