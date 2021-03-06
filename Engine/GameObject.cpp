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

void GameObject::OnSceneActivation(int value)
{
	for (ModelComponent* pModelComponent : mpModelComponents)
		pModelComponent->OnSceneActivation(value);
}

void GameObject::OnSceneDeactivation(int value)
{
	for (ModelComponent* pModelComponent : mpModelComponents)
		pModelComponent->OnSceneDeactivation(value);
}

// Ctrl Components are now in a separate thread
//void GameObject::CtrlUpdate(const float deltaTime)
//{
//	if (mIsActive)
//		for (CtrlComponent* pCtrlComponent : mpCtrlComponents)
//			pCtrlComponent->Update(deltaTime);
//}

void GameObject::CtrlLock()
{
	std::chrono::duration<float> waitForLock{ 0.005f };
	if (mIsActive)
		for (CtrlComponent* pCtrlComponent : mpCtrlComponents)
			pCtrlComponent->Lock(waitForLock);
}

void GameObject::CtrlUnlock()
{
	if (mIsActive)
		for (CtrlComponent* pCtrlComponent : mpCtrlComponents)
			pCtrlComponent->Unlock();
}

void GameObject::ModelUpdate(const float deltaTime)
{
	if (mIsActive)
		for (ModelComponent* pModelComponent : mpModelComponents)
			pModelComponent->Update(deltaTime);
}

void GameObject::ModelCollision()
{
	if (mIsActive)
		for (ModelComponent* pModelComponent : mpModelComponents)
			pModelComponent->Collision();
}

void GameObject::ModelSwitch()
{
	if (mIsActive)
		for (ModelComponent* pModelComponent : mpModelComponents)
			pModelComponent->Switch();
}

void GameObject::ViewUpdate(const float deltaTime)
{
	if (mIsActive)
		for (ViewComponent* pViewComponent : mpViewComponents)
			pViewComponent->Update(deltaTime);
}

void GameObject::ViewRender() const
{
	if (mIsActive)
		for (ViewComponent* pViewComponent : mpViewComponents)
			pViewComponent->Render();
}
