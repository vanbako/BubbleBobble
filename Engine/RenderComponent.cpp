#include "pch.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Minigin.h"

using namespace ieg;

RenderComponent::RenderComponent(Minigin* pEngine)
	: Component(pEngine)
	, mpTransformComponent{ nullptr }
	, mpTexture{ nullptr }
	, mWidth{ 0.f }
	, mHeight{ 0.f }
	, mIndex{ 0 }
{
}

void RenderComponent::Render() const
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

void RenderComponent::SetTransformComponent(TransformComponent* pTransformComponent)
{
	mpTransformComponent = pTransformComponent;
}

void RenderComponent::SetTexture(const std::string& file)
{
	mpTexture = mpEngine->GetResourceManager()->LoadTexture(file, mpEngine->GetRenderer());
}

// When Texture2D is used, we don't remove the old one from ResourceManager
// as it might be used for other RenderComponents
void RenderComponent::SetTexture(Texture2D* pTexture)
{
	mpTexture = pTexture;
}

void RenderComponent::SetSize(float width, float height)
{
	mWidth = width;
	mHeight = height;
}

void RenderComponent::SetIndex(size_t index)
{
	mIndex = index;
}

Texture2D* RenderComponent::SetTexture(SDL_Texture* pSDLTexture)
{
	mpTexture = mpEngine->GetResourceManager()->CreateTexture(pSDLTexture);
	return mpTexture;
}

// When SDL_Texture is used, it's a new one, so we remove the old
// Removing the old is mainly used for changing text textures
// as this is way too confusing, I changed this to ReplaceTexture
Texture2D* RenderComponent::ReplaceTexture(SDL_Texture* pSDLTexture)
{
	if (mpTexture != nullptr)
		mpEngine->GetResourceManager()->RemoveTexture(mpTexture);
	mpTexture = mpEngine->GetResourceManager()->CreateTexture(pSDLTexture);
	return mpTexture;
}
