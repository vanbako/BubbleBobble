#include "pch.h"
#include "Frame.h"
#include "ColorRGBA8.h"

using namespace ieg;

Frame::Frame(size_t width, size_t height)
	: mWidth{ width }
	, mHeight{ height }
	, mpPixels{ new ColorRGBA8[width * height] }
{
}

ieg::Frame::~Frame()
{
	delete[] mpPixels;
}

size_t ieg::Frame::GetWidth() const
{
	return mWidth;
}

size_t ieg::Frame::GetHeight() const
{
	return mHeight;
}
