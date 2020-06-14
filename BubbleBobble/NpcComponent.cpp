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
#include "NpcCtrlComponent.h"

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

void NpcComponent::Collision()
{
	if (mpCurKineticState != mpFloatingState)
	{
		CharacterComponent::Collision();
		if (HasWallCollision())
			mpGameObject->GetCtrlComponent<NpcCtrlComponent>()->SwitchX();
	}
	else
	{
		TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
		ColliderModelComponent* pCollider{ mpGameObject->GetModelComponent<ColliderModelComponent>() };
		unsigned short collision{ mpGOLevel->GetModelComponent<LevelComponent>()->CheckRectangleCollision(pTransform, pCollider) };
		if ((collision & 3) != 0)
			pTransform->ResetNewPosY();
		if ((collision & 12) != 0)
			pTransform->ResetNewPosX();
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
	if (mpCurKineticState == mpStandingState)
		CharacterComponent::Jump();
}

void NpcComponent::Left()
{
	if (mpCurKineticState == mpStandingState)
		CharacterComponent::Left();
}

void NpcComponent::Right()
{
	if (mpCurKineticState == mpStandingState)
		CharacterComponent::Right();
}

void NpcComponent::Release()
{
	if (mpCurKineticState == mpFloatingState)
		mpGameObject->GetViewComponent<RenderViewComponent>()->SetType(int(mNpcType) * 16);
}

void NpcComponent::Pop()
{
	if (mpCurKineticState == mpFloatingState)
	{
		mpGameObject->SetIsActive(false);
		LevelComponent* pLevel{ mpGOLevel->GetModelComponent<LevelComponent>() };
		pLevel->SpawnCandy(mNpcType, mpGameObject->GetModelComponent<TransformModelComponent>());
		pLevel->CheckLastNpc();
	}
}

bool NpcComponent::Capture()
{
	mpCurKineticState->Capture();
	TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
	pTransform->ResetNewPos();
	pTransform->SetIsLookingLeft(false);
	mpGameObject->GetViewComponent<RenderViewComponent>()->SetType(int(NpcType::Count) * 16 + int(mNpcType) * 8);
	return true;
}
