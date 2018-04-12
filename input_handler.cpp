//input_handler.cpp

#include "input_handler.h"

#include <iostream>
#include <math.h>

InputHandler::InputHandler()
	: Keys()
{
	gravity = (2*jumpHeight) /(pow(timeToJumpApex, 2.0f));
	initVelocity = gravity * timeToJumpApex;

	std::cout<<"Gravity "<<gravity<<std::endl;
	std::cout<<"init Velocity "<<initVelocity<<std::endl;
}

InputHandler::~InputHandler()
{

}

void InputHandler::CheckIn(){
	if(this->Keys[GLFW_KEY_ENTER]){
		std::cout<<"Hello World How are you today"<<std::endl;
	}	
}
GlobalEnum::GameState InputHandler::GameStart(){
		if(this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER]){
			this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
			return GlobalEnum::GAME_OVERWORLD;
		}
	return GlobalEnum::GAME_START;
}
GlobalEnum::PlayerInput InputHandler::SingleControls(GlobalEnum::PlayerInput current){
//		glm::vec2 playerVelocity = currentVelocity;
		// Move playerboard
		GlobalEnum::PlayerInput	returnValue = current;
		if(this->Keys[GLFW_KEY_A])
		{	
			returnValue.velocity.x = -10.0f;
//			playerVelocity.x = -10.0f;

		}
		if(this->Keys[GLFW_KEY_D])
		{
			returnValue.velocity.x = 10.0f;
//			playerVelocity.x = 10.0f;
		}
		if(!this->Keys[GLFW_KEY_D] && !this->Keys[GLFW_KEY_A]){
			returnValue.velocity.x = 0.0f;

	//		playerVelocity.x = 0.0f;

		}
		switch(returnValue.condition){
			case GlobalEnum::GROUND:
				if(this->Keys[GLFW_KEY_SPACE] && !this->KeysProcessed[GLFW_KEY_SPACE]){
					this->KeysProcessed[GLFW_KEY_SPACE] = GL_TRUE;
					returnValue.velocity.y = -initVelocity;
				}
				break;
			case GlobalEnum::MIDAIR:
				if(returnValue.velocity.y < this->terminalVelocity)
					returnValue.velocity.y += this->gravity;
				break;
			case GlobalEnum::UNDER_WATER:
				break;
		}

		return returnValue;

}
GlobalEnum::GameState InputHandler::GameOver(){
	if(this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER]){
		this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
		return GlobalEnum::GAME_START;
	}
	return GlobalEnum::GAME_OVER;
}
GlobalEnum::GameState InputHandler::Win(){
	if(this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER]){
		this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
		return GlobalEnum::GAME_START;
	}
	return GlobalEnum::GAME_WIN;
}
