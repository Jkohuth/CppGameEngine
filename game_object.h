#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
/*
// Represents the four possible directions
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};
*/
class GameObject
{
public:
	//Object State
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	GLfloat Rotation;
	GLboolean IsSolid;
	GLboolean Destroyed;
	// Render State
	Texture2D Sprite;
	// Constructor (s)
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	//Draw Sprite
	virtual void Draw(SpriteRenderer &renderer);
};

#endif
