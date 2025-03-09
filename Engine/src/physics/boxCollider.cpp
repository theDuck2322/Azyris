#include "boxCollider.h"


namespace Az
{

	cpSpace* BoxCollider2D::m_Space = nullptr;

	void BoxCollider2D::SetScene(cpSpace* space)
	{
		m_Space = space;
	}

	void BoxCollider2D::CreateCollider(Az::Shapes::Rect& dst, ColliderType type)
	{
		AZ_Assert(m_Space != nullptr, "Scene is nullptr");

		CreateCollider(dst.Position, dst.Size, type);
	}
	void BoxCollider2D::CreateCollider(const glm::vec3& position, const glm::vec3& size, ColliderType type)
	{
		AZ_Assert(m_Space != nullptr, "Scene is nullptr");

		m_ColliderType = type;

		if (type == Az::ColliderType::STATIC)
		{

			m_Body = cpSpaceGetStaticBody(m_Space);
			cpBodySetPosition(m_Body, cpv(position.x, position.y));
			m_Shape = cpBoxShapeNew(m_Body, size.x, size.y, 0);

			cpShapeSetFriction(m_Shape, 1.0f);
			cpShapeSetElasticity(m_Shape, 0.0f); // No bounce
			cpShapeSetCollisionType(m_Shape, 1);
			cpSpaceAddShape(m_Space, m_Shape);

		}
		else if (type == Az::ColliderType::DYNAMIC)
		{

			m_Body = cpSpaceAddBody(m_Space, cpBodyNew(1.0f, cpMomentForBox(1.0f, size.x, size.y)));
			cpBodySetPosition(m_Body, cpv(position.x, position.y));
			
			m_Shape = cpBoxShapeNew(m_Body, size.x, size.y, 0);
			cpShapeSetFriction(m_Shape, 0.7f);
			cpShapeSetElasticity(m_Shape, 0.0f); // No bounce
			cpShapeSetCollisionType(m_Shape, 2);
			cpSpaceAddShape(m_Space, m_Shape);

		}
		else //type = Az::ColliderType::KINEMATIC
 		{
			
			m_Body = cpSpaceAddBody(m_Space, cpBodyNewKinematic());
			cpBodySetPosition(m_Body, cpv(position.x, position.y));
			cpBodySetVelocity(m_Body, cpvzero);

			m_Shape = cpBoxShapeNew(m_Body, size.x, size.y, 0);
			cpShapeSetElasticity(m_Shape, 0.0f); // No bounce
			cpShapeSetCollisionType(m_Shape, 3);
			cpSpaceAddShape(m_Space, m_Shape);

		}
	}

	void BoxCollider2D::SetPosition(glm::vec3 position)
	{
		AZ_Assert(m_ColliderType != Az::ColliderType::STATIC, "Collider is STATIC!!");
		
		cpBodySetPosition(m_Body, cpv(position.x, position.y));

	}
	void BoxCollider2D::SetVelocity(glm::vec3 direction, float speed)
	{
		AZ_Assert(m_ColliderType != Az::ColliderType::STATIC, "Collider is STATIC!!");

		cpBodySetVelocity(m_Body, cpvmult(cpv(direction.x, direction.y), speed));

	}

	glm::vec2 BoxCollider2D::GetPosition()
	{
		cpVect pos = cpBodyGetPosition(m_Body);
		return glm::vec2(pos.x, pos.y);
	}
}

