#include "pch.h"
#include "BufferAsprites.h"
#include "ColorRGBA8.h"

using namespace ieg;

BufferAsprites::BufferAsprites(const std::string& filename)
	: Buffer(filename)
{
}

void ieg::BufferAsprites::GetSprite(size_t sprite, ColorRGBA8* pSprite, ColorRGBA8* pPalette) const
{
	(sprite);
	(pSprite);
	(pPalette);
	//size_t offset{ level % mLevelBlockRowPitch };
	//size_t levelBlockOffset{ mLevelBlockOffset + (level / mLevelBlockRowPitch) * mLevelBlockRowPitch * mBlockHeight };
	//unsigned char byte[mBitplanes];
	//static const size_t pixelsPerBlock{ mBlockWidth * mBlockHeight };
	//unsigned char pixels[pixelsPerBlock];
	//std::memset(pixels, 0, pixelsPerBlock);
	//for (size_t row{ 0 }; row < mBlockHeight; ++row)
	//{
	//	for (size_t col{ 0 }; col < mBlockByteWidth; ++col)
	//	{
	//		for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
	//			byte[bitplane] = mpData[levelBlockOffset + levelOffset * mBlockByteWidth + col + row * mLevelBlockRowPitch + bitplane * mLevelBlockBitplanePitch];
	//		for (size_t bit{ 0 }; bit < 8; ++bit)
	//			for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
	//			{
	//				pixels[row * mBlockWidth + col * 8 + 7 - bit] |= (byte[bitplane] & 1) << bitplane;
	//				byte[bitplane] >>= 1;
	//			}
	//	}
	//}
	//for (size_t row{ 0 }; row < mBlockHeight; ++row)
	//	for (size_t col{ 0 }; col < mBlockWidth; ++col)
	//		pBlock[row * mBlockWidth + col] = pPalette[pixels[row * mBlockWidth + col]];
}
