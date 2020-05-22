#include "pch.h"
#include "FallingState.h"
#include "AvatarComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/ModelComponent.h"
#include "../Engine/TransformModelComponent.h"

using namespace ieg;

ieg::FallingState::FallingState(ModelComponent* pModelComponent)
	: AvatarState(pModelComponent)
	, mIsVerMoving{ 0 }
	, mMoveVerDelay{ AvatarComponent::GetMoveVer2PixelsTime() }
{
}

void FallingState::Update(const float deltaTime)
{
	if (mMoveVerDelay <= 0.f)
	{
		TransformModelComponent* pTransform{ mpModelComponent->GetGameObject()->GetModelComponent<TransformModelComponent>() };
		if (pTransform->GetNewPos().GetY() > 200)
			pTransform->Move(0, -220);
		else
			pTransform->Move(0, 2);
		mMoveVerDelay += AvatarComponent::GetMoveVer2PixelsTime();
	}
	mIsVerMoving = 1;
	mMoveVerDelay -= deltaTime;
}
