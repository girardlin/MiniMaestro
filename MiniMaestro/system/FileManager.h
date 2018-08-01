#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "..\..\Dependencies\stb_image.h"
#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <fstream>
#include <string>
#include <sstream>

class FileManager
{
private:
	FileManager() { }
	~FileManager() { }

public:
	static FILE* m_file;
	static bool m_readLock;

	//static void startUp();

	static void setReadLock(bool&);
	static std::string getContents(const char*);
};