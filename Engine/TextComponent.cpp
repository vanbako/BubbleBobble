#include "pch.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "Texture2D.h"

ieg::TextComponent::TextComponent(const Font* pFont, Renderer* pRenderer)
	: mpFont{ pFont }
	, mpRenderer{ pRenderer }
	, mNeedsUpdate{ true }
	, mText{}
	, mpRenderComponent{ nullptr }
{
}

void ieg::TextComponent::Update(const float deltaTime)
{
	(deltaTime);
	if (mNeedsUpdate && mpRenderComponent != nullptr)
	{
		const SDL_Color color{ 255,255,255 };
		const auto pSurf{ TTF_RenderText_Blended(mpFont->GetFont(), mText.c_str(), color) };
		if (pSurf == nullptr)
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		auto pTexture{ SDL_CreateTextureFromSurface(mpRenderer->GetSDLRenderer(), pSurf) };
		if (pTexture == nullptr)
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		SDL_FreeSurface(pSurf);
		mpRenderComponent->SetTexture(new Texture2D{ pTexture });
		mNeedsUpdate = false;
	}
}

void ieg::TextComponent::SetRenderComponent(RenderComponent* pRenderComponent)
{
	mpRenderComponent = pRenderComponent;
}

void ieg::TextComponent::SetText(const std::string & text)
{
	mText = text;
	mNeedsUpdate = true;
}
