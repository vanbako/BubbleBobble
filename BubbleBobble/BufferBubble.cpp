#include "pch.h"
#include "BufferBubble.h"
#include "ColorRGBA8.h"
#include "ColorXRGB4.h"

using namespace ieg;

const size_t BufferBubble::mPaletteColorCount{ 16 };
const size_t BufferBubble::mPaletteOffset{ 0x7b6 };
const size_t BufferBubble::mLevelColorCount{ 4 };
const size_t BufferBubble::mLevelColorsOffset{ 0x275C };
const size_t BufferBubble::mLevelColorsPaletteOffset{ 22 };

BufferBubble::BufferBubble(const std::string* pFilename)
	: Buffer(pFilename)
{
}

size_t ieg::BufferBubble::GetPaletteColorCount()
{
	return mPaletteColorCount;
}

void BufferBubble::GetLevelColors(ColorRGBA8* pPalette, size_t level)
{
	ColorXRGB4* pColor{};
	for (size_t i{ 0 }; i < mPaletteColorCount; ++i)
	{
		pColor = (ColorXRGB4*)(mpData + mPaletteOffset + i * sizeof(ColorXRGB4));
		pColor->ConvertRGBA8(pPalette + i * sizeof(ColorRGBA8));
	}
	for (size_t i{ 0 }; i < mLevelColorCount; ++i)
	{
		pColor = (ColorXRGB4*)(mpData + mLevelColorsOffset + (level * mLevelColorCount + i) * sizeof(ColorXRGB4));
		pColor->ConvertRGBA8(pPalette + mLevelColorsPaletteOffset + i * sizeof(ColorRGBA8));
	}
}
