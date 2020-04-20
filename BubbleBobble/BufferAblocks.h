#pragma once
#include "Buffer.h"

namespace ieg {
	class ColorRGBA8;

	class BufferAblocks final
		: public Buffer
	{
	public:
		BufferAblocks(const std::string* pFilename);

		void GetLevelBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, size_t level) const;
		void GetLevelBigBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, size_t level) const;
		void GetLevelFalse3D(ColorRGBA8* pFalse3D, ColorRGBA8* pPalette) const;

		static const size_t GetFalse3DCount();
		static const size_t GetBlockPixelCount();
		static const size_t GetBigBlockPixelCount();
		static const size_t GetBlockWidth();
		static const size_t GetBigBlockWidth();
		static const size_t GetBlockHeight();
		static const size_t GetBigBlockHeight();
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
	};
}
