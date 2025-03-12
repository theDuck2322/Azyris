#include <physics/B2_BoxCollider.h>


namespace Az
{
	b2World* B2_BoxCollider::m_World = nullptr;


	B2_BoxCollider::B2_BoxCollider(Az::Rect& dst, B2_ColliderType type)
	{
		CreateCollider(dst, type);
	}

	B2_BoxCollider::B2_BoxCollider(const glm::vec3& position, const glm::vec3& size, float degree, B2_ColliderType type)
	{
		CreateCollider(position, size, degree, type);
	}

	void B2_BoxCollider::SetScene(b2World* scene)
	{
		m_World = scene;
	}

	void B2_BoxCollider::CreateCollider(Az::Rect& dst, B2_ColliderType type)
	{
		AZ_Assert(m_World != nullptr, "Scene reference is nullptr");
		CreateCollider(dst.Position, dst.Size, dst.rotation, type);
		
	}

	void B2_BoxCollider::CreateCollider(const glm::vec3& position, const glm::vec3& size, float degree, B2_ColliderType type)
	{
		AZ_Assert(m_World != nullptr, "Scene reference is nullptr");

		m_DrawableHitbox.Position = position;
		m_DrawableHitbox.Size = size;
		m_DrawableHitbox.rotation = degree;

		if (type == B2_ColliderType::STATIC)
		{
			m_BodyDef.type = b2_staticBody;
			m_BodyDef.position = b2Vec2(PixelsToMeters(position.x), PixelsToMeters(position.y));
			m_BodyDef.angle = toRadians(degree);

			m_Body = m_World->CreateBody(&m_BodyDef);
			m_Shape.SetAsBox(PixelsToMeters(size.x / 2), PixelsToMeters(size.y / 2));

			m_Body->CreateFixture(&m_Shape, 1.0f);

		}
		else if (type == B2_ColliderType::DYNAMIC)
		{
			m_BodyDef.type = b2_dynamicBody;
			m_BodyDef.position = b2Vec2(PixelsToMeters(position.x), PixelsToMeters(position.y));
			m_BodyDef.angle = toRadians(degree);

			m_Body = m_World->CreateBody(&m_BodyDef);
			m_Shape.SetAsBox(PixelsToMeters(size.x / 2), PixelsToMeters(size.y / 2));

			m_FixtureDef.density = 1.0f;
			m_FixtureDef.friction = 0.3f;
			m_FixtureDef.shape = &m_Shape;

			m_Body->CreateFixture(&m_FixtureDef);

		}
		else // type == B2_ColliderType::KINEMATIC
		{
			m_BodyDef.type = b2_kinematicBody;
			m_BodyDef.position = b2Vec2(PixelsToMeters(position.x), PixelsToMeters(position.y));
			m_BodyDef.angle = toRadians(degree);

			m_Body = m_World->CreateBody(&m_BodyDef);
			m_Shape.SetAsBox(PixelsToMeters(size.x / 2), PixelsToMeters(size.y / 2));

			m_FixtureDef.density = 1.0f;
			m_FixtureDef.friction = 0.3f;
			m_FixtureDef.shape = &m_Shape;

			m_Body->CreateFixture(&m_FixtureDef);
		}
	}

	void B2_BoxCollider::SetVelocity(const glm::vec3& direction, float speed)
	{
		AZ_Assert(m_World != nullptr, "Scene reference is nullptr");

		b2Vec2 velocity = b2Vec2(direction.x * PixelsToMeters(speed), direction.y * PixelsToMeters(speed));

		m_Body->SetLinearVelocity(velocity);

	}

	void B2_BoxCollider::SetPosition(const glm::vec3& position)
	{
		AZ_Assert(m_World != nullptr, "Scene reference is nullptr");
		
		float rotation = m_Body->GetAngle();
		b2Vec2 pos = b2Vec2(PixelsToMeters(position.x), PixelsToMeters(position.y));

		m_Body->SetTransform(pos, rotation);
	}

	glm::vec2 B2_BoxCollider::GetPosition()
	{
		AZ_Assert(m_World != nullptr, "Scene reference is nullptr");

		b2Vec2 pos = m_Body->GetPosition();
		glm::vec2 position = glm::vec2(MetersToPixels(pos.x), MetersToPixels(pos.y));

		return position;
	}

	void B2_BoxCollider::SetAngle(float degrees)
	{
		AZ_Assert(m_World != nullptr, "Scene reference is nullptr");

		b2Vec2 position = m_Body->GetPosition();
		float radians = toRadians(degrees);

		m_Body->SetTransform(position, radians);

	}

	float B2_BoxCollider::GetAngle()
	{
		AZ_Assert(m_World != nullptr, "Scene reference is nullptr");

		return toDegrees(m_Body->GetAngle());
	}

}