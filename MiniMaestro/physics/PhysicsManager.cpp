#pragma once

#include "PhysicsManager.h"

glm::mat4 PhysicsManager::finalMatrix;

void PhysicsManager::reset()
{
	finalMatrix = glm::mat4(1.0f);
}

void PhysicsManager::translate(glm::vec3& translation)
{
	finalMatrix = glm::translate(finalMatrix, translation);
}

void PhysicsManager::rotate(float& angle, glm::vec3& rotationAxis)
{
	finalMatrix = glm::rotate(finalMatrix, glm::radians(angle), rotationAxis);
}

void PhysicsManager::scale(glm::vec3& scaling)
{
	finalMatrix = glm::scale(finalMatrix, scaling);
}

void PhysicsManager::translate(glm::vec3 translation)
{
	finalMatrix = glm::translate(finalMatrix, translation);
}

void PhysicsManager::rotate(float angle, glm::vec3 rotationAxis)
{
	finalMatrix = glm::rotate(finalMatrix, glm::radians(angle), rotationAxis);
}

void PhysicsManager::scale(glm::vec3 scaling)
{
	finalMatrix = glm::scale(finalMatrix, scaling);
}

glm::mat4 PhysicsManager::getFinalMatrix()
{
	return finalMatrix;
}