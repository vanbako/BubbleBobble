#pragma once
#include "Buffer.h"

namespace ieg {
	class ColorRGBA8;

	class BufferAsprites final
		: public Buffer
	{
	public:
		explicit BufferAsprites(const std::string& filename);

		void GetSprite(size_t sprite, ColorRGBA8* pSprite, ColorRGBA8* pPalette) const;
	};
}
