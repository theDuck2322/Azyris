#pragma once

#include <Azyris.h>
#include <Managers/AnimationManager.h>

enum class OrcAnimationType
{
	IDLE,
	WALK,
	ATTACK01,
	ATTACK02,
	HURT,
	DEATH
};

class OrcEnemy
{
public:

	OrcEnemy() = default;

	void Start(const glm::vec3& position);
	void Update();
	void Render();

	inline Az::Rect& GetDST() { return m_Dst; }
	inline Az::Rect& GetHitboxClip() { return m_HitBoxclip; }
	inline Az::Rect* GetSRC() { return &m_SRC; }

	inline void SetTexture(Az::Texture texture) { m_Texture = texture; }
	inline void SetTexture(const char* texturePath) { m_Texture.loadFromFile(texturePath); }

	inline Az::Texture& GetTexture() { return m_Texture; }

private: // A section for private function
	void InitAnimManager();
	void InitAnimations();

	void HandleAnimation();


private: // basic entity variables

	Az::B2_BoxCollider m_Collider;

	glm::vec3 m_Direction = GLM_VEC3_ZERO;
	Az::Rect m_Dst;
	Az::Rect m_SRC;
	Az::Rect m_HitBoxclip; // for wall & map collisions

	Az::Texture m_Texture;

	bool m_IsFlippedX = false;


private: // Animation and states

	Az::AnimationManager m_AnimManager;

	//PlayerAnimationType m_AnimType;

	Az::AnimationInfo m_Idle;
	Az::AnimationInfo m_Walk;
	Az::AnimationInfo m_Attack01;
	Az::AnimationInfo m_Attack02;
	Az::AnimationInfo m_Hurt;
	Az::AnimationInfo m_Death;

};