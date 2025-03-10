#include "zPlayer.h"


void zPlayer::Start()
{
	m_Dst.Position = glm::vec3(0, 0, 0);
	m_Dst.Size = glm::vec3(250, 250 * (29.0f / 48.0f), 0);
	m_Dst.rotation = 0;
	initAnimManager();
	initAnimations();

	//m_Collider.CreateCollider(m_Dst, Az::CP_ColliderType::DYNAMIC);
	//cpBodySetAngle(m_Collider.GetBody(), 0.0f);

	m_Collider.CreateCollider(m_Dst, Az::B2_ColliderType::DYNAMIC);
}

void zPlayer::Update()
{
	getDirection();
	Move();
	handleAnimation();
}

void zPlayer::initAnimManager()
{
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

	m_AnimManager = AnimationManager(def);
}

void zPlayer::initAnimations()
{
	m_Idle.FirstFrameX = 0;
	m_Idle.FirstFrameY = 0;
	m_Idle.EndFrameX = 6 * 48;
	m_Idle.FirstFrameY = 0;
	m_Idle.FrameDuration = 0.2f;

	m_Walk.FirstFrameX = 7 * 48;
	m_Walk.FirstFrameY = 0;
	m_Walk.EndFrameX = 8 * 28;
	m_Walk.FirstFrameY = 0;
	m_Walk.FrameDuration = 0.1f;

	m_Attack01.FirstFrameX = 15 * 48;
	m_Attack01.FirstFrameY = 0;
	m_Attack01.EndFrameX = 6 * 48;
	m_Attack01.FirstFrameY = 0;
	m_Attack01.FrameDuration = 0.2f;

	m_Attack02.FirstFrameX = 21 * 48;
	m_Attack02.FirstFrameY = 0;
	m_Attack02.EndFrameX = 5 * 48;
	m_Attack02.FirstFrameY = 0;
	m_Attack02.FrameDuration = 0.2f;

	m_Attack03.FirstFrameX = 27 * 48;
	m_Attack03.FirstFrameY = 0;
	m_Attack03.EndFrameX = 8 * 48;
	m_Attack03.FirstFrameY = 0;
	m_Attack03.FrameDuration = 0.2f;

	m_Hurt.FirstFrameX = 36 * 48;
	m_Hurt.FirstFrameY = 0;
	m_Hurt.EndFrameX = 4 * 48;
	m_Hurt.FirstFrameY = 0;
	m_Hurt.FrameDuration = 0.2f;

	m_Death.FirstFrameX = 40 * 48;
	m_Death.FirstFrameY = 0;
	m_Death.EndFrameX = 4 * 48;
	m_Death.FirstFrameY = 0;
	m_Death.FrameDuration = 0.2f;
}

void zPlayer::getDirection()
{
	m_Direction = glm::vec3(0);
	if (Az::Input::GetKey(AZ_w) && !Az::Input::GetKey(AZ_s))
	{
		m_Direction.y = 1;
	}
	if (Az::Input::GetKey(AZ_s) && !Az::Input::GetKey(AZ_w))
	{
		m_Direction.y = -1;
	}
	if (Az::Input::GetKey(AZ_a) && !Az::Input::GetKey(AZ_d))
	{
		m_Direction.x = -1;
	}
	if (Az::Input::GetKey(AZ_d) && !Az::Input::GetKey(AZ_a))
	{
		m_Direction.x = 1;
	}
}

void zPlayer::Move()
{
	m_Collider.SetVelocity(m_Direction, Speed);

	glm::vec2 pos = glm::vec2(0.0f);

	pos = m_Collider.GetPosition();
	m_Dst.Position.x = pos.x;
	m_Dst.Position.y = pos.y;

	//cpBodySetAngle(m_Collider.GetBody(), 0.0f);

	m_Dst.rotation = m_Collider.GetAngle();

	if (m_Direction.x == 1)
		m_IsFlippedX = false;
	if (m_Direction.x == -1)
		m_IsFlippedX = true;
}

void zPlayer::handleAnimation()
{
	if (m_Direction.x == 0 && m_Direction.y == 0)
	{
		m_AnimType = PlayerAnimationType::IDLE;
	}
	else m_AnimType = PlayerAnimationType::WALK;

	switch (m_AnimType)
	{
	case PlayerAnimationType::IDLE:
		m_AnimManager.RunAnimation(m_Idle);
		break;
	case PlayerAnimationType::WALK:
		m_AnimManager.RunAnimation(m_Walk);
		break;
	case PlayerAnimationType::ATTACK01:
		m_AnimManager.RunAnimation(m_Attack01);
		break;
	case PlayerAnimationType::ATTACK02:
		m_AnimManager.RunAnimation(m_Attack02);
		break;
	case PlayerAnimationType::ATTACK03:
		m_AnimManager.RunAnimation(m_Attack03);
		break;
	case PlayerAnimationType::HURT:
		m_AnimManager.RunAnimation(m_Hurt);
		break;
	case PlayerAnimationType::DEATH:
		m_AnimManager.RunAnimation(m_Death);
		break;
	default:
		m_AnimManager.RunAnimation(m_Idle);
		break;
	}

	m_SRC = m_AnimManager.getFrameSRC();

}


