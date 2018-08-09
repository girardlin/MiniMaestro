#pragma once

#include <iostream>
#include "..\graphics\model\Model.h"
#include "..\physics\BoundingBox.h"
#include "Entity.h"

class GameObject : public Entity
{
public:
	Model* m_Model;
	bool m_Interactable;
	BoundingBox m_BoundingBox;
	glm::vec4 m_Position;
	glm::vec4 m_FinalPosition;
public:
	GameObject(const char* path, bool& isInteractable);
	GameObject(const char* path, bool isInteractable);
	~GameObject();
	
};