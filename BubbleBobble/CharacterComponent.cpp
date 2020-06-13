#include "pch.h"
#include "CharacterComponent.h"
#include "StandingState.h"
#include "JumpingState.h"
#include "FallingState.h"
#include "FloatingState.h"
#include "ReadyState.h"
#include "FiringState.h"
#include "ReloadingState.h"
#include "LevelComponent.h"

using namespace ieg;

const float CharacterComponent::mMoveHor2PixelsTime{ 0.04f };
const float CharacterComponent::mMoveVer2PixelsTime{ 0.02f };

CharacterComponent::CharacterComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpGOLevel{ nullptr }
	, mpObsSubject{ new ObsSubject{} }
	, mpStandingState{ new StandingState{ this } }
	, mpJumpingState{ new JumpingState{ this } }
	, mpFallingState{ new FallingState{ this } }
	, mpFloatingState{ new FloatingState{ this } }
	, mpCurKineticState{ nullptr }
	, mpNewKineticState{ nullptr }
	, mpReadyState{ new ReadyState{ this } }
	, mpFiringState{ new FiringState{ this } }
	, mpReloadingState{ new ReloadingState{ this } }
	, mpCurWeaponState{ nullptr }
	, mpNewWeaponState{ nullptr }
	, mIsHorMoving{ 0 }
	, mMoveHorDelay{ mMoveHor2PixelsTime }
{
	mpCurKineticState = mpStandingState;
	mpNewKineticState = mpStandingState;
	mpCurWeaponState = mpReadyState;
	mpNewWeaponState = mpReadyState;
}

CharacterComponent::~CharacterComponent()
{
	delete mpReloadingState;
	delete mpFiringState;
	delete mpReadyState;
	delete mpFloatingState;
	delete mpFallingState;
	delete mpJumpingState;
	delete mpStandingState;
	delete mpObsSubject;
}

void CharacterComponent::Update(const float deltaTime)
{
	mpCurKineticState->Update(deltaTime);
	mpCurWeaponState->Update(deltaTime);
}

void CharacterComponent::Collision()
{
	// LevelCollision
	TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
	ColliderModelComponent* pCollider{ mpGameObject->GetModelComponent<ColliderModelComponent>() };
	unsigned short collision{ mpGOLevel->GetModelComponent<LevelComponent>()->CheckAvatarCollision(pTransform, pCollider) };
	if (mpNewKineticState == mpStandingState)
		if ((collision & 1) != 0)
		{
			pTransform->ResetNewPosY();
			collision = mpGOLevel->GetModelComponent<LevelComponent>()->CheckAvatarCollision(pTransform, pCollider);
		}
		else
			mpCurKineticState->Fall();
	if ((collision & 12) != 0)
		pTransform->ResetNewPosX();
	if ((collision & 2) != 0 && mpNewKineticState == mpStandingState)
		pTransform->ResetNewPosY();
	if ((collision & 1) != 0 && mpNewKineticState == mpFallingState)
	{
		pTransform->ResetNewPosY();
		mpCurKineticState->Land();
	}
}

void CharacterComponent::Switch()
{
	mpCurKineticState = mpNewKineticState;
	mpCurWeaponState = mpNewWeaponState;
}

void CharacterComponent::Fire()
{
	mpCurWeaponState->Fire();
}

void CharacterComponent::Jump()
{
	mpCurKineticState->Jump();
}

void CharacterComponent::Left()
{
	if (mMoveHorDelay <= 0)
	{
		TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
		pTransform->SetIsLookingLeft(true);
		pTransform->Move(-2, 0);
		mMoveHorDelay += mMoveHor2PixelsTime;
	}
	mIsHorMoving = 2;
}

void CharacterComponent::Right()
{
	if (mMoveHorDelay <= 0)
	{
		TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
		pTransform->SetIsLookingLeft(false);
		pTransform->Move(2, 0);
		mMoveHorDelay += mMoveHor2PixelsTime;
	}
	mIsHorMoving = 2;
}

void CharacterComponent::SetFloatingState()
{
	mpNewKineticState = mpFloatingState;
}

bool ieg::CharacterComponent::IsFloatingState()
{
	return mpCurKineticState == mpFloatingState;
}

void CharacterComponent::SetJumpingState()
{
	mpJumpingState->ResetJumpHeight();
	mpNewKineticState = mpJumpingState;
}

void CharacterComponent::SetFallingState()
{
	mpNewKineticState = mpFallingState;
}

void CharacterComponent::SetStandingState()
{
	mpNewKineticState = mpStandingState;
}

void CharacterComponent::SetReadyState()
{
	mpNewWeaponState = mpReadyState;
}

void CharacterComponent::SetFiringState()
{
	mpNewWeaponState = mpFiringState;
}

void CharacterComponent::SetReloadingState()
{
	mpNewWeaponState = mpReloadingState;
}
