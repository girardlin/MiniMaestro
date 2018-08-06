#pragma once

#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "..\..\input\InputManager.h"
#include "..\..\system\FileManager.h"


class WindowManager
{
private:
	GLFWwindow* m_Window;
	unsigned int m_Width;
	unsigned int m_Height;
	glm::vec3 m_CameraFrontValue;


public:
	//constructors and destructors
	WindowManager(unsigned int, unsigned int, const char*);
	~WindowManager();

	//getters
	GLFWwindow* getWindow();
	//glm::vec3 getCameraFront();

	//setters
	//void setCameraFront(glm::vec3 input);

	//other
	void update();
};