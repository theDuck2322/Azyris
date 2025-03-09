#include <AZScene.h>

namespace Az
{
	void Scene::CreateSpace(glm::vec2 gravity)
	{
		m_Space = cpSpaceNew();
		cpSpaceSetGravity(m_Space, cpv(gravity.x, gravity.y));
	}
	void Scene::SetGravity(glm::vec2 gravity)
	{
		cpSpaceSetGravity(m_Space, cpv(gravity.x, gravity.y));
	}
	void Scene::UpdateScene(float dt)
	{
		cpSpaceStep(m_Space, dt);
	}
}