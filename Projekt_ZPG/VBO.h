#pragma once
#ifndef VBO_H
#define VBO_H

#include <GL/glew.h>
#include <vector>

class VBO {
private:
    unsigned int ID;
    bool isCreated;

public:
    VBO();
    ~VBO();

    void create(const std::vector<float>& data);
    void bind() const;
    void unbind() const;
    void cleanup();
};

#endif