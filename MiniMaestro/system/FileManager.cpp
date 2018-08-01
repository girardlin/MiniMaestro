#pragma once

#include "FileManager.h"

bool FileManager::m_readLock;
FILE* FileManager::m_file;

/*
void FileManager::startUp()
{
	m_readLock = false;
}
*/

void FileManager::setReadLock(bool& readLock)
{
	m_readLock = readLock;
}

std::string FileManager::getContents(const char* path)
{

	if (!m_readLock)
	{
		//lock the FileManager
		m_readLock = true;

		//output variable
		std::string outputString;
		
		//input stream
		std::ifstream inputFile;

		//making sure inputStream can throw exceptions
		inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			//open file
			inputFile.open(path);
			std::stringstream inputStream;

			inputStream << inputFile.rdbuf();

			inputFile.close();

			outputString = inputStream.str();
		}
		catch(std::ifstream::failure e)
		{
			std::cout << "File not successfully read!" << std::endl;
		}

		//unlock the FileManager
		m_readLock = false;

		//std::cout << "Contents of the file being read: " << std::endl;
		std::cout << outputString << std::endl << std::endl;

		//return value
		return outputString;
	}
	else
	{
		std::cout << "This file manager is currently in use." << std::endl;
		return " ";
	}
}