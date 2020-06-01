#include "pch.h"
#include "ReloadingState.h"
#include "CharacterComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/ModelComponent.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

const float ReloadingState::mReloadTime{ 0.1f };

ReloadingState::ReloadingState(ModelComponent* pModelComponent)
	: CharacterWeaponState(pModelComponent)
	, mReloadTimer{ mReloadTime }
{
}

void ReloadingState::Update(const float deltaTime)
{
	mReloadTimer -= deltaTime;
	if (mReloadTimer <= 0.f)
	{
		mReloadTimer = mReloadTime;
		ReloadDone();
	}
}

void ReloadingState::ReloadDone()
{
	((CharacterComponent*)mpModelComponent)->SetReadyState();
}
