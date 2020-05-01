#pragma once
#include "Buffer.h"

namespace ieg {
	class ColorRGBA8;

	class BufferAblocks final
		: public Buffer
	{
	public:
		explicit BufferAblocks(const std::string& filename);
		~BufferAblocks() = default;
		BufferAblocks(const BufferAblocks&) = delete;
		BufferAblocks(BufferAblocks&&) = delete;
		BufferAblocks& operator=(const BufferAblocks&) = delete;
		BufferAblocks& operator=(BufferAblocks&&) = delete;

		void GetLevelBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, int level) const;
		void GetLevelBigBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, int level) const;
		void GetLevelFalse3D(ColorRGBA8* pFalse3D, ColorRGBA8* pPalette) const;
		void GetCharacter(ColorRGBA8* pChr, ColorRGBA8* pPalette, int color, char chr);
		void GetFont(ColorRGBA8* pFont, ColorRGBA8* pPalette, int color);

		static const int GetFalse3DCount();
		static const int GetBlockPixelCount();
		static const int GetBigBlockPixelCount();
		static const int GetBlockWidth();
		static const int GetBigBlockWidth();
		static const int GetBlockHeight();
		static const int GetBigBlockHeight();
		static const int GetFontWidth();
		static const int GetFontHeight();
		static const int GetFontStart();
		static const char GetFontChrCount();
	private:
		static const int mBitplanes;
		static const int mLevelBlockOffset;
		static const int mLevelBlockRowPitch;
		static const int mLevelBlockBitplanePitch;
		static const int mLevelFalse3DOffset;
		static const int mBlockWidth;
		static const int mBigBlockWidth;
		static const int mBlockByteWidth;
		static const int mBigBlockByteWidth;
		static const int mBlockHeight;
		static const int mBigBlockHeight;
		static const int mFalse3DCount;
		static const int mFontOffset1;
		static const int mFontOffset2;
		static const int mFontWidth;
		static const int mFontByteWidth;
		static const int mFontHeight;
		static const int mFontStart;
		static const int mFontRowPitch;
		static const int mFontBitplanePitch;
		static const char mFontChrCount;
	};
}
