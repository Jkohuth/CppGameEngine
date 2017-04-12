//game.cpp
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "text_renderer.h"
#include "character_object.h"

#include <iostream>


// Game-related State Data
SpriteRenderer 	*Renderer;
TextRenderer	*Text;
CharacterObject	*Player;
GameObject		*Menu;
GameObject		*VictoryItem;


Game::Game(GLuint width, GLuint height)
		: State(GAME_OVERWORLD), Keys(), Width(width), Height(height)
{

}




Game::~Game()
{
	delete Renderer;
	delete Player;
	delete Menu;
}



void Game::Init()
{


	// Load Shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	ResourceManager::LoadShader("shaders/text.vs", "shaders/text.frag", nullptr, "text");

	// Configure Shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	glm::mat4 textProjection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), 0.0f, static_cast<GLfloat>(this->Height));

	ResourceManager::GetShader("text").Use().SetInteger("text", 0);
	ResourceManager::GetShader("text").SetMatrix4("projection", textProjection);

	// Load Textures
	ResourceManager::LoadTexture("assets/textures/map/greyBrickGround.png", GL_TRUE, "ground");
	ResourceManager::LoadTexture("assets/sprites/characters/block.png", GL_TRUE, "block");
	ResourceManager::LoadTexture("assets/textures/menu/menu.png", GL_TRUE, "menu");
	ResourceManager::LoadTexture("assets/textures/items/victoryItem.png", GL_TRUE, "victory");

	// Set render-specific controls
	Renderer = new SpriteRenderer((ResourceManager::GetShader("sprite")));
	Text = new TextRenderer((ResourceManager::GetShader("text")), "assets/fonts/retro.ttf");

//	glm::vec2 playerPos = glm::vec2(this->Width/2 - PLAYER_SIZE.x/2, this->Height - PLAYER_SIZE.y);
	glm::vec2 playerPos = glm::vec2(this->Width/2 - PLAYER_SIZE.x/2, this->Height/2 - PLAYER_SIZE.y/2);
	glm::vec2 itemPos = glm::vec2(this->Width/4, this->Height/4);
	glm::vec2 bottomMenu = glm::vec2(0.0f, (this->Height)/2);
	Player = new CharacterObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("block"));
	VictoryItem = new GameObject(itemPos, VICTORYITEM_SIZE, ResourceManager::GetTexture("victory"));
//	Menu = new GameObject(bottomMenu, MENU_SIZE, ResourceManager::GetTexture("menu"));


}


void Game::Update(GLfloat dt)
{
	if(Player->Position.y > this->Height)
	{
		this->State = GAME_OVER;
	}

}

void Game::ProcessInput(GLfloat dt)
{
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
		if(1 == present){
			int axesCount;
			const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
//			std::cout<< "Number of axes available: " << axesCount << std::endl;
//			std::cout << std::endl;
//			std::cout << std::endl;
//			std::cout << std::endl;
//			std::cout << std::endl;
//			std::cout << std::endl;

//			std::cout<< "Dpad X Axis: " << axes[3] << std::endl;
//			std::cout<< "Dpad Y Axis: " << axes[4] << std::endl;

			int buttonCount;
			const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

			if(GLFW_PRESS == buttons[0])
			{
				std::cout << "X button pressed" <<std::endl;
			}			
			if(GLFW_PRESS == buttons[1])
			{
				std::cout << "A button pressed" <<std::endl;
			}			
			if(GLFW_PRESS == buttons[2])
			{
				std::cout << "B button pressed" <<std::endl;
			}
			if(GLFW_PRESS == buttons[3])
			{
				std::cout << "Y button pressed" <<std::endl;
			}
			if(GLFW_PRESS == buttons[4])
			{
				std::cout << "L trigger button pressed" <<std::endl;
			}
			if(GLFW_PRESS == buttons[5])
			{
				std::cout << "R trigger button pressed" <<std::endl;
			}
/*			if(GLFW_PRESS == buttons[6])
			{
				std::cout << "Array button 6 button pressed" <<std::endl;
			}
			if(GLFW_PRESS == buttons[7])
			{
				std::cout << "array button 7 button pressed" <<std::endl;
			}
*/
			if(GLFW_PRESS == buttons[8])
			{
				std::cout << "Select button pressed" <<std::endl;
			}
			if(GLFW_PRESS == buttons[9])
			{
				std::cout << "Start button pressed" <<std::endl;
			}
//			if(GLFW_RELEASE == buttons[3])
//			{
//				std::cout << "X button released" <<std::endl;
//			}


//			const char *name = glfwGetJoystickName( GLFW_JOYSTICK_1);
//			std::cout<< "The name of the gamepad is "<< name << std::endl;

		}

	if(this->State == GAME_START)
	{
//		if(GLFW_PRESS == buttons[9] || this->Keys[GLFW_KEY_ENTER]){
//			this->State = GAME_OVERWORLD;
//		}

		if(this->Keys[GLFW_KEY_ENTER]){
			this->State = GAME_OVERWORLD;
		}
	}
	if (this->State == GAME_OVERWORLD)
	{

/*
		if(axes[3] == -1){
			Player->Move(dt, LEFT);
		}
		if(axes[3] == 1){
			Player->Move(dt, RIGHT);
		}
		if(axes[4] == 1){
			Player->Move(dt, DOWN);
		}
		if(axes[4] == -1){
			Player->Move(dt, UP);
		}
*/


//		GLfloat velocity = PLAYER_VELOCITY * dt;
		// Move playerboard
		if(this->Keys[GLFW_KEY_A])
		{
			Player->Move(dt, LEFT);
//			if(Player->Position.x >= 0)
//				Player->Position.x -= 25;
		}
		if(this->Keys[GLFW_KEY_D])
		{
			Player->Move(dt, RIGHT);

//			if(Player->Position.x <= this->Width - Player->Size.x)
//				Player->Position.x += 25;
		}
		if(this->Keys[GLFW_KEY_S])
		{
			Player->Move(dt, DOWN);

		//	if(Player->Position.y <= this->Height - Player->Size.y)
		//		Player->Position.y += 25;
		}
		if(this->Keys[GLFW_KEY_W])
		{
			Player->Move(dt, UP);
//			if(Player->Position.y >= 0)
//				Player->Position.y -= 25;
		}
//		if(this->Keys[]){
//			std::cout<< this->Keys<<std::endl;
//		}
	}
	if(this->State == GAME_OVER)
	{
		if(this->Keys[GLFW_KEY_ENTER])
		{
			this->State = GAME_START;
		}
	}


}

void Game::Render()
{
	if(this->State == GAME_START)
	{
		Text->RenderText(ResourceManager::GetShader("text").Use(), "First Game", 325.0f, 500.0f, 0.5f, glm::vec3(2.0f, 1.0f, 1.0f));
		Text->RenderText(ResourceManager::GetShader("text").Use(), "JUMP", 295.0f, 435.0f, 2.0f, glm::vec3(2.0f, 1.0f, 1.0f));
		Text->RenderText(ResourceManager::GetShader("text").Use(), "PRESS START", 300.0f, 100.0f, 0.75f, glm::vec3(2.0f, 1.0f, 1.0f));

	}
	if(this->State == GAME_OVERWORLD){
		Renderer->DrawSprite(ResourceManager::GetTexture("ground"), glm::vec2(100.0f, (this->Height - 75.0f)), glm::vec2((this->Width)*0.75f, (this->Height)*0.25f), 0.0f);
		Player->Draw(*Renderer);
		VictoryItem->Draw(*Renderer);
//		Menu->Draw(*Renderer);
//		Text->RenderText(ResourceManager::GetShader("text").Use(), "When you know what to do", 52.0f, 25.0f, 1.5f, glm::vec3(2.0, 1.8f, 1.0f));
	}
	if(this->State == GAME_OVER)
	{
		Text->RenderText(ResourceManager::GetShader("text").Use(), "GAME OVER", 250.0f, 435.0f, 2.0f, glm::vec3(2.0f, 1.0f, 1.0f));

	}
	if(this->State == GAME_WIN)
	{
		Text->RenderText(ResourceManager::GetShader("text").Use(), "YOU WIN!", 295.0f, 435.0f, 2.0f, glm::vec3(2.0f, 1.0f, 1.0f));

	}
}

void Game::DoCollisions(){}














