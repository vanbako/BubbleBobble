#include "pch.h"
#include "BufferBubble.h"
#include "../Engine/ColorRGBA8.h"
#include "ColorXRGB4.h"

using namespace ieg;

const int BufferBubble::mIntroPaletteOffset{ 0x3af8 };
const int BufferBubble::mPaletteColorCount{ 16 };
const int BufferBubble::mPaletteOffset{ 0x7b6 };
const int BufferBubble::mLevelColorCount{ 4 };
const int BufferBubble::mLevelColorsOffset{ 0x275C };
const int BufferBubble::mLevelColorsPaletteOffset{ 11 };
const int BufferBubble::mLevelBigBlockOffsets{ 0x2418 };

BufferBubble::BufferBubble(const std::string& filename)
	: Buffer(filename)
{
}

int BufferBubble::GetPaletteColorCount()
{
	return mPaletteColorCount;
}

void BufferBubble::GetPalette(ColorRGBA8* pPalette, const int offset)
{
	ColorXRGB4* pColor{};
	for (int i{ 0 }; i < mPaletteColorCount; ++i)
	{
		pColor = (ColorXRGB4*)(mpData + offset + i * sizeof(ColorXRGB4));
		pColor->ConvertRGBA8(pPalette + i);
	}
}

void BufferBubble::GetIntroColors(ColorRGBA8* pPalette)
{
	GetPalette(pPalette, mIntroPaletteOffset);
}

void BufferBubble::GetLevelColors(ColorRGBA8* pPalette, int level)
{
	GetPalette(pPalette, mPaletteOffset);
	ColorXRGB4* pColor{};
	for (int i{ 0 }; i < mLevelColorCount; ++i)
	{
		pColor = (ColorXRGB4*)(mpData + mLevelColorsOffset + (level * mLevelColorCount + i) * sizeof(ColorXRGB4));
		pColor->ConvertRGBA8(pPalette + mLevelColorsPaletteOffset + i);
	}
}

int BufferBubble::GetLevelBigBlockOffset(int level)
{
	unsigned int offset{ *(((unsigned int*)(mpData + mLevelBigBlockOffsets)) + level) };
	offset = _byteswap_ulong(offset);
	return int(offset);
}
