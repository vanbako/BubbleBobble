#include "pch.h"
#include "RenderViewComponent.h"
#include "TransformModelComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Minigin.h"

using namespace ieg;

RenderViewComponent::RenderViewComponent(Minigin* pEngine)
	: ViewComponent(pEngine)
	, mpTransformComponent{ nullptr }
	, mpTexture{ nullptr }
	, mWidth{ 0.f }
	, mHeight{ 0.f }
	, mIndex{ 0 }
{
}

void RenderViewComponent::Render() const
{
	if (mpTransformComponent != nullptr && mpTexture != nullptr)
	{
		const auto pos{ mpTransformComponent->GetPosition() };
		if (mWidth == 0.f)
			mpEngine->GetRenderer()->RenderTexture(*mpTexture, pos.x, pos.y);
		else
			mpEngine->GetRenderer()->RenderTexture(*mpTexture, mWidth * float(mIndex), 0.f, mWidth, mHeight, pos.x, pos.y);
	}
}

void RenderViewComponent::SetTransformComponent(TransformModelComponent* pTransformComponent)
{
	mpTransformComponent = pTransformComponent;
}

void RenderViewComponent::SetTexture(const std::string& file)
{
	mpTexture = mpEngine->GetResourceManager()->LoadTexture(file, mpEngine->GetRenderer());
}

// When Texture2D is used, we don't remove the old one from ResourceManager
// as it might be used for other RenderComponents
void RenderViewComponent::SetTexture(Texture2D* pTexture)
{
	mpTexture = pTexture;
}

void RenderViewComponent::SetSize(float width, float height)
{
	mWidth = width;
	mHeight = height;
}

void RenderViewComponent::SetIndex(size_t index)
{
	mIndex = index;
}

Texture2D* RenderViewComponent::SetTexture(SDL_Texture* pSDLTexture)
{
	mpTexture = mpEngine->GetResourceManager()->CreateTexture(pSDLTexture);
	return mpTexture;
}

// When SDL_Texture is used, it's a new one, so we remove the old
// Removing the old is mainly used for changing text textures
// as this is way too confusing, I changed this to ReplaceTexture
Texture2D* RenderViewComponent::ReplaceTexture(SDL_Texture* pSDLTexture)
{
	if (mpTexture != nullptr)
		mpEngine->GetResourceManager()->RemoveTexture(mpTexture);
	mpTexture = mpEngine->GetResourceManager()->CreateTexture(pSDLTexture);
	return mpTexture;
}
