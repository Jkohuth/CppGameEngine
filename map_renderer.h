//map_renderer.h

#ifndef MAP_RENDERER_H
#define MAP_RENDERER_H

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/matrix.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include <string>

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "texture.h"
#include "shader.h"
#include "map_layer.h"

class MapRenderer
{
public:
	MapRenderer(std::vector<std::unique_ptr<MapLayer>>& mapLayers, Shader& shader);
	~MapRenderer();
	void DrawMap();
private:
	void initRenderData();
	Shader shader;
	GLuint width, height;
	GLuint quadVAO, vertID, textID;
	std::vector<std::unique_ptr<MapLayer>>& mapLayers;
};

#endif