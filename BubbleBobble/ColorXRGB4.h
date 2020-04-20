#pragma once

namespace ieg
{
	class ColorRGBA8;

	class ColorXRGB4 final
	{
	public:
		explicit ColorXRGB4();
		~ColorXRGB4() = default;

		void ConvertRGBA8(ColorRGBA8* pColor);
	private:
		unsigned char
			mXR,
			mGB;
	};
}
