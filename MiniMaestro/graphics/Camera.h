#pragma once 

#include "..\..\Dependencies\glm\glm.hpp"
#include "..\..\Dependencies\glm\gtc\matrix_transform.hpp"
#include "..\..\Dependencies\glm\gtc\type_ptr.hpp"
#include "..\input\InputManager.h"

#include <vector>

const float SPEED = 0.01f;

class Camera
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_WorldUp;
	glm::vec3 m_Up;
	glm::vec3 m_Front;

	glm::mat4 m_View;

	float m_MovementSpeed;
	void updateCameraVectors();

public:
	Camera(glm::vec3 Position, glm::vec3 Up);
	~Camera();

	glm::mat4 getView();

};