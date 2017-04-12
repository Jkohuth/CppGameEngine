//FirstGame.cpp

#include <stdlib.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "gl_macros.hpp"
#include "game.h"
#include "resource_manager.h"

//GLFW function declerations
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);

// The width of the screen
const GLuint SCREEN_WIDTH = 800;
// THe height of the screen
const GLuint SCREEN_HEIGHT = 600;

Game Jump(SCREEN_WIDTH, SCREEN_HEIGHT);


int main(int argc, char * argv[])
{
	// Init GLFW
	if( !glfwInit() ) exit(EXIT_FAILURE);
	std::cout << "glfw Initialization\n";

	//Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RPG", NULL, NULL);
	if(!window){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // <- Force interval

	// Initiate GLEW and check to make sure it started correctly
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
		if(glewError != GLEW_OK){
			printf("glew init error\n%s\n", glewGetErrorString(glewError) );
		}
		if(GLEW_APPLE_vertex_array_object){
			printf("genVertexArrayAPPle supported\n");
		} else if(GLEW_ARB_vertex_array_object){
			printf("genVertexArrays supported\n");
		}


	glfwSetKeyCallback(window, key_callback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize game
	Jump.Init();

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// Start Game within Menu State
	Jump.State = GAME_START;


	while( !glfwWindowShouldClose(window) ){

		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// Manage User Input
		Jump.ProcessInput(deltaTime);

		// Update Game State
		Jump.Update(deltaTime);

		// Render
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Jump.Render();

		glfwSwapBuffers(window);

	}

	ResourceManager::Clear();

	glfwTerminate();

	return 0;
}
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we change WindowShouldClose to true closing the application
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if(key >=0 && key <1024){
		if(action == GLFW_PRESS)
			Jump.Keys[key] = GL_TRUE;
		else if(action == GLFW_RELEASE)
			Jump.Keys[key] = GL_FALSE;
	}
	// if(glfwJoystickPresent(GLFW_JOYSTICK_1))
	// {
	// 	RPG.initGamepad();
	// }

}




























