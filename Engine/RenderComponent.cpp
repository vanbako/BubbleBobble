#include "pch.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

ieg::RenderComponent::RenderComponent(ResourceManager* pResourceManager, Renderer* pRenderer)
	: mpResourceManager{ pResourceManager }
	, mpRenderer{ pRenderer }
	, mpTransformComponent{ nullptr }
	, mpTexture{ nullptr }
{
}

void ieg::RenderComponent::Render() const
{
	if (mpTransformComponent != nullptr && mpTexture != nullptr)
	{
		const auto pos{ mpTransformComponent->GetPosition() };
		mpRenderer->RenderTexture(*mpTexture, pos.x, pos.y);
	}
}

void ieg::RenderComponent::SetTransformComponent(TransformComponent* pTransformComponent)
{
	mpTransformComponent = pTransformComponent;
}

void ieg::RenderComponent::SetTexture(const std::string& file)
{
	mpTexture = mpResourceManager->LoadTexture(file, mpRenderer);
}

void ieg::RenderComponent::SetTexture(Texture2D* pTexture)
{
	if (mpTexture != nullptr)
		mpResourceManager->RemoveTexture(mpTexture);
	mpResourceManager->AddTexture(pTexture);
	mpTexture = pTexture;
}
