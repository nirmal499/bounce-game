#include "TextureLoader.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb-master/stb_image.h>

TextureLoader::TextureLoader(){}
TextureLoader::~TextureLoader(){}

GLuint TextureLoader::getTextureID(std::string texFileName)
{
    int width, height, channels;

    stbi_uc* image = stbi_load(texFileName.c_str(), &width, &height, &channels, STBI_rgb);

    if (!image) {
        std::cerr << "Failed to load image: " << stbi_failure_reason() << std::endl;
        exit(0);
    }

    printf("TextureLoader: fileName %s \n", texFileName.c_str());

    GLuint mtexture;
    glGenTextures(1, &mtexture);
    glBindTexture(GL_TEXTURE_2D, mtexture);

    // Set texture wrapping 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /*
        Setting texture filtering parameters

        When the texture is magnified, it is better to set the value to GL_LINEAR to get a smoother
        picture, and when the picture is minimized, it can then be set to GL_NEAREST, as the texels
        (which are texture elements) will be so small that we won't be able to see them anyway 
    */
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /*  It doesn't make sense to load a huge image with the object so far away that you can't even
        see it, so for optimization purposes, you can create mipmaps. Mipmaps basically take the
        texture and converts it to a lower resolution. This will automatically change the image to a
        lower resolution image when the texture is too far away from the camera. It will also
        change to a higher resolution image when the camera is closer.
    */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);     // when the picture is minimized
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);                   // when the picture is maximized

    /* we create the texture using the glTexImage2D function */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    /* Now that the texture is created, we call glGenerateMipmap and pass in the GL_TEXTURE_2D texture type */
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

    return mtexture;

}

