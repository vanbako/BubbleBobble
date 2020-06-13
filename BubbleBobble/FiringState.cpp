#include "pch.h"
#include "FiringState.h"
#include "CharacterComponent.h"

using namespace ieg;

const float FiringState::mFiringTime{ 0.3f };

FiringState::FiringState(ModelComponent* pModelComponent)
	: CharacterWeaponState(pModelComponent)
	, mFiringTimer{ mFiringTime }
{
}

void FiringState::Update(const float deltaTime)
{
	mFiringTimer -= deltaTime;
	if (mFiringTimer <= 0.f)
	{
		mFiringTimer = mFiringTime;
		FiringDone();
	}
}

void FiringState::FiringDone()
{
	((CharacterComponent*)mpModelComponent)->SetReloadingState();
}
