#include <AnimationManager.h>

namespace Az
{
	Az::AnimationManager::AnimationManager(AnimationManagerDef& def)
	{
		Init(def);
	}

	void Az::AnimationManager::Init(AnimationManagerDef def)
	{
		m_SpriteCountX = def.spriteCountX;
		m_SpriteCountY = def.spriteCountY;

		m_SpriteSizeX = def.spriteSizeX;
		m_SpriteSizeY = def.spriteSizeY;

		m_Src.Size.x = m_SpriteSizeX;
		m_Src.Size.y = m_SpriteSizeY;

		m_ManagerIsInitialized = true;
	}

	bool AnimationManager::RunAnimationLinear(AnimationInfo& info)
	{
		AZ_Assert(m_ManagerIsInitialized == true, "Animation Manager is not initialized!!");

		uint32_t endFrameX = info.endFrameX / m_SpriteSizeX;

		m_AnimationIsFinished = false;


		m_CurrentTime += Az::Timer::deltaTime;
		
		if(m_CurrentTime > info.frameDuration)
		{
			m_CurrentTime = 0;
			m_CurrentFrameX++;
			if (m_CurrentFrameX >= endFrameX)
			{
				m_CurrentFrameX = 0;
				
				m_AnimationIsFinished = true;
				
			}
			m_Src.Position.x = info.startFrameX + (m_CurrentFrameX * (0 + m_SpriteSizeX));
			m_Src.Position.y = info.startFrameY;

		}

		return m_AnimationIsFinished;
	}

	bool AnimationManager::RunAnimation()
	{
		AZ_Assert(false, "FUNCTION IS NOT IMPLEMENTED");
		return false;
	}

	void AnimationManager::ResetFrameTime()
	{
		m_CurrentTime = 0;
	}

}