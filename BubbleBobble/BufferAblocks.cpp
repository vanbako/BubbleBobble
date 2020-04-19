#include "pch.h"
#include "BufferAblocks.h"
#include "ColorRGBA8.h"

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
const size_t BufferAblocks::mBlockByteWidth{ 1 };
const size_t BufferAblocks::mBlockHeight{ 8 };
const size_t BufferAblocks::mFalse3DCount{ 6 };

BufferAblocks::BufferAblocks(const std::string* pFilename)
	: Buffer(pFilename)
{
}

void BufferAblocks::GetLevelBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, size_t level) const
{
	unsigned char byte[mBitplanes];
	static const size_t pixelsPerBlock{ mBlockWidth * mBlockHeight };
	unsigned char pixels[pixelsPerBlock];
	std::memset(pixels, 0, pixelsPerBlock);
	for (size_t row{ 0 }; row < mBlockHeight; ++row)
	{
		for (size_t col{ 0 }; col < mBlockByteWidth; ++col)
		{
			for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
				byte[bitplane] = mpData[mLevelBlockOffset + level * mBlockByteWidth + col + row * mLevelBlockRowPitch + bitplane * mLevelBlockBitplanePitch];
			for (size_t bit{ 0 }; bit < 8; ++bit)
				for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
				{
					pixels[row * mBlockWidth + col * 8 + bit] <<= 1;
					pixels[row * mBlockWidth + col * 8 + bit] |= byte[bitplane] & 0x01;
					byte[bitplane] >>= 1;
				}
		}
	}
	for (size_t row{ 0 }; row < mBlockHeight; ++row)
		for (size_t col{ 0 }; col < mBlockWidth; ++col)
			pBlock[row * mBlockWidth + col] = pPalette[pixels[row * mBlockWidth + col]];
}

void BufferAblocks::GetLevelFalse3D(ColorRGBA8* pFalse3D, ColorRGBA8* pPalette, size_t level) const
{
	unsigned char byte[mBitplanes];
	static const size_t pixelsPerBlock{ mBlockWidth * mBlockHeight };
	unsigned char pixels[pixelsPerBlock];
	for (size_t false3D{ 0 }; false3D < mFalse3DCount; ++false3D)
	{
		std::memset(pixels, 0, pixelsPerBlock);
		for (size_t row{ 0 }; row < mBlockHeight; ++row)
		{
			for (size_t col{ 0 }; col < mBlockByteWidth; ++col)
			{
				for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
					byte[bitplane] = mpData[mLevelFalse3DOffset + false3D + level * mBlockByteWidth + col + row * mLevelBlockRowPitch + bitplane * mLevelBlockBitplanePitch];
				for (size_t bit{ 0 }; bit < 8; ++bit)
					for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
					{
						pixels[row * mBlockWidth + col * 8 + bit] <<= 1;
						pixels[row * mBlockWidth + col * 8 + bit] |= byte[bitplane] & 0x01;
						byte[bitplane] >>= 1;
					}
			}
		}
		for (size_t row{ 0 }; row < mBlockHeight; ++row)
			for (size_t col{ 0 }; col < mBlockWidth; ++col)
				pFalse3D[false3D * pixelsPerBlock + row * mBlockWidth + col] = pPalette[pixels[row * mBlockWidth + col]];
	}
}

const size_t ieg::BufferAblocks::GetFalse3DCount()
{
	return mFalse3DCount;
}

const size_t BufferAblocks::GetBlockPixelCount()
{
	return mBlockWidth * mBlockHeight;
}
