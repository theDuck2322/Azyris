#pragma once

#include <Box2D/box2d/box2d.h>
#include <utils/Helpers.h>

namespace Az
{
	class B2_Scene
	{
	public:
		B2_Scene() = default;

		// set b2_linearSlop to 0.005f if there are some problems now it is set to 0.0005f

		void CreateScene(const glm::vec3& gravity);

		void SetGravity(const glm::vec3& gravity);

		void SetIterations(uint32_t velocityIterations = 6, uint32_t positionIterations = 3);

		void UpdateScene(float dt);

		inline b2World* GetScene() { return m_World; }

	private:

		b2World* m_World;

		uint32_t m_VelocityIterations;
		uint32_t m_PositionIterations;

	};
}