#pragma once

#include <Box2D/box2d/box2d.h>
#include <utils/Helpers.h>

namespace Az
{
	enum class B2_ColliderType
	{
		STATIC,
		DYNAMIC,
		KINEMATIC
	};


	class B2_BoxCollider
	{
	public:

		B2_BoxCollider() = default;
		B2_BoxCollider(Az::Rect& dst, B2_ColliderType type = B2_ColliderType::STATIC);
		B2_BoxCollider(const glm::vec3& position, const glm::vec3& size, float degree = 0, B2_ColliderType type = B2_ColliderType::STATIC);

		static void SetScene(b2World* scene);

		void CreateCollider(Az::Rect& dst, B2_ColliderType type = B2_ColliderType::STATIC);
		void CreateCollider(const glm::vec3& position, const glm::vec3& size, float degree = 0, B2_ColliderType type = B2_ColliderType::STATIC);

		// direction should be in range [-1, +1]
		void SetVelocity(const glm::vec3& direction, float speed);
		void SetPosition(const glm::vec3& position);

		glm::vec2 GetPosition();

		inline Az::Rect& GetHitbox() { return m_DrawableHitbox; }

		void SetAngle(float degree);
		float GetAngle();

		inline b2Body* GetBody() { return m_Body; }

	private:

		static b2World* m_World;

	private:

		Az::Rect m_DrawableHitbox;
		b2BodyDef m_BodyDef;
		b2Body* m_Body;
		b2PolygonShape m_Shape;
		b2FixtureDef m_FixtureDef;

		B2_ColliderType m_ColliderType;
	};

}