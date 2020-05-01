#include "pch.h"
#include "GameObject.h"

using namespace ieg;

GameObject::GameObject(Scene* pScene)
	: SceneObject(pScene)
	, mpModelComponents{}
	, mpViewComponents{}
{
}

GameObject::~GameObject()
{
	for (ModelComponent* pModelComponent : mpModelComponents)
		delete pModelComponent;
	for (ViewComponent* pViewComponent : mpViewComponents)
		delete pViewComponent;
}

void GameObject::Update(const float deltaTime)
{
	for (ModelComponent* pModelComponent : mpModelComponents)
		pModelComponent->Update(deltaTime);
	for (ViewComponent* pViewComponent : mpViewComponents)
		pViewComponent->Update(deltaTime);
}

void GameObject::Render() const
{
	for (ViewComponent* pViewComponent : mpViewComponents)
		pViewComponent->Render();
}
