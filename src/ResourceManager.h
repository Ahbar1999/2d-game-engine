#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "Texture.h"
#include "Shader.h"

//A static class to load and store textures and shaders
class ResourceManager
{
public:
	static std::map<std::string, Texture2D> Textures;
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, std::vector<Texture2D>> Animations;
	
	//loads and generates a shader program from vertex, fragment and geometry shader source code file.
	static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	//retrieves the shader program
	static Shader getShader(std::string name);
	
	//loads and store a texture object from a image 
	static Texture2D LoadTexture(const char* file, bool alpha, std::string name, bool flip_verticaly=false);
	
	static std::vector<Texture2D> LoadTextures(const char *file, uint16_t nrFrames, bool alpha, std::string name, bool flip_verticaly=false);
	//retrieves  the shader object 
	static Texture2D getTexture(std::string name);

	// return a reference to the textures of an animations 
	static std::vector<Texture2D>* getAnimation(std::string name);
	//de allocates all the loaded resources, memory and shit allocated in the process 
	static void Clear();

private:
	//Making the constructor private because its a singleton class
	ResourceManager() {};

	//loads and generates shader program from source code files
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);

	//loads and generates a single 2d texture from a file
	static Texture2D loadTextureFromFile(const char* file, bool alpha, bool flip_vertically);

	//loads and generates a vector of 2d texture from a file(sprite sheet) 
	static std::vector<Texture2D> loadAnimationFromFile(const char* file, uint16_t nrFrames, bool alpha, bool flip_vertically);
};

#endif // !RESOURCE_MANAGER_H