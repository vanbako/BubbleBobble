#include "pch.h"
#include "FloatingState.h"
#include "CharacterComponent.h"
#include "NpcComponent.h"

using namespace ieg;

const float FloatingState::mFloatingTime{ 6.f };
const float FloatingState::mMoveHor2PixelsTime{ 0.12f };
const float FloatingState::mMoveVer2PixelsTime{ 0.12f };

FloatingState::FloatingState(ModelComponent* pModelComponent)
	: CharacterKineticState(pModelComponent)
	, mMoveHorDelay{ mMoveHor2PixelsTime }
	, mMoveVerDelay{ mMoveVer2PixelsTime }
	, mFloatingTimer{ mFloatingTime }
{
}

void FloatingState::Update(const float deltaTime)
{
	mFloatingTimer -= deltaTime;
	if (mFloatingTimer <= 0.f)
	{
		mFloatingTimer = mFloatingTime;
		((NpcComponent*)mpModelComponent)->Release();
		Fall();
	}
	TransformModelComponent* pTransform{ mpModelComponent->GetGameObject()->GetModelComponent<TransformModelComponent>() };
	Vec2<int> pos{ pTransform->GetPos() };
	if (mMoveVerDelay <= 0.f)
	{
		if (pos.GetY() > 24)
			pTransform->Move(0, -2);
		mMoveVerDelay += mMoveVer2PixelsTime;
	}
	if (mMoveHorDelay <= 0.f)
	{
		if (pos.GetX() < 128)
			pTransform->Move(-2, 0);
		else
			pTransform->Move(2, 0);
		mMoveHorDelay += mMoveHor2PixelsTime;
	}
	mMoveHorDelay -= deltaTime;
	mMoveVerDelay -= deltaTime;
}

void FloatingState::Fall()
{
	((CharacterComponent*)mpModelComponent)->SetFallingState();
}
