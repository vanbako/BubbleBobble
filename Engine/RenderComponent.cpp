#include "pch.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace ieg;

RenderComponent::RenderComponent(ResourceManager* pResourceManager, Renderer* pRenderer)
	: mpResourceManager{ pResourceManager }
	, mpRenderer{ pRenderer }
	, mpTransformComponent{ nullptr }
	, mpTexture{ nullptr }
{
}

void RenderComponent::Render() const
{
	if (mpTransformComponent != nullptr && mpTexture != nullptr)
	{
		const auto pos{ mpTransformComponent->GetPosition() };
		mpRenderer->RenderTexture(*mpTexture, pos.x, pos.y);
	}
}

void RenderComponent::SetTransformComponent(TransformComponent* pTransformComponent)
{
	mpTransformComponent = pTransformComponent;
}

void RenderComponent::SetTexture(const std::string& file)
{
	mpTexture = mpResourceManager->LoadTexture(file, mpRenderer);
}

// When Texture2D is used, we don't remove the old one from ResourceManager
// as it might be used for other RenderComponents
void RenderComponent::SetTexture(Texture2D* pTexture)
{
	mpTexture = pTexture;
}

// When SDL_Texture is used, it's a new one, so we remove the old
// Removing the old is mainly used for changing text textures
Texture2D* RenderComponent::SetTexture(SDL_Texture* pSDLTexture)
{
	if (mpTexture != nullptr)
		mpResourceManager->RemoveTexture(mpTexture);
	mpTexture = mpResourceManager->CreateTexture(pSDLTexture);
	return mpTexture;
}
