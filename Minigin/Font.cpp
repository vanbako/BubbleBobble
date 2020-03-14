#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "Font.h"

ieg::Font::Font(const std::string& fullPath, unsigned int size)
	: mFont{ nullptr }
	, mSize{ size } 
{
	mFont = TTF_OpenFont(fullPath.c_str(), size);
	if (mFont == nullptr)
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
}

ieg::Font::~Font()
{
	TTF_CloseFont(mFont);
}

TTF_Font* ieg::Font::GetFont() const {
	return mFont;
}
