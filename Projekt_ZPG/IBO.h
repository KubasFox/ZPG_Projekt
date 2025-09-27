#pragma once
#ifndef IBO_H
#define IBO_H

#include <GL/glew.h>
#include <vector>

class IBO {
private:
    unsigned int ID;
    bool isCreated;

public:
    IBO();
    ~IBO();

    void create(const std::vector<unsigned int>& indices);
    void bind() const;
    void unbind() const;
    void cleanup();
};

#endif