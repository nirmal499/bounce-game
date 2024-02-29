#ifndef __SHADERLOADER_HPP
#define __SHADERLOADER_HPP

// #include <GL/glew.h>
#include <glad/glad.h> // used to call OPENGL function

#include <string>

class ShaderLoader{
    public:
        GLuint createProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename);

    private:
        std::string readShader(const char *filename);
		GLuint createShader(GLenum shaderType, std::string source, const char* shaderName);
};

#endif