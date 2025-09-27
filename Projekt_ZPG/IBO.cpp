#include "IBO.h"
#include <iostream>

IBO::IBO() : ID(0), isCreated(false) {}

IBO::~IBO() {
    cleanup();
}

void IBO::create(const std::vector<unsigned int>& indices) {
    cleanup();
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),indices.data(), GL_STATIC_DRAW);
    isCreated = true;
}


void IBO::bind() const {
    if (isCreated) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }
}


void IBO::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void IBO::cleanup() {
    if (isCreated) {
        glDeleteBuffers(1, &ID);
        ID = 0;
        isCreated = false;
    }
}