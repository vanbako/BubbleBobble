#include "pch.h"
#include "LivingState.h"
#include "AvatarComponent.h"

using namespace ieg;

void LivingState::Update(const float deltaTime)
{
	(deltaTime);
}

void LivingState::Die()
{
	AvatarComponent* pAvatarComponent{ ((AvatarComponent*)mpModelComponent) };
	pAvatarComponent->GetObsSubject()->Notify(
		typeid(pAvatarComponent).hash_code(),
		int(AvatarEvent::Die),
		int(pAvatarComponent->GetAvatarType())
	);
	pAvatarComponent->SetDyingState();
}
