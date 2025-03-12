#include <MapManager.h>

MapManager::MapManager()
{
	m_Layers.resize(10);
	m_Textures.resize(10);
}

bool MapManager::LoadMap()
{
	m_Textures.resize(10);
	Az::Rect dst;
	int i = 0;

	dst.Position = glm::vec3(0, 0, -9.0f);
	dst.Position = glm::vec3(0, 0, -9);
	dst.Size = glm::vec3(1024 * 7);

	Az::Texture ground;
	ground.loadFromFile("Knightmare_Descent/Assets/Maps/Cavern_01/Cavern_01_Ground.png");
	m_Layers.push_back(dst);
	m_Textures.push_back(ground);

	Az::Texture walls_low;
	walls_low.loadFromFile("Knightmare_Descent/Assets/Maps/Cavern_01/Cavern_01_Walls_Lower.png");
	dst.Position.z = -8.0f;
	m_Layers.push_back(dst);
	m_Textures.push_back(walls_low);

	Az::Texture walls_high;
	walls_high.loadFromFile("Knightmare_Descent/Assets/Maps/Cavern_01/Cavern_01_Walls_Upper.png");
	dst.Position.z = 8.0f;
	m_Layers.push_back(dst);
	m_Textures.push_back(walls_high);

	Az::Texture doors_low;
	doors_low.loadFromFile("Knightmare_Descent/Assets/Maps/Cavern_01/Cavern_01_Doors_Lower.png");
	dst.Position.z = -7.0f;
	m_Layers.push_back(dst);
	m_Textures.push_back(doors_low);

	Az::Texture doors_high;
	doors_high.loadFromFile("Knightmare_Descent/Assets/Maps/Cavern_01/Cavern_01_Doors_Upper.png");
	dst.Position.z = 10.0f;
	m_Layers.push_back(dst);
	m_Textures.push_back(doors_high);

	Az::Texture pillar_low;
	pillar_low.loadFromFile("Knightmare_Descent/Assets/Maps/Cavern_01/Cavern_01_Pillar_Lower.png");
	dst.Position.z = -2.0f;
	m_Layers.push_back(dst);
	m_Textures.push_back(pillar_low);

	Az::Texture pillar_middle;
	pillar_middle.loadFromFile("Knightmare_Descent/Assets/Maps/Cavern_01/Cavern_01_Pillar_Middle.png");
	dst.Position.z = -1.0f;
	m_Layers.push_back(dst);
	m_Textures.push_back(pillar_middle);

	Az::Texture pillar_high;
	pillar_high.loadFromFile("Knightmare_Descent/Assets/Maps/Cavern_01/Cavern_01_Pillar_Upper.png");
	dst.Position.z = 10.0f;
	m_Layers.push_back(dst);
	m_Textures.push_back(pillar_high);

	return EXIT_SUCCESS;
}

std::vector<Az::Rect>& MapManager::GetLayers()
{
	return m_Layers;
}

std::vector<Az::Texture>& MapManager::GetTextures()
{
	return m_Textures;
}

void MapManager::CreateColliders()
{
	m_Colliders.emplace_back(glm::vec3(-2296, 840, 0), glm::vec3(2128, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-3304, 392, 0), glm::vec3(112, 784, 1));
	m_Colliders.emplace_back(glm::vec3(-2688, 56, 0), glm::vec3(1120, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-2184, -112, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(-2912, -168, 0), glm::vec3(1344, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-3528, -504, 0), glm::vec3(112, 560, 1));
	m_Colliders.emplace_back(glm::vec3(-2912, -728, 0), glm::vec3(1120, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-2408, -952, 0), glm::vec3(112, 336, 1));
	m_Colliders.emplace_back(glm::vec3(-2856, -1064, 0), glm::vec3(784, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-3192, -1512, 0), glm::vec3(112, 784, 1));
	m_Colliders.emplace_back(glm::vec3(-2464, -1848, 0), glm::vec3(1344, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-1848, -1400, 0), glm::vec3(112, 784, 1));
	m_Colliders.emplace_back(glm::vec3(-2016, -1064, 0), glm::vec3(224, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-2072, -840, 0), glm::vec3(112, 336, 1));
	m_Colliders.emplace_back(glm::vec3(-1736, -728, 0), glm::vec3(560, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-1512, -560, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(-1120, -504, 0), glm::vec3(672, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-840, -840, 0), glm::vec3(112, 560, 1));
	m_Colliders.emplace_back(glm::vec3(-1120, -1064, 0), glm::vec3(448, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-1288, -1512, 0), glm::vec3(112, 784, 1));
	m_Colliders.emplace_back(glm::vec3(-560, -1848, 0), glm::vec3(1344, 112, 1));
	m_Colliders.emplace_back(glm::vec3(56, -1680, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(336, -1624, 0), glm::vec3(448, 112, 1));
	m_Colliders.emplace_back(glm::vec3(504, -1456, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(896, -1400, 0), glm::vec3(672, 112, 1));
	m_Colliders.emplace_back(glm::vec3(1176, -1624, 0), glm::vec3(112, 336, 1));
	m_Colliders.emplace_back(glm::vec3(2016, -1736, 0), glm::vec3(1568, 112, 1));
	m_Colliders.emplace_back(glm::vec3(2744, -392, 0), glm::vec3(112, 2576, 1));
	m_Colliders.emplace_back(glm::vec3(1904, 840, 0), glm::vec3(1568, 112, 1));
	m_Colliders.emplace_back(glm::vec3(1176, 616, 0), glm::vec3(112, 336, 1));
	m_Colliders.emplace_back(glm::vec3(952, 504, 0), glm::vec3(336, 112, 1));
	m_Colliders.emplace_back(glm::vec3(840, 728, 0), glm::vec3(112, 336, 1));
	m_Colliders.emplace_back(glm::vec3(-56, 840, 0), glm::vec3(1680, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-840, 616, 0), glm::vec3(112, 336, 1));
	m_Colliders.emplace_back(glm::vec3(-1288, 672, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(-1120, 504, 0), glm::vec3(448, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-1064, 280, 0), glm::vec3(560, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-1288, 112, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(-1624, 56, 0), glm::vec3(560, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-1848, -112, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(-1624, -168, 0), glm::vec3(336, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-840, -280, 0), glm::vec3(1456, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-168, -448, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(-392, -504, 0), glm::vec3(336, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-504, -840, 0), glm::vec3(112, 560, 1));
	m_Colliders.emplace_back(glm::vec3(-168, -1064, 0), glm::vec3(560, 112, 1));
	m_Colliders.emplace_back(glm::vec3(112, -1232, 0), glm::vec3(224, 224, 1));
	m_Colliders.emplace_back(glm::vec3(168, -560, 0), glm::vec3(112, 1120, 1));
	m_Colliders.emplace_back(glm::vec3(504, -616, 0), glm::vec3(112, 1232, 1));
	m_Colliders.emplace_back(glm::vec3(896, -1176, 0), glm::vec3(672, 112, 1));
	m_Colliders.emplace_back(glm::vec3(1176, -392, 0), glm::vec3(112, 1456, 1));
	m_Colliders.emplace_back(glm::vec3(952, 280, 0), glm::vec3(336, 112, 1));
	m_Colliders.emplace_back(glm::vec3(840, 56, 0), glm::vec3(112, 336, 1));
	m_Colliders.emplace_back(glm::vec3(672, -56, 0), glm::vec3(224, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-392, -56, 0), glm::vec3(1008, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-840, 112, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(-2968, 392, 0), glm::vec3(112, 112, 1));
	m_Colliders.emplace_back(glm::vec3(-1848, 392, 0), glm::vec3(112, 112, 1));
	m_Colliders.emplace_back(glm::vec3(1624, 336, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(2296, 336, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(1624, -224, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(2296, -224, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(1624, -784, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(2296, -784, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(1624, -1344, 0), glm::vec3(112, 224, 1));
	m_Colliders.emplace_back(glm::vec3(2296, -1344, 0), glm::vec3(112, 224, 1));
}

void MapManager::RenderMap()
{
	AZ_Assert(Az::Renderer::batchRunning() != false, "Function added incorectly");

	int minSize = min(m_Layers.size(), m_Textures.size());

	for (int i = 0; i < minSize; i++)
	{
		Az::Renderer::DrawQuad(m_Layers[i], nullptr, m_Textures[i]);
	}

}
