//victory_object.cpp
#include "victory_object.h"
#include <iostream>
//Use a sin function to handle it moving back and fourth across the screen what you have is dumb

VictoryObject::VictoryObject() 
    : GameObject(), Radius(12.5f), isTouched(false)  { }

VictoryObject::VictoryObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite)
    :  GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), Radius(radius), isTouched(false) { }

glm::vec2 VictoryObject::Move(GLfloat dt, GLuint window_width)
{
    if(this->Position.x + (Radius * 2) >= window_width){
        this->Position.x = window_width - (Radius *2);
        this->Velocity.x = (this->Velocity.x * -1);
    }
    else if(this->Position.x <= 0){
        this->Position.x = 0;
        this->Velocity.x = (this->Velocity.x * -1);
    }

    this->Position.x += this->Velocity.x * dt;
    return this->Position;
}

// Resets the ball to initial Stuck Position (if ball is outside window bounds)
void VictoryObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
}