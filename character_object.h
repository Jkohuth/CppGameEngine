

#ifndef CHARACTEROBJECT_H
#define CHARACTEROBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "game_object.h"
//#include "power_up.h"
#include "global_enumerations.h"

// CharacterObject holds the state of the ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to character object that
// were too specific for GameObject alone.
class CharacterObject : public GameObject
{
public:
	// Character State
	glm::vec2 						PlayerSize;
	glm::vec2						velocity = glm::vec2(0,0);
	glm::vec2						initialPosition;
	GLfloat 						Scale;
	GLfloat							Speed;
	GLfloat							gravity = 0.05f;
	GLfloat							terminalVelocity = 5.0f;
	GLfloat							xSpeed = 2.5;
	GLboolean						isGrounded = false;
	GlobalEnum::PlayerCondition 	Condition = GlobalEnum::MIDAIR;
	GlobalEnum::PlayerInput			playerState;

	// Made the inherited class public to resolve the issue
//	using GameObject::Position;
//	using GameObject::Size;
//	using GameObject::Velocity;

	// Constructor (s)
	CharacterObject();
	CharacterObject(glm::vec2 pos, glm::vec2 playerSize, glm::vec2 velocity, Texture2D sprite);
	// Moves the ball, keeping it constrained within the winow bounds (except for the bottom edge); returns new posiiton
//	glm::vec2 MovePlayer(GLfloat dt, GlobalEnum::Direction direction);
	void MovePlayer(GlobalEnum::PlayerInput input);
	void EditPlayerState(GlobalEnum::PlayerCondition cond);
	//void xMotion(GLboolean left, GLboolean right);
//	void	  SetVelocity();
	// Resets the ball to original state with given position and velocity
	void	  Reset(glm::vec2 position);
	void	  Physics(GLfloat dt);
};

#endif