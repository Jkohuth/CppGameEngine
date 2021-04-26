//Sprite_renderer.cpp

#include "sprite_renderer.h"
#include "gl_macros.hpp"
#include <iostream>

SpriteRenderer::SpriteRenderer(Shader &shader)
{
	this->shader = shader;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	// Prepare transformations
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f)); // First translate (transformations are: scale, rotate, translate) Reversed order

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); //Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f,0.0f,1.0f)); // Rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move Origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last Scale

	this->shader.SetMatrix4("model", model);

	// Render textured quad
	this->shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
	//BINDVERTEXARRAY(this->quadVAO);
  glBindVertexArray(this->quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
	//BINDVERTEXARRAY(0);
  glBindVertexArray(0);

}

void SpriteRenderer::initRenderData()
{
	// Configure VAO/VBO
	GLuint VBO;
	GLuint posID;
	//texID;
	GLfloat verticies[] = {
		//pos 			//Tex
		0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f

	};
	posID = glGetAttribLocation((GLuint)this->shader.id(), "vertex");
	//GENVERTEXARRAYS(1, &this->quadVAO);
	glGenVertexArrays(1, &this->quadVAO);
  glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	//BINDVERTEXARRAY(this->quadVAO);
  glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(posID);
	glVertexAttribPointer(posID, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
  std::cout<<"Sprite Renderer vector object "<<quadVAO<<" position "<<posID<<std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//BINDVERTEXARRAY(0);
  glBindVertexArray(0);
}





















