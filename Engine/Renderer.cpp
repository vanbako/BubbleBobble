#include "pch.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

using namespace ieg;

ieg::Renderer::Renderer()
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
	SDL_Rect dst{};
	dst.x = static_cast<int>(x) * 4;
	dst.y = static_cast<int>(y) * 4;
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.w *= 4;
	dst.h *= 4;
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer* Renderer::GetSDLRenderer() const
{
	return mpSDLRenderer;
}
