#include "pch.h"
#include "BufferBubble.h"
#include "../Engine/ColorRGBA8.h"
#include "ColorXRGB4.h"

using namespace ieg;

const size_t BufferBubble::mIntroPaletteOffset{ 0x3af8 };
const size_t BufferBubble::mPaletteColorCount{ 16 };
const size_t BufferBubble::mPaletteOffset{ 0x7b6 };
const size_t BufferBubble::mLevelColorCount{ 4 };
const size_t BufferBubble::mLevelColorsOffset{ 0x275C };
const size_t BufferBubble::mLevelColorsPaletteOffset{ 11 };
const size_t BufferBubble::mLevelBigBlockOffsets{ 0x2418 };

BufferBubble::BufferBubble(const std::string& filename)
	: Buffer(filename)
{
}

size_t ieg::BufferBubble::GetPaletteColorCount()
{
	return mPaletteColorCount;
}

void ieg::BufferBubble::GetPalette(ColorRGBA8* pPalette, const size_t offset)
{
	ColorXRGB4* pColor{};
	for (size_t i{ 0 }; i < mPaletteColorCount; ++i)
	{
		pColor = (ColorXRGB4*)(mpData + offset + i * sizeof(ColorXRGB4));
		pColor->ConvertRGBA8(pPalette + i);
	}
}

void ieg::BufferBubble::GetIntroColors(ColorRGBA8* pPalette)
{
	GetPalette(pPalette, mIntroPaletteOffset);
}

void BufferBubble::GetLevelColors(ColorRGBA8* pPalette, size_t level)
{
	GetPalette(pPalette, mPaletteOffset);
	ColorXRGB4* pColor{};
	for (size_t i{ 0 }; i < mLevelColorCount; ++i)
	{
		pColor = (ColorXRGB4*)(mpData + mLevelColorsOffset + (level * mLevelColorCount + i) * sizeof(ColorXRGB4));
		pColor->ConvertRGBA8(pPalette + mLevelColorsPaletteOffset + i);
	}
}

size_t ieg::BufferBubble::GetLevelBigBlockOffset(size_t level)
{
	unsigned int offset{ *(((unsigned int*)(mpData + mLevelBigBlockOffsets)) + level) };
	offset = _byteswap_ulong(offset);
	return size_t(offset);
}
