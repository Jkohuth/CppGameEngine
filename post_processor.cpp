//post_processor.cpp

#include "post_processor.h"
#include "gl_macros.hpp"

#include <iostream>

PostProcessor::PostProcessor(Shader shader, GLuint width, GLuint height)
	: PostProcessingShader(shader), Texture(), Width(width), Height(height), Shake(GL_FALSE)
{
	// Initialize renderbuffer/framebuffer object
	glGenFramebuffers(1, &this->MSFBO);
	glGenFramebuffers(1, &this->FBO);
	glGenRenderbuffers(1, &this->RBO);

	// Initialize renderbuffer storage with a multisampled color buffer (don't need a depth/stencil buffer)
	glBindFramebuffer(GL_FRAMEBUFFER, this->MSFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_RGB, width, height); // Allocate storage for render buffer object
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->RBO); // Attach MS render buffer object to framebuffer
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout<< "ERROR::POSTPROCESSOR: Failed to initialize MSFBO" << std::endl;

	// Also initialize the FBO/texture to blit multisampled color-buffer to; used for shader operations (for postprocessing effects)
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
	this->Texture.Generate(width, height, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->Texture.id(), 0); //Attach texture to framebuffer as its color attachment
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout<< "ERROR::POSTPROCESSOR: Failed to initiaze FBO" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Initialize render data and uniforms
	this->initRenderData();
	this->PostProcessingShader.SetInteger("image", 0, GL_TRUE);
	GLfloat offset = 1.0f / 300.0f;
	GLfloat offsets[9][2] = {
		{ -offset,  offset  },  // top-left
        {  0.0f,    offset  },  // top-center
        {  offset,  offset  },  // top-right
        { -offset,  0.0f    },  // center-left
        {  0.0f,    0.0f    },  // center-center
        {  offset,  0.0f    },  // center - right
        { -offset, -offset  },  // bottom-left
        {  0.0f,   -offset  },  // bottom-center
        {  offset, -offset  }   // bottom-right 
	};
	glUniform2fv(glGetUniformLocation(this->PostProcessingShader.id(), "offsets"), 9, (GLfloat*)offsets);
	GLfloat blur_kernel[9] = {
		1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16
	};
	glUniform1fv(glGetUniformLocation(this->PostProcessingShader.id(), "blur_kernel"), 9, blur_kernel);
}

void PostProcessor::BeginRender(){
	
	glBindFramebuffer(GL_FRAMEBUFFER, this->MSFBO);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
void PostProcessor::EndRender(){
	
	// Now resolve multisampled color-buffer into intermediate FBO to store to texture
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->MSFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->FBO);
	glBlitFramebuffer(0, 0, this->Width, this->Height, 0, 0, this->Width, this->Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // Binds both READ and WRITE framebuffer to default framebuffer
}
void PostProcessor::Render(GLfloat time){

	// Set uniforms/options
	this->PostProcessingShader.Use();
	this->PostProcessingShader.SetFloat("time", time);
	this->PostProcessingShader.SetInteger("shake", this->Shake);
	// Render textured quad
	glActiveTexture(GL_TEXTURE0);	
	this->Texture.Bind();
	BINDVERTEXARRAY(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	BINDVERTEXARRAY(0);
	
}
void PostProcessor::initRenderData(){

	// Configure VAO/VBO
	GLuint VBO;
	GLuint posID;
	GLfloat vertices[] = {
		// Pos        // Tex
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,

        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f
	};
	posID = glGetAttribLocation((GLuint)this->PostProcessingShader.id(), "vertex");

	GENVERTEXARRAYS(1, &this->VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (&vertices[0]), GL_STATIC_DRAW);

	BINDVERTEXARRAY(this->VAO);

	glEnableVertexAttribArray(posID);
	glVertexAttribPointer(posID, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	BINDVERTEXARRAY(0);

}














