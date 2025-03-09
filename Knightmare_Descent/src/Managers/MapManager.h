#pragma once

#include <Azyris.h>


class MapManager
{
public:
	MapManager();
	bool LoadMap();
	std::vector<Az::Rect>& GetLayers();
	std::vector<Az::Texture>& GetTextures();

	// add this function after beginBatch(); and before endBacth();
	void RenderMap();

private:

	std::vector<Az::Rect> m_Layers;
	std::vector<Az::Texture> m_Textures;

};