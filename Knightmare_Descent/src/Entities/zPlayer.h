#pragma once

#include <Azyris.h>
#include <Managers/AnimationManager.h>
#include <UI/Inventory.h>

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
public: // what this class has to offer
	zPlayer() = default;

	void Start();
	void Update();
	void Render();
	void RenderUI();

	inline Az::Rect& GetDST() { return m_Dst; }
	inline Az::Rect& GetHitboxClip() { return m_HitBoxclip; }
	inline Az::Rect* GetSRC() { return &m_SRC; }

	inline void SetTexture(Az::Texture texture) { m_Texture = texture; }
	inline void SetTexture(const char* texturePath) { m_Texture.loadFromFile(texturePath); }

	inline Az::Texture& GetTexture() { return m_Texture; }

	inline bool playerFlipped() { return m_IsFlippedX; }

public: // temporary variables

	float Health = 100;
	float Speed = 500;
	
	Inventory m_Inventory;


private: // A section for private function

	void InitAnimManager();
	void InitAnimations();
	void GetDirection();
	void Move();

	void HandleAnimation();
	void HandleInput();
	void Attack();


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

	PlayerAnimationType m_AnimType;

	Az::AnimationInfo m_Idle;
	Az::AnimationInfo m_Walk;
	Az::AnimationInfo m_Attack01;
	Az::AnimationInfo m_Attack02;
	Az::AnimationInfo m_Attack03;
	Az::AnimationInfo m_Hurt;
	Az::AnimationInfo m_Death;

	bool m_IsAttacking = false;
	bool m_IsMoving = false;
	float m_CurrentFrameAttk = 0;;
	float m_AttackTimer = 1.2f;
	bool m_IsInventory = false;
};