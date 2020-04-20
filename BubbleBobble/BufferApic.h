#pragma once
#include "Buffer.h"

namespace ieg {
	class ColorRGBA8;

	class BufferApic final
		: public Buffer
	{
	public:
		BufferApic(const std::string* pFilename);

		void GetPic(ColorRGBA8* pPic, ColorRGBA8* pPalette) const;
	private:
		static const size_t mBitplanes;
		static const size_t mWidth;
		static const size_t mByteWidth;
		static const size_t mHeight;
		static const size_t mBitplanePitch;
	};
}
