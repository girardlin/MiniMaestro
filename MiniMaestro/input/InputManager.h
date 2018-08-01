#pragma once 

#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "../../Dependencies/glm/glm.hpp"
#include "../../Dependencies/glm/gtc/matrix_transform.hpp"
#include "../../Dependencies/glm/gtc/type_ptr.hpp"
#include <string>

class InputManager
{
private:
	static bool m_TakingInputs;
	static GLFWwindow* m_AffectedWindow;
	InputManager();
	~InputManager();

public:
	//constructors and destructors
	
	// void startUp();

	//setters
	static void setTakingInputs(bool);
	static void setPointerToWindow(GLFWwindow*);

	//getters
	static bool getTakingInputs();
	static glm::vec3 getCameraFrontValue();

	//other
	static void processInput(float& movementSpeed, glm::vec3& cameraPosInput, glm::vec3& cameraFrontInput, glm::vec3& cameraUpInput);
};