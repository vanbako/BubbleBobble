#include "pch.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

void ieg::Renderer::Init(SDL_Window* window)
{
	mpSDLRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mpSDLRenderer == nullptr)
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
}

void ieg::Renderer::Render(SceneManager* pSceneManager) const
{
	SDL_RenderClear(mpSDLRenderer);
	pSceneManager->Render();
	SDL_RenderPresent(mpSDLRenderer);
}

void ieg::Renderer::Destroy()
{
	if (mpSDLRenderer != nullptr)
	{
		SDL_DestroyRenderer(mpSDLRenderer);
		mpSDLRenderer = nullptr;
	}
}

void ieg::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void ieg::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer* ieg::Renderer::GetSDLRenderer() const
{
	return mpSDLRenderer;
}
