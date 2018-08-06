#pragma once

#include "InputManager.h"

bool InputManager::m_TakingInputs;
GLFWwindow* InputManager::m_AffectedWindow;
Camera* InputManager::m_AffectedCamera;


float lastX = 400, lastY = 300;
float someDeltaTime = 0.0f;
float someLastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	/*
	float sensitivity = 0.1f;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFrontValue = glm::normalize(front);
	*/
	InputManager::m_AffectedCamera->processMouseMovement(xoffset, yoffset, GL_TRUE);
	
	
}

//constructor
InputManager::InputManager()
{
	
}

//destructor
InputManager::~InputManager()
{

}

/*
void InputManager::startUp()
{
	m_TakingInputs = true;
}
*/

//setters
void InputManager::setTakingInputs(bool takingInputs)
{
	m_TakingInputs = takingInputs;
}

void InputManager::setPointerToWindow(GLFWwindow* affectedWindow, Camera* affectedCamera)
{
	m_AffectedWindow = affectedWindow;
	//set camera
	m_AffectedCamera = affectedCamera;

	//mouse callback
	glfwSetCursorPosCallback(m_AffectedWindow, mouse_callback);

}

//getters
bool InputManager::getTakingInputs()
{
	return m_TakingInputs;
}

//glm::vec3 InputManager::getCameraFrontValue()
//{
//	return cameraFrontValue;
//}



//other
void InputManager::processInput()
{
	float currentFrame = glfwGetTime();
	someDeltaTime = currentFrame - someLastFrame;
	someLastFrame = currentFrame;
	float movementSpeed = 2.5 * someDeltaTime;

	if (!m_TakingInputs)
	{
		return;
	}

	if (glfwGetKey(m_AffectedWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_AffectedWindow, true);
		return;
	}

	
	if (glfwGetKey(m_AffectedWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_AffectedCamera->processKeyboard(FORWARD, someDeltaTime);
	}
	if (glfwGetKey(m_AffectedWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_AffectedCamera->processKeyboard(BACKWARD, someDeltaTime);
	}
	if (glfwGetKey(m_AffectedWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_AffectedCamera->processKeyboard(LEFT, someDeltaTime);
	}
	if (glfwGetKey(m_AffectedWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_AffectedCamera->processKeyboard(RIGHT, someDeltaTime);
	}
	
	return;

}
