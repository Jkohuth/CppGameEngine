//game.cpp
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "text_renderer.h"
#include "character_object.h"
#include "circle_object.h"
//#include "post_processor.h"
#include "collision.h"
//#include "map_renderer.h"

// Map stuff
#include <glm/gtc/matrix_transform.hpp>

//#include <tmxlite/Map.hpp>
//#include <cassert>
//#include <array>

#include <iostream>

using namespace GlobalEnum;

// Game-related State Data
SpriteRenderer 			*Renderer;
TextRenderer			*Text;
CharacterObject			*Player;
GameObject				*Menu;
GameObject 				*Ground;
GameObject 				*Obstacle;
CircleObject			*VictoryItem;
//PostProcessor 			*Effects;
Collision 				*Collision;
GLfloat					ShakeTime = 0.0f;
std::vector<GameObject>	Terrain;	
//MapRenderer 			*RenderMap;


//Fix GAME_OVERWORLD constructor
Game::Game(GLuint width, GLuint height)
		: State(GAME_OVERWORLD), Keys(), Width(width), Height(height)
{

}




Game::~Game()
{
	delete Renderer;
	delete Player;
	delete Menu;
//	delete Effects;
	delete Collision;
}



void Game::Init()
{


	// Load Shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	//ResourceManager::LoadShader("shaders/texture.vs", "shaders/texture.fs", nullptr, "texture");
	//ResourceManager::LoadShader("shaders/text.vs", "shaders/text.frag", nullptr, "text");
	//ResourceManager::LoadShader("shaders/post_processor.vs", "shaders/post_processor.frag", nullptr, "postprocessing");


	// Configure Shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);


	// Load Textures
	ResourceManager::LoadTexture("assets/textures/map/greyBrickGround.png", GL_TRUE, "ground");
	ResourceManager::LoadTexture("assets/sprites/characters/block.png", GL_TRUE, "block");
	ResourceManager::LoadTexture("assets/textures/menu/menu.png", GL_TRUE, "menu");
	ResourceManager::LoadTexture("assets/textures/items/victoryItem.png", GL_TRUE, "victory");

	// Set render-specific controls
	Renderer = new SpriteRenderer((ResourceManager::GetShader("sprite")));
	//Text = new TextRenderer((ResourceManager::GetShader("text")), "assets/fonts/retro.ttf");
	//Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);

	glm::vec2 playerPos = glm::vec2(this->Width/2 - PLAYER_SIZE.x/2, this->Height/2 - PLAYER_SIZE.y/2);
	glm::vec2 itemPos = glm::vec2(this->Width/2 - VICTORYITEM_RADIUS, this->Height/4);
	Player = new CharacterObject(playerPos, PLAYER_SIZE, PLAYER_VELOCITY, ResourceManager::GetTexture("block"));
	VictoryItem = new CircleObject(itemPos, VICTORYITEM_RADIUS, VICTORYITEM_VELOCITY, ResourceManager::GetTexture("victory"));
	Ground = new GameObject(glm::vec2(100.0f, (this->Height - 75.0f)), glm::vec2((this->Width)*0.75f, (this->Height)*0.25f), ResourceManager::GetTexture("ground"));
	Obstacle = new GameObject(glm::vec2(300.0f, 300.0f),PLAYER_SIZE, ResourceManager::GetTexture("block"));
/*	
	ResourceManager::LoadShader("shaders/tmx.vs", "shaders/tmx.frag", nullptr, "tmx");
	
	glm::mat4 mapprojection = glm::ortho(0.f, 800.f, 600.f, 0.f, -0.1f, 100.f);
	ResourceManager::GetShader("tmx").Use().SetMatrix4("projection", mapprojection);
	ResourceManager::GetShader("tmx").Use().SetInteger("tileMap", 0);
	ResourceManager::GetShader("tmx").Use().SetInteger("lookupMap", 1);
//	ResourceManager::LoadMap("assets/maps/test.tmx", "test");
*/
	//RenderMap = new MapRenderer(ResourceManager::GetMap(), ResourceManager::GetShader("tmx"));
	Terrain.push_back(*Ground);
	Terrain.push_back(*Obstacle);

	//this->LoadMap();
  Text = new TextRenderer(this->Width, this->Height);
  Text->Load("assets/fonts/retro.ttf", 24);
}


void Game::Update(GLfloat dt)
{
	if(this->State == GAME_OVERWORLD){

		Player->Physics(dt);
		for(std::vector<GameObject>::iterator it = Terrain.begin(); it != Terrain.end(); it++){

			GlobalEnum::ColliderCondition cond = Collision->DoPlayerTerrainCollisions(*Player, *it);
			if(cond == GlobalEnum::GROUND){
				Player->EditPlayerState(cond);
				break;
			}
			Player->EditPlayerState(cond);
			//Player->EditPlayerState(Collision->DoPlayerTerrainCollisions(*Player, *it));
					
		}
		if(Collision->CheckCircleCollision(*VictoryItem, *Player))
			this->State = GAME_WIN;

		if(Player->Position.y > this->Height){
			this->State = GAME_OVER;
		}
		VictoryItem->Move(dt, this->Width);
		if(ShakeTime > 0.0f){
			ShakeTime -=dt;
			if(ShakeTime <= 0.0f){}
//				Effects->Shake = false;
		}
	}
	//if(Player->Position.y + Player->Size.y >= Height) 
	//	Player->Position.y = Height - Player->Size.y;
	//}
	if(this->State == GAME_START){
		Player->Reset(glm::vec2(this->Width/2 - PLAYER_SIZE.x/2, this->Height/2 - PLAYER_SIZE.y/2));
	}
}

void Game::ProcessInput(GLfloat dt)
{
	if(this->State == GAME_START)
	{
		this->State = this->InputHandler.GameStart();
	}
	if (this->State == GAME_OVERWORLD)
	{
		Player->MovePlayer(this->InputHandler.SingleControls(Player->playerState));
	//	Player->velocity = this->InputHandler.GameOverWorld(Player->velocity);
	}
	if(this->State == GAME_OVER)
	{
		this->State = this->InputHandler.GameOver();	
	}
	if(this->State == GAME_WIN){
		this->State = this->InputHandler.Win();
	}

}

void Game::Render()
{
//	RenderMap->DrawMap();
	if(this->State == GAME_START)
	{
		Text->RenderText("First Game", 325.0f, 500.0f, 0.5f, glm::vec3(2.0f, 1.0f, 1.0f));
		Text->RenderText("JUMP", 295.0f, 700.0f, 1.0f, glm::vec3(2.0f, 1.0f, 1.0f));
		Text->RenderText("PRESS START", 300.0f, 100.0f, 2.f, glm::vec3(2.0f, 1.0f, 1.0f));
		
	}
	else if(this->State == GAME_OVERWORLD){

	//	Effects->BeginRender();	
			Ground->Draw(*Renderer);
			Player->Draw(*Renderer);
			VictoryItem->Draw(*Renderer);
			Obstacle->Draw(*Renderer);
	//	Menu->Draw(*Renderer);
	//	Effects->EndRender();
	//	Effects->Render(glfwGetTime());
	}
	else if(this->State == GAME_OVER)
	{
		Text->RenderText("GAME OVER", 250.0f, 435.0f, 2.0f, glm::vec3(2.0f, 1.0f, 1.0f));

	}
	else if(this->State == GAME_WIN)
	{
		Text->RenderText("YOU WIN!", 295.0f, 435.0f, 2.0f, glm::vec3(2.0f, 1.0f, 1.0f));

	}
}


/*
void Game::LoadMap()
{

	map.load("assets/maps/test.tmx");

	ResourceManager::LoadShader("shaders/tmx.vs", "shaders/tmx.frag", nullptr, "tmx");
	
	glm::mat4 projectionMap = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);

	RenderMap = new MapRenderer(map, ResourceManager::GetShader("tmx"), projectionMap, this->Width, this->Height);
//	ResourceManager::GetShader("tmx").Use().SetInteger("tileMap", 0);
//	ResourceManager::GetShader("tmx").SetMatrix4("projectionMatrix", projectionMap);
	

}*/








