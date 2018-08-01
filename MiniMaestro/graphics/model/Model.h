#pragma once


#include <iostream>
#include "Mesh.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <fstream>
#include <sstream>


class Model
{
private:

	//functions
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector <Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

public:
	//vector of meshes
	std::vector <Mesh> m_Meshes;
	std::string directory;
	std::vector <Texture> texturesLoaded;

	//functions
	void setSameShader(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);

	//variables
	float biggestX, smallestX, biggestY, smallestY, biggestZ, smallestZ;

	//constructor
	Model(const char* path);
	~Model();
};

