#pragma once

#include <Chipmunk2D/chipmunk/chipmunk.h>
#include <utils/Helpers.h>


namespace Az
{
	enum class CP_ColliderType
	{
		STATIC,
		DYNAMIC,
		KINEMATIC
	};


	class CP_BoxCollider2D
	{
	public:
		CP_BoxCollider2D() = default;

		static void SetScene(cpSpace* space);


		void CreateCollider(Az::Rect& dst, CP_ColliderType type = Az::CP_ColliderType::STATIC);
		void CreateCollider(const glm::vec3& position, const glm::vec3& size, CP_ColliderType type = Az::CP_ColliderType::STATIC);

		void SetPosition(glm::vec3 position);
		void SetVelocity(glm::vec3 direction, float speed);

		inline float GetAngle() { return Az::toDegrees(cpBodyGetAngle(m_Body)); }

		inline cpBody* GetBody() { return m_Body; }
		inline cpShape* GetShape() { return m_Shape; }

		glm::vec2 GetPosition();

	private:
		static cpSpace* m_Space;

	private:

		CP_ColliderType m_ColliderType;

		//Az::Shapes::Rect m_DST;
		cpBody* m_Body;
		cpShape* m_Shape;
	};
}