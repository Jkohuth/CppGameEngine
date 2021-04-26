//resource_manager.h

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <glad/glad.h>
#define GLM_FORCE_RADIANS
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <cassert>

//#include <Map.hpp>
#include "texture.h"
#include "shader.h"
//#include "map_layer.h"


// A static singleton ResourceManager class that hosts several functions to oad textures and Shaders
// Each loaded Texture and/or shader is also stored for future reference by string handles
// All functions and resources are static and no public contructor is defined

class ResourceManager
{
public:
	static std::map<std::string, Shader>	Shaders;
	static std::map<std::string, Texture2D>	Textures;
	//static std::map<std::string, Map> 		Maps;
	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads the geometry shader
	static Shader 	 LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	// Retrieves a stored Shader
	static Shader& 	 GetShader(std::string name);
	// Load a stored Texture
	static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
	// Retrieves a stored Texture
	static Texture2D& GetTexture(std::string name);
//	static std::vector<std::unique_ptr<MapLayer>>& GetMap();
///	static void LoadMap(const GLchar *file, std::string name);
	// Properly de-allocates all loaded resources
	static void	Clear();
private:
	//std::vector<GLuint> GetTileTextures();

	// Private Constructor, that is we do not want any actual resource manager objects, Its members and functions should be publicly available (static).
	ResourceManager() { }
	// Loads and generates a shader from file
	static Shader 	loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	// Loads a single Texture from file
	static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);

	//static std::vector<GLuint> tileTextures;
	//static std::vector<std::unique_ptr<MapLayer>> mapLayers;

//	static void loadMapTexturesFromFile(const tmx::Map& map);
};

#endif
