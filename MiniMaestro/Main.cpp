#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "graphics/window/WindowManager.h"
#include "system/FileManager.h"
#include "graphics/RenderManager.h"
#include "physics/PhysicsManager.h"

#include "graphics/Camera.h"
#include "graphics/model/Model.h"
#include "entity/GameObject.h"

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"
#include "../Dependencies/glm/gtc/type_ptr.hpp"



int main()
{

	//window creation
	unsigned int window_width = 800;
	unsigned int window_height = 600;

	WindowManager myWindowManager(window_width, window_height, "Mini Maestro");
	//camera initialization

	glm::vec3 input_Position = { 0.0f, 1.0f, 3.0f };
	glm::vec3 input_Up = { 0.0f, 1.0f, 0.0f };

	//Camera* myCamera = new Camera(input_Position, input_Up, -90.0f, 0.0f);

	Camera myCamera(input_Position, input_Up, -90.0f, 0.0f);
	InputManager::setPointerToWindow(myWindowManager.getWindow(), &myCamera);



	//path to model.obj
	const char* myPath = "C:/Users/Girard/source/repos/MiniMaestro - Copy/MiniMaestro/res/sylvanas/Sylvanas.obj";

	//Model Generation
	//Model myModel(myPath);

	GameObject myGO(myPath, true);

	myPath = "C:/Users/Girard/source/repos/MiniMaestro - Copy/MiniMaestro/res/chogall/Chogall.obj";

	GameObject myGO2(myPath, true);

	//Model mySecondModel(myPath);

	//myPath = "C:/Users/Girard/source/repos/MiniMaestro - Copy/MiniMaestro/res/guitar/guitar.obj";
	//Model myThirdModel(myPath);

	//paths to basic shaders
	const char* somePathA = "C:/Users/Girard/source/repos/MiniMaestro - Copy/MiniMaestro/graphics/shaders/BasicVertex.vs";
	const char* somePathB = "C:/Users/Girard/source/repos/MiniMaestro - Copy/MiniMaestro/graphics/shaders/BasicFragment.fs";

	//set all meshes within the model to use the same mesh
	//myModel.setSameShader(somePathA, somePathB);
	//mySecondModel.setSameShader(somePathA, somePathB);
	myGO.m_Model->setSameShader(somePathA, somePathB);
	myGO2.m_Model->setSameShader(somePathA, somePathB);
	//myThirdModel.setSameShader(somePathA, somePathB);

	PhysicsManager::reset();
	PhysicsManager::translate(glm::vec3(2.0f, -1.0f, 0.0f));
	//PhysicsManager::rotate(30.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	PhysicsManager::scale(glm::vec3(2.0f, 2.0f, 2.0f));
	glm::mat4 transform1 = PhysicsManager::getFinalMatrix();

	PhysicsManager::reset();
	PhysicsManager::translate(glm::vec3(-2.0f, -1.0f, 0.0f));
	PhysicsManager::rotate(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//PhysicsManager::scale(glm::vec3(3.0f, 2.0f, 1.0f));
	glm::mat4 transform2 = PhysicsManager::getFinalMatrix();


	glm::mat4 viewTrans = glm::mat4(1.0f);
	viewTrans = glm::translate(viewTrans, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projectionTrans = glm::mat4(1.0f);
	projectionTrans = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);
	
	
	glEnable(GL_DEPTH_TEST);

	//camera setup
	
	/*
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
	
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt( glm::vec3(0.0f, 0.0f, 3.0f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.0f, 1.0f, 0.0f));
	*/	
	
	//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	//glm::vec3 cameraFront = InputManager::getCameraFrontValue();
	//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::mat4(1.0f);


	//engine loop
	while (!glfwWindowShouldClose(myWindowManager.getWindow()))
	{


		//glm::vec3 cameraFront = InputManager::getCameraFrontValue();
		//std::cout << "XYZ camera front values: " << myWindowManager.getCameraFront().x << myWindowManager.getCameraFront().y << myWindowManager.getCameraFront().z << std::endl;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderManager::createRenderedModelsVector();

		//trans = glm::rotate(trans, (float)glfwGetTime()/100, glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		/*
		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		*/
		InputManager::processInput();

		view = myCamera.getViewMatrix();

		

		
		RenderManager::drawModel(*(myGO.m_Model)); 
		myGO.m_Model->m_Meshes[0].getShader()->setMVP(transform1, view, projectionTrans);
	
		
		RenderManager::drawBoundingBox(myGO.m_BoundingBox);
		myGO.m_BoundingBox.getShader()->setMVP(transform1, view, projectionTrans);



		RenderManager::drawModel(*(myGO2.m_Model));
		myGO2.m_Model->m_Meshes[0].getShader()->setMVP(transform2, view, projectionTrans);


		RenderManager::drawBoundingBox(myGO2.m_BoundingBox);
		myGO2.m_BoundingBox.getShader()->setMVP(transform2, view, projectionTrans);

		

	

		//myModel.m_Meshes[0].getShader()->setMVP(transform1, view, projectionTrans);

		//system("PAUSE");
		//RenderManager::drawModel(myModel);

		//mySecondModel.m_Meshes[0].getShader()->setMVP(transform2, view, projectionTrans);

		//RenderManager::drawMesh(*(myMesh.getShader()), myMesh.m_Textures, myMesh.m_Indices, myMesh.getVAO());
		//RenderManager::drawModel(mySecondModel);


		//RenderManager::drawModel(myThirdModel);
		
		
		myWindowManager.update();

		RenderManager::clearRenderedModelsVector();
		
	}
	glfwTerminate();
}