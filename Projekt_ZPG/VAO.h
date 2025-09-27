#pragma once
#ifndef VAO_H
#define VAO_H

#include <GL/glew.h>
#include "VBO.h"

class VAO {
private:
    unsigned int ID;
    bool isCreated;

public:
    VAO();
    ~VAO();

    void create();
    void bind() const;
    void unbind() const;
    void cleanup();
    void linkToVBO(int location, int size, const VBO& vbo, int stride, void* offset);
};

#endif