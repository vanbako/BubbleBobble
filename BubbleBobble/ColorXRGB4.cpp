module BubbleBobble:Color;
import Engine;

using namespace ieg;

ColorXRGB4::ColorXRGB4()
	: mXR{ 0 }
	, mGB{ 0 }
{
}

void ColorXRGB4::ConvertRGBA8(ColorRGBA8* pColor)
{
	pColor->SetR((mXR & 0x0F) * (unsigned char)(17));
	pColor->SetG(((mGB & 0xF0) >> 4) * (unsigned char)(17));
	pColor->SetB((mGB & 0x0F) * (unsigned char)(17));
	if (mXR == 0 && mGB == 0)
		pColor->SetA(0);
	else
		pColor->SetA((unsigned char)0xFF);
}
