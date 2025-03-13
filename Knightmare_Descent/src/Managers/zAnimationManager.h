#pragma once

#include <Azyris.h>

struct AnimationManagerDef
{
	float SpriteStartX;
	float SpriteStartY;

	float SpriteSizeX;
	float SpriteSizeY;

	float SpriteOffsetX;
	float SpriteOffsetY;

	float FrameDuration;

	uint32_t SpritesPerLine;
	uint32_t Columns;
};

struct AnimationInfo
{
	uint32_t FirstFrameX;
	uint32_t FirstFrameY;

	uint32_t EndFrameX;
	uint32_t EndFrameY;

	float FrameDuration;

};

class zAnimationManager
{
public:
	zAnimationManager() = default;
	zAnimationManager(AnimationManagerDef& animDef);
	void init(AnimationManagerDef& animDef);

	Az::Rect getFrameSRC();

	void Update();
	bool RunAnimation(AnimationInfo& info);

private:

	float m_SpriteStartX;
	float m_SpriteStartY;

	float m_SpriteSizeX;
	float m_SpriteSizeY;

	float m_SpriteOffsetX;
	float m_SpriteOffsetY;

	uint32_t m_SpritesPerLine;
	uint32_t m_Columns;

	uint32_t m_CurrentFrameX;
	uint32_t m_CurrentFrameY;

	Az::Rect m_CurrentSRC;

	float m_FrameDuration;
	float m_CurrentTime;
	uint32_t m_CurrentFrame;

	bool m_AnimDefIsInit = false;
};