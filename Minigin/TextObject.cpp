#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

ieg::TextObject::TextObject(const ResourceManager* pRes, const std::string& text, const Font* pFont)
	: mpRes{ pRes }
	, mNeedsUpdate{ true }
	, mText{ text }
	, mTransform{}
	, mpFont{ pFont }
	, mpTexture{ nullptr }
{
}

ieg::TextObject::~TextObject()
{
	if (mpTexture != nullptr)
		delete mpTexture;
}

void ieg::TextObject::Update(const float deltaTime)
{
	(deltaTime);
	if (mNeedsUpdate)
	{
		const SDL_Color color{ 255,255,255 }; // only white text is supported now
		const auto pSurf{ TTF_RenderText_Blended(mpFont->GetFont(), mText.c_str(), color) };
		if (pSurf == nullptr)
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		auto pTexture{ SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), pSurf) };
		if (pTexture == nullptr)
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		SDL_FreeSurface(pSurf);
		if (mpTexture != nullptr)
			delete mpTexture;
		mpTexture = new Texture2D{ pTexture };
		mNeedsUpdate = false;
	}
}

void ieg::TextObject::Render() const
{
	if (mpTexture != nullptr)
	{
		const auto pos{ mTransform.GetPosition() };
		Renderer::GetInstance().RenderTexture(*mpTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void ieg::TextObject::SetText(const std::string& text)
{
	mText = text;
	mNeedsUpdate = true;
}

void ieg::TextObject::SetPosition(const float x, const float y)
{
	mTransform.SetPosition(x, y, 0.0f);
}
