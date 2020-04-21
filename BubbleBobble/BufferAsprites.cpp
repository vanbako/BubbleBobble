#include "pch.h"
#include "BufferAsprites.h"
#include "ColorRGBA8.h"

using namespace ieg;

const size_t BufferAsprites::mBitplanes{ 4 };
const size_t BufferAsprites::mWidth{ 32 };
const size_t BufferAsprites::mByteWidth{ 4 };
const size_t BufferAsprites::mHeight{ 16 };

BufferAsprites::BufferAsprites(const std::string& filename)
	: Buffer(filename)
{
}

void BufferAsprites::GetSprites(ColorRGBA8* pSprite, size_t count, Sprite sprite, ColorRGBA8* pPalette) const
{
	static const size_t pixelCount{ mWidth * mHeight };
	unsigned char pixels[pixelCount];
	unsigned char byte[mBitplanes];
	for (size_t i{ 0 }; i < count; ++i)
	{
		std::memset(pixels, 0, pixelCount);
		size_t offset{ (size_t(sprite) + i) * mBitplanes * mByteWidth * mHeight };
		for (size_t row{ 0 }; row < mHeight; ++row)
			for (size_t col{ 0 }; col < mByteWidth; ++col)
			{
				for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
					byte[bitplane] = mpData[offset + row * mByteWidth + col + bitplane * mByteWidth * mHeight];
				for (size_t bit{ 0 }; bit < 8; ++bit)
					for (size_t bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
					{
						pixels[row * mWidth + col * 8 + 7 - bit] |= (byte[bitplane] & 1) << bitplane;
						byte[bitplane] >>= 1;
					}
			}
		for (size_t row{ 0 }; row < mHeight; ++row)
			for (size_t col{ 0 }; col < mWidth; ++col)
				pSprite[i * pixelCount + row * mWidth + col] = pPalette[pixels[row * mWidth + col]];
	}
}

const size_t BufferAsprites::GetWidth()
{
	return mWidth;
}

const size_t BufferAsprites::GetByteWidth()
{
	return mByteWidth;
}

const size_t BufferAsprites::GetHeight()
{
	return mHeight;
}
