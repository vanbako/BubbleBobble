#include "pch.h"
#include "FallingState.h"
#include "CharacterComponent.h"

using namespace ieg;

FallingState::FallingState(ModelComponent* pModelComponent)
	: CharacterKineticState(pModelComponent)
	, mIsVerMoving{ 0 }
	, mMoveVerDelay{ CharacterComponent::GetMoveVer2PixelsTime() }
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
		mMoveVerDelay += CharacterComponent::GetMoveVer2PixelsTime();
	}
	mIsVerMoving = 1;
	mMoveVerDelay -= deltaTime;
}

void FallingState::Jump()
{
}

void FallingState::Land()
{
	((CharacterComponent*)mpModelComponent)->SetStandingState();
}

void FallingState::Capture()
{
	((CharacterComponent*)mpModelComponent)->SetFloatingState();
}
