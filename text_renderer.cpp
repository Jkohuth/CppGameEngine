//text_renderer.cpp
#define GLM_FORCE_RADIANS
#include "text_renderer.h"
#include "gl_macros.hpp"
#include "resource_manager.h"
//GLuint textVBO;
#include <iostream>

TextRenderer::TextRenderer(unsigned int width, unsigned int height)
{
  this->TextShader = ResourceManager::LoadShader("shaders/text.vs", "shaders/text.frag", nullptr, "text");
  this->TextShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f), true);
  this->TextShader.SetInteger("text", 0);
  GLuint posID;
  posID = glGetAttribLocation((GLuint)this->TextShader.id(), "vertex");

  GENVERTEXARRAYS(1, &this->textVAO);
  glGenBuffers(1, &this->textVBO);
  BINDVERTEXARRAY(this->textVAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->textVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);  

  //glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glVertexAttribPointer(posID, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  std::cout<<"Vector Array Object Text "<<textVAO<<" positionID "<<posID<<std::endl;
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  BINDVERTEXARRAY(0);


}

TextRenderer::~TextRenderer()
{
	glDeleteVertexArrays(1, &this->textVAO);
}
void TextRenderer::Load(std::string font, unsigned int fontSize){
    // first clear the previously loaded Characters
    this->Characters.clear();
    // then initialize and load the FreeType library
    FT_Library ft;    
    if (FT_Init_FreeType(&ft)) // all functions return a value different than 0 whenever an error occurred
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    // set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
    // then for the first 128 ASCII characters, pre-load/compile their characters and store them
    for (GLubyte c = 0; c < 128; c++) // lol see what I did there 
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
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
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<GLuint>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state	
    this->TextShader.Use();
    this->TextShader.SetVector3f("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    BINDVERTEXARRAY(this->textVAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos,       0.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, this->textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
    }
    BINDVERTEXARRAY(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
/*void TextRenderer::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{

	//text = "hello";
	//std::cout<<"Made it here\n";
	//std::cout<<color.x<<" "<<color.y<<" "<<color.z<<" \n";
	// Prepare the text to appear on screen
	this->TextShader.Use();
  this->TextShader.SetVector3f("textColor", color);
	//glUniform3f(glGetUniformLocation(shader.id(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    BINDVERTEXARRAY(this->textVAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = this->Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },            
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }           
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    BINDVERTEXARRAY(0);
    glBindTexture(GL_TEXTURE_2D, 0);



}
*/
void TextRenderer::initTextRenderer(Shader &shader, const char* filePathName)
{

	// Configure VAO/VBO
//	GLuint VBO;
	GLuint posID;
			// FreeType
		FT_Library ft;
		// All functions return a value different than 0 whenever an error occurred
		if(FT_Init_FreeType(&ft))
			std::cout<< "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

		// Load font as face
		FT_Face face;
		if(FT_New_Face(ft, filePathName, 0, &face))
//		if(FT_New_Face(ft, "assets/fonts/retro.ttf", 0, &face))
				std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		// Set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// Disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Load first 128 characters of ASCII set
		for(GLubyte c = 0; c < 128; c++)
		{
			// Load character glyph
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR:: FREETYPE: Failed to load Glyph" << std::endl;
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
			// Set texture optinos
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				(GLuint)face->glyph->advance.x
			};
			this->Characters.insert(std::pair<GLchar, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		// Destroy Freetype once we're finished
		FT_Done_Face(face);
		FT_Done_FreeType(ft);


		// Configure VAO/VBO for texture quads
//		posID = glGetAttribLocation(ResourceManager::GetShader("text").Use(), "vertex");
		GENVERTEXARRAYS(1, &this->textVAO);
		glGenBuffers(1, &textVBO);
//		glGenBuffers(1, VBO);

		BINDVERTEXARRAY(this->textVAO);
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* 6 * 4, NULL, GL_DYNAMIC_DRAW);

		posID = glGetAttribLocation((GLuint)this->TextShader.id(), "vertex");
		glEnableVertexAttribArray(posID);
		glVertexAttribPointer(posID, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		BINDVERTEXARRAY(0);

//		this->RenderText(shader.Use(), "When you know what to do", 52.0f, 25.0f, 1.5f, glm::vec3(1.0, 0.8f, 1.0f));

}
