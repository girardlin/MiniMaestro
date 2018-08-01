#pragma once

#include "../../Dependencies/glm/glm.hpp"
#include "../../Dependencies/glm/gtc/matrix_transform.hpp"
#include "../../Dependencies/glm/gtc/type_ptr.hpp"
#include "../graphics/model/Model.h"

#include <vector>

class PhysicsManager
{
private:
	static glm::mat4 finalMatrix;
	PhysicsManager() { }
	~PhysicsManager() { }

public:
	static void reset();
	static void translate(glm::vec3& translation);
	static void rotate(float& angle, glm::vec3& rotationAxis);
	static void scale(glm::vec3& scaling);
	static void translate(glm::vec3 translation);
	static void rotate(float angle, glm::vec3 rotationAxis);
	static void scale(glm::vec3 scaling);
	static glm::mat4 getFinalMatrix();
};