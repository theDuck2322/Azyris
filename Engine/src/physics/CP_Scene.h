#pragma once

#include <Chipmunk2D/chipmunk/chipmunk.h>
#include <utils/Helpers.h>

namespace Az
{
	class CP_Scene
	{
	public:

		CP_Scene() = default;
		void CreateSpace(glm::vec2 gravity);
		void SetGravity(glm::vec2 gravity);


		inline cpSpace* GetSpace() { return m_Space; }

		void UpdateScene(float dt);

	private:

		cpSpace* m_Space;
		glm::vec2 m_Gravity;

	};
}