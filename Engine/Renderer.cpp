#include "pch.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

using namespace ieg;

const int Renderer::mGlobalScale{ 4 };

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

void Renderer::RenderTexture(const Texture2D& texture, Vec2<int> pos) const
{
	SDL_Rect dst{ pos.GetX() * mGlobalScale, pos.GetY() * mGlobalScale, 0, 0 };
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.w *= 4;
	dst.h *= 4;
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, Vec2<int> srcPos, Vec2<int> srcSize, Vec2<int> dstPos) const
{
	SDL_Rect src{ srcPos.GetX(), srcPos.GetY(), srcSize.GetX(), srcSize.GetY() };
	SDL_Rect dst{ dstPos.GetX() * mGlobalScale, dstPos.GetY() * mGlobalScale, srcSize.GetX() * mGlobalScale, srcSize.GetY() * mGlobalScale };
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

SDL_Renderer* Renderer::GetSDLRenderer() const
{
	return mpSDLRenderer;
}
