//input_handler.h

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "global_enumerations.h"

class InputHandler
{
public:
	GLboolean Keys[1024];
	GLboolean KeysProcessed[1024];
	GlobalEnum::GameState State;

	GLfloat jumpHeight = 5.0f;
	GLfloat timeToJumpApex = 2.0f;
	GLfloat terminalVelocity = 1.0f;
	GLfloat initVelocity;
	GLfloat gravity;
	InputHandler();
	~InputHandler();
	void CheckIn();
	GlobalEnum::GameState GameStart();
	GlobalEnum::GameState  GameOver();
//	glm::vec2 GameOverWorld(GlobalEnum::PlayerInput current);
	GlobalEnum::PlayerInput SingleControls(GlobalEnum::PlayerInput current);
	GlobalEnum::GameState Win();
};

#endif