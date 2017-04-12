

#include "character_object.h"

CharacterObject::CharacterObject()
	: GameObject(), PlayerSize(), Scale(1), Speed(1) { }

CharacterObject::CharacterObject(glm::vec2 pos, glm::vec2 playerSize, Texture2D sprite)
	: GameObject(pos, glm::vec2(playerSize.x * 1.0f, playerSize.y * 1.0f), sprite, glm::vec3(1.0f), glm::vec2(0.0f,0.0f)), Scale(1) { }

glm::vec2 CharacterObject::Move(GLfloat dt, Direction direction)
{
	glm::vec2 currentPos = this->Position;
	glm::vec2 stride = glm::vec2(100.0f, 100.9f);
	switch(direction){
		case LEFT: 
			this->Position.x -= (dt * stride.x);
		//	this->Position.x +=25;
			break;
		case RIGHT:
			this->Position.x += (dt * stride.x);

			//this->Position.x -=25;
			break;
		case UP:
			this->Position.y -= (dt * stride.y);

//			this->Position.y -=25;
			break;
		case DOWN:
			this->Position.y += (dt * stride.y);

			//this->Position.y +=25;
			break;
}
//		if(this->Keys[GLFW_KEY_RIGHT])
	//	{
	//		if(Player->Position.x <= this->Width - Player->Size.x)
	//			Player->Position.x += 25;
	//	}
	//	if(this->Keys[GLFW_KEY_DOWN])
///		{
//			if(Player->Position.y <= this->Height - Player->Size.y)
//				Player->Position.y += 25;
//		}
//		if(this->Keys[GLFW_KEY_UP])
//		{
//			if(Player->Position.y >= 0)
//				Player->Position.y -= 25;
//		}



	// If not stuck to player board
/*	
	if(!this->Stuck)
	{
		// Move the ball
		this->Position += this->Velocity * dt;
		// Then check if outside window bounds and if so, reverse velocity and restore at correct position
		if (this->Position.x <= 0.0f)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = 0.0f;
		}
		else if(this->Position.x + this->Size.x >= window_width)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = window_width - this->Size.x;
		}
		if(this->Position.y <= 0.0f)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = 0.0f;
		}
	}
*/
	return this->Position;
}


// Resets the ball to initial Stuck Position (if ball is outside winow bounds)
void CharacterObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
}









