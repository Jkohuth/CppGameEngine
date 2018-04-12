// collisions.h

#ifndef COLLISION_H
#define COLLISION_H

#include <tuple>
#include "game_object.h"
#include "character_object.h"
#include "circle_object.h"
#include "global_enumerations.h"

#include <glm/glm.hpp>

// Defines a Collision typedef that represents collision data
typedef std::tuple<GLboolean, GlobalEnum::Direction, glm::vec2> Collider; // <Collision, what direction, difference vector center - closest point>

class Collision
{
public: 
	GlobalEnum::PlayerCondition DoPlayerTerrainCollisions(CharacterObject &one, GameObject &two);
	GLboolean CheckCircleCollision(CircleObject &one, GameObject &two);

private:
	Collider CheckCollision(CharacterObject &one, GameObject &two);
	GlobalEnum::Direction VectorDirection(glm::vec2 target);
	GLboolean CheckBoxCollision(GameObject &one, GameObject &two);


	void CheckDirection(glm::vec2 vector_Dir);

};

#endif