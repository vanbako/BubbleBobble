#pragma once
#include "Buffer.h"

namespace ieg {
	class ColorRGBA8;

	class BufferApic final
		: public Buffer
	{
	public:
		explicit BufferApic(const std::string& filename);
		~BufferApic() = default;
		BufferApic(const BufferApic&) = delete;
		BufferApic(BufferApic&&) = delete;
		BufferApic& operator=(const BufferApic&) = delete;
		BufferApic& operator=(BufferApic&&) = delete;

		void GetPic(ColorRGBA8* pPic, ColorRGBA8* pPalette) const;
	private:
		static const int mBitplanes;
		static const int mWidth;
		static const int mByteWidth;
		static const int mHeight;
		static const int mBitplanePitch;
	};
}
