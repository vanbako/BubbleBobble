#pragma once

namespace ieg
{
	class ColorRGBA8;

	class Fragment final
	{
	public:
		explicit Fragment(size_t width, size_t height);
		~Fragment();
		Fragment(const Fragment&) = delete;
		Fragment(Fragment&&) = delete;
		Fragment& operator=(const Fragment&) = delete;
		Fragment& operator=(Fragment&&) = delete;

		size_t GetWidth() const;
		size_t GetHeight() const;
	private:
		size_t mWidth;
		size_t mHeight;
		ColorRGBA8* mpPixels;
	};
}
