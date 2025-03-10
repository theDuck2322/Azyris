#include <physics/B2_Scene.h>

namespace Az
{
	void B2_Scene::CreateScene(const glm::vec3& gravity)
	{
		m_World = new b2World(b2Vec2(gravity.x, gravity.y));
	}
	void B2_Scene::SetGravity(const glm::vec3& gravity)
	{
		m_World->SetGravity(b2Vec2(gravity.x, gravity.y));
	}
	void B2_Scene::SetIterations(uint32_t velocityIterations, uint32_t positionIterations)
	{
		m_VelocityIterations = velocityIterations;
		m_PositionIterations = positionIterations;
	}
	void B2_Scene::UpdateScene(float dt)
	{
		m_World->Step(dt, m_VelocityIterations, m_PositionIterations);
	}
}