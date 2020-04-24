#pragma once

namespace ieg
{
	class ColorRGBA8;

	class ColorXRGB4 final
	{
	public:
		explicit ColorXRGB4();
		~ColorXRGB4() = default;
		ColorXRGB4(const ColorXRGB4&) = delete;
		ColorXRGB4(ColorXRGB4&&) = delete;
		ColorXRGB4& operator=(const ColorXRGB4&) = delete;
		ColorXRGB4& operator=(ColorXRGB4&&) = delete;

		void ConvertRGBA8(ColorRGBA8* pColor);
	private:
		unsigned char
			mXR,
			mGB;
	};
}
