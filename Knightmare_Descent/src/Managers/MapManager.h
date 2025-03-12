#pragma once

#include <Azyris.h>


class MapManager
{
public:
	MapManager();
	bool LoadMap();
	std::vector<Az::Rect>& GetLayers();
	std::vector<Az::Texture>& GetTextures();

	void CreateColliders();

	inline std::vector<Az::B2_BoxCollider>& GetColliders() { return m_Colliders; }

	// add this function after beginBatch(); and before endBacth();
	void RenderMap();

private:

	std::vector<Az::B2_BoxCollider> m_Colliders;
	std::vector<Az::Rect> m_Layers;
	std::vector<Az::Texture> m_Textures;

};