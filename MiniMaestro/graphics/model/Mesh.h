#pragma once

#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <vector>
#include "..\..\math\math.h"
#include "..\shaders\Shader.h"

class Mesh
{
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
	Shader* m_Shader;

public:
	Mesh();
	Mesh(std::vector <Vertex> vertices, std::vector <unsigned int> indices, std::vector <Texture> textures);
	Mesh(std::vector <Vertex> vertices, std::vector <unsigned int> indices, std::vector <Texture> textures, const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);
	~Mesh();


	void setupShader(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);

	std::vector <Vertex> m_Vertices;
	std::vector <unsigned int> m_Indices;
	std::vector <Texture> m_Textures;

	Shader* getShader();
	void setShader(Shader*);

	unsigned int* getVAO();
	
};