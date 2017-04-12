//RPG.cpp

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

Game RPG(SCREEN_WIDTH, SCREEN_HEIGHT);


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
	RPG.Init();

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// Start Game within Menu State
	RPG.State = GAME_OVERWORLD;

	while( !glfwWindowShouldClose(window) ){

		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

/*
		int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
		if(1 == present){
			int axesCount;
			const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
//			std::cout<< "Number of axes available: " << axesCount << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;

	//		std::cout<< "Dpad X Axis: " << axes[0] << std::endl;
	//		std::cout<< "Dpad y Axis: " << axes[1] << std::endl;
	//		std::cout<< "Unknown Axis: " << axes[2] << std::endl;
		

		//	std::cout<< "Dpad X Axis: " << axes[3] << std::endl;
		//	std::cout<< "Dpad Y Axis: " << axes[4] << std::endl;

			int buttonCount;
			const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

			if(GLFW_PRESS == buttons[2])
			{
				std::cout << "A button pressed" <<std::endl;
			}
			if(GLFW_RELEASE == buttons[2])
			{
				std::cout << "A button released" <<std::endl;
			}

			if(GLFW_PRESS == buttons[3])
			{
				std::cout << "X button pressed" <<std::endl;
			}
			if(GLFW_RELEASE == buttons[3])
			{
				std::cout << "X button released" <<std::endl;
			}


			const char *name = glfwGetJoystickName( GLFW_JOYSTICK_1);
			std::cout<< "The name of the gamepad is "<< name << std::endl;

		}

*/

		// deltaTime = 0.001f;
		// Manage User Input
		RPG.ProcessInput(deltaTime);

		// Update Game State
		RPG.Update(deltaTime);

		// Render 
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		RPG.Render();

		glfwSwapBuffers(window);


	}

	// Delete all resources as loaded using the resource manager
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
			RPG.Keys[key] = GL_TRUE;
		else if(action == GLFW_RELEASE)
			RPG.Keys[key] = GL_FALSE;
	}
	// if(glfwJoystickPresent(GLFW_JOYSTICK_1))
	// {
	// 	RPG.initGamepad();
	// }

}


