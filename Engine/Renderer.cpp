#include "pch.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

using namespace ieg;

const size_t Renderer::mGlobalScale{ 4 };

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

void Renderer::RenderTexture(const Texture2D& texture, Vec2<size_t> pos) const
{
	SDL_Rect dst{ int(pos.GetX() * mGlobalScale), int(pos.GetY() * mGlobalScale), 0, 0 };
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.w *= 4;
	dst.h *= 4;
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, Vec2<size_t> srcPos, Vec2<size_t> srcSize, Vec2<size_t> dstPos) const
{
	SDL_Rect src{ int(srcPos.GetX()), int(srcPos.GetY()), int(srcSize.GetX()), int(srcSize.GetY()) };
	SDL_Rect dst{ int(dstPos.GetX() * mGlobalScale), int(dstPos.GetY() * mGlobalScale), int(srcSize.GetX() * mGlobalScale), int(srcSize.GetY() * mGlobalScale) };
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

SDL_Renderer* Renderer::GetSDLRenderer() const
{
	return mpSDLRenderer;
}
