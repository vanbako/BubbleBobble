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
#include "LivingState.h"
#include "DyingState.h"
#include "InvincibleState.h"
#include "AvatarManager.h"
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
	: CharacterComponent(pGameObject, pEngine)
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
	, mpLivingState{ new LivingState{ this } }
	, mpDyingState{ new DyingState{ this } }
	, mpInvincibleState{ new InvincibleState{ this } }
	, mpCurHealthState{ nullptr }
	, mpNewHealthState{ nullptr }
	, mIsHorMoving{ 0 }
	, mMoveHorDelay{ mMoveHor2PixelsTime }
	, mpObsSubject{ new ObsSubject{} }
{
	mpCurKineticState = mpStandingState;
	mpNewKineticState = mpStandingState;
	mpCurWeaponState = mpReadyState;
	mpNewWeaponState = mpReadyState;
	mpCurHealthState = mpLivingState;
	mpNewHealthState = mpLivingState;
	mJumpSoundId = pEngine->GetServiceLocator()->GetAudio()->AddSound("../Data/Audio/jump.wav", false);
}

AvatarComponent::~AvatarComponent()
{
	delete mpInvincibleState;
	delete mpDyingState;
	delete mpLivingState;
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
	if (mpCurHealthState != mpDyingState)
	{
		mpCurKineticState->Update(deltaTime);
		mpCurWeaponState->Update(deltaTime);
	}
	mpCurHealthState->Update(deltaTime);
	if (mIsHorMoving > 0)
	{
		--mIsHorMoving;
		mMoveHorDelay -= deltaTime;
	}
}

void AvatarComponent::Collision()
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
	// NpcCollision
	if (mpCurHealthState == mpLivingState && mpGOLevel->GetModelComponent<LevelComponent>()->CheckNpcCollision(pTransform, pCollider))
		SetDyingState();
}

void AvatarComponent::Switch()
{
	mpCurKineticState = mpNewKineticState;
	mpCurWeaponState = mpNewWeaponState;
	mpCurHealthState = mpNewHealthState;
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

void AvatarComponent::SetJumpingState()
{
	mpJumpingState->ResetJumpHeight();
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

void AvatarComponent::SetLivingState()
{
	mpNewHealthState = mpLivingState;
}

void AvatarComponent::SetDyingState()
{
	mpNewHealthState = mpDyingState;
}

void AvatarComponent::SetInvincibleState()
{
	mpNewHealthState = mpInvincibleState;
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

void AvatarComponent::Spawn()
{
	mpGameObject->GetModelComponent<TransformModelComponent>()->SetPos(AvatarManager::GetAvatarInitialPos(0));
	mpGameObject->GetModelComponent<TransformModelComponent>()->Switch();
}

void AvatarComponent::Fire()
{
	if (mpCurHealthState != mpDyingState)
		mpCurWeaponState->Fire();
}

void AvatarComponent::Jump()
{
	if (mpCurHealthState != mpDyingState)
		mpCurKineticState->Jump();
}

void AvatarComponent::Left()
{
	if (mpCurHealthState != mpDyingState)
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
}

void AvatarComponent::Right()
{
	if (mpCurHealthState != mpDyingState)
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
}

float AvatarComponent::GetMoveVer2PixelsTime()
{
	return mMoveVer2PixelsTime;
}
