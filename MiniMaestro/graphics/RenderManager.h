#pragma once

#include <iostream>
#include <string>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "..\math\Math.h"
#include "model/Model.h"
#include "..\graphics\shaders\Shader.h"
#include "..\physics\BoundingBox.h"
#include "..\entity\GameObject.h"


class RenderManager
{
private:
	RenderManager() { }
	static std::vector <GameObject*>* renderedObjects;

public:
	static void drawMesh(Shader& shader, std::vector <Texture>& meshTextureVector, std::vector <unsigned int>& meshIndexVector, unsigned int* VAO);
	static void drawModel(Shader& shader, std::vector <Mesh>& modelMeshVector);
	static void drawModel(Shader& shader, Model& modelInput);
	static void drawModel(Model&);
	static void drawGO(GameObject&);
	static void drawBoundingBox(BoundingBox&);

	static std::vector <GameObject*> getRenderedObjects();

	static void createRenderedObjectsVector();
	static void clearRenderedObjectsVector();
	static void sortRenderedObjectsVector();
};