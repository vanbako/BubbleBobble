#include "pch.h"
#include "AvatarComponent.h"
#include "LevelComponent.h"
#include "HudComponent.h"
#include "StandingState.h"
#include "JumpingState.h"
#include "FallingState.h"
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

const float AvatarComponent::mFireWaitTime{ 0.4f };
const float AvatarComponent::mMoveHor2PixelsTime{ 0.04f };
const float AvatarComponent::mMoveVer2PixelsTime{ 0.02f };

AvatarComponent::AvatarComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: ModelComponent(pGameObject, pEngine)
	, mpGOLevel{ nullptr }
	, mpStandingState{ new StandingState{ this } }
	, mpJumpingState{ new JumpingState{ this } }
	, mpFallingState{ new FallingState{ this } }
	, mpCurState{ nullptr }
	, mpNewState{ nullptr }
	, mCurIsFiring{ false }
	, mNewIsFiring{ false }
	, mIsHorMoving{ 0 }
	, mFireDelay{ mFireWaitTime }
	, mMoveHorDelay{ mMoveHor2PixelsTime }
	, mpObsSubject{ new ObsSubject{} }
{
	mpCurState = mpStandingState;
	mpNewState = mpStandingState;
	mJumpSoundId = pEngine->GetServiceLocator()->GetAudio()->AddSound("../Data/Audio/jump.wav", false);
}

AvatarComponent::~AvatarComponent()
{
	delete mpFallingState;
	delete mpJumpingState;
	delete mpStandingState;
	delete mpObsSubject;
	mpGameObject->GetScene()->GetInputManager()->DeleteInputActions(this);
}

void AvatarComponent::Update(const float deltaTime)
{
	mpCurState->Update(deltaTime);
	if (mIsHorMoving > 0)
	{
		--mIsHorMoving;
		mMoveHorDelay -= deltaTime;
	}
	if (mCurIsFiring && mFireDelay == mFireWaitTime)
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
	if (mCurIsFiring)
	{
		mFireDelay -= deltaTime;
		if (mFireDelay <= 0.f)
		{
			mFireDelay = mFireWaitTime;
			mNewIsFiring = false;
		}
	}
}

void AvatarComponent::Collision()
{
	unsigned short collision{ mpGOLevel->GetModelComponent<LevelComponent>()->CheckAvatarCollision(
	mpGameObject->GetModelComponent<TransformModelComponent>(),
	mpGameObject->GetModelComponent<ColliderModelComponent>()) };
	if (mpNewState == mpStandingState)
		if ((collision & 1) != 0)
		{
			mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
			collision = mpGOLevel->GetModelComponent<LevelComponent>()->CheckAvatarCollision(
				mpGameObject->GetModelComponent<TransformModelComponent>(),
				mpGameObject->GetModelComponent<ColliderModelComponent>());
		}
		else
			mpNewState = mpFallingState;
	if ((collision & 12) != 0)
		mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosX();
	if ((collision & 2) != 0 && mpNewState == mpStandingState)
		mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
	if ((collision & 1) != 0 && mpNewState == mpFallingState)
	{
		mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
		mpNewState = mpStandingState;
	}
}

void AvatarComponent::Switch()
{
	mpCurState = mpNewState;
	mCurIsFiring = mNewIsFiring;
}

ObsSubject* AvatarComponent::GetObsSubject()
{
	return mpObsSubject;
}

void AvatarComponent::SetFiring(bool isFiring)
{
	mNewIsFiring = isFiring;
}

void AvatarComponent::SetLevel(GameObject* pLevel)
{
	mpGOLevel = pLevel;
}

void AvatarComponent::SetFallingState()
{
	mpNewState = mpFallingState;
}

void AvatarComponent::Fire()
{
	mNewIsFiring = true;
}

void AvatarComponent::Jump()
{
	if (mpCurState == mpStandingState)
	{
		((JumpingState*)mpJumpingState)->ResetJumpHeight();
		mpNewState = mpJumpingState;
		mpEngine->GetServiceLocator()->GetAudio()->PlaySound(mJumpSoundId);
	}
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
