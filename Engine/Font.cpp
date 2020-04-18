#include "pch.h"
#include <SDL_ttf.h>
#include "Font.h"

using namespace ieg;

Font::Font(const std::string& fullPath, unsigned int size)
	: mFont{ nullptr }
	, mSize{ size } 
{
	mFont = TTF_OpenFont(fullPath.c_str(), size);
	if (mFont == nullptr)
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
}

Font::~Font()
{
	TTF_CloseFont(mFont);
}

TTF_Font* Font::GetFont() const {
	return mFont;
}
