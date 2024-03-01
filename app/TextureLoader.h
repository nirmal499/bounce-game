#ifndef __TEXTURELOADER_HPP_
#define __TEXTURELOADER_HPP_

#include <string>
// GLAD needs to be included first
#include <glad/glad.h>

class TextureLoader{
    public:
        TextureLoader();

        GLuint getTextureID(std::string texFileName);

        ~TextureLoader();
};


#endif