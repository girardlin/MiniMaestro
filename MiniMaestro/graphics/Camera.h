#pragma once 

#include <iostream>
#include "..\..\Dependencies\glm\glm.hpp"
#include "..\..\Dependencies\glm\gtc\matrix_transform.hpp"
#include "..\..\Dependencies\glm\gtc\type_ptr.hpp"
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <vector>

enum Camera_Movement
{
	FORWARD, BACKWARD, LEFT, RIGHT
};

const float SPEED = 0.01f;
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_WorldUp;
	glm::vec3 m_Up;
	glm::vec3 m_Right;

	glm::mat4 m_ViewMatrix;
	float m_Yaw;
	float m_Pitch;

	float m_MovementSpeed;
	float m_MouseSensitivity;
	void updateCameraVectors();

public:
	Camera(glm::vec3 Position, glm::vec3 Up, float yaw, float pitch);
	Camera();
	~Camera();

	void processKeyboard(Camera_Movement direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);

	glm::mat4 getViewMatrix();

};