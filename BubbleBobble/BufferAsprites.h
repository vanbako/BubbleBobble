#pragma once
#include "Buffer.h"

namespace ieg {
	class ColorRGBA8;

	enum class Sprite
		: int
	{
		Bub = 0,
		Bob = 16,
		ZenChan = 32,		// 0
		Hidegons = 48,		// 1
		Banebou = 64,		// 2
		PulPul = 80,		// 3
		Monsta = 88,		// 4
		Drunk = 104,		// 5
		Maita = 120,		// 6
		Invader = 136,		// 7
		SkelMonsta = 144,
		BubFireAnim = 160,
		BobFireAnim = 192,
		BubBalloon = 224,
		BobBalloon = 232,
		ZenChanBubble = 240,
		HidegonsBubble = 248,
		BanebouBubble = 256,
		PulPulBubble = 264,
		MonstaBubble = 272,
		DrunkBubble = 280,
		MaitaBubble = 288,
		InvaderBubble = 296,
		BubBubble = 416,
		BobBubble = 420,
		BubDieAnim = 424,
		BobDieAnim = 428,
		HudBub1Up = 652,
		HudBob1Up = 654,
		HudBUB = 541,
		HudBLE = 542,
		HudBOB = 543
	};

	class BufferAsprites final
		: public Buffer
	{
	public:
		explicit BufferAsprites(const std::string& filename);
		~BufferAsprites() = default;
		BufferAsprites(const BufferAsprites&) = delete;
		BufferAsprites(BufferAsprites&&) = delete;
		BufferAsprites& operator=(const BufferAsprites&) = delete;
		BufferAsprites& operator=(BufferAsprites&&) = delete;

		void GetSprites(ColorRGBA8* pSprite, int count, Sprite sprite, ColorRGBA8* pPalette) const;

		static const int GetWidth();
		static const int GetByteWidth();
		static const int GetHeight();
	private:
		static const int mBitplanes;
		static const int mWidth;
		static const int mByteWidth;
		static const int mHeight;
	};
}
