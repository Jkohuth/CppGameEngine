//map_layer.cpp

#include "map_layer.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <GLCheck.hpp>

#include <iostream>

MapLayer::MapLayer(const tmx::Map& map, std::size_t layerIdx, const std::vector<unsigned>& textures)
  : tilesetTextures (textures)
{
    createSubsets(map, layerIdx);
}
MapLayer::~MapLayer()
{
    for(auto& ss : subsets)
    {
        if(ss.vbo)
        {
            glDeleteBuffers(1, &ss.vbo);
        }
        if(ss.lookup)
        {
            glDeleteTextures(1, &ss.lookup);
        }
        //don't delete the tileset textures as these are
        //shared and deleted elsewhere
    }
}
void ::MapLayer::draw(GLuint vertID, GLuint textID)
{  
/*
    glEnableVertexAttribArray(vertID);
    glVertexAttribPointer(vertID, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(textID);
    glVertexAttribPointer(textID, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(float)));
*/ 
   glCheck(glEnableVertexAttribArray(vertID));
    glCheck(glEnableVertexAttribArray(textID));
    glCheck(glVertexAttribPointer(vertID, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0));
    glCheck(glVertexAttribPointer(textID, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
   
    for(const Subset& ss : subsets){
    
        glCheck(glActiveTexture(GL_TEXTURE0));
        glCheck(glBindTexture(GL_TEXTURE_2D, ss.texture));
        
        glCheck(glActiveTexture(GL_TEXTURE1));
        glCheck(glBindTexture(GL_TEXTURE_2D, ss.lookup));
        
        glCheck(glBindBuffer(GL_ARRAY_BUFFER, ss.vbo));
        glCheck(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
    }

    glCheck(glDisableVertexAttribArray(vertID));
    glCheck(glDisableVertexAttribArray(textID));
}

//private
void MapLayer::createSubsets(const tmx::Map& map, std::size_t layerIdx)
{
    const std::vector<tmx::Layer::Ptr>& layers = map.getLayers();
    if(layerIdx >= layers.size() || (layers[layerIdx]->getType() != tmx::Layer::Type::Tile))
    {
        std::cout << "Invalid layer index or layer type, layer will be empty" << std::endl;
        return;
    }
    const tmx::TileLayer* layer = dynamic_cast<const tmx::TileLayer*>(layers[layerIdx].get());
    
    tmx::FloatRect bounds = map.getBounds();
    float verts[] = 
    {
      bounds.left, bounds.top, 0.f, 0.f, 0.f,
      bounds.left + bounds.width, bounds.top, 0.f, 1.f, 0.f,
      bounds.left, bounds.top + bounds.height, 0.f, 0.f, 1.f,
      bounds.left + bounds.width, bounds.top + bounds.height, 0.f, 1.f, 1.f
    };
    
    const tmx::Vector2u& mapSize = map.getTileCount();
    const std::vector<tmx::Tileset>& tilesets = map.getTilesets();
    for(auto i = 0; i < tilesets.size(); ++i)
    {        
        //check each tile ID to see if it falls in the current tile set
        const tmx::Tileset& ts = tilesets[i];
//      const std::vector<Tile>& tileIDs = layer->getTiles();
        const auto& tileIDs = layer->getTiles();
        std::vector<std::uint16_t> pixelData;
        bool tsUsed = false;
        
        for(float y = 0; y < mapSize.y; ++y)
        {
            for(float x = 0; x < mapSize.x; ++x)
            {
                float idx = y * mapSize.x + x;
                if(idx < tileIDs.size() && tileIDs[idx].ID >= ts.getFirstGID()
                    && tileIDs[idx].ID < (ts.getFirstGID() + ts.getTileCount()))
                {
                    pixelData.push_back(static_cast<std::uint16_t>((tileIDs[idx].ID - ts.getFirstGID()) + 1)); //red channel - making sure to index relative to the tileset
                    pixelData.push_back(static_cast<std::uint16_t>(tileIDs[idx].flipFlags)); //green channel - tile flips are performed on the shader
                    tsUsed = true;
                }
                else
                {
                    //pad with empty space
                    pixelData.push_back(0);
                    pixelData.push_back(0);
                }
            }
        }
        
        //if we have some data for this tile set, create the resources
        if(tsUsed)
        {
            subsets.emplace_back();
            subsets.back().texture = tilesetTextures[i];
     
            glCheck(glGenBuffers(1, &subsets.back().vbo));
            glCheck(glBindBuffer(GL_ARRAY_BUFFER, subsets.back().vbo));
            glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW));
            
            glCheck(glGenTextures(1, &subsets.back().lookup));
            glCheck(glBindTexture(GL_TEXTURE_2D, subsets.back().lookup));
            glCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16UI, mapSize.x, mapSize.y, 0, GL_RG_INTEGER, GL_UNSIGNED_SHORT, (void*)pixelData.data()));

            glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
            glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
            glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
            glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
            

        }

    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}











