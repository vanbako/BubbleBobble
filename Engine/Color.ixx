export module Engine:Color;

namespace ieg
{
	export class ColorRGBA8 final
	{
	public:
		explicit ColorRGBA8();
		~ColorRGBA8() = default;
		ColorRGBA8(const ColorRGBA8&) = default;
		ColorRGBA8(ColorRGBA8&&) = default;
		ColorRGBA8& operator=(const ColorRGBA8&) = default;
		ColorRGBA8& operator=(ColorRGBA8&&) = default;

		void SetR(unsigned char r);
		void SetG(unsigned char g);
		void SetB(unsigned char b);
		void SetA(unsigned char a);
	private:
		unsigned char mR;
		unsigned char mG;
		unsigned char mB;
		unsigned char mA;
	};
}
