#pragma once

#include "RenderManager.h"

std::vector <GameObject*>* RenderManager::renderedObjects;


void RenderManager::drawMesh(Shader& shader, std::vector <Texture>& meshTextureVector, std::vector <unsigned int>& meshIndexVector , unsigned int* VAO)
{
	if (!renderedObjects)
	{
		std::cout << "Unable to place model into renderedObjects" << std::endl;
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
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


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
	
}

void RenderManager::drawModel(Model& modelInput)
{
	
	for (unsigned int i = 0; i < modelInput.m_Meshes.size(); i++)
	{
		drawMesh(*(modelInput.m_Meshes[i].getShader()), modelInput.m_Meshes[i].m_Textures, modelInput.m_Meshes[i].m_Indices, modelInput.m_Meshes[i].getVAO());
	}
	
}

void RenderManager::drawGO(GameObject& GOInput)
{
	renderedObjects->push_back(&GOInput);
	for (unsigned int i = 0; i < GOInput.m_Model->m_Meshes.size(); i++)
	{
		drawMesh(*(GOInput.m_Model->m_Meshes[i].getShader()), GOInput.m_Model->m_Meshes[i].m_Textures, GOInput.m_Model->m_Meshes[i].m_Indices, GOInput.m_Model->m_Meshes[i].getVAO());
	}

}

void RenderManager::createRenderedObjectsVector()
{
	renderedObjects = new std::vector <GameObject*>;
}

void RenderManager::clearRenderedObjectsVector()
{
	delete renderedObjects;
}

void RenderManager::drawBoundingBox(BoundingBox& input_BB)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	input_BB.getShader()->use();
	//draw call
	glBindVertexArray(*(input_BB.getVAO()));
	glDrawElements(GL_TRIANGLES, input_BB.m_Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

std::vector <GameObject*> RenderManager::getRenderedObjects()
{
	return *(renderedObjects);

	
}

void RenderManager::sortRenderedObjectsVector()
{
	bool swapped;
	int i, j;
	GameObject* placeholder;
	
	for (i = 0; i < renderedObjects->size() - 1; i++)
	{
		swapped = false;
		for (j = 0; j < renderedObjects->size() - i - 1; j++)
		{
			if ((*(renderedObjects))[j]->m_FinalPosition.z > (*(renderedObjects))[j + 1]->m_FinalPosition.z)
			{
				placeholder = (*(renderedObjects))[j];
				(*(renderedObjects))[j] = (*(renderedObjects))[j + 1];
				(*(renderedObjects))[j + 1] = placeholder;

				swapped = true;
			}
		}
		if (!swapped)
		{
			break;
		}
		
	}
	
	for (i = 0; i < renderedObjects->size(); i++)
	{
		std::cout << (*(renderedObjects))[i]->m_Model->directory << std::endl;
	}
	
}