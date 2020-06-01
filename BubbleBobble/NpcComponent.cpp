#include "pch.h"
#include "NpcComponent.h"
#include "LevelComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/RenderViewComponent.h"
#include "../Engine/ColliderModelComponent.h"
#include "../Engine/ObsSubject.h"

using namespace ieg;

const float NpcComponent::mMoveHor2PixelsTime{ 0.04f };
const float NpcComponent::mMoveVer2PixelsTime{ 0.02f };
const int NpcComponent::mMaxJumpHeight{ 42 };

NpcComponent::NpcComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: CharacterComponent(pGameObject, pEngine)
	, mpGOLevel{ nullptr }
	, mNpcType{ NpcType::ZenChan }
	, mCurState{ NpcState::Standing }
	, mNewState{ NpcState::Standing }
	, mCurIsFiring{ false }
	, mNewIsFiring{ false }
	, mIsHorMoving{ 0 }
	, mIsVerMoving{ 0 }
	, mMoveHorDelay{ mMoveHor2PixelsTime }
	, mMoveVerDelay{ mMoveVer2PixelsTime }
	, mJumpHeight{ 0 }
	, mpObsSubject{ new ObsSubject{} }
{
}

NpcComponent::~NpcComponent()
{
	delete mpObsSubject;
}

void NpcComponent::Update(const float deltaTime)
{
	switch (mNewState)
	{
	case NpcState::Falling:
		if (mMoveVerDelay <= 0)
		{
			TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
			if (pTransform->GetNewPos().GetY() > 200)
				pTransform->Move(0, -220);
			else
				pTransform->Move(0, 2);
			mMoveVerDelay += mMoveVer2PixelsTime;
		}
		mIsVerMoving = 2;
		break;
	case NpcState::Jumping:
		if (mJumpHeight >= mMaxJumpHeight)
		{
			mJumpHeight = 0;
			mNewState = NpcState::Falling;
		}
		else
		{
			if (mMoveVerDelay <= 0)
			{
				mpGameObject->GetModelComponent<TransformModelComponent>()->Move(0, -2);
				mJumpHeight += 2;
				mMoveVerDelay += mMoveVer2PixelsTime;
			}
			mIsVerMoving = 2;
		}
		break;
	case NpcState::Standing:
		mpGameObject->GetModelComponent<TransformModelComponent>()->Move(0, 2);
		break;
	}

	if (mIsHorMoving > 0)
	{
		--mIsHorMoving;
		mMoveHorDelay -= deltaTime;
	}
	if (mIsVerMoving > 0)
	{
		--mIsVerMoving;
		mMoveVerDelay -= deltaTime;
	}
}

void NpcComponent::Collision()
{
	unsigned short collision{ mpGOLevel->GetModelComponent<LevelComponent>()->CheckAvatarCollision(
	mpGameObject->GetModelComponent<TransformModelComponent>(),
	mpGameObject->GetModelComponent<ColliderModelComponent>()) };
	if (mNewState == NpcState::Standing)
		if ((collision & 1) != 0)
		{
			mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
			collision = mpGOLevel->GetModelComponent<LevelComponent>()->CheckAvatarCollision(
				mpGameObject->GetModelComponent<TransformModelComponent>(),
				mpGameObject->GetModelComponent<ColliderModelComponent>());
		}
		else
			mNewState = NpcState::Falling;
	if ((collision & 12) != 0)
		mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosX();
	if ((collision & 2) != 0 && mNewState == NpcState::Standing)
		mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
	if ((collision & 1) != 0 && mNewState == NpcState::Falling)
	{
		mpGameObject->GetModelComponent<TransformModelComponent>()->ResetNewPosY();
		mNewState = NpcState::Standing;
	}
}

void NpcComponent::Switch()
{
	mCurState = mNewState;
	mCurIsFiring = mNewIsFiring;
}

ObsSubject* NpcComponent::GetObsSubject()
{
	return mpObsSubject;
}

void NpcComponent::SetFiring(bool isFiring)
{
	mNewIsFiring = isFiring;
}

void NpcComponent::SetLevel(GameObject* pLevel)
{
	mpGOLevel = pLevel;
}

void NpcComponent::SetNpcType(NpcType npcType)
{
	mNpcType = npcType;
	mpGameObject->GetViewComponent<RenderViewComponent>()->SetType(int(mNpcType) * 16);
}

NpcType NpcComponent::GetNpcType()
{
	return mNpcType;
}

void NpcComponent::Fire()
{
}

void NpcComponent::Jump()
{
	if (mCurState == NpcState::Standing)
	{
		mJumpHeight = 0;
		mNewState = NpcState::Jumping;
	}
}

void NpcComponent::Left()
{
	if (mNewState == NpcState::Standing)
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

void NpcComponent::Right()
{
	if (mNewState == NpcState::Standing)
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
