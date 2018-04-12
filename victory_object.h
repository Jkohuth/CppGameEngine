#ifndef VICTORYOBJECT_H
#define VICTORYOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include <cmath>


class VictoryObject : public GameObject
{
    public:
        // State	
        GLfloat   Radius;
        GLboolean isTouched;
 

        VictoryObject();
        VictoryObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);

        glm::vec2 Move(GLfloat dt, GLuint window_width);
        void      Reset(glm::vec2 position, glm::vec2 velocity);
}; 

#endif