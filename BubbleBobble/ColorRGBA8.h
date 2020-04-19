#pragma once

namespace ieg
{
	class ColorRGBA8
	{
	public:
		ColorRGBA8() = default;
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
