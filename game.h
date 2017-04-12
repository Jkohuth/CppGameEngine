//game.h

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <tuple>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


#include <ft2build.h>
#include FT_FREETYPE_H 


#include "game_object.h"

/*
#include "game_level.h"
#include "power_up.h"
*/

// Represents the current state of the game
enum GameState {
	GAME_START,
	GAME_OVERWORLD,
	GAME_OVER,
	GAME_WIN
};
/*
// Represents the four possible directions
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};*/

// Defines a Collision typedef that represents collision data
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision; // <Collision, what direction, difference vector center - closest point>

// Initial size of the player
const glm::vec2 PLAYER_SIZE(50, 50);
// Initial size of the menu
const glm::vec2 MENU_SIZE(800, 300);

const glm::vec2 VICTORYITEM_SIZE(25, 25);
// Initial velocity of the player 
const GLfloat PLAYER_VELOCITY(500.0f);

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class
// for easy access to each of the components and manageability
class Game
{
public:
	// Game State
	GameState		State;
	GLboolean		Keys[1024];
	GLuint			Width, Height;
//	std::vector<GameLevel> Levels;
//	GLuint			Level;
//	std::vector<PowerUp>	PowerUps;
	Game(GLuint width, GLuint height);
	~Game();
	// Initalize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void DoCollisions();

//	void ResetLevel();
//	void ResetPlayer();



};


#endif
























