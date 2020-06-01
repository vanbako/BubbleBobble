#include "pch.h"
#include "BubblePoppingState.h"
#include "BubbleComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/ModelComponent.h"
#include "../Engine/TransformModelComponent.h"
#include "BubbleFloatingState.h"

using namespace ieg;

const float BubblePoppingState::mPoppingTime{ 1.f };

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
		Pop();
	}
}

void BubblePoppingState::PopDone()
{
}
