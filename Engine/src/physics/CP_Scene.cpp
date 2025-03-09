#include <CP_Scene.h>

namespace Az
{
	void CP_Scene::CreateSpace(glm::vec2 gravity)
	{
		m_Space = cpSpaceNew();
		cpSpaceSetGravity(m_Space, cpv(gravity.x, gravity.y));
	}
	void CP_Scene::SetGravity(glm::vec2 gravity)
	{
		cpSpaceSetGravity(m_Space, cpv(gravity.x, gravity.y));
	}
	void CP_Scene::UpdateScene(float dt)
	{
		cpSpaceStep(m_Space, dt);
	}
}