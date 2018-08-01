#pragma once

#include "BoundingBox.h"

BoundingBox::BoundingBox()
{

}

BoundingBox::~BoundingBox()
{

}

void BoundingBox::setupShader(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath)
{
	m_Shader = new Shader(vertexShaderSourcePath, fragmentShaderSourcePath);
}

void BoundingBox::setBoundingVertices(float3D tftl, float3D tfbr, float3D bftl, const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath)
{
	std::cout << "Bounding Box entry smallest Y: " << bftl.b << std::endl;
	m_tftl = tftl;
	m_tfbr = tfbr;
	m_tftr = { tfbr.a, tftl.b, tftl.c };
	m_tfbl = { tftl.a, tftl.b, tfbr.c };
	m_bftl = bftl;
	m_bfbr = { m_tfbr.a, bftl.b, m_tfbr.c };
	m_bftr = { m_tfbr.a, bftl.b, m_tftr.c };
	m_bfbl = { m_tfbl.a, bftl.b, m_bfbr.c };
	
	m_Length = abs(m_tfbr.a - m_tfbl.a);
	m_Height = abs(m_bftl.b - m_tftl.b);
	m_Width = abs(m_tfbl.c - m_tftl.c);

	std::cout << "Bounding box tftl values: " << m_tftl.a << " - " << m_tftl.b << " - " << m_tftl.c << std::endl;
	std::cout << "Bounding box tftr values: " << m_tftr.a << " - " << m_tftr.b << " - " << m_tftr.c << std::endl;
	std::cout << "Bounding box tfbl values: " << m_tfbl.a << " - " << m_tfbl.b << " - " << m_tfbl.c << std::endl;
	std::cout << "Bounding box tfbr values: " << m_tfbr.a << " - " << m_tfbr.b << " - " << m_tfbr.c << std::endl;
	std::cout << "Bounding box bftl values: " << m_bftl.a << " - " << m_bftl.b << " - " << m_bftl.c << std::endl;
	std::cout << "Bounding box bftr values: " << m_bftr.a << " - " << m_bftr.b << " - " << m_bftr.c << std::endl;
	std::cout << "Bounding box bfbl values: " << m_bfbl.a << " - " << m_bfbl.b << " - " << m_bfbl.c << std::endl;
	std::cout << "Bounding box bfbr values: " << m_bfbr.a << " - " << m_bfbr.b << " - " << m_bfbr.c << std::endl;

	setupShader(vertexShaderSourcePath, fragmentShaderSourcePath);

	//m_Vertices.clear();

	m_Vertices.push_back(m_tftl);
	m_Vertices.push_back(m_tftr);
	m_Vertices.push_back(m_tfbl);
	m_Vertices.push_back(m_tfbr);
	m_Vertices.push_back(m_bftl);
	m_Vertices.push_back(m_bftr);
	m_Vertices.push_back(m_bfbl);
	m_Vertices.push_back(m_bfbr);

	
	//m_Indices.clear();

	//top face
	m_Indices.push_back(0);
	m_Indices.push_back(1);
	m_Indices.push_back(2);

	m_Indices.push_back(1);
	m_Indices.push_back(2);
	m_Indices.push_back(3);
	
	//left face
	m_Indices.push_back(0);
	m_Indices.push_back(2);
	m_Indices.push_back(4);

	m_Indices.push_back(2);
	m_Indices.push_back(4);
	m_Indices.push_back(6);

	//back face
	m_Indices.push_back(0);
	m_Indices.push_back(1);
	m_Indices.push_back(4);

	m_Indices.push_back(1);
	m_Indices.push_back(4);
	m_Indices.push_back(5);

	//right face
	m_Indices.push_back(1);
	m_Indices.push_back(3);
	m_Indices.push_back(5);

	m_Indices.push_back(3);
	m_Indices.push_back(5);
	m_Indices.push_back(7);

	//front face
	m_Indices.push_back(2);
	m_Indices.push_back(3);
	m_Indices.push_back(6);

	m_Indices.push_back(3);
	m_Indices.push_back(6);
	m_Indices.push_back(7);

	//bottom face
	m_Indices.push_back(4);
	m_Indices.push_back(5);
	m_Indices.push_back(6);

	m_Indices.push_back(5);
	m_Indices.push_back(6);
	m_Indices.push_back(7);
	
	setupMesh();

}

void BoundingBox::setupMesh()
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
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float3D), &m_Vertices[0], GL_STATIC_DRAW);

	//bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//store m_indices into EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

	//use binded VAO's attribute list
	//vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float3D), (void*)0);

	//unbind VAO since we are done
	glBindVertexArray(0);
}

unsigned int* BoundingBox::getVAO()
{
	return &VAO;
}

Shader* BoundingBox::getShader()
{
	return m_Shader;
}