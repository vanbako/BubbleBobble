module BubbleBobble:Buffer;

using namespace ieg;

// Code supports:
//   Bitplane count [1,8]
//   BlockWidth is a multiple of 8
const int BufferAblocks::mBitplanes{ 4 };
const int BufferAblocks::mLevelBlockOffset{ 0 };
const int BufferAblocks::mLevelBlockRowPitch{ 40 };
const int BufferAblocks::mLevelBlockBitplanePitch{ 3520 };
const int BufferAblocks::mLevelFalse3DOffset{ 661 };
const int BufferAblocks::mBlockWidth{ 8 };
const int BufferAblocks::mBigBlockWidth{ 16 };
const int BufferAblocks::mBlockByteWidth{ 1 };
const int BufferAblocks::mBigBlockByteWidth{ 2 };
const int BufferAblocks::mBlockHeight{ 8 };
const int BufferAblocks::mBigBlockHeight{ 16 };
const int BufferAblocks::mFalse3DCount{ 6 };
const int BufferAblocks::mFontOffset1{ 0xb40 };
const int BufferAblocks::mFontOffset2{ 0xc80 };
const int BufferAblocks::mFontWidth{ 8 } ;
const int BufferAblocks::mFontByteWidth{ 1 };
const int BufferAblocks::mFontHeight{ 8 };
const int BufferAblocks::mFontStart{ 48 };
const int BufferAblocks::mFontRowPitch{ 40 };
const int BufferAblocks::mFontBitplanePitch{ 0xdc0 };
const char BufferAblocks::mFontChrCount{ 50 };

BufferAblocks::BufferAblocks(const std::string& filename)
	: Buffer(filename)
{
}

void BufferAblocks::GetLevelBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, int level) const
{
	int levelOffset{ level % mLevelBlockRowPitch };
	int levelBlockOffset{ mLevelBlockOffset + (level / mLevelBlockRowPitch) * mLevelBlockRowPitch * mBlockHeight };
	unsigned char byte[mBitplanes]{};
	static const int pixelsPerBlock{ mBlockWidth * mBlockHeight };
	unsigned char pixels[pixelsPerBlock]{};
	std::memset(pixels, 0, pixelsPerBlock);
	for (int row{ 0 }; row < mBlockHeight; ++row)
	{
		for (int col{ 0 }; col < mBlockByteWidth; ++col)
		{
			for (int bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
				byte[bitplane] = mpData[levelBlockOffset + levelOffset * mBlockByteWidth + col + row * mLevelBlockRowPitch + bitplane * mLevelBlockBitplanePitch];
			for (int bit{ 0 }; bit < 8; ++bit)
				for (int bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
				{
					pixels[row * mBlockWidth + col * 8 + 7 - bit] |= (byte[bitplane] & 1) << bitplane;
					byte[bitplane] >>= 1;
				}
		}
	}
	for (int row{ 0 }; row < mBlockHeight; ++row)
		for (int col{ 0 }; col < mBlockWidth; ++col)
			pBlock[row * mBlockWidth + col] = pPalette[pixels[row * mBlockWidth + col]];
}

void BufferAblocks::GetLevelBigBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, int offset) const
{
	unsigned char byte[mBitplanes]{};
	static const int pixelsPerBlock{ mBigBlockWidth * mBigBlockHeight };
	unsigned char pixels[pixelsPerBlock]{};
	std::memset(pixels, 0, pixelsPerBlock);
	for (int row{ 0 }; row < mBigBlockHeight; ++row)
	{
		for (int col{ 0 }; col < mBigBlockByteWidth; ++col)
		{
			for (int bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
				byte[bitplane] = mpData[offset + col + row * mLevelBlockRowPitch + bitplane * mLevelBlockBitplanePitch];
			for (int bit{ 0 }; bit < 8; ++bit)
				for (int bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
				{
					pixels[row * mBigBlockWidth + col * 8 + 7 - bit] |= (byte[bitplane] & 1) << bitplane;
					byte[bitplane] >>= 1;
				}
		}
	}
	for (int row{ 0 }; row < mBigBlockHeight; ++row)
		for (int col{ 0 }; col < mBigBlockWidth; ++col)
			pBlock[row * mBigBlockWidth + col] = pPalette[pixels[row * mBigBlockWidth + col]];
}

void BufferAblocks::GetLevelFalse3D(ColorRGBA8* pFalse3D, ColorRGBA8* pPalette) const
{
	unsigned char byte[mBitplanes]{};
	static const int pixelsPerBlock{ mBlockWidth * mBlockHeight };
	unsigned char pixels[pixelsPerBlock]{};
	for (int false3D{ 0 }; false3D < mFalse3DCount; ++false3D)
	{
		std::memset(pixels, 0, pixelsPerBlock);
		for (int row{ 0 }; row < mBlockHeight; ++row)
		{
			for (int col{ 0 }; col < mBlockByteWidth; ++col)
			{
				for (int bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
					byte[bitplane] = mpData[mLevelFalse3DOffset + false3D + col + row * mLevelBlockRowPitch + bitplane * mLevelBlockBitplanePitch];
				for (int bit{ 0 }; bit < 8; ++bit)
					for (int bitplane{ 0 }; bitplane < mBitplanes; ++bitplane)
					{
						pixels[row * mBlockWidth + col * 8 + 7 - bit] |= (byte[bitplane] & 1) << bitplane;
						byte[bitplane] >>= 1;
					}
			}
		}
		for (int row{ 0 }; row < mBlockHeight; ++row)
			for (int col{ 0 }; col < mBlockWidth; ++col)
				pFalse3D[false3D * pixelsPerBlock + row * mBlockWidth + col] = pPalette[pixels[row * mBlockWidth + col]];
	}
}

void BufferAblocks::GetCharacter(ColorRGBA8* pChr, ColorRGBA8* pPalette, int color, char chr)
{
	unsigned char byte{};
	static const int pixelsPerChr{ mFontWidth * mFontHeight };
	char pixels[pixelsPerChr]{};
	int offset{ mFontOffset1 };
	if (chr == ' ')
		chr = 91;
	chr -= mFontStart;
	if (chr >= 40)
	{
		offset = mFontOffset2;
		chr -= 40;
	}
	offset += chr;
	for (int row{ 0 }; row < mFontHeight; ++row)
	{
		byte = mpData[offset + row * mFontRowPitch];
		byte |= mpData[offset + row * mFontRowPitch + mFontBitplanePitch];
		byte |= mpData[offset + row * mFontRowPitch + mFontBitplanePitch * 2];
		byte |= mpData[offset + row * mFontRowPitch + mFontBitplanePitch * 3];
		for (int bit{ 0 }; bit < 8; ++bit)
		{
			pixels[row * mFontWidth + 7 - bit] = byte & 1;
			byte >>= 1;
		}
	}
	memset(pChr, 0, mFontByteWidth * mFontHeight * sizeof(ColorRGBA8));
	for (int row{ 0 }; row < mFontHeight; ++row)
		for (int col{ 0 }; col < mFontWidth; ++col)
			if (pixels[row * mFontWidth + col] != 0)
				pChr[row * mFontWidth + col] = pPalette[color];
}

void BufferAblocks::GetFont(ColorRGBA8* pFont, ColorRGBA8* pPalette, int color)
{
	for (char chr{ 0 }; chr < mFontChrCount; ++chr)
		GetCharacter(&pFont[int(chr) * mFontWidth * mFontHeight], pPalette, color, unsigned char(chr) + mFontStart);
}

const int BufferAblocks::GetFalse3DCount()
{
	return mFalse3DCount;
}

const int BufferAblocks::GetBlockPixelCount()
{
	return mBlockWidth * mBlockHeight;
}

const int BufferAblocks::GetBigBlockPixelCount()
{
	return mBigBlockWidth * mBigBlockHeight;
}

const int BufferAblocks::GetBlockWidth()
{
	return mBlockWidth;
}

const int BufferAblocks::GetBigBlockWidth()
{
	return mBigBlockWidth;
}

const int BufferAblocks::GetBlockHeight()
{
	return mBlockHeight;
}

const int BufferAblocks::GetBigBlockHeight()
{
	return mBigBlockHeight;
}

const int BufferAblocks::GetFontWidth()
{
	return mFontWidth;
}

const int BufferAblocks::GetFontHeight()
{
	return mFontHeight;
}

const int BufferAblocks::GetFontStart()
{
	return mFontStart;
}

const char BufferAblocks::GetFontChrCount()
{
	return mFontChrCount;
}
