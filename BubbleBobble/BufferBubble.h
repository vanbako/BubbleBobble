#pragma once
#include "Buffer.h"

namespace ieg {

	class ColorRGBA8;

	class BufferBubble final
		: public Buffer
	{
	public:
		explicit BufferBubble(const std::string& filename);
		~BufferBubble() = default;
		BufferBubble(const BufferBubble&) = delete;
		BufferBubble(BufferBubble&&) = delete;
		BufferBubble& operator=(const BufferBubble&) = delete;
		BufferBubble& operator=(BufferBubble&&) = delete;

		void GetIntroColors(ColorRGBA8* pPalette);
		void GetLevelColors(ColorRGBA8* pPalette, int level);
		int GetLevelBigBlockOffset(int level);

		static int GetPaletteColorCount();
	private:
		static const int mIntroPaletteOffset;
		static const int mPaletteColorCount;
		static const int mPaletteOffset;
		static const int mLevelColorCount;
		static const int mLevelColorsOffset;
		static const int mLevelColorsPaletteOffset;
		static const int mLevelBigBlockOffsets;

		void GetPalette(ColorRGBA8* pPalette, const int offset);
	};
}
