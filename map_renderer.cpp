//map_renderer.cpp

#include "map_renderer.h"
#include "gl_macros.hpp"


MapRenderer::MapRenderer(std::vector<std::unique_ptr<MapLayer>>& mapLayers, Shader& shader)
    : mapLayers(mapLayers)
{
    this->shader = shader;
    this->initRenderData();

}

void MapRenderer::initRenderData()
{
    GENVERTEXARRAYS(1, &this->quadVAO);
    BINDVERTEXARRAY(this->quadVAO);
//    glBindAttribLocation(shader.id(), 0, "vertex");
//    glBindAttribLocation(shader.id(), 1, "texture");
    
   // vertID = glGetAttribLocation((GLuint)this->shader.id(), "vertex");
   // textID = glGetAttribLocation((GLuint)this->shader.id(), "texture");

   // glEnableVertexAttribArray(vertID);
   // glVertexAttribPointer(vertID, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
 //   glEnableVertexAttribArray(textID);
//    glVertexAttribPointer(textID, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(float)));

    BINDVERTEXARRAY(0);

}
void MapRenderer::DrawMap(){

    this->shader.Use();
    BINDVERTEXARRAY(this->quadVAO);
    vertID = glGetAttribLocation((GLuint)this->shader.id(), "vertex");
    textID = glGetAttribLocation((GLuint)this->shader.id(), "texture");

//    for(std::unique_ptr<MapLayer>::iterator layer : mapLayers)
    for(const auto& layer : mapLayers)
    {
        layer->draw(vertID, textID);
    }
    BINDVERTEXARRAY(0);
}

MapRenderer::~MapRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}
/*
void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
    // Prepare transformations
    this->shader.Use();
    glm::mat4 model;
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

    BINDVERTEXARRAY(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    BINDVERTEXARRAY(0);

}
*/

























