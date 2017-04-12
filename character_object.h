

#ifndef CHARACTEROBJECT_H
#define CHARACTEROBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "game_object.h"
//#include "power_up.h"

// CharacterObject holds the state of the ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to character object that
// were too specific for GameObject alone.
class CharacterObject : public GameObject
{
public:
	// Character State
	glm::vec2 	PlayerSize;
	GLfloat 	Scale;
	GLfloat		Speed;
//	GLboolean	Stuck;
//	GLboolean Sticky, PassThrough;

	// Made the inherited class public to resolve the issue
//	using GameObject::Position;
//	using GameObject::Size;
//	using GameObject::Velocity;

	// Constructor (s)
	CharacterObject();
	CharacterObject(glm::vec2 pos, glm::vec2 playerSize, Texture2D sprite);
	// Moves the ball, keeping it constrained within the winow bounds (except for the bottom edge); returns new posiiton
	glm::vec2 Move(GLfloat dt, Direction direction);
	// Resets the ball to original state with given position and velocity
	void	  Reset(glm::vec2 position, glm::vec2 velocity);

};

#endif