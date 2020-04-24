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

		void GetLevelBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, size_t level) const;
		void GetLevelBigBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, size_t level) const;
		void GetLevelFalse3D(ColorRGBA8* pFalse3D, ColorRGBA8* pPalette) const;
		void GetCharacter(ColorRGBA8* pChr, ColorRGBA8* pPalette, size_t color, char chr);
		void GetFont(ColorRGBA8* pFont, ColorRGBA8* pPalette, size_t color);

		static const size_t GetFalse3DCount();
		static const size_t GetBlockPixelCount();
		static const size_t GetBigBlockPixelCount();
		static const size_t GetBlockWidth();
		static const size_t GetBigBlockWidth();
		static const size_t GetBlockHeight();
		static const size_t GetBigBlockHeight();
		static const size_t GetFontWidth();
		static const size_t GetFontHeight();
		static const size_t GetFontStart();
		static const char GetFontChrCount();
	private:
		static const size_t mBitplanes;
		static const size_t mLevelBlockOffset;
		static const size_t mLevelBlockRowPitch;
		static const size_t mLevelBlockBitplanePitch;
		static const size_t mLevelFalse3DOffset;
		static const size_t mBlockWidth;
		static const size_t mBigBlockWidth;
		static const size_t mBlockByteWidth;
		static const size_t mBigBlockByteWidth;
		static const size_t mBlockHeight;
		static const size_t mBigBlockHeight;
		static const size_t mFalse3DCount;
		static const size_t mFontOffset1;
		static const size_t mFontOffset2;
		static const size_t mFontWidth;
		static const size_t mFontByteWidth;
		static const size_t mFontHeight;
		static const size_t mFontStart;
		static const size_t mFontRowPitch;
		static const size_t mFontBitplanePitch;
		static const char mFontChrCount;
	};
}
