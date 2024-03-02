#include "TextRenderer.h"

TextRenderer::TextRenderer(std::string text, std::string font, int size, glm::vec3 color, GLuint  program, glm::vec2 position){
    
    this->text = text;
	this->color = color;
	this->scale = 1.0;
	this->program = program;
    this->position = position;

    /* For text, we specify the orthographic projection instead of perspective projection since it doesn't have any depth */
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // FreeType
	FT_Library ft;

	// Initialise freetype
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	
	// Load font
	FT_Face face;
	if (FT_New_Face(ft, font.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	// Set size of glyphs
	FT_Set_Pixel_Sizes(face, 0, size);

    // Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	// Load first 128 characters of ASCII set
	// From the loaded font
    for(GLubyte i = 0; i < 128 ; ++i){

        /*  we will load the first 128 characters into the font we loaded and create and
            assign the texture ID, size, bearing, and advance. After, we will store the font in
            the characters map
        */

        // Load character glyph 
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)){
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

        // Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

        // Set texture filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	
		// Create a character
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<GLuint>(face->glyph->advance.x)
		};

        // Store character in characters map
		Characters.insert(std::pair<GLchar, Character>(i, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);

	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

    // Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // unbind VBO
	glBindVertexArray(0);               // unbind VAO

}


TextRenderer::~TextRenderer(){}

void TextRenderer::draw(){
    // we'll get the position where the text needs to start drawing
    glm::vec2 textPos = this->position;

    //enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Set program, text color and texture: we need to call the glUSeProgram function to set the program, set the text color to the uniform location, and set the default texture */
	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "textColor"), this->color.x, this->color.y, this->color.z);
	glActiveTexture(GL_TEXTURE0);
	

	glBindVertexArray(VAO);
    // Iterate through all characters
	std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++){

        /*  Let's go through all the characters in the text we want to draw and get their size, the bearing, 
            so that we can set the position, and the texture ID of each glyph we
            want to draw. The text we want to draw is this->text variable
        */
        Character ch = Characters[*c];

        GLfloat xpos = textPos.x + ch.Bearing.x * this->scale;
		GLfloat ypos = textPos.y - (ch.Size.y - ch.Bearing.y) * this->scale;

		GLfloat w = ch.Size.x * this->scale;
		GLfloat h = ch.Size.y * this->scale;

        // Per Character Update VBO
		GLfloat vertices[6][4] = {
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos, ypos, 0.0, 1.0 },
			{ xpos + w, ypos, 1.0, 1.0 },

			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 0.0 }
		};

        // Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		
		// Use glBufferSubData and not glBufferData
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
    
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		// Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		textPos.x += (ch.Advance >> 6) * this->scale;
        /*  we calculate textPos.x, which will determine where the next glyph will
            be drawn. We get this distance by multiplying the advance of the current glyph
            by the scale and adding it to the current text position's x component. A bit shift of
            6 is done to advance, to get the value in pixels 
        */
    }

    glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_BLEND);

}

void TextRenderer::setPosition(glm::vec2 _position){

	this->position = _position;
}


void TextRenderer::setText(std::string _text){

	this->text = _text;

}