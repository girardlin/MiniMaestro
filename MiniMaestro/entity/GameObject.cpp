#pragma once 

#include "GameObject.h"

GameObject::GameObject(const char* path, bool& isInteractable)
{
	m_Interactable = isInteractable;
	m_Model = new Model(path);

	const char* somePathA = "C:/Users/Girard/source/repos/MiniMaestro - Copy/MiniMaestro/graphics/shaders/BoundingBoxVertex.vs";
	const char* somePathB = "C:/Users/Girard/source/repos/MiniMaestro - Copy/MiniMaestro/graphics/shaders/BoundingBoxFragment.fs";

	float3D tftlplaceholder = { m_Model->smallestX, m_Model->biggestY, m_Model->smallestZ };
	float3D tfbrplaceholder = { m_Model->biggestX, m_Model->biggestY, m_Model->biggestZ };
	float3D bftlplaceholder = { m_Model->smallestX, m_Model->smallestY, m_Model->smallestZ };
	
	std::cout << "Bounding box smallest/biggest x values: " << m_Model->smallestX << " - " << m_Model->biggestX << std::endl;
	std::cout << "Bounding box smallest/biggest y values: " << m_Model->smallestY << " - " << m_Model->biggestY << std::endl;
	std::cout << "Bounding box smallest/biggest z values: " << m_Model->smallestZ << " - " << m_Model->biggestZ << std::endl;

	m_BoundingBox.setBoundingVertices(tftlplaceholder, tfbrplaceholder, bftlplaceholder, somePathA, somePathB);
	
	std::cout << "Created bounding box!" << std::endl;

	m_Position.x = ((m_Model->smallestX + m_Model->biggestX) / 2);
	m_Position.y = ((m_Model->smallestY + m_Model->biggestY) / 2);
	m_Position.z = ((m_Model->smallestZ + m_Model->biggestZ) / 2);
	m_Position.w = 1;

}

GameObject::GameObject(const char* path, bool isInteractable)
{
	m_Interactable = isInteractable;
	m_Model = new Model(path);

	const char* somePathA = "C:/Users/Girard/source/repos/MiniMaestro - Copy/MiniMaestro/graphics/shaders/BoundingBoxVertex.vs";
	const char* somePathB = "C:/Users/Girard/source/repos/MiniMaestro - Copy/MiniMaestro/graphics/shaders/BoundingBoxFragment.fs";

	float3D tftlplaceholder = { m_Model->smallestX, m_Model->biggestY, m_Model->smallestZ };
	float3D tfbrplaceholder = { m_Model->biggestX, m_Model->biggestY, m_Model->biggestZ };
	float3D bftlplaceholder = { m_Model->smallestX, m_Model->smallestY, m_Model->smallestZ };

	std::cout << "Bounding box smallest/biggest x values: " << m_Model->smallestX << " - " << m_Model->biggestX << std::endl;
	std::cout << "Bounding box smallest/biggest y values: " << m_Model->smallestY << " - " << m_Model->biggestY << std::endl;
	std::cout << "Bounding box smallest/biggest z values: " << m_Model->smallestZ << " - " << m_Model->biggestZ << std::endl;

	m_BoundingBox.setBoundingVertices(tftlplaceholder, tfbrplaceholder, bftlplaceholder, somePathA, somePathB);
	std::cout << "Created bounding box!" << std::endl;

	m_Position.x = ((m_Model->smallestX + m_Model->biggestX) / 2);
	m_Position.y = ((m_Model->smallestY + m_Model->biggestY) / 2);
	m_Position.z = ((m_Model->smallestZ + m_Model->biggestZ) / 2);
	m_Position.w = 1;
}

GameObject::~GameObject()
{
	delete m_Model;
}