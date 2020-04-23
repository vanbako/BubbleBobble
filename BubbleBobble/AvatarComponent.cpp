#include "pch.h"
#include "AvatarComponent.h"
#include "AvatarState.h"
#include "StandingState.h"

using namespace ieg;

AvatarComponent::AvatarComponent(Minigin* pEngine)
	: Component(pEngine)
	, mpAvatar{ nullptr }
	, mpState{ nullptr }
{
}

AvatarComponent::~AvatarComponent()
{
	delete mpState;
}

void AvatarComponent::Initialize(Avatar* pAvatar)
{
	mpAvatar = pAvatar;
	mpState = new StandingState{ mpAvatar };
}

void AvatarComponent::Update(const float deltaTime)
{
	if (mpState != nullptr)
		mpState->Update(deltaTime);
}

void AvatarComponent::Left()
{
	if (mpState != nullptr)
		ReplaceState(mpState->Left());
}

void AvatarComponent::Right()
{
	if (mpState != nullptr)
		ReplaceState(mpState->Right());
}

void AvatarComponent::Fire()
{
	if (mpState != nullptr)
		ReplaceState(mpState->Fire());
}

void AvatarComponent::Jump()
{
	if (mpState != nullptr)
		ReplaceState(mpState->Jump());
}

void AvatarComponent::ReplaceState(AvatarState* pState)
{
	if (pState != nullptr)
	{
		delete mpState;
		mpState = pState;
	}
}
