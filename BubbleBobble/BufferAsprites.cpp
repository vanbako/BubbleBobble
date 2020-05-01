#include "pch.h"
#include "BufferAsprites.h"
#include "../Engine/ColorRGBA8.h"

using namespace ieg;

const int BufferAsprites::mBitplanes{ 4 };
const int BufferAsprites::mWidth{ 32 };
const int BufferAsprites::mByteWidth{ 4 };
const int BufferAsprites::mHeight{ 16 };

BufferAsprites::BufferAsprites(const std::string& filename)
	: Buffer(filename)
{
}

void BufferAsprites::GetSprites(ColorRGBA8* pSprite, int count, Sprite sprite, ColorRGBA8* pPalette) const
{
	static const int pixelCount{ mWidth * mHeight };
	unsigned char pixels[pixelCount];
	unsigned char byte[mBitplanes];
	for (int i{ 0 }; i < count; ++i)
	{
		std::memset(pixels, 0, pixelCount);
		int offset{ (int(sprite) + i) * mBitplanes * mByteWidth * mHeight };
		for (int row{ 0 }; row < mHeight; ++row)
			for (int col{ 0 }; col < mByteWidth; ++col)
			{
				for (int bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
					byte[bitplane] = mpData[offset + row * mByteWidth + col + bitplane * mByteWidth * mHeight];
				for (int bit{ 0 }; bit < 8; ++bit)
					for (int bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
					{
						pixels[row * mWidth + col * 8 + 7 - bit] |= (byte[bitplane] & 1) << bitplane;
						byte[bitplane] >>= 1;
					}
			}
		for (int row{ 0 }; row < mHeight; ++row)
			for (int col{ 0 }; col < mWidth; ++col)
				pSprite[i * pixelCount + row * mWidth + col] = pPalette[pixels[row * mWidth + col]];
	}
}

const int BufferAsprites::GetWidth()
{
	return mWidth;
}

const int BufferAsprites::GetByteWidth()
{
	return mByteWidth;
}

const int BufferAsprites::GetHeight()
{
	return mHeight;
}
