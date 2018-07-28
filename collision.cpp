//collision.cpp

#include "collision.h"

#include <iostream>

using namespace GlobalEnum;

GlobalEnum::PlayerCondition Collision::DoPlayerTerrainCollisions(CharacterObject &one, GameObject &two){

	Collider collider = CheckCollision(one, two);
	GlobalEnum::PlayerCondition condition;
// Back to this savagery
	if(std::get<0>(collider) == true){
		Direction dir = std::get<1>(collider);
		glm::vec2 overlap = std::get<2>(collider);
	
		switch(dir){
			case NONE:
				break;
			case UP: 
				if(one.playerState.velocity.y > 0){
					one.playerState.velocity.y = 0; 
					one.Position.y += overlap.y;
				}
				condition = GlobalEnum::GROUND;
				break;
			case DOWN:
				one.playerState.velocity.y = 0;
				one.Position.y -= overlap.y;
				
				condition = GlobalEnum::GROUND;

				break;
			case LEFT:
				one.Position.x += overlap.x;
				condition = GlobalEnum::GROUND;
				break;
			case RIGHT:
				one.Position.x -= overlap.x;
				condition = GlobalEnum::GROUND;
				break;
		}
	}
	else if(std::get<0>(collider)==false)
	{
		condition = GlobalEnum::MIDAIR;
	//	grounded = false;
	}//else if(std::get<0>(collider)==false && condition != GlobalEnum::GROUND)
	//{
	//	condition = GlobalEnum::MIDAIR;
	//	grounded = false;
	//}
	return condition;

}

Collider Collision::CheckCollision(CharacterObject &one, GameObject &two){
	// Get center point of Player
	glm::vec2 character_aabb_half_extents(one.Size.x/2, one.Size.y/2);
	glm::vec2 character_aabb_center(one.Position.x + character_aabb_half_extents.x, one.Position.y + character_aabb_half_extents.y);

	glm::vec2 object_aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 object_aabb_center(two.Position.x + object_aabb_half_extents.x, two.Position.y + object_aabb_half_extents.y);

	glm::vec2 differenceBetweenCenters =  character_aabb_center - object_aabb_center;
	glm::vec2 minSeperation = character_aabb_half_extents + object_aabb_half_extents;

	glm::vec2 object_clamped = glm::clamp(differenceBetweenCenters, -object_aabb_half_extents, object_aabb_half_extents);
	
	// This gets me the correct Vector direction
	glm::vec2 whichSideCollided = character_aabb_center - (object_clamped + object_aabb_center);

	glm::vec2 overlap = glm::vec2(0,0);
	Direction dir = VectorDirection(whichSideCollided);
	switch(dir){
		case NONE:
			break;
		case UP:
			overlap.y = (fabs(differenceBetweenCenters.y) - fabs(minSeperation.y));
			break;
		case DOWN:
			overlap.y = (fabs(differenceBetweenCenters.y) - fabs(minSeperation.y));
			break;
		case LEFT:
			overlap.x = (fabs(differenceBetweenCenters.x) - fabs(minSeperation.x));
			break;
		case RIGHT:
			overlap.x = (fabs(differenceBetweenCenters.x) - fabs(minSeperation.x));
			break;
	}
	if(CheckBoxCollision(one, two)){
		return std::make_tuple(GL_TRUE, VectorDirection(whichSideCollided), overlap);
	}
	else
		return std::make_tuple(GL_FALSE, NONE, glm::vec2(0, 0));
}

GLboolean Collision::CheckBoxCollision(GameObject &one, GameObject &two){
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x && two.Position.x + two.Size.x >= one.Position.x;
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y && two.Position.y + two.Size.y >= one.Position.y;
	return collisionX && collisionY;
}

GLboolean Collision::CheckCircleCollision(CircleObject &one, GameObject &two){
	// Get center point circle first
	glm::vec2 center(one.Position + one.Radius);

	// Calculate AABB info (Center, half extents)
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);

	// Get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

	// Add clamped value to AABB_Center and we get the value of box closet to circle
	glm::vec2 closet = aabb_center + clamped;

	// Retrieve vector between cener circle and closet point AABB and check if length <= radius
	difference = closet - center;

	return glm::length(difference) < one.Radius;
}

void Collision::CheckDirection(glm::vec2 vector_Dir){
	Direction dir = VectorDirection(vector_Dir);
	switch(dir){
		case NONE:
			std::cout<<"NONE\n";
			break;
		case UP: 
			std::cout<<"UP\n";
			break;
		case DOWN:
			std::cout<<"DOWN\n";
			break;
		case LEFT:
			std::cout<<"LEFT\n";
			break;
		case RIGHT:
			std::cout<<"RIGHT\n";
		break;
	}
	std::cout<<"\n";
}

GlobalEnum::Direction Collision::VectorDirection(glm::vec2 target){

	glm::vec2 compass[] = {
		glm::vec2(0.0f, -1.0f),	// UP
		glm::vec2(1.0f,  0.0f),	// RIGHT
		glm::vec2(0.0f,  1.0f),	// DOWN
		glm::vec2(-1.0f, 0.0f)	// LEFT
	};

	GLfloat max = 0.0f;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; i++){

		GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
		if(dot_product > max){

			max = dot_product;
			best_match = i;
		}
		
	}
	return (Direction)best_match;

}