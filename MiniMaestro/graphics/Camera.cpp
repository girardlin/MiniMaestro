#pragma once

#include "Camera.h"

Camera::Camera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f)) :m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED)
{
	m_Position = Position;
	m_WorldUp = Up;
	m_View = glm::mat4(1.0f);
	updateCameraVectors();
}

Camera::~Camera()
{

}

glm::mat4 Camera::getView()
{
	return m_View;
}

void Camera::updateCameraVectors()
{
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}