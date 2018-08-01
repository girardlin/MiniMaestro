#pragma once

#include "RenderManager.h"

std::vector <Model*>* RenderManager::renderedModels;

void RenderManager::drawMesh(Shader& shader, std::vector <Texture>& meshTextureVector, std::vector <unsigned int>& meshIndexVector , unsigned int* VAO)
{
	if (!renderedModels)
	{
		std::cout << "Unable to place model into renderedModels" << std::endl;
		return;
	}
	//number of diffuse and specular textures
	unsigned int diffuseNumber = 1;
	//unsigned int specularNumber = 1;

	std::string number;
	std::string name;

	
	for (unsigned int i = 0; i < meshTextureVector.size(); i++)
	{
		//activate texture before binding
		glActiveTexture(GL_TEXTURE0 + i);

		name = meshTextureVector[i].type;
		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNumber++);
			//std::cout << "diffuse texture number = " << number << std::endl;
		}
		/*
		else if (name == "texture_specular")
		{
			number = std::to_string(specularNumber++);
		}
		*/
		//"material." + caused bug
		//set uniform float to the appropriate texture and bind the texture
		//std::cout << "name of uniform sampler2D should be: " << name << number << std::endl;
		shader.setFloat((/*"material." + */name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, meshTextureVector[i].id);
	}
	glActiveTexture(GL_TEXTURE0);
	
	

	shader.use();
	//draw call
	glBindVertexArray(*(VAO));
	glDrawElements(GL_TRIANGLES, meshIndexVector.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
}

void RenderManager::drawModel(Shader& shader, std::vector <Mesh>& modelMeshVector)
{
	//traverse the model vector and render all the meshes using their information
	for (unsigned int i = 0; i < modelMeshVector.size(); i++)
	{
		drawMesh(shader, modelMeshVector[i].m_Textures, modelMeshVector[i].m_Indices, modelMeshVector[i].getVAO());
	}
}

void RenderManager::drawModel(Shader& shader, Model& modelInput)
{
	for (unsigned int i = 0; i < modelInput.m_Meshes.size(); i++)
	{
		drawMesh(shader, modelInput.m_Meshes[i].m_Textures, modelInput.m_Meshes[i].m_Indices, modelInput.m_Meshes[i].getVAO());
	}
	renderedModels->push_back(&modelInput);
}

void RenderManager::drawModel(Model& modelInput)
{
	for (unsigned int i = 0; i < modelInput.m_Meshes.size(); i++)
	{
		drawMesh(*(modelInput.m_Meshes[i].getShader()), modelInput.m_Meshes[i].m_Textures, modelInput.m_Meshes[i].m_Indices, modelInput.m_Meshes[i].getVAO());
	}
	renderedModels->push_back(&modelInput);
}

void RenderManager::createRenderedModelsVector()
{
	renderedModels = new std::vector <Model*>;
}

void RenderManager::clearRenderedModelsVector()
{
	delete renderedModels;
}

void RenderManager::drawBoundingBox(BoundingBox& input_BB)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	input_BB.getShader()->use();
	//draw call
	glBindVertexArray(*(input_BB.getVAO()));
	glDrawElements(GL_TRIANGLES, input_BB.m_Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}