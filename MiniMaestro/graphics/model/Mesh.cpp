#pragma once

#include "Mesh.h"

Mesh::Mesh()
{

}

Shader* Mesh::getShader()
{
	return m_Shader;
}

void Mesh::setShader(Shader* input)
{
	m_Shader = input;
}

Mesh::Mesh(std::vector <Vertex> vertices, std::vector <unsigned int> indices, std::vector <Texture> textures)
{
	m_Shader = new Shader;

	m_Vertices = vertices;
	m_Indices = indices;
	m_Textures = textures;

	//std::cout << m_Vertices[0].position.a << "   " << m_Vertices[0].position.b << std::endl;
	//std::cout << m_Indices[0] << "   " << m_Indices[1] << "   "<< m_Indices[2] << std::endl;
	//std::cout << m_Textures[0].id << "   " << m_Textures[0].path << std::endl;

	setupMesh();
}

Mesh::Mesh(std::vector <Vertex> vertices, std::vector <unsigned int> indices, std::vector <Texture> textures, const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath)
{
	m_Shader = new Shader(vertexShaderSourcePath, fragmentShaderSourcePath);

	//set all of our data to the inputted vectors
	m_Vertices = vertices;
	m_Indices = indices;
	m_Textures = textures;

	setupMesh();
}

Mesh::~Mesh()
{
	
}

void Mesh::setupShader(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath)
{
	m_Shader = new Shader(vertexShaderSourcePath, fragmentShaderSourcePath);
}

void Mesh::setupMesh()
{
	//still using one VBO for all attributes in VAO
	
	//create VAO, VBO, and EBO and assigning their id's to the unsigned int members
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind VAO and VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//store m_Vertices into VBO
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

	//bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
	//store m_indices into EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

	//use binded VAO's attribute list
	//vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//texutre coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoord));

	//unbind VAO since we are done
	glBindVertexArray(0);
}

unsigned int* Mesh::getVAO()
{
	return &VAO;
}