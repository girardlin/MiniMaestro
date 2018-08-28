#pragma once

#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "..\..\system\FileManager.h"
#include "../../../Dependencies/glm/glm.hpp"
#include "../../../Dependencies/glm/gtc/matrix_transform.hpp"
#include "../../../Dependencies/glm/gtc/type_ptr.hpp"

class Shader
{
public:
	Shader();
	Shader(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);
	~Shader();

	//comment
	unsigned int ID;
	
	void use();
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, glm::mat4 value) const;
	void setMVP(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) const;

};

