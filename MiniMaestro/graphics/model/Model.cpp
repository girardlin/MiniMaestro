#pragma once

#include "Model.h"

bool firstRun = true;

unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma)
{
	std::string fileName = std::string(path);
	fileName = directory + '/' + fileName;

	//debug
	std::cout << fileName << std::endl;
	

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, componentsNumber;

	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &componentsNumber, 0);
	if (data)
	{
		std::cout << "Successfully loaded!" << std::endl;
		GLenum format;
		if (componentsNumber == 1)
			format = GL_RED;
		else if (componentsNumber == 3)
			format = GL_RGB;
		else if (componentsNumber == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

	}
	else
	{
		std::cout << stbi_failure_reason() << std::endl;
		std::cout << "Texture failed to load path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}


Model::Model(const char* path)
{

	loadModel(path);
}

Model::~Model()
{
	delete m_Meshes[0].getShader();
	
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
	{
		m_Meshes[i].setShader(NULL);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer myImporter;
	const aiScene* scene = myImporter.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << myImporter.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;


	//done for very vertex
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		float3D placeholder3D;

		//copy vertex positions to our placeholder vec3
		placeholder3D.a = mesh->mVertices[i].x;
		placeholder3D.b = mesh->mVertices[i].y;
		placeholder3D.c = mesh->mVertices[i].z;

		if (firstRun)
		{
			firstRun = false;

			smallestX = placeholder3D.a;
			smallestY = placeholder3D.b;
			smallestZ = placeholder3D.c;
			biggestX - placeholder3D.a;
			biggestY = placeholder3D.b;
			biggestZ = placeholder3D.c;

			std::cout << "Triggered Once" << std::endl;
		}

		if (placeholder3D.a > biggestX)
		{
			//std::cout << "biggest x: " <<biggestX << std::endl;
			biggestX = placeholder3D.a;
		}
		if (placeholder3D.b > biggestY)
		{
			//std::cout << "biggest y: " << biggestY << std::endl;
			biggestY = placeholder3D.b;
		}
		if (placeholder3D.c > biggestZ)
		{
			//std::cout << "biggest z: " << biggestZ << std::endl;
			biggestZ = placeholder3D.c;
		}
		if (placeholder3D.a < smallestX)
		{
			//std::cout << "smallest x: " << smallestX << std::endl;
			smallestX = placeholder3D.a;
		}
		if (placeholder3D.b < smallestY)
		{
			//std::cout << "smallest y: " << smallestY << std::endl;
			smallestY = placeholder3D.b;
		}
		if (placeholder3D.c < smallestZ)
		{
			//std::cout << "smallest z: " << smallestZ << std::endl;
			smallestZ = placeholder3D.c;
		}

		//std::cout << "WTF " << smallestY << " lol " << biggestY << std::endl;
		//std::cout << placeholder3D.a << "   " << placeholder3D.b << "   " << placeholder3D.c << "   " << std::endl;

		//store the positions into a placeholder vertex
		vertex.position = placeholder3D;

		//copy normal positions to our placegolder vec3
		placeholder3D.a = mesh->mNormals[i].x;
		placeholder3D.b = mesh->mNormals[i].y;
		placeholder3D.c = mesh->mNormals[i].z;

		//store the normals into the same placeholder vertex
		vertex.normal = placeholder3D;

		//check if there are any texture coordinates
		if (mesh->mTextureCoords[0])
		{
			//make a 2D placeholder for texture coords and store values into them
			float2D placeholder2D;
			placeholder2D.a = mesh->mTextureCoords[0][i].x;
			placeholder2D.b = mesh->mTextureCoords[0][i].y;
			vertex.textureCoord = placeholder2D;
		}
		else
		{
			float2D noTexCoords = { 0.0f, 0.0f };
			vertex.textureCoord = noTexCoords;
		}

		//store it to the Model's vertices vector
		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector <Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		/*
		std::vector <Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		*/
	}


	return Mesh(vertices, indices, textures);
}

std::vector <Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector <Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < texturesLoaded.size(); j++)
		{
			if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
			{
				std::cout << "Texture has been loaded previously, skipping." << std::endl;

				textures.push_back(texturesLoaded[j]);
				skip = true;
				break;
			}
		}
		
		if (!skip)
		{
			//if the texture hasn't been loaded yet, load it
			std::cout << "New texture, loading." << std::endl;

			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory, false);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			texturesLoaded.push_back(texture); //add to the vector of loaded textures
		}
	}

	return textures;

}

void Model::setSameShader(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath)
{
	Shader* placeholder = new Shader(vertexShaderSourcePath, fragmentShaderSourcePath);
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
	{
		m_Meshes[i].setShader(placeholder);
	}
}