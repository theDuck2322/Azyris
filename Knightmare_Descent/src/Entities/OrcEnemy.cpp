#include <OrcEnemy.h>



void OrcEnemy::Start(const glm::vec3& position)
{
	m_Dst.Position = glm::vec3(position);
	m_Dst.Size = glm::vec3(250, 250 * (29.0f / 48.0f), 0);
	m_Dst.rotation = 0;

	InitAnimManager();
	InitAnimations();
}

void OrcEnemy::Update()
{
	HandleAnimation();
}

void OrcEnemy::Render()
{
	Az::Renderer::DrawQuad(m_Dst, &m_SRC, m_Texture, m_IsFlippedX);
}


// PRIVATE FUNCTION IMPLEMENTATION



void OrcEnemy::InitAnimManager()
{
	Az::AnimationManagerDef def{};
	def.spriteSizeX = 48;
	def.spriteSizeY = 29;

	def.spriteCountX = 43;
	def.spriteCountY = 1;
	m_AnimManager.Init(def);
}

void OrcEnemy::InitAnimations()
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

	m_Hurt.startFrameX = 27 * 48;
	m_Hurt.startFrameY = 0;
	m_Hurt.endFrameX = 4 * 48;
	m_Hurt.endFrameY = 0;
	m_Hurt.frameDuration = 0.2f;

	m_Death.startFrameX = 31 * 48;
	m_Death.startFrameY = 0;
	m_Death.endFrameX = 4 * 48;
	m_Death.endFrameY = 0;
	m_Death.frameDuration = 0.2f;
}

void OrcEnemy::HandleAnimation()
{
	m_AnimManager.BindInfo(m_Idle);

	m_AnimManager.RunAnimationLinear();

	m_SRC = m_AnimManager.GetFrameSRC();
}
