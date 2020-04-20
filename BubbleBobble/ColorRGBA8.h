#pragma once

namespace ieg
{
	class ColorRGBA8 final
	{
	public:
		explicit ColorRGBA8();
		~ColorRGBA8() = default;

		void SetR(unsigned char r);
		void SetG(unsigned char g);
		void SetB(unsigned char b);
		void SetA(unsigned char a);
	private:
		unsigned char
			mR,
			mG,
			mB,
			mA;
	};
}
