#ifndef __TEXTRENDERER_HPP__
#define __TEXTRENDERER_HPP__

// #include <GL/glew.h>
#include <glad/glad.h> // used to call OPENGL function

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>
#include <iostream>

struct Character {
	GLuint     TextureID;  // Texture ID of each glyph texture
	glm::ivec2 Size;       // glyph Size
	glm::ivec2 Bearing;    // baseline to left/top of glyph
	GLuint     Advance;    // id to next glyph
};

class TextRenderer{

public:
	TextRenderer(std::string text, std::string font, int size, glm::vec3 color, GLuint  program, glm::vec2 position);
	~TextRenderer();

	void draw();
	void setPosition(glm::vec2 _position);
	void setText(std::string _text);

private:
	std::string text;
	GLfloat scale;
	glm::vec3 color;
	glm::vec2 position;

	GLuint VAO, VBO, program;
	std::map<GLchar, Character> Characters;

};


#endif