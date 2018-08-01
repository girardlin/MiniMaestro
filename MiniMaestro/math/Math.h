#pragma once

#include <string>


struct float2D
{
	float a, b;
};

struct float3D
{
	float a, b, c;
};

struct Vertex 
{
	float3D position;
	float3D normal;
	float2D textureCoord;
};


struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};