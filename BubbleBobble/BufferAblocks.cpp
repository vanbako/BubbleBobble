#include "pch.h"
#include "BufferAblocks.h"
#include "../Engine/ColorRGBA8.h"

using namespace ieg;

// Code supports:
//   Bitplane count [1,8]
//   BlockWidth is a multiple of 8
const size_t BufferAblocks::mBitplanes{ 4 };
const size_t BufferAblocks::mLevelBlockOffset{ 0 };
const size_t BufferAblocks::mLevelBlockRowPitch{ 40 };
const size_t BufferAblocks::mLevelBlockBitplanePitch{ 3520 };
const size_t BufferAblocks::mLevelFalse3DOffset{ 661 };
const size_t BufferAblocks::mBlockWidth{ 8 };
const size_t BufferAblocks::mBigBlockWidth{ 16 };
const size_t BufferAblocks::mBlockByteWidth{ 1 };
const size_t BufferAblocks::mBigBlockByteWidth{ 2 };
const size_t BufferAblocks::mBlockHeight{ 8 };
const size_t BufferAblocks::mBigBlockHeight{ 16 };
const size_t BufferAblocks::mFalse3DCount{ 6 };
const size_t BufferAblocks::mFontOffset1{ 0xb40 };
const size_t BufferAblocks::mFontOffset2{ 0xc80 };
const size_t BufferAblocks::mFontWidth{ 8 } ;
const size_t BufferAblocks::mFontByteWidth{ 1 };
const size_t BufferAblocks::mFontHeight{ 8 };
const size_t BufferAblocks::mFontStart{ 48 };
const size_t BufferAblocks::mFontRowPitch{ 40 };
const size_t BufferAblocks::mFontBitplanePitch{ 0xdc0 };
const char BufferAblocks::mFontChrCount{ 50 };

BufferAblocks::BufferAblocks(const std::string& filename)
	: Buffer(filename)
{
}

void BufferAblocks::GetLevelBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, size_t level) const
{
	size_t levelOffset{ level % mLevelBlockRowPitch };
	size_t levelBlockOffset{ mLevelBlockOffset + (level / mLevelBlockRowPitch) * mLevelBlockRowPitch * mBlockHeight };
	unsigned char byte[mBitplanes]{};
	static const size_t pixelsPerBlock{ mBlockWidth * mBlockHeight };
	unsigned char pixels[pixelsPerBlock]{};
	std::memset(pixels, 0, pixelsPerBlock);
	for (size_t row{ 0 }; row < mBlockHeight; ++row)
	{
		for (size_t col{ 0 }; col < mBlockByteWidth; ++col)
		{
			for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
				byte[bitplane] = mpData[levelBlockOffset + levelOffset * mBlockByteWidth + col + row * mLevelBlockRowPitch + bitplane * mLevelBlockBitplanePitch];
			for (size_t bit{ 0 }; bit < 8; ++bit)
				for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
				{
					pixels[row * mBlockWidth + col * 8 + 7 - bit] |= (byte[bitplane] & 1) << bitplane;
					byte[bitplane] >>= 1;
				}
		}
	}
	for (size_t row{ 0 }; row < mBlockHeight; ++row)
		for (size_t col{ 0 }; col < mBlockWidth; ++col)
			pBlock[row * mBlockWidth + col] = pPalette[pixels[row * mBlockWidth + col]];
}

void BufferAblocks::GetLevelBigBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, size_t offset) const
{
	unsigned char byte[mBitplanes]{};
	static const size_t pixelsPerBlock{ mBigBlockWidth * mBigBlockHeight };
	unsigned char pixels[pixelsPerBlock]{};
	std::memset(pixels, 0, pixelsPerBlock);
	for (size_t row{ 0 }; row < mBigBlockHeight; ++row)
	{
		for (size_t col{ 0 }; col < mBigBlockByteWidth; ++col)
		{
			for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
				byte[bitplane] = mpData[offset + col + row * mLevelBlockRowPitch + bitplane * mLevelBlockBitplanePitch];
			for (size_t bit{ 0 }; bit < 8; ++bit)
				for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
				{
					pixels[row * mBigBlockWidth + col * 8 + 7 - bit] |= (byte[bitplane] & 1) << bitplane;
					byte[bitplane] >>= 1;
				}
		}
	}
	for (size_t row{ 0 }; row < mBigBlockHeight; ++row)
		for (size_t col{ 0 }; col < mBigBlockWidth; ++col)
			pBlock[row * mBigBlockWidth + col] = pPalette[pixels[row * mBigBlockWidth + col]];
}

void BufferAblocks::GetLevelFalse3D(ColorRGBA8* pFalse3D, ColorRGBA8* pPalette) const
{
	unsigned char byte[mBitplanes]{};
	static const size_t pixelsPerBlock{ mBlockWidth * mBlockHeight };
	unsigned char pixels[pixelsPerBlock]{};
	for (size_t false3D{ 0 }; false3D < mFalse3DCount; ++false3D)
	{
		std::memset(pixels, 0, pixelsPerBlock);
		for (size_t row{ 0 }; row < mBlockHeight; ++row)
		{
			for (size_t col{ 0 }; col < mBlockByteWidth; ++col)
			{
				for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
					byte[bitplane] = mpData[mLevelFalse3DOffset + false3D + col + row * mLevelBlockRowPitch + bitplane * mLevelBlockBitplanePitch];
				for (size_t bit{ 0 }; bit < 8; ++bit)
					for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
					{
						pixels[row * mBlockWidth + col * 8 + 7 - bit] |= (byte[bitplane] & 1) << bitplane;
						byte[bitplane] >>= 1;
					}
			}
		}
		for (size_t row{ 0 }; row < mBlockHeight; ++row)
			for (size_t col{ 0 }; col < mBlockWidth; ++col)
				pFalse3D[false3D * pixelsPerBlock + row * mBlockWidth + col] = pPalette[pixels[row * mBlockWidth + col]];
	}
}

void BufferAblocks::GetCharacter(ColorRGBA8* pChr, ColorRGBA8* pPalette, size_t color, char chr)
{
	unsigned char byte{};
	static const size_t pixelsPerChr{ mFontWidth * mFontHeight };
	char pixels[pixelsPerChr]{};
	size_t offset{ mFontOffset1 };
	if (chr == ' ')
		chr = 91;
	chr -= mFontStart;
	if (chr >= 40)
	{
		offset = mFontOffset2;
		chr -= 40;
	}
	offset += chr;
	for (size_t row{ 0 }; row < mFontHeight; ++row)
	{
		byte = mpData[offset + row * mFontRowPitch];
		byte |= mpData[offset + row * mFontRowPitch + mFontBitplanePitch];
		byte |= mpData[offset + row * mFontRowPitch + mFontBitplanePitch * 2];
		byte |= mpData[offset + row * mFontRowPitch + mFontBitplanePitch * 3];
		for (size_t bit{ 0 }; bit < 8; ++bit)
		{
			pixels[row * mFontWidth + 7 - bit] = byte & 1;
			byte >>= 1;
		}
	}
	memset(pChr, 0, mFontByteWidth * mFontHeight * sizeof(ColorRGBA8));
	for (size_t row{ 0 }; row < mFontHeight; ++row)
		for (size_t col{ 0 }; col < mFontWidth; ++col)
			if (pixels[row * mFontWidth + col] != 0)
				pChr[row * mFontWidth + col] = pPalette[color];
}

void BufferAblocks::GetFont(ColorRGBA8* pFont, ColorRGBA8* pPalette, size_t color)
{
	for (char chr{ 0 }; chr < mFontChrCount; ++chr)
		GetCharacter(&pFont[size_t(chr) * mFontWidth * mFontHeight], pPalette, color, unsigned char(chr) + mFontStart);
}

const size_t BufferAblocks::GetFalse3DCount()
{
	return mFalse3DCount;
}

const size_t BufferAblocks::GetBlockPixelCount()
{
	return mBlockWidth * mBlockHeight;
}

const size_t BufferAblocks::GetBigBlockPixelCount()
{
	return mBigBlockWidth * mBigBlockHeight;
}

const size_t BufferAblocks::GetBlockWidth()
{
	return mBlockWidth;
}

const size_t BufferAblocks::GetBigBlockWidth()
{
	return mBigBlockWidth;
}

const size_t BufferAblocks::GetBlockHeight()
{
	return mBlockHeight;
}

const size_t BufferAblocks::GetBigBlockHeight()
{
	return mBigBlockHeight;
}

const size_t BufferAblocks::GetFontWidth()
{
	return mFontWidth;
}

const size_t BufferAblocks::GetFontHeight()
{
	return mFontHeight;
}

const size_t BufferAblocks::GetFontStart()
{
	return mFontStart;
}

const char BufferAblocks::GetFontChrCount()
{
	return mFontChrCount;
}
