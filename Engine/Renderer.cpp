#include "pch.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

using namespace ieg;

Renderer::Renderer()
	: mpSDLRenderer{ nullptr }
{
}

void Renderer::Init(SDL_Window* window)
{
	mpSDLRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mpSDLRenderer == nullptr)
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
}

void Renderer::Render(SceneManager* pSceneManager) const
{
	SDL_RenderClear(mpSDLRenderer);
	pSceneManager->Render();
	SDL_RenderPresent(mpSDLRenderer);
}

void Renderer::Destroy()
{
	if (mpSDLRenderer != nullptr)
	{
		SDL_DestroyRenderer(mpSDLRenderer);
		mpSDLRenderer = nullptr;
	}
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{int(x) * 4, int(y) * 4, 0, 0};
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.w *= 4;
	dst.h *= 4;
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, float srcX, float srcY, float width, float height, float dstX, float dstY) const
{
	SDL_Rect src{ int(srcX), int(srcY), int(width), int(height) };
	SDL_Rect dst{ int(dstX) * 4, int(dstY) * 4, int(width) * 4, int(height) * 4 };
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

SDL_Renderer* Renderer::GetSDLRenderer() const
{
	return mpSDLRenderer;
}
