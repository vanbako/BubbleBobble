#include "pch.h"
#include "AvatarComponent.h"
#include "LevelComponent.h"
#include "HudComponent.h"
#include "StandingState.h"
#include "JumpingState.h"
#include "FallingState.h"
#include "ReadyState.h"
#include "FiringState.h"
#include "ReloadingState.h"
#include "../Engine/Minigin.h"
#include "../Engine/Scene.h"
#include "../Engine/InputManager.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/ColliderModelComponent.h"
#include "../Engine/ObsSubject.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/Audio.h"

using namespace ieg;

const float AvatarComponent::mMoveHor2PixelsTime{ 0.04f };
const float AvatarComponent::mMoveVer2PixelsTime{ 0.02f };

AvatarComponent::AvatarComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpGOLevel{ nullptr }
	, mpStandingState{ new StandingState{ this } }
	, mpJumpingState{ new JumpingState{ this } }
	, mpFallingState{ new FallingState{ this } }
	, mpCurKineticState{ nullptr }
	, mpNewKineticState{ nullptr }
	, mpReadyState{ new ReadyState{ this } }
	, mpFiringState{ new FiringState{ this } }
	, mpReloadingState{ new ReloadingState{ this } }
	, mpCurWeaponState{ nullptr }
	, mpNewWeaponState{ nullptr }
	, mIsHorMoving{ 0 }
	, mMoveHorDelay{ mMoveHor2PixelsTime }
	, mpObsSubject{ new ObsSubject{} }
{
	mpCurKineticState = mpStandingState;
	mpNewKineticState = mpStandingState;
	mpCurWeaponState = mpReadyState;
	mpNewWeaponState = mpReadyState;
	mJumpSoundId = pEngine->GetServiceLocator()->GetAudio()->AddSound("../Data/Audio/jump.wav", false);
}

AvatarComponent::~AvatarComponent()
{
	delete mpReloadingState;
	delete mpFiringState;
	delete mpReadyState;
	delete mpFallingState;
	delete mpJumpingState;
	delete mpStandingState;
	delete mpObsSubject;
	mpGameObject->GetScene()->GetInputManager()->DeleteInputActions(this);
}

void AvatarComponent::Update(const float deltaTime)
{
	mpCurKineticState->Update(deltaTime);
	mpCurWeaponState->Update(deltaTime);
	if (mIsHorMoving > 0)
	{
		--mIsHorMoving;
		mMoveHorDelay -= deltaTime;
	}
}

void AvatarComponent::Collision()
{
	unsigned short collision{ mpGOLevel->GetModelComponent<LevelComponent>()->CheckAvatarCollision(
	mpGameObject->GetModelComponent<TransformModelComponent>(),
	mpGameObject->GetModelComponent<ColliderModelComponent>()) };
	if (mpNewKineticState == mpStandingState)
		if ((collision & 1) != 0)
		{
			mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
			collision = mpGOLevel->GetModelComponent<LevelComponent>()->CheckAvatarCollision(
				mpGameObject->GetModelComponent<TransformModelComponent>(),
				mpGameObject->GetModelComponent<ColliderModelComponent>());
		}
		else
			mpCurKineticState->Fall();
	if ((collision & 12) != 0)
		mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosX();
	if ((collision & 2) != 0 && mpNewKineticState == mpStandingState)
		mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
	if ((collision & 1) != 0 && mpNewKineticState == mpFallingState)
	{
		mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
		mpCurKineticState->Land();
	}
}

void AvatarComponent::Switch()
{
	mpCurKineticState = mpNewKineticState;
	mpCurWeaponState = mpNewWeaponState;
}

ObsSubject* AvatarComponent::GetObsSubject()
{
	return mpObsSubject;
}

void AvatarComponent::SetLevel(GameObject* pLevel)
{
	mpGOLevel = pLevel;
}

void AvatarComponent::SetFallingState()
{
	mpNewKineticState = mpFallingState;
}

void ieg::AvatarComponent::SetJumpingState()
{
	((JumpingState*)mpJumpingState)->ResetJumpHeight();
	mpNewKineticState = mpJumpingState;
	mpEngine->GetServiceLocator()->GetAudio()->PlaySound(mJumpSoundId);
}

void AvatarComponent::SetStandingState()
{
	mpNewKineticState = mpStandingState;
}

void AvatarComponent::SetReadyState()
{
	mpNewWeaponState = mpReadyState;
}

void AvatarComponent::SetFiringState()
{
	mpNewWeaponState = mpFiringState;
}

void AvatarComponent::SetReloadingState()
{
	mpNewWeaponState = mpReloadingState;
}

void AvatarComponent::FireBubble()
{
	TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
	Vec2<int> pos{};
	pos = pTransform->GetNewPos();
	if (pTransform->GetIsLookingLeft())
		pos.Move(-16, 0);
	else
		pos.Move(16, 0);
	mpGOLevel->GetModelComponent<LevelComponent>()->FireBubble(pos);
}

void AvatarComponent::Fire()
{
	mpCurWeaponState->Fire();
}

void AvatarComponent::Jump()
{
	mpCurKineticState->Jump();
}

void AvatarComponent::Left()
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

void AvatarComponent::Right()
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

float AvatarComponent::GetMoveVer2PixelsTime()
{
	return mMoveVer2PixelsTime;
}
