/*
 * =====================================================================================
 *
 *       Filename:  glfw_window.h
 *
 *    Description:  a window wrapper around glfwWindow
 *       Compiler:  gcc
 *
 *
 *         This is merely practice
 *
 * =====================================================================================
 */

#ifndef PRACTICE_WINDOW_H_INCLUDED
#define PRACTICE_WINDOW_H_INCLUDED

#include "gl_lib.hpp"
#include <iostream>

using namespace std;

namespace practice{

/*-----------------------------------------
 *	Some Callbacks to be implemented later
 *-----------------------------------------*/

struct Interface{

	static void * app; // <-- an unknown application to be defined later

	template<class APPLICATION>
	static void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods){
		((APPLICATION*)(app))->onKeyDown(key,action);
	}

	template<class APPLICATION>
	static void OnMouseMove(GLFWwindow* window, double x, double y){
		((APPLICATION*)(app))->onMouseMove(x,y);
	}

	template<class APPLICATION>
	static void OnMouseDown(GLFWwindow* window, int button, int action, int mods){
		((APPLICATION*)(app))->onMouseDown(button,action);
	}
};

void * Interface::app;


/*-----------------------------------------
 *	A GLFW Window Wrapper
 *-----------------------------------------*/
struct Window{
	GLFWwindow * window;
	Interface interface;

	int mWidth, mHeight;

	int width() { return mWidth; }
	int height() { return mHeight; }
	float ratio() { return (float)mWidth/mHeight;}

	Window() {}

	//Create a window context
	template<class APPLICATION>
	void create(APPLICATION * app, int w, int h, const char * name = "Pong"){

		interface.app = app;

		mWidth = w; mHeight = h;

		window = glfwCreateWindow(w,h,name,NULL,NULL);

		if(!window){
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); //<-- force interval

		//register callbacks for keyboard and mouse
		glfwSetKeyCallback(window, Interface::OnKeyDown<APPLICATION>);

		glfwSetCursorPosCallback(window, Interface::OnMouseMove<APPLICATION>);
		
		glfwSetMouseButtonCallback(window, Interface::OnMouseDown<APPLICATION>);

	}

	//Get the Current framebuffer Size in pixels and Set the viewport to it
	void setViewport(){
		glfwGetFramebufferSize(window, &mWidth, &mHeight);
		glViewport(0,0,mWidth,mHeight);
	}

	//Check whether the window should close
	bool shouldClose(){
		return glfwWindowShouldClose(window);
	}

	//Swap front and back buffers
	void swapBuffers(){
		glfwSwapBuffers(window);
	}

	//Destroy the window
	void destroy(){
		glfwDestroyWindow(window);
	}

	~Window(){
		destroy();
	}



};

}

#endif

