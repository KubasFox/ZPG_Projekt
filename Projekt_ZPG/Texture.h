#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>
#include <string>

class Texture {
private:
    unsigned int ID;
    int width, height, nrChannels;
    bool isLoaded;

public:
    Texture();
    ~Texture();

    enum WrapMode {
        REPEAT = GL_REPEAT,
        MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
        CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
        CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
    };
    enum FilterMode {
        NEAREST = GL_NEAREST,
        LINEAR = GL_LINEAR,
        NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
    };

    void create(const std::string& filePath, WrapMode wrapS = REPEAT, WrapMode wrapT = REPEAT, FilterMode minFilter = LINEAR, FilterMode magFilter = LINEAR);
    void bind(unsigned int slot = 0) const;
    void unbind() const;
    void cleanup();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif