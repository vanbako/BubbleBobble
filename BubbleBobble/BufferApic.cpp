#include "pch.h"
#include "BufferApic.h"
#include "../Engine/ColorRGBA8.h"

using namespace ieg;

const int BufferApic::mBitplanes{ 4 };
const int BufferApic::mWidth{ 320 };
const int BufferApic::mByteWidth{ 40 };
const int BufferApic::mHeight{ 200 };
const int BufferApic::mBitplanePitch{ 8000 };

BufferApic::BufferApic(const std::string& filename)
	: Buffer(filename)
{
}

void BufferApic::GetPic(ColorRGBA8* pPic, ColorRGBA8* pPalette) const
{
	unsigned char byte[mBitplanes];
	unsigned char pixels[mWidth * mHeight];
	std::memset(pixels, 0, mWidth * mHeight);
	for (int row{ 0 }; row < mHeight; ++row)
	{
		for (int col{ 0 }; col < mByteWidth; ++col)
		{
			for (int bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
				byte[bitplane] = mpData[col + row * mByteWidth + bitplane * mBitplanePitch];
			for (int bit{ 0 }; bit < 8; ++bit)
				for (int bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
				{
					pixels[row * mWidth + col * 8 + 7 - bit] |= (byte[bitplane] & 1) << bitplane;
					byte[bitplane] >>= 1;
				}
		}
	}
	for (int row{ 0 }; row < mHeight; ++row)
		for (int col{ 0 }; col < mWidth; ++col)
			pPic[row * mWidth + col] = pPalette[pixels[row * mWidth + col]];

}
