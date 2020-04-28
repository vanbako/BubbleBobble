#include "pch.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "TextViewComponent.h"
#include "RenderViewComponent.h"
#include "Minigin.h"
#include "Texture2D.h"

using namespace ieg;

TextViewComponent::TextViewComponent(Minigin* pEngine, const Font* pFont)
	: ViewComponent(pEngine)
	, mpFont{ pFont }
	, mNeedsUpdate{ true }
	, mText{}
	, mpRenderComponent{ nullptr }
{
}

void TextViewComponent::Update(const float deltaTime)
{
	(deltaTime);
	if (mNeedsUpdate && mpRenderComponent != nullptr)
	{
		const SDL_Color color{ 255,255,255 };
		const auto pSurf{ TTF_RenderText_Blended(mpFont->GetFont(), mText.c_str(), color) };
		if (pSurf == nullptr)
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		SDL_Texture* pSDLTexture{ SDL_CreateTextureFromSurface(mpEngine->GetRenderer()->GetSDLRenderer(), pSurf) };
		if (pSDLTexture == nullptr)
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		SDL_FreeSurface(pSurf);

		mpRenderComponent->ReplaceTexture(pSDLTexture);
		mNeedsUpdate = false;
	}
}

void TextViewComponent::SetRenderComponent(RenderViewComponent* pRenderComponent)
{
	mpRenderComponent = pRenderComponent;
}

void TextViewComponent::SetText(const std::string& text)
{
	mText = text;
	mNeedsUpdate = true;
}
