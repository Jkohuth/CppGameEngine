// global_enumerations.h

#ifndef GLOBAL_ENUMERATIONS_H
#define GLOBAL_ENUMERATIONS_H

#include <glm/glm.hpp>
namespace GlobalEnum{
	
	// Represents the current state of the game
	enum GameState {
		GAME_START,
		GAME_OVERWORLD,
		GAME_OVER,
		GAME_WIN
	};

	// Represents the four possible directions
	enum Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE
	};
// Really need better names for these things
	enum ColliderCondition {
		GROUND,
		MIDAIR,
		CEILING,
		WALL,
		UNDER_WATER
	};
	struct PlayerInput {
		GlobalEnum::ColliderCondition condition;
		glm::vec2 					velocity;

	};
};


#endif 