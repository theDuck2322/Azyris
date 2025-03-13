#include "zAnimationManager.h"


zAnimationManager::zAnimationManager(AnimationManagerDef& animDef)
{
	init(animDef);
}

void zAnimationManager::init(AnimationManagerDef& animDef)
{
	// Const variable initialization;
	m_SpriteStartX = animDef.SpriteStartX;
	m_SpriteStartY = animDef.SpriteStartY;

	m_SpriteSizeX = animDef.SpriteSizeX;
	m_SpriteSizeY = animDef.SpriteSizeY;

	m_SpriteOffsetX = animDef.SpriteOffsetX;
	m_SpriteOffsetY = animDef.SpriteOffsetY;

	m_FrameDuration = animDef.FrameDuration;

	m_SpritesPerLine = animDef.SpritesPerLine;
	m_Columns = animDef.Columns;

	// CurrentSRC initialization;
	m_CurrentSRC.Position.x = m_SpriteStartX;
	m_CurrentSRC.Position.y = m_SpriteStartY;
	m_CurrentSRC.Size.x = m_SpriteSizeX;
	m_CurrentSRC.Size.y = m_SpriteSizeY;

	// Other vatiable initialization;
	m_CurrentTime = 0;
	m_CurrentFrame = 0;

	m_CurrentFrameX = 0;
	m_CurrentFrameY = 0;

	m_AnimDefIsInit = true;
}

Az::Rect zAnimationManager::getFrameSRC()
{
	return m_CurrentSRC;
}

void zAnimationManager::Update()
{

	if (m_CurrentTime < m_FrameDuration)
	{
		m_CurrentTime += Az::Timer::deltaTime;
	}
	else
	{
		m_CurrentFrameX++;
		if (m_CurrentFrameX >= m_SpritesPerLine)
		{
			m_CurrentFrameX = 0;
			m_CurrentFrameY++;
			if (m_CurrentFrameY >= m_Columns)
			{
				m_CurrentFrameY = 0;
			}
		}

		m_CurrentSRC.Position.x = m_SpriteStartX + (m_CurrentFrameX * (m_SpriteOffsetX + m_SpriteSizeX));
		m_CurrentSRC.Position.x = m_SpriteStartY + (m_CurrentFrameY * (m_SpriteOffsetY + m_SpriteSizeY));
		m_CurrentTime = 0;
	}
}

bool zAnimationManager::RunAnimation(AnimationInfo& info)
{
	AZ_Assert(m_AnimDefIsInit != false, "AnimationManager is NOT initialized");

	uint32_t endFrameX = info.EndFrameX / m_SpriteSizeX;
	uint32_t endFrameY = info.EndFrameY / m_SpriteSizeY;

	int srcX = 0;
	int srcY = 0;

	bool animationIsFinished = false;

	if (m_CurrentTime < info.FrameDuration)
	{
		m_CurrentTime += Az::Timer::deltaTime;
	}
	else
	{
		m_CurrentFrameX++;
		if (m_CurrentFrameX >= endFrameX)
		{
			m_CurrentFrameX = 0;
			m_CurrentFrameY++;
			if (m_CurrentFrameY >= endFrameY)
			{
				animationIsFinished = true;
				m_CurrentFrameY = 0;
			}
		}

		//m_CurrentSRC.Position.x = info.FirstFrameX + (m_CurrentFrameX * (m_SpriteOffsetX + m_SpriteSizeX));
		//m_CurrentSRC.Position.x = info.FirstFrameY + (m_CurrentFrameY * (m_SpriteOffsetY + m_SpriteSizeY));
		srcX = info.FirstFrameX + (m_CurrentFrameX * (m_SpriteOffsetX + m_SpriteSizeX));
		srcY = info.FirstFrameY + (m_CurrentFrameY * (m_SpriteOffsetY + m_SpriteSizeY));

		m_CurrentSRC.Position.x = srcX;
		m_CurrentSRC.Position.y = srcY;
		m_CurrentTime = 0;

	}
	return animationIsFinished;

}
