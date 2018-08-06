#pragma once

#include "Camera.h"

Camera::Camera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH ):m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY)
{
	m_Position = Position;
	m_WorldUp = Up;
	m_Yaw = yaw;
	m_Pitch = pitch;


	//m_ViewMatrix = glm::mat4(1.0f);
	m_MovementSpeed = 2.0f;
	m_MouseSensitivity = 0.1f;

	updateCameraVectors();
}

Camera::Camera()
{

}

Camera::~Camera()
{

}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);


	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = m_MovementSpeed * deltaTime;
	if (direction == FORWARD)
	{
		m_Position += m_Front * velocity;
	}
	if (direction == BACKWARD)
	{
		m_Position -= m_Front * velocity;
	}
	if (direction == LEFT)
	{
		m_Position -= m_Right * velocity;
	}
	if (direction == RIGHT)
	{
		m_Position += m_Right * velocity;
	}
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
{
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	if (constrainPitch)
	{
		if (m_Pitch > 89.0f)
		{
			m_Pitch = 89.0f;
		}
		if (m_Pitch < -89.0f)
		{
			m_Pitch = -89.0f;
		}
	}

	updateCameraVectors();
}

