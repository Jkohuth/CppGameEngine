//game.h

#ifndef GAME_H
#define GAME_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <vector>
#include <memory>

#include <tmxlite/Map.hpp>
#include <array>


/*
	Expanding to include TMX Parsing
*/

#include "global_enumerations.h"
#include "game_object.h"
#include "input_handler.h"

// Initial size of the player
const glm::vec2 PLAYER_SIZE(50, 50);
const glm::vec2 PLAYER_VELOCITY(10.0f, 5.0f);
// Initial size of the menu
const glm::vec2 MENU_SIZE(800, 300);

const glm::vec2 VICTORYITEM_SIZE(25, 25);
const glm::vec2 VICTORYITEM_VELOCITY(750, 0);
const GLfloat VICTORYITEM_RADIUS(15);
// Initial velocity of the player 
//const GLfloat PLAYER_VELOCITY(500.0f);

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class
// for easy access to each of the components and manageability

class Game
{
public:
	// Game State
	GlobalEnum::GameState		State;
	InputHandler 				InputHandler;
	GLboolean					Keys[1024];
	GLboolean					KeysProcessed[1024];
	GLboolean 					canPress = true;
	GLuint						Width, Height;
	tmx::Map 					map;
//	glm::mat4 projectionMatrixLevel;
//	std::vector<std::unique_ptr<MapLayer>> mapLayers;
//	void LoadMap();
//	void initGLStuff(const tmx::Map&);
//	GLuint tmx_shader;


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

//	void ResetLevel();
//	void ResetPlayer();



};


#endif
























