#include "pch.h"
#include "BubblePoppingState.h"
#include "BubbleComponent.h"
#include "BubbleFloatingState.h"

using namespace ieg;

const float BubblePoppingState::mPoppingTime{ 0.2f };

BubblePoppingState::BubblePoppingState(ModelComponent* pModelComponent)
	: BubbleKineticState(pModelComponent)
	, mPoppingTimer{ mPoppingTime }
{
}

void BubblePoppingState::Update(const float deltaTime)
{
	mPoppingTimer -= deltaTime;
	if (mPoppingTimer <= 0.f)
	{
		mPoppingTimer = mPoppingTime;
		PopDone();
	}
}

void BubblePoppingState::PopDone()
{
	mpModelComponent->GetGameObject()->SetIsActive(false);
}
