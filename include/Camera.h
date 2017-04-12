
#pragma once

// Std. Includes
#include <vector>

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Defines several possible options for camera movement. 
// Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default Camera Vaules
const GLfloat YAW 			= -90.0f;
const GLfloat PITCH 		= 0.0f;
const GLfloat SPEED 		= 3.0f;
const GLfloat SENSITIVITY	= 0.25f;
const GLfloat ZOOM 			= 45.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors, and Matrices for use in OpenGL
class Camera
{
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera Options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		this->Position = glm::vec3(posX, posY, posZ);
		this->WorldUp = glm::vec3(upX,upY,upZ);
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}
	// Returns the view matrix calculated using the Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return this->calculate_lookAt_matrix(this->Position, this->Position + this->Front, this->Up);
		//return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
	}
	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
	{
		GLfloat velocity = this->MovementSpeed * deltaTime;
		if(direction == FORWARD)
			this->Position += this->Front * velocity;
		if(direction == BACKWARD)
			this->Position -= this->Front * velocity;
		if(direction == LEFT)
			this->Position -= this->Right * velocity;
		if(direction == RIGHT)
			this->Position += this->Right * velocity;
		//Make sure user stays at the ground level
		this->Position.y = 0.0f;
	}
	// Processes input received from a mouse input system. Expects the offset value in both the x and y difection.
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true)
	{
		xOffset *= this->MouseSensitivity;
		yOffset *= this->MouseSensitivity;

		this->Yaw 	+= xOffset;
		this->Pitch += yOffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if(constrainPitch){
			if(this->Pitch > 89.0f)
				this->Pitch = 89.0f;
			if(this->Pitch < -89.0f)
				this->Pitch = -89.0f;
		}

		//Update Front, Right and Up Vectors using the updated Eular Angles
		this->updateCameraVectors();
	}
	// Process input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(GLfloat yOffset){
		
		if(this->Zoom >= 1.0f && this->Zoom <= 45.0f)
			this->Zoom -= yOffset;
		if(this->Zoom <= 1.0f)
			this->Zoom = 1.0f;
		if(this->Zoom >=45.0f)
			this->Zoom = 45.0f;
	}

private:
	// Calulates the front vector from the Camera's (Updated) Eular Angles
	void updateCameraVectors()
	{
		// Calculates the new Front Vector
		glm::vec3 front;
		front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		front.y = sin(glm::radians(this->Pitch));
		front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(front);
		//Also re-calculate the right and Up vector
		this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp)); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->Up = glm::normalize(glm::cross(this->Right, this->Front));
	}
	//THe lookAt method
	glm::mat4 calculate_lookAt_matrix(glm::vec3 eye, glm::vec3 center, glm::vec3 Up){

		glm::vec3 zAxis = glm::normalize(eye - center);
		glm::vec3 xAxis = glm::normalize(glm::cross(glm::normalize(Up), zAxis));
		glm::vec3 yAxis = glm::cross(zAxis, -xAxis);

		glm::mat4 translation;
		translation[3][0] = -eye.x;
		translation[3][1] = -eye.y;
		translation[3][2] = -eye.z;

		glm::mat4 rotation;
		rotation[0][0] = xAxis.x;
		rotation[1][0] = xAxis.y;
		rotation[2][0] = xAxis.z;
		rotation[0][1] = yAxis.x;
		rotation[1][1] = yAxis.y;
		rotation[2][1] = yAxis.z;
		rotation[0][2] = zAxis.x;
		rotation[1][2] = zAxis.y;
		rotation[2][2] = zAxis.z;

		return rotation * translation;



/*
		glm::mat4 look;
		glm::mat4 at;
		GLfloat lookArr[16] = {
			eye.x, 		eye.y, 		eye.z, 		0, //First Column
			center.x, 	center.y, 	center.z, 	0,//Second Column
			Up.x, 		Up.y, 		Up.z, 		0, //Third Column
			0, 			0, 			0, 			1 //Last column 
		};
		GLfloat atArr[16] = {
			1, 0, 0, 1,
			0, 1, 0, 1,
			0, 0, 1, 1,
			0, 0, 0, 1

		};

		memcpy( glm::value_ptr(look), lookArr, sizeof(lookArr));
		memcpy(glm::value_ptr(at), atArr, sizeof(atArr));

		return look;
		*/

	}



};
























