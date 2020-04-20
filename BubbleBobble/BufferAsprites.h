#pragma once
#include "Buffer.h"

namespace ieg {
	class ColorRGBA8;

	class BufferAsprites final
		: public Buffer
	{
	public:
		BufferAsprites(const std::string* pFilename);

		void GetSprite(size_t sprite, ColorRGBA8* pSprite, ColorRGBA8* pPalette) const;
	};
}
