#include "VBO.h"
#include <iostream>

VBO::VBO() : ID(0), isCreated(false) {}

VBO::~VBO() {cleanup();}


void VBO::create(const std::vector<float>& data) {
    cleanup();
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    isCreated = true;
}


void VBO::bind() const {
    if (isCreated) {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }
}


void VBO::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void VBO::cleanup() {
    if (isCreated) {
        glDeleteBuffers(1, &ID);
        ID = 0;
        isCreated = false;
    }
}
