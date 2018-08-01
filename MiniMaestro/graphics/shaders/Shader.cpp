#pragma once

#include "Shader.h"

Shader::Shader()
{

}

Shader::Shader(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath)
{
	int success;

	std::string a = FileManager::getContents(vertexShaderSourcePath);
	std::string b = FileManager::getContents(fragmentShaderSourcePath);

	//std::cout << a << std::endl;
	//std::cout << b << std::endl;

	const char* vertexShaderCode = a.c_str();
	const char* fragmentShaderCode = b.c_str();

	//std::cout << vertexShaderCode << std::endl;
	//std::cout << fragmentShaderCode << std::endl;

	char infoLog[512];

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);

	glCompileShader(vertex);

	//check for compile errors
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILSE\n" << infoLog << std::endl;
	}


	glCompileShader(fragment);

	//check for compile errors
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILSE\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	
	//check for linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//delete shaders since we are done with them
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{

}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMVP(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(ID, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(ID, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}