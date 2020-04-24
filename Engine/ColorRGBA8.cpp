#include "pch.h"
#include "ColorRGBA8.h"

using namespace ieg;

ColorRGBA8::ColorRGBA8()
	: mR{ 0 }
	, mG{ 0 }
	, mB{ 0 }
	, mA{ 0 }
{
}

void ColorRGBA8::SetR(unsigned char r)
{
	mR = r;
}

void ColorRGBA8::SetG(unsigned char g)
{
	mG = g;
}

void ColorRGBA8::SetB(unsigned char b)
{
	mB = b;
}

void ColorRGBA8::SetA(unsigned char a)
{
	mA = a;
}
