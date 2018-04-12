//map_layer.h

#ifndef MAP_LAYER_H
#define MAP_LAYER_H

#include <GL/glew.h>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gl_macros.hpp"
#include "texture.h"
#include "shader.h"

namespace tmx
{
	class Map;
}

class MapLayer
{
public:
	MapLayer(const tmx::Map& map, std::size_t layerIdx, const std::vector<unsigned>& textures);
	~MapLayer();

	MapLayer(const MapLayer&) = delete;
	MapLayer& operator = (const MapLayer&) = delete;

	void draw(GLuint vertID, GLuint textID);

private:

	struct Subset
	{
		GLuint vbo = 0;
		GLuint texture = 0;
		GLuint lookup = 0;
	};

	const std::vector<unsigned>& tilesetTextures;
	std::vector<Subset> subsets;

	void createSubsets(const tmx::Map&, std::size_t);
};

#endif