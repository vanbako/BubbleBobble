#include "pch.h"
#include "NpcComponent.h"
#include "LevelComponent.h"
#include "StandingState.h"
#include "JumpingState.h"
#include "FallingState.h"
#include "FloatingState.h"
#include "ReadyState.h"
#include "FiringState.h"
#include "ReloadingState.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/RenderViewComponent.h"
#include "../Engine/ColliderModelComponent.h"

using namespace ieg;

NpcComponent::NpcComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: CharacterComponent(pGameObject, pEngine)
	, mNpcType{ NpcType::ZenChan }
{
}

void NpcComponent::Update(const float deltaTime)
{
	CharacterComponent::Update(deltaTime);
	if (mIsHorMoving > 0)
	{
		--mIsHorMoving;
		mMoveHorDelay -= deltaTime;
	}
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

void NpcComponent::Jump()
{
	// TODO: override in state
	if (mpCurKineticState == mpStandingState)
		CharacterComponent::Jump();
}

void NpcComponent::Left()
{
	// TODO: override in state
	if (mpCurKineticState == mpStandingState)
		CharacterComponent::Left();
}

void NpcComponent::Right()
{
	// TODO: override in state
	if (mpCurKineticState == mpStandingState)
		CharacterComponent::Right();
}

void NpcComponent::Pop()
{
	// TODO: override in state
	// TODO: Spawn Candy
	if (mpCurKineticState == mpFloatingState)
		mpGameObject->SetIsActive(false);
}

bool NpcComponent::Capture()
{
	SetFloatingState();
	mpGameObject->GetViewComponent<RenderViewComponent>()->SetType(int(NpcType::Count) * 16 + int(mNpcType) * 8);
	return true;
}
