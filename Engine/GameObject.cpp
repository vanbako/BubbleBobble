#include "pch.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

using namespace ieg;

GameObject::GameObject( ResourceManager* pRes)
	: mpRes{ pRes }
	, mpComponents{}
{
}

GameObject::~GameObject()
{
	for (Component* pComponent : mpComponents)
		delete pComponent;
}

void GameObject::Update(const float deltaTime)
{
	(deltaTime);
	for (Component* pComponent : mpComponents)
		pComponent->Update(deltaTime);
}

void GameObject::Render() const
{
	for (Component* pComponent : mpComponents)
		pComponent->Render();
}
