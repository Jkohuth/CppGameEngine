//text_renderer.h

#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <iostream>
#include <map>
#include <string>

// GLEW
//#define GLEW_STATIC
//#include <GL/glew.h>
// GLFW
//#include <GLFW/glfw3.h>
// GLM

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Freetype
#include <ft2build.h>
#include FT_FREETYPE_H
// GL includes
#include "shader.h"
#include "texture.h"
#include "sprite_renderer.h"
#include "gl_macros.hpp"

// Holds all state information relevant to a character as loaded using Freetype
struct Character {
	GLuint TextureID; // ID handle of the glyph texture
	glm::ivec2 Size; // Size of glyph
	glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance; // Horizontal offset to advance to next glyph
};

class TextRenderer
{
public:
	// Hold the font once uploaded
	std::map<GLchar, Character> Characters;
	//Constructor (Inits shaders/fonts)
	TextRenderer(Shader &shader, const char* filePathName);
	//Destructor
	~TextRenderer();

void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

private:
	// Render State
	Shader shader;
	GLuint textVAO;
	GLuint textVBO;
	// Initializes and configures the text's, buffer and vertex attrbutes

	void initTextRenderer(Shader &shader, const char* filePathName);


};



#endif























