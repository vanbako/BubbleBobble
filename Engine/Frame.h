#pragma once

namespace ieg
{
	class ColorRGBA8;

	class Frame final
	{
	public:
		explicit Frame(size_t width, size_t height);
		~Frame();
		Frame(const Frame&) = delete;
		Frame(Frame&&) = delete;
		Frame& operator= (const Frame&) = delete;
		Frame& operator= (const Frame&&) = delete;

		size_t GetWidth() const;
		size_t GetHeight() const;
	private:
		size_t mWidth;
		size_t mHeight;
		ColorRGBA8* mpPixels;
	};
}
