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
#include "ObjectsManager.h"
#include "BubbleManager.h"
#include "CandyComponent.h"

using namespace ieg;

AvatarComponent::AvatarComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: CharacterComponent(pGameObject, pEngine)
	, mAvatarType{ AvatarType::Bub }
	, mpLivingState{ new LivingState{ this } }
	, mpDyingState{ new DyingState{ this } }
	, mpInvincibleState{ new InvincibleState{ this } }
	, mpCurHealthState{ nullptr }
	, mpNewHealthState{ nullptr }
	, mpObjectsManager{ nullptr }
	, mpObsSubject{ new ObsSubject{} }
	, mJumpSoundId{ 0 }
	, mCatchSoundId{ 0 }
{
	std::va_list args{};
	va_start(args, pEngine);
	std::va_list vaList{ va_arg(args, std::va_list) };
	mpObjectsManager = va_arg(vaList, ObjectsManager*);
	va_end(args);
	mpCurHealthState = mpLivingState;
	mpNewHealthState = mpLivingState;
	mJumpSoundId = pEngine->GetServiceLocator()->GetAudio()->AddSound("../Data/Audio/jump.wav", false);
	mCatchSoundId = pEngine->GetServiceLocator()->GetAudio()->AddSound("../Data/Audio/catch.wav", false);
}

AvatarComponent::~AvatarComponent()
{
	delete mpObsSubject;
	delete mpInvincibleState;
	delete mpDyingState;
	delete mpLivingState;

	mpGameObject->GetScene()->GetInputManager()->DeleteInputActions(this);
}

void AvatarComponent::Update(const float deltaTime)
{
	if (mpCurHealthState != mpDyingState)
		CharacterComponent::Update(deltaTime);
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
	CharacterComponent::Collision();
	// ObjectCollision
	TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
	ColliderModelComponent* pCollider{ mpGameObject->GetModelComponent<ColliderModelComponent>() };
	if (mpCurHealthState != mpDyingState)
	{
		LevelComponent* pLevel{ mpGOLevel->GetModelComponent<LevelComponent>() };
		// NpcCollision
		GameObject* pGONpc{ pLevel->CheckNpcCollision(pTransform, pCollider) };
		if (pGONpc != nullptr)
		{
			NpcComponent* pNpcComponent{ pGONpc->GetModelComponent<NpcComponent>() };
			if (pNpcComponent->IsFloatingState())
				pNpcComponent->Pop();
			else
				mpCurHealthState->Die();
		}
		// CandyCollision
		GameObject* pGOCandy{ pLevel->CheckCandyCollision(pTransform, pCollider) };
		if (pGOCandy != nullptr)
		{
			mpEngine->GetServiceLocator()->GetAudio()->PlaySound(mCatchSoundId);
			CandyComponent* pCandyComponent{ pGOCandy->GetModelComponent<CandyComponent>() };
			pCandyComponent->Seize();
			mpObsSubject->Notify(
				typeid(this).hash_code(),
				int(AvatarEvent::Score),
				(int(mAvatarType) << 16) | 100);
		}
	}
}

void AvatarComponent::Switch()
{
	CharacterComponent::Switch();
	mpCurHealthState = mpNewHealthState;
}

void AvatarComponent::SetAvatarType(AvatarType avatarType)
{
	mAvatarType = avatarType;
}

AvatarType AvatarComponent::GetAvatarType()
{
	return mAvatarType;
}

ObsSubject* AvatarComponent::GetObsSubject()
{
	return mpObsSubject;
}

void AvatarComponent::SetJumpingState()
{
	CharacterComponent::SetJumpingState();
	mpEngine->GetServiceLocator()->GetAudio()->PlaySound(mJumpSoundId);
}

void AvatarComponent::SetFiringState()
{
	CharacterComponent::SetFiringState();
	FireBubble();
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
	SetRenderInvincible(true);
}

void AvatarComponent::SetRenderInvincible(bool setOn)
{
	mpGameObject->GetViewComponent<RenderViewComponent>()->SetIsOnOff(setOn);
}

void AvatarComponent::FireBubble()
{
	BubbleManager* pBubbleManager{ mpObjectsManager->GetBubbleManager() };
	TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
	ColliderModelComponent* pCollider{ pBubbleManager->GetCollider() };
	Vec2<int> pos1{ pTransform->GetPos() };
	Vec2<int> pos2{ pos1 };
	Vec2<int> pos3{ pos1 };
	if (pTransform->GetIsLookingLeft())
	{
		pos2.Move(-8, 0);
		pos3.Move(-16, 0);
	}
	else
	{
		pos2.Move(8, 0);
		pos3.Move(16, 0);
	}
	LevelComponent* pLevelComponent{ mpGOLevel->GetModelComponent<LevelComponent>() };
	if (pLevelComponent != nullptr)
	{
		if (pLevelComponent->CheckRectanglePosCollision(pos3, pCollider) == 0)
			pBubbleManager->FireBubble(mAvatarType, pos3, pTransform->GetIsLookingLeft());
		else if (pLevelComponent->CheckRectanglePosCollision(pos2, pCollider) == 0)
			pBubbleManager->FireBubble(mAvatarType, pos2, pTransform->GetIsLookingLeft());
		else if (pLevelComponent->CheckRectanglePosCollision(pos1, pCollider) == 0)
			pBubbleManager->FireBubble(mAvatarType, pos1, pTransform->GetIsLookingLeft());
	}
}

void AvatarComponent::Spawn()
{
	mpGOLevel->GetModelComponent<LevelComponent>()->SpawnAvatar(mAvatarType);
}

void AvatarComponent::Fire()
{
	if (mpCurHealthState != mpDyingState)
		CharacterComponent::Fire();
}

void AvatarComponent::Jump()
{
	if (mpCurHealthState != mpDyingState)
		CharacterComponent::Jump();
}

void AvatarComponent::Left()
{
	if (mpCurHealthState != mpDyingState)
		CharacterComponent::Left();
}

void AvatarComponent::Right()
{
	if (mpCurHealthState != mpDyingState)
		CharacterComponent::Right();
}
