#pragma once

#include "..\math\Math.h"
#include <iostream>
#include <vector>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "..\graphics\shaders\Shader.h"
#include "..\graphics\model\Mesh.h"

class BoundingBox
{
private:
	float3D m_tftl, m_tftr, m_tfbl, m_tfbr, m_bftl, m_bftr, m_bfbl, m_bfbr;
	unsigned int m_Length, m_Width, m_Height;
	
	unsigned int VAO, VBO, EBO;
	Shader* m_Shader;

public:
	void setBoundingVertices(float3D tftl, float3D tfbr, float3D bftl, const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);

	std::vector <float3D> m_Vertices;
	std::vector <unsigned int> m_Indices;

	Shader* getShader();
	unsigned int* getVAO();

	void setupMesh();
	void setupShader(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);

	BoundingBox();
	~BoundingBox();
};