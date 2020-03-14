#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

ieg::Texture2D::Texture2D(SDL_Texture* pTexture)
	: mpTexture{ pTexture }
{
}

ieg::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(mpTexture);
}

SDL_Texture* ieg::Texture2D::GetSDLTexture() const
{
	return mpTexture;
}
