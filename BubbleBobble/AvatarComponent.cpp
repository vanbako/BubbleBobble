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
#include "../Engine/Minigin.h"
#include "../Engine/Scene.h"
#include "../Engine/InputManager.h"
#include "../Engine/GameObject.h"
#include "../Engine/TransformModelComponent.h"
#include "../Engine/ColliderModelComponent.h"
#include "../Engine/ServiceLocator.h"
#include "../Engine/Audio.h"

using namespace ieg;

AvatarComponent::AvatarComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: CharacterComponent(pGameObject, pEngine)
	, mpLivingState{ new LivingState{ this } }
	, mpDyingState{ new DyingState{ this } }
	, mpInvincibleState{ new InvincibleState{ this } }
	, mpCurHealthState{ nullptr }
	, mpNewHealthState{ nullptr }
{
	mpCurHealthState = mpLivingState;
	mpNewHealthState = mpLivingState;
	mJumpSoundId = pEngine->GetServiceLocator()->GetAudio()->AddSound("../Data/Audio/jump.wav", false);
}

AvatarComponent::~AvatarComponent()
{
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
	// NpcCollision
	TransformModelComponent* pTransform{ mpGameObject->GetModelComponent<TransformModelComponent>() };
	ColliderModelComponent* pCollider{ mpGameObject->GetModelComponent<ColliderModelComponent>() };
	if (mpCurHealthState == mpLivingState && mpGOLevel->GetModelComponent<LevelComponent>()->CheckNpcCollision(pTransform, pCollider))
		SetDyingState();
}

void AvatarComponent::Switch()
{
	CharacterComponent::Switch();
	mpCurHealthState = mpNewHealthState;
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
}

void AvatarComponent::FireBubble()
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

void AvatarComponent::Spawn()
{
	mpGameObject->GetModelComponent<TransformModelComponent>()->SetPos(AvatarManager::GetAvatarInitialPos(0));
	mpGameObject->GetModelComponent<TransformModelComponent>()->Switch();
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
