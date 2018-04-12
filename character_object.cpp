

#include "character_object.h"
#include <iostream>

CharacterObject::CharacterObject()
	: GameObject(), PlayerSize(), Scale(1), Speed(1) { }

CharacterObject::CharacterObject(glm::vec2 pos, glm::vec2 playerSize, glm::vec2 velocity, Texture2D sprite)
	: GameObject(pos, glm::vec2(playerSize.x * 1.0f, playerSize.y * 1.0f), sprite, glm::vec3(1.0f), velocity), Scale(1)
{
	playerState.condition = Condition;

}
void CharacterObject::EditPlayerState(GlobalEnum::PlayerCondition cond)
{
//	std::cout<<"Here is everything\n";
	playerState.condition = cond;
}
/*
glm::vec2 CharacterObject::MovePlayer(GLfloat dt, GlobalEnum::Direction direction)
{

//	this->Position += this->Velocity * dt;
	switch(direction){
		case GlobalEnum::LEFT:
			this->velocity.x = -xSpeed; 
			break;
		case GlobalEnum::RIGHT:
			this->velocity.x = xSpeed;
			break;
		case GlobalEnum::UP:
//			this->Position.y -= velocity.y;
			break;
		case GlobalEnum::DOWN:
//			this->Position.y += velocity.y;
			break;
	}
//	return this->Position;
}
//void CharacterObject::SetVelocity(){
//	this->velocity = glm::vec2(0.0f,0.0f);
//}
//void CharacterObject::Grounded(bool isGrounded){

//}
*/
/*void CharacterObject::xMotion(GLboolean left, GLboolean right){
	if(left){
		this->velocity.x = -xSpeed;
		return; 
	}else if (right) {
		this->velocity.x = xSpeed;
		return;
	}else {
		this->velocity.x = 0;
	}
}*/
// Resets the ball to initial Stuck Position (if ball is outside winow bounds)
void CharacterObject::Reset(glm::vec2 position)
{
	this->Position = position;
//	this->Velocity = velocity;
}
void CharacterObject::MovePlayer(GlobalEnum::PlayerInput input)
{
	playerState.condition = input.condition;
	playerState.velocity = input.velocity;
}
void CharacterObject::Physics(GLfloat dt){

	switch(playerState.condition){
		case GlobalEnum::GROUND:
		
			std::cout<<"GROUND\n";
			break;
		case GlobalEnum::MIDAIR:
			std::cout<<"MIDAIR\n";

//			if(this->velocity.y < this->terminalVelocity)
//				this->velocity.y += this->gravity;
			break;
		case GlobalEnum::UNDER_WATER:
			std::cout<<"UNDER_WATER\n";

			break;

	}
//	if(!isGrounded){
//		if(this->velocity.y < this->terminalVelocity){
//			this->velocity.y += this->gravity;
//		}else{
//			this->velocity.y = this->terminalVelocity;
//		}
//	}else{
//
//	}
//	std::cout<<"Tht velocity : "<<velocity.x<<"\t"<<velocity.y<<"\n";
//	std::cout<<<<" The velocity yo"<<std::endl;
	this->Position += this->playerState.velocity;
}








