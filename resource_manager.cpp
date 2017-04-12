//resource_manager.cpp

#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL.h>

std::map<std::string, Texture2D>	ResourceManager::Textures;
std::map<std::string, Shader>		ResourceManager::Shaders;

Shader 	 ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name){
	
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}
Shader& 	 ResourceManager::GetShader(std::string name){
	return Shaders[name];
}
Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name){
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];

}
Texture2D& ResourceManager::GetTexture(std::string name){
	return Textures[name];
}
void 	  ResourceManager::Clear(){
	for(auto iter : Shaders){
		glDeleteProgram(iter.second.ID);
	}
	for(auto iter : Textures){
		glDeleteTextures(1, &iter.second.ID);
	}
}

Shader 	ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile){

	// 1. Retrieve the vertex/fragment shader files from file path
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	try{
		// Open File
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// Close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert Stream into strings
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
        
		if(gShaderFile != nullptr){

			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();

		}
	}
	catch(std::exception e){

			std::cout << "ERROR:SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();
	
	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;

}

Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	Texture2D texture;
	if(alpha){
		texture.Image_Format = GL_RGBA;
		texture.Internal_Format = GL_RGBA;
	}
	// Load Image
	int width, height;
	unsigned char *image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	// Now Generate Texture
	texture.Generate(width, height, image);
	// And finally free image data
	SOIL_free_image_data(image);
	return texture;
}

























