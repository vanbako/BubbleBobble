#include "pch.h"
#include "Fragment.h"
#include "ColorRGBA8.h"

using namespace ieg;

Fragment::Fragment(size_t width, size_t height)
	: mWidth{ width }
	, mHeight{ height }
	, mpPixels{ new ColorRGBA8[width * height] }
{
}

Fragment::~Fragment()
{
	delete[] mpPixels;
}

size_t Fragment::GetWidth() const
{
	return mWidth;
}

size_t Fragment::GetHeight() const
{
	return mHeight;
}
