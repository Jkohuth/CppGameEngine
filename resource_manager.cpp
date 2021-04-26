//resource_manager.cpp

#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

//#include <SOIL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::map<std::string, Texture2D>				ResourceManager::Textures;
std::map<std::string, Shader>					ResourceManager::Shaders;
//std::vector<GLuint> 							ResourceManager::tileTextures;
//std::vector<std::unique_ptr<MapLayer>> 			ResourceManager::mapLayers;
//std::map<std::string, Map>						ResourceManager::Maps;
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
/*
void ResourceManager::LoadMap(const GLchar *file, std::string name)
{
	tmx::Map map;
	map.load(file);
	

	loadMapTexturesFromFile(map);

	const std::vector<tmx::Layer::Ptr>& layers = map.getLayers();

	for(uint i = 0; i <layers.size(); ++i)
	{
		if(layers[i]->getType() == tmx::Layer::Type::Tile)
		{
				mapLayers.emplace_back(std::make_unique<MapLayer>(map, i, tileTextures));
		}
	}	
}
std::vector<std::unique_ptr<MapLayer>>& ResourceManager::GetMap()
{
	return mapLayers;
}
*/
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
	int width, height, nrChannels;
	//unsigned char *image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	// Now Generate Texture
  unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
	texture.Generate(width, height, data);
  stbi_image_free(data);
	// And finally free image data
	//SOIL_free_image_data(image);
	return texture;
}
/*std::vector<GLuint> ResourceManager::GetTileTextures()
{
	return tileTextures;
}*/
/*
void ResourceManager::loadMapTexturesFromFile(const tmx::Map& map) //might take a shader argument
{
	const std::vector<tmx::Tileset>& tilesets = map.getTilesets();
	for(tmx::Tileset ts : tilesets)
	{
		// Transparency alpha stuff later
//		tileTextures.emplace_back(0);
		Texture2D texture;
		texture.Image_Format = GL_RGBA;
		texture.Internal_Format = GL_RGBA;
		int width, height;
		const char *path = ts.getImagePath().c_str();
		unsigned char *image = SOIL_load_image(path, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB );
		texture.GenerateMapTexture(width, height, image);
		SOIL_free_image_data(image);
		tileTextures.emplace_back(texture.id());


	}
}*/
	// Unsure if need these
//	glCheck(glClearColor(0.6f, 0.8f, 0.92f, 1.f));
//    glCheck(glEnable(GL_BLEND));
//    glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//    glCheck(glBlendEquation(GL_FUNC_ADD));
























