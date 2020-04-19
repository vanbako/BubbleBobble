#pragma once
#include "Buffer.h"

namespace ieg {

	class ColorRGBA8;

	class BufferBubble final
		: public Buffer
	{
	public:
		BufferBubble(const std::string* pFilename);

		void GetLevelColors(ColorRGBA8* pPalette, size_t level);

		static size_t GetPaletteColorCount();
	private:
		static const size_t mPaletteColorCount;
		static const size_t mPaletteOffset;
		static const size_t mLevelColorCount;
		static const size_t mLevelColorsOffset;
		static const size_t mLevelColorsPaletteOffset;
	};
}