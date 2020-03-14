#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

ieg::GameObject::GameObject(ResourceManager* pRes)
	: mpRes{ pRes }
	, mpComponents{}
{
}

ieg::GameObject::~GameObject()
{
	for (Component* pComponent : mpComponents)
		delete pComponent;
}

void ieg::GameObject::Add(Component* pComponent)
{
	if (pComponent != nullptr)
		mpComponents.push_back(pComponent);
}

void ieg::GameObject::Update(const float deltaTime)
{
	(deltaTime);
	for (Component* pComponent : mpComponents)
		pComponent->Update(deltaTime);
}

void ieg::GameObject::Render() const
{
	for (Component* pComponent : mpComponents)
		pComponent->Render();
}
