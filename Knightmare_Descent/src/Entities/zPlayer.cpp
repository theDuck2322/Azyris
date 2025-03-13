#include "zPlayer.h"


void zPlayer::Start()
{
	m_Dst.Position = glm::vec3(-2520, -1512, 0);
	m_Dst.Size = glm::vec3(250, 250 * (29.0f / 48.0f), 0);
	m_Dst.rotation = 0;

	m_HitBoxclip.Position = glm::vec3(-2520, -1502, 0);
	m_HitBoxclip.Size = glm::vec3(80, 40, 1);
	m_HitBoxclip.rotation = 0;

	initAnimManager();
	initAnimations();

	m_Collider.CreateCollider(m_HitBoxclip, Az::B2_ColliderType::DYNAMIC);
	m_Collider.GetBody()->SetFixedRotation(true);
}

void zPlayer::Update()
{
	getDirection();
	Move();
	Attack();
	handleAnimation();
	//RunAnimations();
}

void zPlayer::getDirection()
{
	m_Direction = glm::vec3(0);
	m_IsMoving = false;

	if (Az::Input::GetKey(AZ_w) && !Az::Input::GetKey(AZ_s))
	{
		m_Direction.y = 1;
		m_IsMoving = true;
	}
	if (Az::Input::GetKey(AZ_s) && !Az::Input::GetKey(AZ_w))
	{
		m_Direction.y = -1;
		m_IsMoving = true;
	}
	if (Az::Input::GetKey(AZ_a) && !Az::Input::GetKey(AZ_d))
	{
		m_Direction.x = -1;
		m_IsMoving = true;
	}
	if (Az::Input::GetKey(AZ_d) && !Az::Input::GetKey(AZ_a))
	{
		m_Direction.x = 1;
		m_IsMoving = true;
	}
}

void zPlayer::Move()
{
	m_Collider.SetVelocity(m_Direction, Speed);

	glm::vec2 pos = glm::vec2(0.0f);

	pos = m_Collider.GetPosition();
	m_HitBoxclip.Position.x = pos.x;
	m_HitBoxclip.Position.y = pos.y;
	m_Dst.Position.x = pos.x;
	m_Dst.Position.y = pos.y+50;

	//cpBodySetAngle(m_Collider.GetBody(), 0.0f);

	m_Dst.rotation = m_Collider.GetAngle();

	if (m_Direction.x == 1)
		m_IsFlippedX = false;
	if (m_Direction.x == -1)
		m_IsFlippedX = true;
}

void zPlayer::handleAnimation()
{
	// Priority Order:
	// 1. Death
	// 2. Hurt
	// 3. Attack (Only one attack at a time)
	// 4. Walk
	// 5. Idle

	if (Health <= 0)
	{
		m_AnimType = PlayerAnimationType::DEATH;
		m_AnimManager.BindInfo(m_Death);

	}
	else if (m_IsAttacking)
	{

		m_CurrentFrameAttk += Az::Timer::deltaTime;
		if (m_CurrentFrameAttk >= m_AttackTimer)
		{
			m_IsAttacking = 0;
			m_AnimManager.ResetFrameTime();
		}
		else
		{
			m_AnimManager.BindInfo(m_Attack01);
		}
		
	}
	else if (m_IsMoving)
	{
		m_AnimManager.BindInfo(m_Walk);
	}
	else
	{
		m_AnimManager.BindInfo(m_Idle);
	}

	m_AnimManager.RunAnimationLinear();

	m_SRC = m_AnimManager.GetFrameSRC();

}

void zPlayer::Attack()
{
	if (Az::Input::GetMouseButtonDown(1) && !m_IsAttacking)
	{
		m_IsAttacking = true;
		m_AnimType = PlayerAnimationType::ATTACK01;
		m_CurrentFrameAttk = 0;
		if (m_AnimManager.AnimationIsFinished())
		{
			m_AnimManager.ResetFrameTime();  // Reset only if the animation finished
		}

	}

}

void zPlayer::RunAnimations()
{
	// Run the selected animation
	switch (m_AnimType)
	{
	case PlayerAnimationType::IDLE:
		m_AnimManager.RunAnimationLinear(m_Idle);
		break;
	case PlayerAnimationType::WALK:
		m_AnimManager.RunAnimationLinear(m_Walk);
		break;
	case PlayerAnimationType::ATTACK01:
		m_AnimManager.RunAnimationLinear(m_Attack01);
		break;
	case PlayerAnimationType::ATTACK02:
		m_AnimManager.RunAnimationLinear(m_Attack02);
		break;
	case PlayerAnimationType::ATTACK03:
		m_AnimManager.RunAnimationLinear(m_Attack03);
		break;
	case PlayerAnimationType::HURT:
		m_AnimManager.RunAnimationLinear(m_Hurt);
		break;
	case PlayerAnimationType::DEATH:
		m_AnimManager.RunAnimationLinear(m_Death);
		break;
	default:
		m_AnimManager.RunAnimationLinear(m_Idle);
		break;
	}

	m_SRC = m_AnimManager.GetFrameSRC();
}

void zPlayer::initAnimManager()
{
	/*
	AnimationManagerDef def{};

	def.SpriteStartX = 0 * 48; // 40
	def.SpriteStartY = 0; // 38

	def.SpriteSizeX = 48; // 17
	def.SpriteSizeY = 29; // 20

	def.SpriteOffsetX = 0; // 84
	def.SpriteOffsetY = 0;

	def.FrameDuration = 0.2;

	def.SpritesPerLine = 6;
	def.Columns = 1;

	m_AnimManager = zAnimationManager(def);
	*/


	Az::AnimationManagerDef def{};
	def.spriteSizeX = 48;
	def.spriteSizeY = 29;
	
	def.spriteCountX = 43;
	def.spriteCountY = 1;
	m_AnimManager.Init(def);
}

void zPlayer::initAnimations()
{
	m_Idle.startFrameX = 0;
	m_Idle.startFrameY = 0;
	m_Idle.endFrameX = 6 * 48;
	m_Idle.endFrameY = 0;
	m_Idle.frameDuration = 0.2f;

	m_Walk.startFrameX = 7 * 48;
	m_Walk.startFrameY = 0;
	m_Walk.endFrameX = 8 * 48;
	m_Walk.endFrameY = 0;
	m_Walk.frameDuration = 0.1f;

	m_Attack01.startFrameX = 15 * 48;
	m_Attack01.startFrameY = 0;
	m_Attack01.endFrameX = 6 * 48;
	m_Attack01.endFrameY = 0;
	m_Attack01.frameDuration = 0.2f;

	m_Attack02.startFrameX = 21 * 48;
	m_Attack02.startFrameY = 0;
	m_Attack02.endFrameX = 5 * 48;
	m_Attack02.endFrameY = 0;
	m_Attack02.frameDuration = 0.2f;

	m_Attack03.startFrameX = 27 * 48;
	m_Attack03.startFrameY = 0;
	m_Attack03.endFrameX = 8 * 48;
	m_Attack03.endFrameY = 0;
	m_Attack03.frameDuration = 0.2f;

	m_Hurt.startFrameX = 36 * 48;
	m_Hurt.startFrameY = 0;
	m_Hurt.endFrameX = 4 * 48;
	m_Hurt.endFrameY = 0;
	m_Hurt.frameDuration = 0.2f;

	m_Death.startFrameX = 40 * 48;
	m_Death.startFrameY = 0;
	m_Death.endFrameX = 4 * 48;
	m_Death.endFrameY = 0;
	m_Death.frameDuration = 0.2f;
}


