#pragma once

#include <Chipmunk2D/chipmunk/chipmunk.h>
#include <utils/Helpers.h>


namespace Az
{
	enum class ColliderType
	{
		STATIC,
		DYNAMIC,
		KINEMATIC
	};


	class BoxCollider2D
	{
	public:
		BoxCollider2D() = default;

		static void SetScene(cpSpace* space);


		void CreateCollider(Az::Shapes::Rect& dst, ColliderType type = Az::ColliderType::STATIC);
		// u have to specify the center of the rect
		void CreateCollider(const glm::vec3& position, const glm::vec3& size, ColliderType type = Az::ColliderType::STATIC);

		void SetPosition(glm::vec3 position);
		void SetVelocity(glm::vec3 direction, float speed);

		glm::vec2 GetPosition();

	private:
		static cpSpace* m_Space;

	private:

		ColliderType m_ColliderType;

		//Az::Shapes::Rect m_DST;
		cpBody* m_Body;
		cpShape* m_Shape;
	};
}