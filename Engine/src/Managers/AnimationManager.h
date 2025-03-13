#pragma once

#include <stdint.h>
#include <utils/Helpers.h>
#include <utils/Timer.h>

namespace Az
{

	struct AnimationManagerDef
	{
		float spriteSizeX = 0;
		float spriteSizeY = 0;

		uint32_t spriteCountX = 0;
		uint32_t spriteCountY = 0;
	};


	struct AnimationInfo
	{
		uint32_t startFrameX = 0;
		uint32_t startFrameY = 0;

		uint32_t endFrameX = 0;
		uint32_t endFrameY = 0;

		float frameDuration = 0;
	};

	class AnimationManager
	{
	public:

		AnimationManager() = default;
		AnimationManager(AnimationManagerDef& def);
		void Init(AnimationManagerDef def);


		void BindInfo(AnimationInfo& info);

		// if the atlas has 2D lists of sprites, it wont work
		bool RunAnimationLinear(AnimationInfo& info);
		bool RunAnimationLinear();

		inline bool AnimationIsFinished() { return m_AnimationIsFinished; }

		// doesnt work yet;
		bool RunAnimation();

		void ResetFrameTime();

		inline Az::Rect GetFrameSRC() { return m_Src; }

	private:

		AnimationInfo m_BindedInfo;

		bool m_InfoIsChanged = false;

		bool m_ManagerIsInitialized = false;
		bool m_AnimationIsFinished = false;

		float m_SpriteSizeX = 0;
		float m_SpriteSizeY = 0;

		uint32_t m_SpriteCountX = 0;
		uint32_t m_SpriteCountY = 0;

		Az::Rect m_Src;

		float m_CurrentTime = 0;
		uint32_t m_CurrentFrameX = 0;
		uint32_t m_CurrentFrameY = 0;

	};
};