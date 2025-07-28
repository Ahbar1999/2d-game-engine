#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>	

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, std::vector<Texture2D>> ResourceManager::Animations; 
std::map<std::string, Shader>       ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name) {
	Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

std::vector<Texture2D> ResourceManager::LoadTextures(const char *file, uint16_t nrFrames, bool alpha, std::string name) {
    std::cout << "loading textures for: " << name << std::endl;
    // load sprite sheet
    return Animations[name] = loadAnimationFromFile(file, nrFrames, alpha);
}

Shader ResourceManager::getShader(std::string name)
{
	return Shaders[name];
}

Texture2D ResourceManager::getTexture(std::string name) {
	return Textures[name];
}

std::vector<Texture2D> ResourceManager::getAnimation(std::string name) {
    return Animations[name]; 
}

void ResourceManager::Clear()
{
	// (properly) delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	// (properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.id);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
	try {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

// frame_size = {width, heighh} of a single frame, nrFrames = number of frames expected in the sprite sheet 
std::vector<Texture2D> ResourceManager::loadAnimationFromFile(const char* file, uint16_t nrFrames, bool alpha) {
    // load sprite sheet 
    int width, height, nrChannels;
     
    std::vector<Texture2D> textures;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (data == NULL) {
        std::cerr << "Could not load file: " << std::endl;
        exit(0);
        // return textures;
    }
    int frame_width = width / nrFrames;
    int frame_height = height;
    // std::cout << frame_width << "x" << frame_height << " " << nrChannels << std::endl;
    // heap data to store single frame data
    const uint32_t pixels_per_frame = frame_height * frame_width * nrChannels;

    unsigned char* frame_data = (unsigned char*)malloc(sizeof(unsigned char) * pixels_per_frame);
    for (int i=0; i < nrFrames; i++) {
        // create texture object
        Texture2D texture;
        if (alpha) {
            texture.Internal_Format = GL_RGBA;
            texture.Image_Format = GL_RGBA;
        }

        for (int y = 0; y < frame_height; y++) {
            for (int x = 0; x < frame_width; x++) {
                for (int c = 0; c < nrChannels; c++) {
                    // Source calculation (in bytes):
                    // - y * width * nrChannels: skip to correct row
                    // - i * frame_width * nrChannels: offset to correct frame
                    // - x * nrChannels: offset to correct pixel in row  
                    // - c: offset to correct channel
                    int src_index = (y * width + i * frame_width + x) * nrChannels + c;
                    int dst_index = (y * frame_width + x) * nrChannels + c;
                    frame_data[dst_index] = data[src_index];
                }
            }
        }

        // now generate texture
        texture.Generate(frame_width, frame_height, frame_data);
        textures.push_back(texture);
    }

    // and finally free image data
    stbi_image_free(data);
    free(frame_data);
    std::cout << "animation textures loaded: " <<  textures.size() << std::endl;
    return textures;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha) {
    // create texture object
    Texture2D texture;
    if (alpha) {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}