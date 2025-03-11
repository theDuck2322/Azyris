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

	//m_Colliders.emplace_back(glm::vec3(-3192, -1512, 0), glm::vec3(112, 784, 1));
	//m_Colliders.emplace_back(glm::vec3(-3192, -1512, 0), glm::vec3(112, 784, 1));
	//m_Colliders.emplace_back(glm::vec3(-3192, -1512, 0), glm::vec3(112, 784, 1));
	//m_Colliders.emplace_back(glm::vec3(-3192, -1512, 0), glm::vec3(112, 784, 1));


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
