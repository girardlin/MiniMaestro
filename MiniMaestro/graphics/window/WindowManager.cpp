#pragma once

#include "WindowManager.h"
#include <vector>


//resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


//constructor
WindowManager::WindowManager(unsigned int width, unsigned int height, const char* windowName)
{
	//GLFW Loading
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Width = width;
	m_Height = height;

	//Window creation
	m_Window = glfwCreateWindow(m_Width, m_Height, windowName, NULL, NULL);
	if (m_Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	//Callback to resizing window
	glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

	//"Bind" window
	glfwMakeContextCurrent(m_Window);

	//Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	//inputs
	InputManager::setTakingInputs(true);
	InputManager::setPointerToWindow(m_Window);

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	
}


//destructor
WindowManager::~WindowManager()
{

}


//window getter
GLFWwindow* WindowManager::getWindow()
{
	return m_Window;
}

//window update function
void WindowManager::update()
{
	//InputManager::processInput();
	

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

