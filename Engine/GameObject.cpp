#include "pch.h"
#include "GameObject.h"

using namespace ieg;

GameObject::GameObject(Scene* pScene)
	: SceneObject(pScene)
	, mpCtrlComponents{}
	, mpModelComponents{}
	, mpViewComponents{}
	, mIsActive{ false }
{
}

GameObject::~GameObject()
{
	for (CtrlComponent* pCtrlComponent : mpCtrlComponents)
		delete pCtrlComponent;
	for (ModelComponent* pModelComponent : mpModelComponents)
		delete pModelComponent;
	for (ViewComponent* pViewComponent : mpViewComponents)
		delete pViewComponent;
}

void GameObject::Update(const float deltaTime)
{
	if (mIsActive)
	{
		for (CtrlComponent* pCtrlComponent : mpCtrlComponents)
			pCtrlComponent->Update(deltaTime);
		for (ModelComponent* pModelComponent : mpModelComponents)
			pModelComponent->Update(deltaTime);
		for (ModelComponent* pModelComponent : mpModelComponents)
			pModelComponent->Collision();
		for (ModelComponent* pModelComponent : mpModelComponents)
			pModelComponent->Switch();
		for (ViewComponent* pViewComponent : mpViewComponents)
			pViewComponent->Update(deltaTime);
	}
}

void GameObject::Render() const
{
	if (mIsActive)
	{
		for (ViewComponent* pViewComponent : mpViewComponents)
			pViewComponent->Render();
	}
}
