#pragma once

#include <Azyris.h>
#include <Managers/AnimationManager.h>

enum class PlayerAnimationType
{
	IDLE,
	WALK,
	ATTACK01,
	ATTACK02,
	ATTACK03,
	HURT,
	DEATH
};

class zPlayer
{
public:
	zPlayer() = default;

	inline Az::Rect& GetDST() { return m_Dst; }
	inline Az::Rect& GetHitboxClip() { return m_HitBoxclip; }
	inline Az::Rect* GetSRC() { return &m_SRC; }

	inline bool playerFlipped() { return m_IsFlippedX; }

	void Start();
	void Update();

	inline void SetTexture(Az::Texture texture) { m_Texture = texture; }
	inline void SetTexture(const char* texturePath) { m_Texture.loadFromFile(texturePath); }

	inline Az::Texture& GetTexture() { return m_Texture; }
public:

	float health = 100;
	float Speed = 500;

private:

	void initAnimManager();
	void initAnimations();
	void getDirection();
	void Move();
	void handleAnimation();


	//Az::CP_BoxCollider2D m_Collider;
	Az::B2_BoxCollider m_Collider;

	glm::vec3 m_Direction = GLM_VEC3_ZERO;
	Az::Rect m_Dst;
	Az::Rect m_SRC;
	Az::Rect m_HitBoxclip; // for wall & map collisions

	Az::Texture m_Texture;

	bool m_IsFlippedX = false;

private:


	AnimationManager m_AnimManager;

	PlayerAnimationType m_AnimType;

	AnimationInfo m_Idle;
	AnimationInfo m_Walk;
	AnimationInfo m_Attack01;
	AnimationInfo m_Attack02;
	AnimationInfo m_Attack03;
	AnimationInfo m_Hurt;
	AnimationInfo m_Death;


};