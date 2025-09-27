#include "Texture.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() : ID(0), width(0), height(0), nrChannels(0), isLoaded(false) {}


Texture::~Texture() {
    cleanup();
}


void Texture::create(const std::string& filePath, WrapMode wrapS, WrapMode wrapT, FilterMode minFilter, FilterMode magFilter) { 
    cleanup();

    const std::string folder = "../Textures/";
    std::string fullPath = folder + filePath;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);

    if (!data) { std::cerr << "Failed to load texture: " << fullPath << std::endl; }

    // Generování textury a nastaveni parametru
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

    GLenum format;
    if (nrChannels == 1)      { format = GL_RED; }
    else if (nrChannels == 3) { format = GL_RGB; }
    else if (nrChannels == 4) { format = GL_RGBA; }

    // Ukladani dat do textury
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    isLoaded = true;
}


void Texture::bind(unsigned int slot) const {
    if (!isLoaded) { std::cout << "Texture is not loaded"; return; }
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, ID);
}


void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::cleanup() {
    if (isLoaded) {
        glDeleteTextures(1, &ID);
        ID = 0;
        width = height = nrChannels = 0;
        isLoaded = false;
    }
}